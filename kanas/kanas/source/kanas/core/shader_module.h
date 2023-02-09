#ifndef _SHADER_MODULE_H_
#define _SHADER_MODULE_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class shader_module final : public device_object<VkShaderModule>
{

	friend class device;

	bool allocate(const std::vector<std::uint32_t>& code_bytes);

public:

	shader_module(device& owner);

	virtual ~shader_module() override;

private:

	std::vector<std::uint32_t> Code;

};

_KANAS_CORE_END

#endif