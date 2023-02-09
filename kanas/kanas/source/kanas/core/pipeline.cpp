#include "pipeline.h"
#include "device.h"
#include "pipeline_cache.h"
#include "command_buffer.h"
#include "descriptor_set.h"
#include "descriptor_set_layout.h"
#include "pipeline_layout.h"

kanas::core::pipeline::pipeline(device& owner, VkPipelineBindPoint InBindPoint) :
    device_object(owner),
    _bind_point(InBindPoint)
{
}

kanas::core::pipeline::~pipeline()
{
    if (is_valid())
    {
        vkDestroyPipeline(dev().handle(), handle(), nullptr);
        
        reset_handle();
    }
}

void kanas::core::pipeline::cmd_bind(command_buffer& cb)
{
    vkCmdBindPipeline(cb.handle(), _bind_point, handle());

    cmd_bind_descriptor_sets(cb);
    cmd_push_constants(cb);
}

void kanas::core::pipeline::cmd_push_constants(kanas::core::command_buffer &cb)
{
    if (_constants)
    {
        vkCmdPushConstants(cb.handle(), _layout->handle(), 0, 0, static_cast<std::uint32_t>(_constants->GetSize()), _constants->GetData());
    }
}

void kanas::core::pipeline::cmd_bind_descriptor_sets(kanas::core::command_buffer &cb)
{
    std::vector<VkDescriptorSet> DescriptorSetHandles;
    //get_raw(_layout->GetDescriptorSetLayouts(), DescriptorSetHandles);

    vkCmdBindDescriptorSets(cb.handle(), _bind_point, _layout->handle(),
        0, static_cast<std::uint32_t>(DescriptorSetHandles.size()), DescriptorSetHandles.data(), 
        0, nullptr
    );
}

std::shared_ptr<kanas::core::pipeline_layout> kanas::core::pipeline::layout() const
{
    return _layout;
}
