#ifndef _ACCELERATION_STRUCTURE_H_
#define _ACCELERATION_STRUCTURE_H_

#include "kanas/core/device_object.h"

_KANAS_CORE_BEGIN

class device_memory;

class acceleration_structure : device_object<VkAccelerationStructureKHR>
{
public:

    acceleration_structure(device& owner);

	virtual ~acceleration_structure() override;
	

	std::shared_ptr<device_memory> Mem;

};

_KANAS_CORE_END


#endif