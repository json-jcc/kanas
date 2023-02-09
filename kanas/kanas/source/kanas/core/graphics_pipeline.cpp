#include "graphics_pipeline.h"
#include "device.h"
#include "command_buffer.h"
#include "kanas/core/resource/buffer.h"
#include "pipeline_cache.h"
#include "pipeline_layout.h"
#include "render_pass.h"
#include "shader_module.h"
#include "shader.h"

kanas::core::graphics_pipeline::graphics_pipeline(device& owner) :
    pipeline(owner, VK_PIPELINE_BIND_POINT_GRAPHICS)
{
}

kanas::core::graphics_pipeline::~graphics_pipeline()
{
}

bool kanas::core::graphics_pipeline::allocate(const kanas::core::graphics_pipeline_state_initializer &initializer,
                                              std::shared_ptr<pipeline_layout> layout,
                                              std::shared_ptr<pipeline_cache> cache) {

    std::vector<std::shared_ptr<shader>> Shaders;
    initializer.GetShaders(Shaders);

    std::vector<VkPipelineShaderStageCreateInfo> ShaderStageCreateInfos{};

    for (const auto& Shader : Shaders)
    {
        VkSpecializationInfo SpecializationInfo{};
        SpecializationInfo.mapEntryCount;
        SpecializationInfo.pMapEntries;
        SpecializationInfo.dataSize;
        SpecializationInfo.pData;

        VkPipelineShaderStageCreateInfo ShaderStageCreateInfo{};
        ShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        ShaderStageCreateInfo.pNext = nullptr;
        ShaderStageCreateInfo.flags = {};
        ShaderStageCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        //ShaderStageCreateInfo.module = Shader->GetShaderModule()->get_handle();
        //ShaderStageCreateInfo.pName = Shader->GetName().c_str();
        ShaderStageCreateInfo.pSpecializationInfo = &SpecializationInfo;

        ShaderStageCreateInfos.emplace_back(ShaderStageCreateInfo);
    }
    
    std::vector<VkVertexInputAttributeDescription> AttributeDescriptions;
    std::vector<VkVertexInputBindingDescription> BindingDescriptions;

    VkPipelineVertexInputStateCreateInfo VertexInputStateCreateInfo{};
    VertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    VertexInputStateCreateInfo.pNext = nullptr;
    VertexInputStateCreateInfo.flags = {};
    VertexInputStateCreateInfo.pVertexAttributeDescriptions = AttributeDescriptions.data();
    VertexInputStateCreateInfo.pVertexBindingDescriptions = BindingDescriptions.data();
    VertexInputStateCreateInfo.vertexAttributeDescriptionCount = static_cast<std::uint32_t>(AttributeDescriptions.size());
    VertexInputStateCreateInfo.vertexBindingDescriptionCount = static_cast<std::uint32_t>(BindingDescriptions.size());

    VkPipelineInputAssemblyStateCreateInfo InputAssemblyStateCreateInfo{};
    InputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    InputAssemblyStateCreateInfo.pNext = nullptr;
    InputAssemblyStateCreateInfo.flags = {};
    InputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
    InputAssemblyStateCreateInfo.primitiveRestartEnable = false;

    VkPipelineTessellationStateCreateInfo TessellationStateCreateInfo;
    TessellationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
    TessellationStateCreateInfo.pNext = nullptr;
    TessellationStateCreateInfo.flags = {};
    TessellationStateCreateInfo.patchControlPoints = 0;

    std::vector<VkViewport> Viewports;
    std::vector<VkRect2D> Scissors;

    VkPipelineViewportStateCreateInfo ViewportStateCreateInfo;
    ViewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    ViewportStateCreateInfo.pNext = nullptr;
    ViewportStateCreateInfo.flags = {};
    ViewportStateCreateInfo.viewportCount = static_cast<std::uint32_t>(Viewports.size());
    ViewportStateCreateInfo.pViewports = Viewports.data();
    ViewportStateCreateInfo.scissorCount = static_cast<std::uint32_t>(Scissors.size());
    ViewportStateCreateInfo.pScissors = Scissors.data();


    VkPipelineRasterizationStateCreateInfo RasterizationStateCreateInfo{};
    RasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    RasterizationStateCreateInfo.pNext = nullptr;
    RasterizationStateCreateInfo.flags = {};
    RasterizationStateCreateInfo.depthClampEnable = false;
    RasterizationStateCreateInfo.rasterizerDiscardEnable = false;
    RasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
    RasterizationStateCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT | VK_CULL_MODE_FRONT_BIT;
    RasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
    RasterizationStateCreateInfo.depthBiasEnable = false;
    RasterizationStateCreateInfo.depthBiasConstantFactor = 0.f;
    RasterizationStateCreateInfo.depthBiasClamp = 0.f;
    RasterizationStateCreateInfo.depthBiasSlopeFactor = 0.f;
    RasterizationStateCreateInfo.lineWidth = 0.f;

    VkSampleMask SampleMask;

    VkPipelineMultisampleStateCreateInfo MultisampleStateCreateInfo{};
    MultisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    MultisampleStateCreateInfo.pNext = nullptr;
    MultisampleStateCreateInfo.flags = {};
    MultisampleStateCreateInfo.rasterizationSamples = VkSampleCountFlagBits::VK_SAMPLE_COUNT_2_BIT;
    MultisampleStateCreateInfo.sampleShadingEnable = false;
    MultisampleStateCreateInfo.minSampleShading = 0.f;
    MultisampleStateCreateInfo.pSampleMask = &SampleMask;
    MultisampleStateCreateInfo.alphaToCoverageEnable = false;
    MultisampleStateCreateInfo.alphaToOneEnable = false;

    VkStencilOpState Front = {};
    VkStencilOpState Back = {};

    VkPipelineDepthStencilStateCreateInfo DepthStencilStateCreateInfo{};
    DepthStencilStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    DepthStencilStateCreateInfo.pNext = nullptr;
    DepthStencilStateCreateInfo.flags = {};
    DepthStencilStateCreateInfo.depthTestEnable = false;
    DepthStencilStateCreateInfo.depthWriteEnable = false;
    DepthStencilStateCreateInfo.depthCompareOp = VK_COMPARE_OP_ALWAYS;
    DepthStencilStateCreateInfo.depthBoundsTestEnable = false;
    DepthStencilStateCreateInfo.stencilTestEnable = false;
    DepthStencilStateCreateInfo.front = Front;
    DepthStencilStateCreateInfo.back = Back;
    DepthStencilStateCreateInfo.minDepthBounds = 0.f;
    DepthStencilStateCreateInfo.maxDepthBounds = 1.f;

    const std::vector<VkPipelineColorBlendAttachmentState> ColorBlendAttachments;
    //std::array<float, 4> BlendConstants = {};

    VkPipelineColorBlendStateCreateInfo ColorBlendStateCreateInfo{};
    ColorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    ColorBlendStateCreateInfo.pNext = nullptr;
    ColorBlendStateCreateInfo.flags = {};
    ColorBlendStateCreateInfo.logicOpEnable = false;
    ColorBlendStateCreateInfo.logicOp = VK_LOGIC_OP_AND;
    ColorBlendStateCreateInfo.attachmentCount = static_cast<std::uint32_t>(ColorBlendAttachments.size());
    ColorBlendStateCreateInfo.pAttachments = ColorBlendAttachments.data();
    //ColorBlendStateCreateInfo.blendConstants[4] = BlendConstants.data();

    std::vector<VkDynamicState> DynamicStates;

    VkPipelineDynamicStateCreateInfo DynamicStateCreateInfo{};
    DynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    DynamicStateCreateInfo.pNext = nullptr;
    DynamicStateCreateInfo.flags = {};
    DynamicStateCreateInfo.dynamicStateCount = static_cast<std::uint32_t>(DynamicStates.size());
    DynamicStateCreateInfo.pDynamicStates = DynamicStates.data();

    VkGraphicsPipelineCreateInfo PipelineCreateInfo{};
    PipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    PipelineCreateInfo.pNext = nullptr;
    PipelineCreateInfo.flags = {};
    PipelineCreateInfo.stageCount = static_cast<std::uint32_t>(ShaderStageCreateInfos.size());
    PipelineCreateInfo.pStages = ShaderStageCreateInfos.data();
    PipelineCreateInfo.pVertexInputState = &VertexInputStateCreateInfo;
    PipelineCreateInfo.pInputAssemblyState = &InputAssemblyStateCreateInfo;
    PipelineCreateInfo.pTessellationState = &TessellationStateCreateInfo;
    PipelineCreateInfo.pViewportState = &ViewportStateCreateInfo;
    PipelineCreateInfo.pRasterizationState = &RasterizationStateCreateInfo;
    PipelineCreateInfo.pMultisampleState = &MultisampleStateCreateInfo;
    PipelineCreateInfo.pDepthStencilState = &DepthStencilStateCreateInfo;
    PipelineCreateInfo.pColorBlendState = &ColorBlendStateCreateInfo;
    PipelineCreateInfo.pDynamicState = &DynamicStateCreateInfo;
    PipelineCreateInfo.layout = layout->handle();
    PipelineCreateInfo.renderPass = initializer.render_pass->handle();
    PipelineCreateInfo.subpass = initializer.subpass_index;
    PipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
    PipelineCreateInfo.basePipelineIndex = -1;

    const VkResult GraphicsPipelineCreationResult = vkCreateGraphicsPipelines(dev().handle(), cache->handle(), 1, &PipelineCreateInfo, nullptr, &_handle);

    if (GraphicsPipelineCreationResult == VK_SUCCESS)
    {
        return true;
    }

    return false;
}
/*

void kanas::core::graphics_pipeline::CmdBindIndexBuffer(command_buffer& InRecorder, std::shared_ptr<FIndexBuffer> IndexBuffer)
{
    vkCmdBindIndexBuffer(InRecorder.get_handle(), IndexBuffer->get_handle(), 0, IndexBuffer->GetIndexType());
}

void kanas::core::graphics_pipeline::CmdBindVertexBuffers(command_buffer& InRecorder, std::uint32_t Binding, std::shared_ptr<FVertexBuffer> VertexBuffer, std::uint64_t Offset)
{
    std::uint32_t BindingIndex = 0; // GetMappedIndex
    const auto BufferHandle = VertexBuffer->get_handle();
    vkCmdBindVertexBuffers(InRecorder.get_handle(), BindingIndex, 1, &BufferHandle, &Offset);

}

void kanas::core::graphics_pipeline::CmdDraw(command_buffer& InRecorder, std::uint32_t InVertexCount, std::uint32_t InInstanceCount, std::uint32_t InFirstVertex, std::uint32_t InFirstInstance)
{
    vkCmdDraw(InRecorder.get_handle(), InVertexCount, InInstanceCount, InFirstVertex, InFirstInstance);
}

void kanas::core::graphics_pipeline::CmdDrawIndirect(command_buffer& InRecorder, buffer& InBuffer, std::uint64_t InOffset, std::uint32_t InDrawCount, std::uint32_t InStride)
{
    vkCmdDrawIndirect(InRecorder.get_handle(), InBuffer.get_handle(), InOffset, InDrawCount, InStride);
}

void kanas::core::graphics_pipeline::CmdDrawIndirectCount(command_buffer& InRecorder, buffer& InBuffer, std::uint32_t InOffset, buffer& InCountBuffer, std::uint64_t InCountOffset, std::uint32_t InMaxDrawCount, std::uint32_t InStride)
{
    vkCmdDrawIndirectCount(InRecorder.get_handle(), InBuffer.get_handle(), InOffset, InCountBuffer.get_handle(), InCountOffset, InMaxDrawCount, InStride);
}

void kanas::core::graphics_pipeline::CmdDrawIndexed(command_buffer& InRecorder, std::uint32_t InIndexCount, std::uint32_t InInstanceCount, std::uint32_t InFirstIndex, std::uint32_t InVertexOffset, std::uint32_t InFirstInstance)
{
    vkCmdDrawIndexed(InRecorder.get_handle(), InIndexCount, InInstanceCount, InFirstIndex, InVertexOffset, InFirstIndex);
}

void kanas::core::graphics_pipeline::CmdDrawIndexedIndirect(command_buffer& InRecorder, buffer& InBuffer, std::uint64_t InOffset, std::uint32_t InDrawCount, std::uint32_t InStride)
{
    vkCmdDrawIndexedIndirect(InRecorder.get_handle(), InBuffer.get_handle(), InOffset, InDrawCount, InStride);
}

void kanas::core::graphics_pipeline::CmdDrawIndexedIndirectCount(command_buffer& InRecorder, buffer& InBuffer, std::uint64_t InOffset, buffer& InCountBuffer, std::uint64_t InCountOffset, std::uint32_t InMaxDrawCount, std::uint32_t InStride)
{
    vkCmdDrawIndexedIndirectCount(InRecorder.get_handle(), InBuffer.get_handle(), InOffset, InCountBuffer.get_handle(), InCountOffset, InMaxDrawCount, InStride);
}
*/
