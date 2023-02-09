#include "pipeline_layout.h"
#include "device.h"
#include "descriptor_set_layout.h"

kanas::core::pipeline_layout::pipeline_layout(device& owner) :
    device_object(owner)
{
}

kanas::core::pipeline_layout::~pipeline_layout()
{
    if (is_valid())
    {
        vkDestroyPipelineLayout(dev().handle(), handle(), nullptr);
        
        reset_handle();
    }
}

std::shared_ptr<kanas::core::descriptor_set_layout> kanas::core::pipeline_layout::GetDescriptorSetLayout(std::uint32_t SetIndex) const
{
    if (DescriptorSetLayouts.size() > SetIndex)
    {
        return DescriptorSetLayouts[SetIndex];
    }
    return nullptr;
}

const std::vector<std::shared_ptr<kanas::core::descriptor_set_layout>>& kanas::core::pipeline_layout::GetDescriptorSetLayouts() const
{
    return DescriptorSetLayouts;
}

bool kanas::core::pipeline_layout::alllocate(const std::vector<std::shared_ptr<descriptor_set_layout>>& InDescriptorSetLayouts, const std::vector<VkPushConstantRange>& InPushConstantRanges)
{
    // layout(push_constant) uniform BlockName {
    //  int member1;
    //  float member2;
    // } InstanceName;

    std::vector<VkDescriptorSetLayout> DescriptorSetLayoutHandles;
    DescriptorSetLayoutHandles.reserve(InDescriptorSetLayouts.size());

    for(const auto& DescriptorSetLayout : InDescriptorSetLayouts)
    {
        DescriptorSetLayoutHandles.emplace_back(DescriptorSetLayout->handle());
    }

    VkPipelineLayoutCreateInfo pipeline_layoutCreateInfo{};
    pipeline_layoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipeline_layoutCreateInfo.flags = {};
    pipeline_layoutCreateInfo.pSetLayouts = DescriptorSetLayoutHandles.data();
    pipeline_layoutCreateInfo.setLayoutCount = static_cast<std::uint32_t>(DescriptorSetLayoutHandles.size());
    pipeline_layoutCreateInfo.pPushConstantRanges = InPushConstantRanges.data();
    pipeline_layoutCreateInfo.pushConstantRangeCount = static_cast<std::uint32_t>(InPushConstantRanges.size());
    
    const VkResult PipelineCreationResult = vkCreatePipelineLayout(dev().handle(), &pipeline_layoutCreateInfo, nullptr, &_handle);
    
    if (PipelineCreationResult == VK_SUCCESS)
    {
        return true;
    }

    return false;
}
