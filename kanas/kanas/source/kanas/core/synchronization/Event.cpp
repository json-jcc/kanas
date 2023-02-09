#include "Event.h"
#include "kanas/core/device.h"
#include "kanas/core/command_buffer.h"

bool kanas::core::FEvent::allocate()
{
	VkEventCreateInfo EventCreateInfo{};
	EventCreateInfo.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
	EventCreateInfo.pNext = nullptr;
	EventCreateInfo.flags = {};

	if (vkCreateEvent(dev().handle(), &EventCreateInfo, nullptr, &_handle) == VK_SUCCESS)
	{
		return true;
	}

	return false;
}

VkResult kanas::core::FEvent::GetStatus()
{
	return vkGetEventStatus(dev().handle(), handle());
}

kanas::core::FEvent::FEvent(device& owner) :
	device_object(owner)
{
}

kanas::core::FEvent::~FEvent()
{
	if (is_valid())
	{
		vkDestroyEvent(dev().handle(), handle(), nullptr);

		reset_handle();
	}
}

void kanas::core::FEvent::Set()
{
	VkResult Result = vkSetEvent(dev().handle(), handle());
}

void kanas::core::FEvent::Reset()
{
	VkResult Result = vkResetEvent(dev().handle(), handle());
}

void kanas::core::FEvent::CmdSet(command_buffer& InRecorder, VkPipelineStageFlags InPipelineStageFlags)
{
	vkCmdSetEvent(InRecorder.handle(), handle(), InPipelineStageFlags);
}

void kanas::core::FEvent::CmdReset(command_buffer& InRecorder, VkPipelineStageFlags InPipelineStageFlags)
{
	vkCmdResetEvent(InRecorder.handle(), handle(), InPipelineStageFlags);
}

void kanas::core::FEvent::CmdWait(command_buffer& InRecorder)
{
	VkEvent EventHandles[] = { handle() };
	VkPipelineStageFlags SrcMask = VkPipelineStageFlagBits::VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
	VkPipelineStageFlags DstMask{};

	std::vector<VkMemoryBarrier> MemBarriers;
	std::vector<VkBufferMemoryBarrier> BufferMemBarriers;
	std::vector<VkImageMemoryBarrier> ImageMemBarriers;

	vkCmdWaitEvents(InRecorder.handle(), 1, EventHandles, SrcMask, DstMask,
		static_cast<std::uint32_t>(MemBarriers.size()), MemBarriers.data(), 
		static_cast<std::uint32_t>(BufferMemBarriers.size()), BufferMemBarriers.data(), 
		static_cast<std::uint32_t>(ImageMemBarriers.size()), ImageMemBarriers.data()
	);
}
