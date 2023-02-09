#ifndef _ENUMERATORS_H_
#define _ENUMERATORS_H_

#include "KanasCoreMacros.h"

_KANAS_CORE_BEGIN

template<typename VK_ENUM_T>
struct vulkan_enum
{

};

struct image_layout
{
    enum class t
    {
        undefined = VK_IMAGE_LAYOUT_UNDEFINED,
        general = VK_IMAGE_LAYOUT_GENERAL,
        color_attachment_optimal = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        depth_stencil_attachment_optimal = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
        depth_stencil_read_only_optimal = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
        shader_read_only_optimal = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        transfer_src_optimal = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
        transfer_dst_optimal = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        preinitialized = VK_IMAGE_LAYOUT_PREINITIALIZED,
        depth_read_only_stencil_attachment_optimal = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL,
        depth_attachment_stencil_read_only_optimal = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL,
        depth_attachment_optimal = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
        depth_read_only_optimal = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
        stencil_attachment_optimal = VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL,
        stencil_read_only_optimal = VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL,
        present_src = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
    };

    t v{ t::undefined };

    [[nodiscard]] VkImageLayout raw() const
    {
        return static_cast<VkImageLayout>(v);
    }

    image_layout() = default;

    image_layout(image_layout::t val) : v(val) {}

};

struct attachment_store_op
{
    enum class t
    {
        store = VK_ATTACHMENT_STORE_OP_STORE,
        dont_care = VK_ATTACHMENT_STORE_OP_DONT_CARE,
        none_qcom = VK_ATTACHMENT_STORE_OP_NONE_QCOM
    };

    t v{ t::dont_care };

    [[nodiscard]] VkAttachmentStoreOp raw() const
    {
        return static_cast<VkAttachmentStoreOp>(v);
    }

    attachment_store_op() = default;

    explicit attachment_store_op(attachment_store_op::t val) : v(val) {}
};

struct attachment_load_op
{
    enum class t
    {
        load = VK_ATTACHMENT_LOAD_OP_LOAD,
        clear = VK_ATTACHMENT_LOAD_OP_CLEAR,
        dont_care = VK_ATTACHMENT_LOAD_OP_DONT_CARE
    };

    t v{ t::dont_care };

    [[nodiscard]] VkAttachmentLoadOp raw() const
    {
        return static_cast<VkAttachmentLoadOp>(v);
    }

    attachment_load_op() = default;

    explicit attachment_load_op(attachment_load_op::t val) : v(val) {}

};

struct sample_count
{
    enum class t
    {
        count_1 = VK_SAMPLE_COUNT_1_BIT,
        count_2 = VK_SAMPLE_COUNT_2_BIT,
        count_4 = VK_SAMPLE_COUNT_4_BIT,
        count_8 = VK_SAMPLE_COUNT_8_BIT,
        count_16 = VK_SAMPLE_COUNT_16_BIT,
        count_32 = VK_SAMPLE_COUNT_32_BIT,
        count_64 = VK_SAMPLE_COUNT_64_BIT
    };

    t v{ t::count_1 };

    [[nodiscard]] constexpr VkSampleCountFlagBits raw() const
    {
        return static_cast<VkSampleCountFlagBits>(v);
    }

    sample_count() = default;

    explicit sample_count(sample_count::t val) : v(val) {}
};

enum class PipelineStageFlagBits
{
    TransformFeedbackEXT = VK_PIPELINE_STAGE_TRANSFORM_FEEDBACK_BIT_EXT,
    ConditionalRenderingEXT = VK_PIPELINE_STAGE_CONDITIONAL_RENDERING_BIT_EXT,
    AccelerationStructureBuildKHR = VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR,
    RayTracingShaderKHR = VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR,
    ShadingRateImage = VK_PIPELINE_STAGE_SHADING_RATE_IMAGE_BIT_NV,
    TaskShaderNV = VK_PIPELINE_STAGE_TASK_SHADER_BIT_NV,
    MeshShaderNV = VK_PIPELINE_STAGE_MESH_SHADER_BIT_NV,

    FragmentDensityProcessEXT = VK_PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT,
    CommandPrepocessNV = VK_PIPELINE_STAGE_COMMAND_PREPROCESS_BIT_NV,
    NoneKHR = VK_PIPELINE_STAGE_NONE_KHR,
    RayTracingShaderNV = VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_NV,
    AccelerationStructureBuildNV = VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_NV,
    FragmentShadingRateAttachmentKHR = VK_PIPELINE_STAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR,
    MaxEnum = VK_PIPELINE_STAGE_FLAG_BITS_MAX_ENUM
};

enum class CommandBufferLevel : std::uint32_t
{
    Primary = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
    Secondary = VK_COMMAND_BUFFER_LEVEL_SECONDARY,
    MaxEnum = VK_COMMAND_BUFFER_LEVEL_MAX_ENUM
};

enum class EDescriptorType
{
    Sampler = VK_DESCRIPTOR_TYPE_SAMPLER,
    CombinedImageSampler = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
    SampledImage = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
    StorageImage = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
    UniformTexelBuffer = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,
    StorageTexelBuffer = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,
    UniformBuffer = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
    StorageBuffer = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
    UniformBufferDynamic = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
    StorageBufferDynamic = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC,
    InputAttachment = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,
    InlineUniformBlock = VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT,
    AccelerationStructure = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR,
    MutableValue = VK_DESCRIPTOR_TYPE_MUTABLE_VALVE,
    None = VK_DESCRIPTOR_TYPE_MAX_ENUM
};

_KANAS_CORE_END


#endif
