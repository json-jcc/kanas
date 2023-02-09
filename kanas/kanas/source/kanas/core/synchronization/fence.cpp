#include "fence.h"
#include "kanas/core/device.h"

kanas::core::fence::fence(device& owner) :
	device_object(owner)
{
}

kanas::core::fence::~fence()
{
	if (is_valid())
	{
		vkDestroyFence(dev().handle(), handle(), nullptr);

		reset_handle();
	}
}

bool kanas::core::fence::allocate(bool IsSignaled)
{
	VkFenceCreateInfo FenceCreateInfo;
	FenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	FenceCreateInfo.pNext = nullptr;
	FenceCreateInfo.flags = {};

	VkResult Result = vkCreateFence(dev().handle(), &FenceCreateInfo, nullptr, &_handle);
	
	if (Result == VkResult::VK_SUCCESS)
	{
		return true;
	}
	
	return false;
}

bool kanas::core::fence::Wait(std::uint64_t InTimeoutInNs)
{
	// VK_SUCCESS VK_TIMEOUT VK_ERROR_DEVICE_LOST
	const VkResult Result = vkWaitForFences(dev().handle(), 1, &_handle, true, InTimeoutInNs);
	return Result == VkResult::VK_SUCCESS;
}

VkResult kanas::core::fence::GetStatus()
{
	return vkGetFenceStatus(dev().handle(), handle());
}

void kanas::core::fence::Reset()
{
	vkResetFences(dev().handle(), 1, &_handle);
}

bool kanas::core::fence::IsSignaled()
{
	// VK_SUCCESS VK_NOT_READY VK_ERROR_DEVICE_LOST
	return GetStatus() == VkResult::VK_SUCCESS;
}

void kanas::core::FTransientFenceGroup::Reset()
{
}

bool kanas::core::FTransientFenceGroup::Wait(bool InWaitAll, std::uint64_t InTimeoutInMs)
{
	if (Fences.size() > 0)
	{
		device& TheDevice = Fences[0]->dev();

		std::vector<VkFence> FenceHandles;

		const VkResult Result = vkWaitForFences(TheDevice.handle(), static_cast<std::uint32_t>(FenceHandles.size()), FenceHandles.data(), InWaitAll, InTimeoutInMs);
		return Result == VkResult::VK_SUCCESS;
	}
	return false;
}

