#ifndef _SURFACE_H_
#define _SURFACE_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class surface : public vulkan_object<VkSurfaceKHR>
{

	bool allocate();

public:

	surface(){}

	virtual ~surface() override;
};

_KANAS_CORE_END

#endif