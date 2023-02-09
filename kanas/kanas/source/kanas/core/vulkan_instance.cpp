#include "vulkan_instance.h"
#include "physical_device.h"

kanas::core::vulkan_instance::vulkan_instance()
{
}

kanas::core::vulkan_instance::~vulkan_instance()
{
	if (is_valid())
	{
		vkDestroyInstance(handle(), nullptr);

		reset_handle();
	}
}

bool kanas::core::vulkan_instance::initialize()
{
	VkApplicationInfo ApplicationInfo;
	ApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	ApplicationInfo.pNext = nullptr;
	ApplicationInfo.pApplicationName = "";
	ApplicationInfo.applicationVersion = 0;
	ApplicationInfo.pEngineName = "";
	ApplicationInfo.engineVersion;
	ApplicationInfo.apiVersion;

	std::vector<const char*> EnabledLayerNames;
	std::vector<const char*> EnabledExtensionNames;

	VkInstanceCreateInfo InstanceCreateInfo;
	InstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	InstanceCreateInfo.pNext = nullptr;
	InstanceCreateInfo.flags = {};
	InstanceCreateInfo.pApplicationInfo = &ApplicationInfo;
	InstanceCreateInfo.enabledLayerCount = static_cast<std::uint32_t>(EnabledLayerNames.size());
	InstanceCreateInfo.ppEnabledLayerNames = EnabledLayerNames.data();
	InstanceCreateInfo.enabledExtensionCount = static_cast<std::uint32_t>(EnabledExtensionNames.size());
	InstanceCreateInfo.ppEnabledExtensionNames = EnabledExtensionNames.data();

	if (vkCreateInstance(&InstanceCreateInfo, nullptr, &_handle) == VK_SUCCESS)
	{

		std::uint32_t _physical_device_count = 0;
		vkEnumeratePhysicalDevices(handle(), &_physical_device_count, nullptr);

		std::vector<VkPhysicalDevice> _raw_physical_devices;
        _raw_physical_devices.resize(_physical_device_count);

		vkEnumeratePhysicalDevices(handle(), nullptr, _raw_physical_devices.data());

		for (auto _raw_physical_device : _raw_physical_devices)
		{
			if (_raw_physical_device != VK_NULL_HANDLE)
			{
				auto _new_physical_device = std::make_unique<physical_device>(*this, _raw_physical_device);
				if (_new_physical_device)
				{
					_GPUs.emplace_back(std::move(_new_physical_device));
				}
			}
		}

		return true;
	}

	return false;
}
