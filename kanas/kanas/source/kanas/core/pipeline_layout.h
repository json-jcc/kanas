#ifndef _PIPELINE_LAYOUT_H_
#define _PIPELINE_LAYOUT_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class descriptor_set_layout;

enum class EShaderVarType
{
	vec2,
	vec3,
	vec4,

	mat2,
	mat2x3,
	mat2x4,

	mat3x2,
	mat3,
	mat3x4,

	mat4x2,
	mat4x3,
	mat4,
	
};

class pipeline_layout final : public device_object<VkPipelineLayout>
{
	friend class device;

	bool alllocate(
		const std::vector<std::shared_ptr<descriptor_set_layout>>& InDescriptorSetLayouts, 
		const std::vector<VkPushConstantRange>& InPushConstantRanges = {}
	);

public:

	pipeline_layout(device& owner);

	virtual ~pipeline_layout() override;

	std::shared_ptr<descriptor_set_layout> GetDescriptorSetLayout(std::uint32_t SetIndex) const;

	const std::vector<std::shared_ptr<descriptor_set_layout>>& GetDescriptorSetLayouts() const;

private:

	std::vector<std::shared_ptr<descriptor_set_layout>> DescriptorSetLayouts;

};


_KANAS_CORE_END

#endif