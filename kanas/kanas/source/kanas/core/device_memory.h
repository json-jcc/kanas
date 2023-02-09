#ifndef _DEVICE_MEMORY_H_
#define _DEVICE_MEMORY_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

struct MemoryHeapDescription
{
	bool IsDeviceLocal;
	bool IsHostVisible;
	bool IsHostCoherent;
	bool IsHostCached;
	bool IsLazilyAllocated;
	bool IsProtected;
};

struct MemoryHeap
{
	VkDeviceSize Size;

	bool IsDeviceLocal;
	bool IsMultiInstance;

	std::vector<MemoryHeapDescription> Descriptions;
};

class device_memory final : public device_object<VkDeviceMemory>
{
	friend class image;
	friend class buffer;

	bool allocate(VkDeviceSize alloc_size, std::uint32_t mem_type_index);

public:

	device_memory(device& owner);

	virtual ~device_memory() override;

private:

	using device_memoryHandler = std::function<void(std::uint64_t InSize, void* InData)>;

	void HandleMemory(std::uint64_t InOffset, std::uint64_t InSize, const device_memoryHandler& InHandler, VkMemoryMapFlags InFlags);

};


_KANAS_CORE_END

#endif