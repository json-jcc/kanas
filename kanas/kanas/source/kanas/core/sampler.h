#ifndef _SAMPLER_H_
#define _SAMPLER_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class sampler final : public device_object<VkSampler>
{
	friend class device;

	bool allocate();

public:

	sampler(device& owner);

	virtual ~sampler() override;

};

_KANAS_CORE_END

#endif
