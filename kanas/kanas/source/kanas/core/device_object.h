#ifndef _DEVICE_OBJECT_H_
#define _DEVICE_OBJECT_H_

#include "vulkan_object.h"

_KANAS_CORE_BEGIN

class device;
class command_buffer;

template<typename VkHandleT>
class device_object : public vulkan_object<VkHandleT>
{

public:

	using handle_t = VkHandleT;
	
	device_object(device& owner) :
		_dev(owner)
	{}

	virtual ~device_object() {}

private:

	device& _dev;

public:

	device& dev() { return _dev; }

	const device& dev() const { return _dev; }

};

_KANAS_CORE_END

#endif