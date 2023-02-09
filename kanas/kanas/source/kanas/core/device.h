#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "vulkan_object.h"

_KANAS_CORE_BEGIN

class physical_device;

class queue;

class device_memory;

class buffer;
class buffer_view;
class image;
class image_view;

class framebuffer;

class descriptor_pool;
class descriptor_set_layout;

class sampler;
class shader_module;
class pipeline_cache;
class pipeline_layout;
class render_pass;

class graphics_pipeline;
class compute_pipeline;
class ray_tracing_pipeline;

class fence;
class semaphore;
class FEvent;

class command_pool;

class device final : public vulkan_object<VkDevice>
{
	friend class physical_device;

	bool allocate();

public:

	device(physical_device& InPhysicalDevice);

	device(const device&) = delete;
	device& operator=(const device&) = delete;

	virtual ~device() override;

	std::shared_ptr<queue> get_queue(std::uint32_t queue_family_index, std::uint32_t queue_index);

    std::shared_ptr<buffer> create_buffer(std::uint64_t size, buffer_usage_flags usage, const concurrent_guide& guide = {});

    std::shared_ptr<buffer_view> create_buffer_view(const std::shared_ptr<buffer>& target, VkFormat fmt, const x_range_1d<std::uint64_t>& range);

    std::shared_ptr<graphics_pipeline> create_graphics_pipeline();

    std::shared_ptr<compute_pipeline> create_compute_pipeline();

    std::shared_ptr<ray_tracing_pipeline> create_ray_tracing_pipeline();

    std::shared_ptr<kanas::core::fence> create_fence(bool IsDefaultSignaled);

    std::shared_ptr<kanas::core::semaphore> create_semaphore();

	physical_device& GetPhysicalDevice() const { return GPU; }

private:

	physical_device& GPU;

};

_KANAS_CORE_END


#endif
