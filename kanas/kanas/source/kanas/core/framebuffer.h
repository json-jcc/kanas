#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class render_pass;
class image_view;

class framebuffer final : public device_object<VkFramebuffer>
{
	friend class render_pass;

	std::vector<std::shared_ptr<image_view>> attachments;

	bool allocate(
		const render_pass& pass, 
		std::uint32_t width, std::uint32_t height, std::uint32_t layers, 
		const std::vector<std::shared_ptr<image_view>>& image_views
	);

public:

	framebuffer(device& owner);

	framebuffer(const framebuffer&) = delete;
	framebuffer(framebuffer&& Other);

	framebuffer& operator=(const framebuffer&) = delete;

	virtual ~framebuffer() override;

};

_KANAS_CORE_END

#endif