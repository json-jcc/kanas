#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include "kanas/core/device_object.h"

_KANAS_CORE_BEGIN

class semaphore final : public device_object<VkSemaphore>
{
	friend class device;

	bool allocate(VkSemaphoreType type, std::uint64_t initial_val);

public:

	semaphore(device& owner);

	virtual ~semaphore() override;

	VkResult Wait(std::uint64_t InValue, std::uint64_t InTimeout);

	VkResult Signal(std::uint64_t InValue);

	std::uint64_t GetCounterValue();

};

_KANAS_CORE_END

#endif