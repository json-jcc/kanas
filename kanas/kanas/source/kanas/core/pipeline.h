#ifndef _PIPELINE_H_
#define _PIPELINE_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class buffer;
class shader_module;
class pipeline_layout;
class pipeline_cache;
class descriptor_set;
class command_buffer;

class pipelineConstants
{

public:

	std::uint8_t* GetData() {return nullptr;}

	std::uint64_t GetSize() {return 0;}
};


class pipeline : public device_object<VkPipeline>
{
public:

	pipeline(device& owner, VkPipelineBindPoint InBindPoint);

	pipeline(const device&) = delete;
	pipeline& operator=(const device&) = delete;

	virtual ~pipeline() override;

	virtual void cmd_bind(command_buffer& cb);

	std::shared_ptr<pipeline_layout> layout() const;

	VkPipelineBindPoint bind_point() const;

protected:

    void cmd_bind_descriptor_sets(command_buffer& cb);

    void cmd_push_constants(command_buffer& cb);

private:

	std::shared_ptr<pipeline_layout> _layout;

	VkPipelineBindPoint _bind_point;

	std::shared_ptr<pipelineConstants> _constants;

};

_KANAS_CORE_END

#endif