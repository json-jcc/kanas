#ifndef _COMMAND_POOL_H_
#define _COMMAND_POOL_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class command_buffer;

class command_pool final : public device_object<VkCommandPool>
{

	bool bCanBufferResetSelf{ false };

	bool bTransientBuffer{ false };

public:

	command_pool(device& owner);

	virtual ~command_pool() override;

	bool allocate(std::uint32_t InQueueFamilyIndex, bool bInTransientBuffer = false , bool bInCanBufferResetSelf = true);

	VkResult Reset(bool bInRecycle = false);

	command_buffer* CreateCmdBuffer(VkCommandBufferLevel InCmdBufferLevel);

	void ReleaseCmdBuffer(command_buffer* InCmdBufferToRelease);

	bool CanBufferReset() const;

	bool IsTransientBuffer() const;

private:

	std::vector<std::unique_ptr<command_buffer>> CmdBuffers;

};

_KANAS_CORE_END

#endif