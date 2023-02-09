#ifndef _DEFERRED_OPERATION_H_
#define _DEFERRED_OPERATION_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class deferred_operation : public device_object<VkDeferredOperationKHR>
{

	bool allocate();

public:

	deferred_operation(device& Device);

	virtual ~deferred_operation();

};

_KANAS_CORE_END

#endif