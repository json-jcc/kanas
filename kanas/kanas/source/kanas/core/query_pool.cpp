#include "query_pool.h"
#include "device.h"
#include "command_buffer.h"
#include "kanas/core/resource/buffer.h"

kanas::core::query_pool::query_pool(device& owner) :
	device_object(owner)
{
}

kanas::core::query_pool::~query_pool()
{
	if (is_valid())
	{
		vkDestroyQueryPool(dev().handle(), handle(), nullptr);

		reset_handle();
	}
}

bool kanas::core::query_pool::allocate(VkQueryType InQueryType, std::uint32_t InQueryCount)
{
	VkQueryPoolCreateInfo query_poolCreateInfo;
	query_poolCreateInfo.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
	query_poolCreateInfo.pNext = nullptr;
	query_poolCreateInfo.flags;
	query_poolCreateInfo.queryType = InQueryType;
	query_poolCreateInfo.queryCount = InQueryCount;
	query_poolCreateInfo.pipelineStatistics;

	VkResult Result = vkCreateQueryPool(dev().handle(), &query_poolCreateInfo, nullptr, &_handle);
	
	if (Result == VkResult::VK_SUCCESS)
	{
		return true;
	}
	
	return false;
}

void kanas::core::query_pool::CmdCopyResults(command_buffer& InRecorder, std::uint32_t InFirstQuery, std::uint32_t InQueryCount, buffer& InDstBuffer, std::uint64_t InDstOffset, std::uint64_t InStride, VkQueryResultFlags InQueryResultFlags)
{
	vkCmdCopyQueryPoolResults(InRecorder.handle(), handle(), InFirstQuery, InQueryCount, InDstBuffer.handle(), InDstOffset, InStride, InQueryResultFlags);
}

void kanas::core::query_pool::CmdReset(command_buffer& InRecorder, std::uint32_t InFirstQuery, std::uint32_t InQueryCount)
{
	vkCmdResetQueryPool(InRecorder.handle(), handle(), InFirstQuery, InQueryCount);
}

void kanas::core::query_pool::CmdBeginQuery(command_buffer& InRecorder, std::uint32_t InQueryIndex, VkQueryControlFlags InQueryControlFlags)
{
	vkCmdBeginQuery(InRecorder.handle(), handle(), InQueryIndex, InQueryControlFlags);
}

void kanas::core::query_pool::CmdEndQuery(command_buffer& InRecorder, std::uint32_t InQueryIndex)
{
	vkCmdEndQuery(InRecorder.handle(), handle(), InQueryIndex);
}
