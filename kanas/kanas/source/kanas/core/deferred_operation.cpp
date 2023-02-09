#include "deferred_operation.h"
#include "device.h"

bool kanas::core::deferred_operation::allocate()
{
	/*const VkResult DeferredOperationCreationResult = vkCreateDeferredOperationKHR(dev().handle(), nullptr, &_handle);

	if (DeferredOperationCreationResult == VK_SUCCESS)
	{
		return true;
	}*/

	return false;
}

kanas::core::deferred_operation::deferred_operation(device& Device) :
	device_object(Device)
{
}

kanas::core::deferred_operation::~deferred_operation()
{
	if (is_valid())
	{
		//vkDestroyDeferredOperationKHR(dev().handle(), handle(), nullptr);

		reset_handle();
	}
}
