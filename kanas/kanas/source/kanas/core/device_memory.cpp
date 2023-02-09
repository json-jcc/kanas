#include "device_memory.h"
#include "device.h"
#include "physical_device.h"

kanas::core::device_memory::device_memory(device& owner) :
	device_object(owner)
{
}

kanas::core::device_memory::~device_memory()
{
	if (is_valid())
	{
		vkFreeMemory(dev().handle(), handle(), nullptr);
		
		reset_handle();
	}
}

bool kanas::core::device_memory::allocate(VkDeviceSize alloc_size, std::uint32_t mem_type_index)
{
	VkMemoryAllocateInfo _memoryAllocateInfo{};
    _memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    _memoryAllocateInfo.pNext = nullptr;
    _memoryAllocateInfo.allocationSize = alloc_size;
    _memoryAllocateInfo.memoryTypeIndex = mem_type_index;

	const VkResult _Result = vkAllocateMemory(dev().handle(), &_memoryAllocateInfo, nullptr, &_handle);
	
	if (_Result == VkResult::VK_SUCCESS)
	{
		return true;
	}

	return false;
}

void kanas::core::device_memory::HandleMemory(std::uint64_t InOffset, std::uint64_t InSize, const device_memoryHandler& InHandler, VkMemoryMapFlags InFlags)
{
	void* Data = nullptr;

	const VkResult _Result = vkMapMemory(dev().handle(), handle(), InOffset, InSize, InFlags, &Data);
	
	if (_Result != VkResult::VK_SUCCESS || !Data)
	{
		return;
	}

	InHandler(InSize, Data);

	vkUnmapMemory(dev().handle(), handle());
}
