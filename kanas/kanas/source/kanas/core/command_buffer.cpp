#include "command_buffer.h"
#include "command_pool.h"
#include "render_pass.h"
#include "subpass.h"
#include "framebuffer.h"
#include "device.h"

bool kanas::core::command_buffer::allocate(command_buffer_level level)
{
    VkCommandBufferAllocateInfo CommandBufferAllocateInfo;
    CommandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    CommandBufferAllocateInfo.commandBufferCount = 1;
    CommandBufferAllocateInfo.commandPool = _pool.handle();
    CommandBufferAllocateInfo.level = static_cast<VkCommandBufferLevel>(level);

    VkResult Result = vkAllocateCommandBuffers(dev().handle(), &CommandBufferAllocateInfo, &_handle);

    if (Result == VkResult::VK_SUCCESS)
    {
        return true;
    }

    return false;
}

kanas::core::command_buffer::command_buffer(device& owner,command_pool& pool) :
    device_object(owner), 
    _pool(pool)
{
}

kanas::core::command_buffer::~command_buffer()
{
    if (is_valid())
    {
        vkFreeCommandBuffers(dev().handle(), _pool.handle(), 1, &_handle);

        reset_handle();
    }
}

void kanas::core::command_buffer::cmd_barrier()
{
    VkMemoryBarrier MemoryBarriers[1] = {};
    VkBufferMemoryBarrier BufferMemoryBarriers[1] = {};
    VkImageMemoryBarrier ImageMemoryBarriers[1] = {};

    VkPipelineStageFlags InSrcStageMask = VkPipelineStageFlagBits::VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT;
    VkPipelineStageFlags InDstStageMask = VkPipelineStageFlagBits::VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
    VkDependencyFlags DependencyFlags = VkDependencyFlagBits::VK_DEPENDENCY_BY_REGION_BIT;

    vkCmdPipelineBarrier(handle(), InSrcStageMask, InDstStageMask, DependencyFlags, 1, MemoryBarriers, 1, BufferMemoryBarriers, 1, ImageMemoryBarriers);
}

bool kanas::core::command_buffer::reset(command_buffer_reset_flags flags)
{
    return vkResetCommandBuffer(handle(), flags.raw()) == VK_SUCCESS;
}

kanas::core::primary_command_buffer::primary_command_buffer(device& owner, command_pool& pool) :
        command_buffer(owner, pool)
{
}

kanas::core::primary_command_buffer::~primary_command_buffer()
{
}

bool kanas::core::primary_command_buffer::record(const kanas::core::render_pass &pass)
{
    VkCommandBufferBeginInfo CommandBufferBeginInfo{};
    CommandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    CommandBufferBeginInfo.pNext = nullptr;
    CommandBufferBeginInfo.flags = command_buffer_usage_flags().set_one_time_submit().raw();
    CommandBufferBeginInfo.pInheritanceInfo = nullptr;

    if (vkBeginCommandBuffer(handle(), &CommandBufferBeginInfo) != VK_SUCCESS)
    {
        return false;
    }

    pass.cmd_execute(*this);

    if (vkEndCommandBuffer(handle()) != VK_SUCCESS)
    {
        return false;
    }

    return true;
}

bool kanas::core::primary_command_buffer::record(const kanas::core::primary_command_buffer::transition &trans)
{
    VkCommandBufferBeginInfo _begin_info{};
    _begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    _begin_info.pNext = nullptr;
    _begin_info.flags = command_buffer_usage_flags().set_one_time_submit().raw();
    _begin_info.pInheritanceInfo = nullptr;

    if (vkBeginCommandBuffer(handle(), &_begin_info) != VK_SUCCESS)
    {
        return false;
    }

    trans(*this);

    if (vkEndCommandBuffer(handle()) != VK_SUCCESS)
    {
        return false;
    }

    return true;
}

kanas::core::secondary_command_buffer::secondary_command_buffer(device& owner, command_pool& pool) :
        command_buffer(owner, pool)
{
}

kanas::core::secondary_command_buffer::~secondary_command_buffer()
{
}

bool kanas::core::secondary_command_buffer::record(subpass& pass)
{
    VkCommandBufferInheritanceInfo CommandBufferInheritanceInfo;
    CommandBufferInheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
    CommandBufferInheritanceInfo.pNext = nullptr;
    /*CommandBufferInheritanceInfo.renderPass = pass.render()->get_handle();
    CommandBufferInheritanceInfo.subpass = pass.get_index();
    CommandBufferInheritanceInfo.framebuffer = pass.get_render_pass()->render_target()->get_handle();*/
    CommandBufferInheritanceInfo.occlusionQueryEnable = false;
    CommandBufferInheritanceInfo.queryFlags = query_control_flags().set_precise().raw();
    CommandBufferInheritanceInfo.pipelineStatistics = query_pipeline_statistic_flags().set_geometry_shader_invocations().raw();

    VkCommandBufferBeginInfo CommandBufferBeginInfo;
    CommandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    CommandBufferBeginInfo.pNext = nullptr;
    // secondary cmd buffer must activate render_pass_continue
    CommandBufferBeginInfo.flags = command_buffer_usage_flags().set_render_pass_continue().raw();
    CommandBufferBeginInfo.pInheritanceInfo = &CommandBufferInheritanceInfo;

    if(vkBeginCommandBuffer(handle(), &CommandBufferBeginInfo) != VK_SUCCESS)
    {
        return false;
    }

    pass.cmd_execute(*this);

    if (vkEndCommandBuffer(handle()) != VK_SUCCESS)
    {
        return false;
    }

    return  true;
}