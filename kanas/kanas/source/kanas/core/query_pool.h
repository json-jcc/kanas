#ifndef _PIPELINE_H_
#define _PIPELINE_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class command_buffer;
class buffer;

class query_pool : public device_object<VkQueryPool>
{
public:

	query_pool(device& owner);

	virtual ~query_pool() override;

	bool allocate(VkQueryType InQueryType, std::uint32_t InQueryCount);

	void CmdCopyResults(command_buffer& InRecorder, std::uint32_t InFirstQuery, std::uint32_t InQueryCount, buffer& InDstBuffer, std::uint64_t InDstOffset, std::uint64_t InStride, VkQueryResultFlags InQueryResultFlags);

	void CmdReset(command_buffer& InRecorder, std::uint32_t InFirstQuery, std::uint32_t InQueryCount);

	void CmdBeginQuery(command_buffer& InRecorder, std::uint32_t InQueryIndex, VkQueryControlFlags InQueryControlFlags);

	void CmdEndQuery(command_buffer& InRecorder, std::uint32_t InQueryIndex);

};

_KANAS_CORE_END

#endif