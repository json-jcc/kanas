#include "render_pass.h"
#include "framebuffer.h"
#include "pipeline.h"
#include "command_buffer.h"
#include "kanas/core/resource/image_view.h"
#include "kanas/core/resource/image.h"
#include "subpass.h"
#include "device.h"
#include "pipeline.h"

_KANAS_CORE_BEGIN

struct render_pass_static_helper
{
    static void get_raw(const std::vector<attachment>& attachments, std::vector<VkAttachmentDescription>& raw_attachment_descriptions)
    {
        raw_attachment_descriptions.reserve(attachments.size());
        for(const auto& attachment : attachments)
        {
            VkAttachmentDescription desc{};
            desc.flags = {};
            desc.format = attachment.format;
            desc.samples = attachment.samples.raw();
            desc.loadOp= attachment.load_op.raw();
            desc.storeOp = attachment.store_op.raw();
            desc.stencilLoadOp = attachment.stencil_load_op.raw();
            desc.stencilStoreOp = attachment.stencil_store_op.raw();
            desc.initialLayout = attachment.initial_layout.raw();
            desc.finalLayout = attachment.final_layout.raw();

            raw_attachment_descriptions.emplace_back(desc);
        }
    }

    static void get_raw(const subpass_list& list, std::vector<VkSubpassDescription>& rawSubpassDescriptions, std::vector<VkSubpassDependency>& rawSubpassDependencies)
    {
        {
            VkAttachmentReference attachmentRef;
            attachmentRef.attachment = 0;
            attachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

            std::vector<VkAttachmentReference> inputAttachments =
                    {
                            attachmentRef
                    };

            std::vector<VkAttachmentReference> colorAttachments =
                    {

                    };

            VkSubpassDescription _subpassDescription;
            _subpassDescription.flags = {};
            _subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
            _subpassDescription.inputAttachmentCount = static_cast<std::uint32_t>(inputAttachments.size());
            _subpassDescription.pInputAttachments = inputAttachments.data();
            _subpassDescription.colorAttachmentCount = static_cast<std::uint32_t>(colorAttachments.size());
            _subpassDescription.pColorAttachments = colorAttachments.data();
            _subpassDescription.pResolveAttachments;
            _subpassDescription.pDepthStencilAttachment;
            _subpassDescription.preserveAttachmentCount;
            _subpassDescription.pPreserveAttachments;
        }
    }


};

_KANAS_CORE_END

bool kanas::core::render_pass::allocate(const std::string& name,
                                        const std::vector<attachment>& attachments,
                                        const subpass_list& subpasses)
{
    // check

    std::vector<VkAttachmentDescription> _rawAttachmentDescriptions;
    render_pass_static_helper::get_raw(attachments, _rawAttachmentDescriptions);

    std::vector<VkSubpassDescription> _rawSubpassDescriptions;
    std::vector<VkSubpassDependency> _rawSubpassDependencies;

    render_pass_static_helper::get_raw(subpasses, _rawSubpassDescriptions, _rawSubpassDependencies);

    VkRenderPassCreateInfo renderPassCreateInfo{};
    renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassCreateInfo.flags = {};
    renderPassCreateInfo.attachmentCount = static_cast<std::uint32_t>(_rawAttachmentDescriptions.size());
    renderPassCreateInfo.pAttachments = _rawAttachmentDescriptions.data();
    renderPassCreateInfo.subpassCount = static_cast<std::uint32_t>(_rawSubpassDescriptions.size());
    renderPassCreateInfo.pSubpasses = _rawSubpassDescriptions.data();
    renderPassCreateInfo.dependencyCount = static_cast<std::uint32_t>(_rawSubpassDependencies.size());
    renderPassCreateInfo.pDependencies = _rawSubpassDependencies.data();

    if (vkCreateRenderPass(dev().handle(), &renderPassCreateInfo, nullptr, &_handle) == VK_SUCCESS)
    {
        return true;
    }

    return false;
}

kanas::core::render_pass::render_pass(device& owner) :
    device_object(owner), _subpass_list(nullptr)
{
}

kanas::core::render_pass::render_pass(render_pass& other) :
    device_object(other.dev()), _subpass_list(nullptr)
{
}

kanas::core::render_pass::~render_pass()
{
    if (is_valid())
    {
        vkDestroyRenderPass(dev().handle(), handle(), nullptr);
        reset_handle();
    }
}

void kanas::core::render_pass::cmd_execute(primary_command_buffer& pcb) const
{
    std::vector<std::shared_ptr<subpass>> _subpasses;
    _subpass_list.get_subpasses(_subpasses);

    VkRenderPassBeginInfo renderPassBeginInfo{};
    renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassBeginInfo.framebuffer = _current_render_target->handle();
    renderPassBeginInfo.renderPass = handle();
    renderPassBeginInfo.clearValueCount = static_cast<std::uint32_t>(_clear_values.size());
    renderPassBeginInfo.pClearValues = _clear_values.data();
    renderPassBeginInfo.renderArea = _render_area;

    pcb.reset();

    vkCmdBeginRenderPass(pcb.handle(), &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

    for (std::size_t _idx = 0; _idx < _subpasses.size(); ++_idx)
    {
        if (_idx != 0)
        {
            vkCmdNextSubpass(pcb.handle(), VK_SUBPASS_CONTENTS_INLINE);
        }
        _subpasses[_idx]->cmd_execute(pcb);
    }

    vkCmdEndRenderPass(pcb.handle());
}

void kanas::core::render_pass::cmd_execute_fast(kanas::core::primary_command_buffer &pcb) const
{
    std::vector<std::shared_ptr<subpass>> _subpasses;
    _subpass_list.get_subpasses(_subpasses);

    VkRenderPassBeginInfo _begin_info{};
    _begin_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    _begin_info.framebuffer = _current_render_target->handle();
    _begin_info.renderPass = handle();
    _begin_info.clearValueCount = static_cast<std::uint32_t>(_clear_values.size());
    _begin_info.pClearValues = _clear_values.data();
    _begin_info.renderArea = _render_area;

    std::vector<std::shared_ptr<secondary_command_buffer>> _scbs;

    const std::size_t _num_of_subpasses = _subpasses.size();

    if (_scbs.size() != _num_of_subpasses)
    {
        std::cerr << "can not find enough scbs" << std::endl;
        return;
    }

    // multithreading or not
    {
        std::vector<std::future<bool>> _futures;

        for (std::size_t _idx = 0; _idx < _num_of_subpasses; ++_idx)
        {
            check(_scbs[_idx]);

            auto& _scb = _scbs[_idx];
            auto& _subpass = _subpasses[_idx];

            _futures.push_back(std::async(std::launch::async, [_scb, _subpass](){
                return _scb->record(*_subpass);
            }));
        }

        // check result
        for(auto& _future : _futures)
        {
            if(!_future.get())
            {
                return;
            }
        }
    }

    std::vector<VkCommandBuffer> _raw_scbs;
    //get_raw(_scbs, _raw_scbs);

    pcb.reset();

    vkCmdBeginRenderPass(pcb.handle(), &_begin_info, VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS);

    for (std::size_t _idx = 0; _idx < _raw_scbs.size(); ++_idx)
    {
        if (_idx != 0)
        {
            vkCmdNextSubpass(pcb.handle(), VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS);
        }
        vkCmdExecuteCommands(pcb.handle(), 1, _raw_scbs.data());
    }

    vkCmdEndRenderPass(pcb.handle());
}

void kanas::core::render_pass::set_render_area(const VkRect2D& val)
{
    _render_area = val;
}

void kanas::core::render_pass::set_clear_values(const std::vector<VkClearValue>& vals)
{
    _clear_values = vals;
}

