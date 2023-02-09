#ifndef _PIPELINE_CACHE_H_
#define _PIPELINE_CACHE_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class pipeline_cache final : public device_object<VkPipelineCache>
{
public:

	explicit pipeline_cache(device& owner);

	virtual ~pipeline_cache() override;

	bool allocate();

	bool allocate(const std::vector<std::uint8_t>& InCacheData);

	/*void get_cache_data(std::vector<std::uint8_t>& OutData);*/

};

_KANAS_CORE_END

#endif