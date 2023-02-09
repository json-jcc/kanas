#ifndef _FENCE_H_
#define _FENCE_H_

#include "kanas/core/device_object.h"

_KANAS_CORE_BEGIN

/**
* Queue Submit
* Queue BindSpare
*/
class fence final : public device_object<VkFence>
{
private:

	friend class device;
	friend class FTransientFenceGroup;

	bool allocate(bool IsSignaled);

	VkResult GetStatus();

public:

	fence(device& owner);

	virtual ~fence() override;

	/** Block current thread until GPU has signaled this fence or timeout.
	* @param InTimeoutInNs 
	* @return TRUE if this fence is signaled, otherwise is timeout or device lost.
	*/
	bool Wait(std::uint64_t InTimeoutInNs);

	/** Reset the fence to unsignaled state.(Non-Blocked)
	* 
	*/
	void Reset();

	/** Whether the fence is signaled.(Non-Blocked)
	* @return True if this fence is signaled, otherwise is unsignaled or device lost.
	*/
	bool IsSignaled();

};

class FTransientFenceGroup
{
public:

	void Reset();

	bool Wait(bool InWaitAll, std::uint64_t InTimeoutInMs);

	std::vector<fence*> Fences;
};

_KANAS_CORE_END

#endif