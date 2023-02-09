#ifndef _CUSTOM_RENDER_PASS_DISPATCHER_H_
#define _CUSTOM_RENDER_PASS_DISPATCHER_H_

#include "kanas_macros.h"
#include "core/device.h"

_KANAS_BEGIN

namespace core
{
    class vulkan_instance;
    class physical_device;
    class device;
    class queue;
    class command_buffer;
    class primary_command_buffer;
}

class dispatcher final
{
    std::unique_ptr<core::vulkan_instance> _app;

    std::vector<std::shared_ptr<core::device>> _devices;

    std::vector<std::shared_ptr<core::command_buffer>> command_buffers;

    std::vector<std::shared_ptr<core::queue>> _queues;

    std::vector<std::shared_ptr<core::render_pass>> _render_passes;

public:

	dispatcher();

	~dispatcher();

    bool initialize();

	void tick(float delta_time);

	void create_render_pass(const nlohmann::json& rpd);

	static void pak(std::int32_t c)
	{
		
	}

};


_KANAS_END

#endif