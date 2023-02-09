#ifndef _DESCRIPTOR_POOL_H_
#define _DESCRIPTOR_POOL_H_

#include "device_object.h"

_KANAS_CORE_BEGIN


class descriptor_set;
class descriptor_set_layout;

class descriptor_pool final : public device_object<VkDescriptorPool>
{
	friend class device;

	bool allocate(const std::vector<VkDescriptorPoolSize>& InPoolSizes, std::uint32_t MaxSets);

public:

	descriptor_pool(device& owner);

	virtual ~descriptor_pool();

private:

	std::vector<std::unique_ptr<descriptor_set>> DescriptorSets;

};

_KANAS_CORE_END

#endif