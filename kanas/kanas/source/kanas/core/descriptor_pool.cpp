#include "descriptor_pool.h"
#include "descriptor_set.h"
#include "device.h"

bool kanas::core::descriptor_pool::allocate(const std::vector<VkDescriptorPoolSize>& InPoolSizes, std::uint32_t MaxSets)
{
	VkDescriptorPoolCreateInfo DescriptorPoolCreateInfo{};
	DescriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	DescriptorPoolCreateInfo.pNext = nullptr;
	DescriptorPoolCreateInfo.flags = {};
	DescriptorPoolCreateInfo.pPoolSizes = InPoolSizes.data();
	DescriptorPoolCreateInfo.poolSizeCount = static_cast<std::uint32_t>(InPoolSizes.size());
	DescriptorPoolCreateInfo.maxSets = MaxSets;

	const VkResult Result = vkCreateDescriptorPool(dev().handle(), &DescriptorPoolCreateInfo, nullptr, &_handle);

	if (Result == VK_SUCCESS)
	{
		return true;
	}

	return false;
}

kanas::core::descriptor_pool::descriptor_pool(device& owner) :
	device_object(owner)
{
}

kanas::core::descriptor_pool::~descriptor_pool()
{
	if (is_valid())
	{
		vkDestroyDescriptorPool(dev().handle(), handle(), nullptr);

		reset_handle();
	}
}

