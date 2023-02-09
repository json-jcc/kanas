#include "shader_module.h"
#include "device.h"

kanas::core::shader_module::shader_module(device& owner) :
	device_object(owner)
{
}

kanas::core::shader_module::~shader_module()
{
	if (is_valid())
	{
		vkDestroyShaderModule(dev().handle(), handle(), nullptr);

		reset_handle();
	}
}

bool kanas::core::shader_module::allocate(const std::vector<std::uint32_t>& code_bytes)
{
	VkShaderModuleCreateInfo shader_module_create_info{};
	shader_module_create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	shader_module_create_info.pNext = nullptr;
	shader_module_create_info.flags = {};
	shader_module_create_info.codeSize = static_cast<std::uint32_t>(code_bytes.size());
	shader_module_create_info.pCode = code_bytes.data();

	if (vkCreateShaderModule(dev().handle(), &shader_module_create_info, nullptr, &_handle) == VK_SUCCESS)
	{
		Code = code_bytes;
		return true;
	}

	return false;
}
