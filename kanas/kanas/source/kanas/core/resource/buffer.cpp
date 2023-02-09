#include "buffer.h"
#include "kanas/core/device.h"
#include "kanas/core/physical_device.h"
#include "kanas/core/command_buffer.h"
#include "kanas/core/synchronization/semaphore.h"
#include "image.h"
#include "kanas/core/device_memory.h"

bool kanas::core::buffer::allocate(std::uint64_t size, buffer_usage_flags usage, const concurrent_guide& guide)
{
    // size must > 0
    // buffer must be specified at least one usage
	if (size == 0 || usage.empty())
	{
		return false;
	}

	VkBufferCreateInfo _buffer_create_info{};
	_buffer_create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	_buffer_create_info.pNext = nullptr;
	_buffer_create_info.flags = {} ;
	_buffer_create_info.size = size;
	_buffer_create_info.usage = usage.raw();

    // exclusive mode, record nothing
    // concurrent mode, record queues
	if (guide.DoesSupportConcurrency())
	{
		std::vector<std::uint32_t> _queue_family_indices;
        guide.GetConcurrentFamilyIndices(_queue_family_indices);
		// family index count must > 1
		_buffer_create_info.sharingMode = VK_SHARING_MODE_CONCURRENT;
		_buffer_create_info.queueFamilyIndexCount = static_cast<std::uint32_t>(_queue_family_indices.size());
		_buffer_create_info.pQueueFamilyIndices = _queue_family_indices.data();
	}
	else {
		_buffer_create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		_buffer_create_info.queueFamilyIndexCount = 0;
		_buffer_create_info.pQueueFamilyIndices = nullptr;
	}

	if (vkCreateBuffer(dev().handle(), &_buffer_create_info, nullptr, &_handle) == VK_SUCCESS)
	{
		VkMemoryRequirements _mem_requirements;
		vkGetBufferMemoryRequirements(dev().handle(), handle(), &_mem_requirements);

		const std::uint64_t _mem_alloc_size = _mem_requirements.size;
		const std::uint32_t _mem_type_index = 0;

		auto _new_mem = std::make_unique<device_memory>(dev());
		if (_new_mem && _new_mem->allocate(_mem_alloc_size, _mem_type_index))
		{
			if (vkBindBufferMemory(dev().handle(), handle(), _mem_block->handle(), 0) == VK_SUCCESS)
			{
				_mem_block = std::move(_new_mem);
				return true;
			}
		}
	}

	return false;
}

kanas::core::buffer::buffer(device& owner) :
	device_object(owner)
{
}

kanas::core::buffer::buffer(buffer&& other) noexcept :
	device_object(other.dev())
{
	_handle = other.handle();
    other.reset_handle();
}

kanas::core::buffer::~buffer()
{
	if (is_valid())
	{
		vkDestroyBuffer(dev().handle(), handle(), nullptr);
		reset_handle();
	}
}

void kanas::core::buffer::cmd_copy(command_buffer& cb, buffer& dst_buf, const std::vector<VkBufferCopy>& regions)
{
    vkCmdCopyBuffer(cb.handle(), handle(), dst_buf.handle(), static_cast<std::uint32_t>(regions.size()), regions.data());
}

void kanas::core::buffer::cmd_copy_to_image(command_buffer& cb, image& dst_img, const std::vector<VkBufferImageCopy>& regions)
{
	vkCmdCopyBufferToImage(cb.handle(), handle(), dst_img.handle(), dst_img.layout(), static_cast<std::uint32_t>(regions.size()), regions.data());
}

void kanas::core::buffer::cmd_fill(command_buffer& cb, std::uint64_t offset, std::uint64_t size, std::uint32_t data)
{
	vkCmdFillBuffer(cb.handle(), handle(), offset, size, data);
}

void kanas::core::buffer::cmd_update(command_buffer& cb, std::uint64_t offset, std::uint64_t size, void* data)
{
	vkCmdUpdateBuffer(cb.handle(), handle(), offset, size, data);
}
