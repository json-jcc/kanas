#include "physical_device.h"
#include "device.h"
#include "vulkan_instance.h"

kanas::core::physical_device::physical_device(vulkan_instance& InInstance, VkPhysicalDevice InHandle) :
	Instance(InInstance)
{
	_handle = InHandle;
}

kanas::core::physical_device::~physical_device()
{
}

void kanas::core::physical_device::GetFeatures(VkPhysicalDeviceFeatures& OutFeatures)
{
	vkGetPhysicalDeviceFeatures(handle(), &OutFeatures);
}

void kanas::core::physical_device::GetProperties(VkPhysicalDeviceProperties& OutProperties)
{
	vkGetPhysicalDeviceProperties(handle(), &OutProperties);
}

void kanas::core::physical_device::GetMemoryProperties(VkPhysicalDeviceMemoryProperties& OutMemoryProperties)
{
	vkGetPhysicalDeviceMemoryProperties(handle(), &OutMemoryProperties);

	VK_MAX_MEMORY_HEAPS;
	OutMemoryProperties.memoryHeaps[0].size;
	OutMemoryProperties.memoryHeaps[0].flags;
	VK_MAX_MEMORY_TYPES;
	OutMemoryProperties.memoryTypes[0].heapIndex;
	OutMemoryProperties.memoryTypes[0].propertyFlags;

	VK_MEMORY_HEAP_DEVICE_LOCAL_BIT; // DeviceLocal
	VK_MEMORY_HEAP_MULTI_INSTANCE_BIT; // MultiInstance

	/*struct FMemoryHeap
	{
		std::uint32_t HeapIndex;
		std::uint64_t HeapSize;
		std::vector<FMemoryProperty> Properties;
	};*/

}

void kanas::core::physical_device::GetQueueFamilyProperties(std::vector<VkQueueFamilyProperties>& OutQueueFamilyProperties)
{
	std::uint32_t Count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(handle(), &Count, nullptr);
	
	OutQueueFamilyProperties.resize(Count);
	vkGetPhysicalDeviceQueueFamilyProperties(handle(), nullptr, OutQueueFamilyProperties.data());
}

void kanas::core::physical_device::EnumerateExtensionProperties(const std::string& PlayerName, std::vector<VkExtensionProperties>& OutExtensionProperties)
{
	std::uint32_t Count = 0;
	vkEnumerateDeviceExtensionProperties(handle(), PlayerName .c_str(), & Count, nullptr);
	
	if (Count > 0)
	{
		OutExtensionProperties.resize(Count);
		vkEnumerateDeviceExtensionProperties(handle(), PlayerName.c_str(), nullptr, OutExtensionProperties.data());
	}
}

void kanas::core::physical_device::EnumerateLayerProperties(std::vector<VkLayerProperties>& OutLayerProperties)
{
	std::uint32_t Count = 0;
	vkEnumerateDeviceLayerProperties(handle(), &Count, nullptr);

	if (Count > 0)
	{
		OutLayerProperties.resize(Count);
		vkEnumerateDeviceLayerProperties(handle(), nullptr, OutLayerProperties.data());
	}
}
std::shared_ptr<kanas::core::device> kanas::core::physical_device::derive() {
    return std::shared_ptr<device>();
}
