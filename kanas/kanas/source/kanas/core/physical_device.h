#ifndef _PHYSICAL_DEVICE_H_
#define _PHYSICAL_DEVICE_H_

#include "vulkan_object.h"

_KANAS_CORE_BEGIN

class vulkan_instance;
class device;

class physical_device final : public vulkan_object<VkPhysicalDevice>
{
public:

	physical_device(vulkan_instance& InInstance, VkPhysicalDevice InHandle);

	virtual ~physical_device() override;

	void GetFeatures(VkPhysicalDeviceFeatures& OutFeatures);

	void GetProperties(VkPhysicalDeviceProperties& OutProperties);

	void GetMemoryProperties(VkPhysicalDeviceMemoryProperties& OutMemoryProperties);

	void GetQueueFamilyProperties(std::vector<VkQueueFamilyProperties>& OutQueueFamilyProperties);

	void EnumerateExtensionProperties(const std::string& PlayerName, std::vector<VkExtensionProperties>& OutExtensionProperties);

	void EnumerateLayerProperties(std::vector<VkLayerProperties>& OutLayerProperties);

	std::shared_ptr<device> derive();

private:

	vulkan_instance& Instance;

};

_KANAS_CORE_END

#endif
