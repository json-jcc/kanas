#ifndef _SUBPASS_H_
#define _SUBPASS_H_

#include "KanasCoreMacros.h"
#include "types.h"

_KANAS_CORE_BEGIN

class render_pass;
class pipeline;
class primary_command_buffer;
class secondary_command_buffer;

class subpass
{
public:

    std::vector<attachment_ref> input_attachment_refs;

    std::vector<attachment_ref> color_attachment_refs;
    std::vector<attachment_ref> resolve_attachment_refs;

    attachment_ref depth_stencil_attachment_ref;

    std::vector<attachment_ref> preserve_attachment_refs;

    std::shared_ptr<class pipeline> pipe;

    std::function<bool(class command_buffer& cb, const std::shared_ptr<class pipeline>& pipe)> lambda;

    void cmd_execute(command_buffer& cb);

};

_KANAS_CORE_END

#endif

