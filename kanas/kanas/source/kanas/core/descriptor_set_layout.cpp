#include "descriptor_set_layout.h"
#include "device.h"
#include "sampler.h"

bool kanas::core::descriptor_set_layout::allocate()
{
    std::shared_ptr<sampler> ImmutableSampler;

    // Sampler
    // uniform sampler
    
    // CombinedImageSampler
    // uniform sampler2D, sampler3D ...
    
    // SampledImage
    // uniform texture2D, texture3D ...
    
    // StorageImage 
    // uniform image2D, image3D ...
    
    // UniformTexelBuffer
    // uniform textureBuffer 
    
    // StorageTexelBuffer
    // uniform imageBuffer
    
    
    // UniformBuffer
    // uniform
    
    // StorageBuffer
    // buffer
    
    // UniformBufferDynamic
    // StorageBufferDynamic
    
    // InputAttachment
    // uniform subpassInput

    /*shaderStageFlags StageFlags;
    StageFlags.SetAllGraphics();

    struct descriptor_set_layoutBinding
    {
        std::uint32_t Count{ 0 };

        EDescriptorType Type{ EDescriptorType::SampledImage };

        shaderStageFlags Stages{};

        std::vector<std::shared_ptr<sampler>> ImmutableSamplers;
    };*/

   /* std::vector<descriptor_set_layoutBinding> Bindings;
    std::vector<VkDescriptorSetLayoutBinding> VkDescriptorSetLayoutBindings;

    for (const auto& Binding : Bindings)
    {
        descriptor_set_layoutBinding SetLayoutBinding
        {
            .Count = 4,
            .Type = EDescriptorType::SampledImage,
            .Stages = shaderStageFlags().SetAllGraphics()
        };

        VkDescriptorSetLayoutBinding VkBinding;
        VkBinding.binding = 0;
        VkBinding.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
        VkBinding.descriptorCount = 1;
        VkBinding.stageFlags = StageFlags.Get();
        VkBinding.pImmutableSamplers;
    }*/
    

    VkDescriptorSetLayoutCreateInfo DescriptorSetLayoutCreateInfo{};
    DescriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    DescriptorSetLayoutCreateInfo.pNext = nullptr;
    DescriptorSetLayoutCreateInfo.flags = {};
    /*DescriptorSetLayoutCreateInfo.bindingCount = static_cast<std::uint32_t>(VkDescriptorSetLayoutBindings.size());
    DescriptorSetLayoutCreateInfo.pBindings = VkDescriptorSetLayoutBindings.data();*/

    const VkResult DescriptorSetLayoutCreationResult = vkCreateDescriptorSetLayout(dev().handle(), &DescriptorSetLayoutCreateInfo, nullptr, &_handle);
    
    if (DescriptorSetLayoutCreationResult == VK_SUCCESS)
    {
        return true;
    }

    return false;
}

kanas::core::descriptor_set_layout::descriptor_set_layout(device& owner) :
    device_object(owner)
{
}

kanas::core::descriptor_set_layout::~descriptor_set_layout()
{
    if (is_valid())
    {
        vkDestroyDescriptorSetLayout(dev().handle(), handle(), nullptr);

        reset_handle();
    }
}


