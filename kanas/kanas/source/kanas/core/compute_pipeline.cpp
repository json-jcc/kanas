#include "compute_pipeline.h"
#include "command_buffer.h"
#include "pipeline_layout.h"
#include "pipeline_cache.h"
#include "shader_module.h"
#include "shader.h"
#include "kanas/core/resource/buffer.h"
#include "device.h"

bool kanas::core::compute_pipeline::allocate(std::shared_ptr<compute_shader> InComputeShader, std::shared_ptr<pipeline_layout> Layout, std::shared_ptr<pipeline_cache> Cache)
{
    if (!InComputeShader)
    {
        return false;
    }
    
    /*if (const auto ShaderModule = InComputeShader->GetShaderModule())
    {
        VkPipelineShaderStageCreateInfo ShaderStageCreateInfo{};
        ShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        ShaderStageCreateInfo.flags = {};
        ShaderStageCreateInfo.module = ShaderModule->get_handle();
        ShaderStageCreateInfo.pName = InComputeShader->GetName().c_str();
        ShaderStageCreateInfo.pSpecializationInfo = nullptr;
        ShaderStageCreateInfo.stage = VK_SHADER_STAGE_COMPUTE_BIT;

        VkComputePipelineCreateInfo ComputePipelineCreateInfo{};
        ComputePipelineCreateInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
        ComputePipelineCreateInfo.pNext = nullptr;
        ComputePipelineCreateInfo.flags = {};
        ComputePipelineCreateInfo.stage = ShaderStageCreateInfo;
        ComputePipelineCreateInfo.layout = Layout->handle();
        ComputePipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
        ComputePipelineCreateInfo.basePipelineIndex = -1;

        const VkResult ComputePipelineCreationResult = vkCreateComputePipelines(dev().handle(), Cache->handle(), 1, &ComputePipelineCreateInfo, nullptr, &_handle);

        if (ComputePipelineCreationResult == VK_SUCCESS)
        {
            return true;
        }
    }*/

    return false;
}

kanas::core::compute_pipeline::compute_pipeline(device& owner) :
    pipeline(owner, VK_PIPELINE_BIND_POINT_COMPUTE)
{
}

kanas::core::compute_pipeline::~compute_pipeline()
{
}

/*
void kanas::core::compute_pipeline::CmdDispatch(command_buffer& InRecorder, const GroupCount& InGroupCount)
{
    vkCmdDispatch(InRecorder.handle(), InGroupCount[0], InGroupCount[1], InGroupCount[2]);
}

void kanas::core::compute_pipeline::CmdDispatchBase(command_buffer& InRecorder, const BaseGroup& InBaseGroup, const GroupCount& InGroupCount)
{
    vkCmdDispatchBase(InRecorder.handle(), InBaseGroup[0], InBaseGroup[1], InBaseGroup[2], InGroupCount[0], InGroupCount[1], InGroupCount[2]);
}

void kanas::core::compute_pipeline::CmdDispatchIndirect(command_buffer& InRecorder, buffer& InBuffer, std::uint64_t InOffset)
{
    vkCmdDispatchIndirect(InRecorder.handle(), InBuffer.handle(), InOffset);
}
*/
