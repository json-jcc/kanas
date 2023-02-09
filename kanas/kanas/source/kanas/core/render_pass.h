#ifndef _RENDER_PASS_H_
#define _RENDER_PASS_H_

#include "device_object.h"
#include "subpass_list.h"

_KANAS_CORE_BEGIN

class subpass;
class framebuffer;
class command_buffer;
class primary_command_buffer;
class image_view;
class pipeline;

class render_pass : public device_object<VkRenderPass>
{
	friend class deivce;

public:

	bool allocate(
            const std::string& name,
            const std::vector<attachment>& attachments,
            const subpass_list& subpasses
	);

	explicit render_pass(device& owner);
	render_pass(const render_pass&) = delete;

	render_pass(render_pass& other);

	virtual ~render_pass() override;

	void cmd_execute(primary_command_buffer& pcb) const;

    void cmd_execute_fast(primary_command_buffer& pcb) const;

	void set_render_area(const VkRect2D& val);
	
	void set_clear_values(const std::vector<VkClearValue>& vals);

	[[nodiscard]] const std::string& name() const { return _name; }

	[[nodiscard]] const std::vector<std::shared_ptr<framebuffer>>& render_targets() const
	{
		return _render_targets;
	}

private:

	std::string _name{ "null" };

    subpass_list _subpass_list;

	std::vector<VkClearValue> _clear_values;

	VkRect2D _render_area;

    std::vector<std::shared_ptr<framebuffer>> _render_targets;

    std::shared_ptr<framebuffer> _current_render_target;

};






_KANAS_CORE_END

#endif