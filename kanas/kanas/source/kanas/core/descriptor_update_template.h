#ifndef _DESCRIPTOR_UPDATE_TEMPLATE_H_
#define _DESCRIPTOR_UPDATE_TEMPLATE_H_


#include "device_object.h"

_KANAS_CORE_BEGIN

class descriptor_update_template : public device_object<VkDescriptorUpdateTemplate>
{
public:

	descriptor_update_template();

	virtual ~descriptor_update_template() override;

};


_KANAS_CORE_END

#endif