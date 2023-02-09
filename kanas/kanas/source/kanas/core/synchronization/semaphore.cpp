#include "semaphore.h"
#include "kanas/core/device.h"

kanas::core::semaphore::semaphore(device& owner) :
	device_object(owner)
{
}

kanas::core::semaphore::~semaphore()
{
	if (is_valid())
	{
		vkDestroySemaphore(dev().handle(), handle(), nullptr);

		reset_handle();
	}
}

bool kanas::core::semaphore::allocate(VkSemaphoreType type, std::uint64_t initial_val)
{
	VkSemaphoreTypeCreateInfo SemaphoreTypeCreateInfo{};
	SemaphoreTypeCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO;
	SemaphoreTypeCreateInfo.pNext = nullptr;
	SemaphoreTypeCreateInfo.semaphoreType = type;
	SemaphoreTypeCreateInfo.initialValue = initial_val;

	VkSemaphoreCreateInfo SemaphoreCreateInfo{};
	SemaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	SemaphoreCreateInfo.pNext = &SemaphoreTypeCreateInfo;
	SemaphoreCreateInfo.flags = {};

	VkResult Result = vkCreateSemaphore(dev().handle(), &SemaphoreCreateInfo, nullptr, &_handle);

	if (Result == VkResult::VK_SUCCESS)
	{
		return true;
	}

	return false;
}

VkResult kanas::core::semaphore::Wait(std::uint64_t InValue, std::uint64_t InTimeout)
{
	VkSemaphore SemaphoreHandles[] = { handle() };

	VkSemaphoreWaitInfo SemaphoreWaitInfo;
	SemaphoreWaitInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO;
	SemaphoreWaitInfo.pNext = nullptr;
	SemaphoreWaitInfo.flags = {};
	SemaphoreWaitInfo.semaphoreCount = 1;
	SemaphoreWaitInfo.pSemaphores = SemaphoreHandles;
	SemaphoreWaitInfo.pValues = &InValue;

	return vkWaitSemaphores(dev().handle(), &SemaphoreWaitInfo, InTimeout);
}

VkResult kanas::core::semaphore::Signal(std::uint64_t InValue)
{
	VkSemaphoreSignalInfo SemaphoreSignalInfo;
	SemaphoreSignalInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO;
	SemaphoreSignalInfo.pNext = nullptr;
	SemaphoreSignalInfo.semaphore = handle();
	SemaphoreSignalInfo.value = InValue;

	return vkSignalSemaphore(dev().handle(), &SemaphoreSignalInfo);
}

std::uint64_t kanas::core::semaphore::GetCounterValue()
{
	std::uint64_t Value = 0;
	vkGetSemaphoreCounterValue(dev().handle(), handle(), &Value);
	return Value;
}


