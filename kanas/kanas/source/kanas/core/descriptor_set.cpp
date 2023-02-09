#include "descriptor_set.h"
#include "descriptor_set_layout.h"
#include "descriptor_pool.h"
#include "descriptor_update_template.h"
#include "device.h"
#include "command_buffer.h"
#include "pipeline.h"
#include "pipeline_layout.h"
#include "kanas/core/resource/image_view.h"
#include "kanas/core/resource/image.h"
#include "kanas/core/resource/buffer_view.h"
#include "kanas/core/resource/buffer.h"
#include "sampler.h"

bool kanas::core::descriptor_set::allocate(std::shared_ptr<descriptor_set_layout> InLayout)
{
    VkDescriptorSetLayout LayoutHandles[] = { InLayout->handle() };

    VkDescriptorSetAllocateInfo _allocate_info{};
    _allocate_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    _allocate_info.descriptorPool = Pool.handle();
    _allocate_info.descriptorSetCount = 1;
    _allocate_info.pSetLayouts = LayoutHandles;

    const VkResult DescriptorSetsAllocationResult = vkAllocateDescriptorSets(dev().handle(), &_allocate_info, &_handle);

    if (DescriptorSetsAllocationResult == VK_SUCCESS)
    {
        Layout = InLayout;

        return true;
    }

    return false;
}

void kanas::core::descriptor_set::Write(std::uint32_t BindingIndex, std::uint32_t ArrayIndex, const std::vector<FDescriptorImageInfo>& DescriptorImageInfos)
{
    std::vector<VkDescriptorImageInfo> _ImageInfos;
    for (const auto& DescriptorImageInfo : DescriptorImageInfos)
    {
        VkDescriptorImageInfo _ImageInfo;
        _ImageInfo.sampler = DescriptorImageInfo.Sampler->handle();
        _ImageInfo.imageView = DescriptorImageInfo.ImageView->handle();
        _ImageInfo.imageLayout = DescriptorImageInfo.ImageView->GetImage()->layout();
        _ImageInfos.emplace_back(_ImageInfo);
    }

    VkWriteDescriptorSet WriteDescriptorSet{};
    WriteDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    WriteDescriptorSet.pNext = nullptr;
    WriteDescriptorSet.dstSet = handle();
    WriteDescriptorSet.dstBinding = BindingIndex;
    WriteDescriptorSet.dstArrayElement = ArrayIndex;
    WriteDescriptorSet.descriptorCount = static_cast<std::uint32_t>(_ImageInfos.size());
    WriteDescriptorSet.descriptorType = Layout->GetBindingInfo(BindingIndex)->descriptorType;
    WriteDescriptorSet.pImageInfo = _ImageInfos.data();
    WriteDescriptorSet.pBufferInfo = nullptr;
    WriteDescriptorSet.pTexelBufferView = nullptr;

    vkUpdateDescriptorSets(dev().handle(), 1, &WriteDescriptorSet, 0, nullptr);
}

void kanas::core::descriptor_set::Copy(std::uint32_t SrcBindingIndex, std::uint32_t SrcArrayIndex, std::shared_ptr<descriptor_set> DstDescriptorSet, std::uint32_t DstBindingIndex, std::uint32_t DstArrayIndex, std::uint32_t CopyNum)
{
    VkCopyDescriptorSet CopyDescriptorSet{};
    CopyDescriptorSet.sType = VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET;
    CopyDescriptorSet.pNext = nullptr;
    CopyDescriptorSet.srcSet = handle();
    CopyDescriptorSet.srcBinding = SrcBindingIndex;
    CopyDescriptorSet.srcArrayElement = SrcArrayIndex;
    CopyDescriptorSet.dstSet = DstDescriptorSet->handle();
    CopyDescriptorSet.dstBinding = DstBindingIndex;
    CopyDescriptorSet.dstArrayElement = DstArrayIndex;
    CopyDescriptorSet.descriptorCount = CopyNum;

    vkUpdateDescriptorSets(dev().handle(), 0, nullptr, 1, &CopyDescriptorSet);
}

void kanas::core::descriptor_set::Update(std::shared_ptr<descriptor_update_template> InTemplate)
{
    vkUpdateDescriptorSetWithTemplate(dev().handle(), handle(), InTemplate->handle(), nullptr);
}

void kanas::core::descriptor_set::CmdPushDescriptorSet(command_buffer& InRecorder)
{
    //vkCmdPushDescriptorSetKHR(InRecorder.get_handle(),);
}

void kanas::core::descriptor_set::CmdPushDescriptorSetWithTemplate(command_buffer& InRecorder)
{
    //vkCmdPushDescriptorSetWithTemplateKHR();
}

kanas::core::descriptor_set::descriptor_set(device& owner, descriptor_pool& InPool) :
	device_object(owner), Pool(InPool)
{
}

kanas::core::descriptor_set::~descriptor_set()
{
	if (is_valid())
	{
        vkFreeDescriptorSets(dev().handle(), Pool.handle(), 1, &_handle);

		reset_handle();
	}
}

std::shared_ptr<kanas::core::descriptor_set_layout> kanas::core::descriptor_set::GetLayout() const
{
    return Layout;
}


