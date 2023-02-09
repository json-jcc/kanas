#ifndef _VULKAN_INSTANCE_H_
#define _VULKAN_INSTANCE_H_

#include "vulkan_object.h"

_KANAS_CORE_BEGIN

class physical_device;
class device;

class vulkan_instance final : public vulkan_object<VkInstance>
{
public:

	vulkan_instance();

	virtual ~vulkan_instance() override;

	bool initialize();

	[[nodiscard]] const std::vector<std::unique_ptr<physical_device>>& GPUs() const
    {
        return _GPUs;
    }

private:

	std::vector<std::unique_ptr<physical_device>> _GPUs;

};

_KANAS_CORE_END

#endif