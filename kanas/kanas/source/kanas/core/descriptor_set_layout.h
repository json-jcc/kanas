#ifndef _DESCRIPTOR_SET_LAYOUT_H_
#define _DESCRIPTOR_SET_LAYOUT_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class sampler;

class descriptor_set_layout final : public device_object<VkDescriptorSetLayout>
{
	bool allocate();

public:

	descriptor_set_layout(device& owner);

	virtual ~descriptor_set_layout();

	VkDescriptorSetLayoutBinding* GetBindingInfo(std::uint32_t Binding) const
    {
        return nullptr;
    }

private:

	std::vector<VkDescriptorSetLayoutBinding> Bindings;

};

_KANAS_CORE_END

#endif