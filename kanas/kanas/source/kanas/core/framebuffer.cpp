#include "framebuffer.h"
#include "device.h"
#include "kanas/core/resource/image_view.h"
#include "render_pass.h"

bool kanas::core::framebuffer::allocate(
	const render_pass& pass, 
	std::uint32_t width, std::uint32_t height, std::uint32_t layers, 
	const std::vector<std::shared_ptr<image_view>>& image_views)
{
	std::vector<VkImageView> _raw_image_views;
	//get_raw(image_views, _raw_image_views);

	framebuffer_create_flags _fb_create_flags;

	if (image_views.size() == 0)
	{
		_fb_create_flags.set_imageless();
	}

	VkFramebufferCreateInfo framebufferCreateInfo;
	framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	framebufferCreateInfo.pNext = nullptr;
	framebufferCreateInfo.flags = _fb_create_flags.raw();
	framebufferCreateInfo.renderPass = pass.handle();
	framebufferCreateInfo.attachmentCount = static_cast<std::uint32_t>(_raw_image_views.size());
	framebufferCreateInfo.pAttachments = _raw_image_views.data();
	framebufferCreateInfo.width = width;
	framebufferCreateInfo.height = height;
	framebufferCreateInfo.layers = layers; 

	if (vkCreateFramebuffer(dev().handle(), &framebufferCreateInfo, nullptr, &_handle) == VK_SUCCESS)
	{
		attachments = image_views;
		return true;
	}

	return false;
}

kanas::core::framebuffer::framebuffer(device& owner) :
	device_object(owner)
{
}

kanas::core::framebuffer::framebuffer(framebuffer&& Other) :
	device_object(Other.dev())
{
}

kanas::core::framebuffer::~framebuffer()
{
	if (is_valid())
	{
		vkDestroyFramebuffer(dev().handle(), handle(), nullptr);

		reset_handle();
	}
}

