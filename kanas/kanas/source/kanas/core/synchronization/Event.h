#ifndef _EVENT_H_
#define _EVENT_H_

#include "kanas/core/device_object.h"

_KANAS_CORE_BEGIN

class command_buffer;

class FEvent final : public device_object<VkEvent>
{
	friend class device;

	bool allocate();

	VkResult GetStatus();

public:

	FEvent(device& owner);

	virtual ~FEvent();

	void Set();

	void Reset();

	void CmdSet(command_buffer& InRecorder, VkPipelineStageFlags InPipelineStageFlags);

	void CmdReset(command_buffer& InRecorder, VkPipelineStageFlags InPipelineStageFlags);

	void CmdWait(command_buffer& InRecorder);

};

_KANAS_CORE_END

#endif