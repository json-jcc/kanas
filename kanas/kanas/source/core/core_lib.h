#ifndef _CORE_LIBRARY_H_
#define _CORE_LIBRARY_H_

#include "public/stl.h"

template<typename T, typename Handle_T = typename T::Handle_T>
static void get_raw(const std::vector<std::shared_ptr<T>>& device_objects, std::vector<Handle_T>& OutHandles)
{
	OutHandles.reserve(device_objects);
	for (const auto& device_object : device_objects)
	{
		OutHandles.emplace_back(device_object->handle());
	}
}


#define check(expr)\
{\
	if (!expr) { std::abort(); }\
}

#define checkf(expr, message)\
{\
	if (!expr)\
	{\
		std::cerr << message << std::endl;\
		std::abort();\
	}\
}

#endif