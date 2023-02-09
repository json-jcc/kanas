#ifndef _VULKAN_OBJECT_H_
#define _VULKAN_OBJECT_H_

#include "core/core_lib.h"
#include "types.h"

_KANAS_CORE_BEGIN

template<typename VkHandleT>
class vulkan_object
{
public:
	vulkan_object() = default;

	virtual ~vulkan_object() {}

protected:

	VkHandleT _handle{ VK_NULL_HANDLE };

	inline void reset_handle() { _handle = VK_NULL_HANDLE; }

	bool is_valid() const { return _handle != VK_NULL_HANDLE; }

public:

	VkHandleT handle() const { return _handle; }

};

_KANAS_CORE_END

#endif