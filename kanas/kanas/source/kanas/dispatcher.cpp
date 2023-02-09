#include "dispatcher.h"
#include "core/vulkan_instance.h"
#include "core/physical_device.h"
#include "core/device.h"
#include "core/queue.h"
#include "core/command_buffer.h"
#include "core/resource/buffer.h"
#include "core/resource/buffer_view.h"
#include "core/render_pass.h"
#include "core/graphics_pipeline.h"

kanas::dispatcher::dispatcher() {

    std::shared_mutex mtx;
}

kanas::dispatcher::~dispatcher() {

}

bool kanas::dispatcher::initialize()
{
    _app = std::make_unique<core::vulkan_instance>();

    check(_app);
    if(!_app->initialize())
    {
        return false;
    }

    for(const auto& _GPU : _app->GPUs())
    {
        if(_GPU)
        {
            if(const auto _dev = _GPU->derive())
            {
                _dev->get_queue(0, 0);

                _devices.push_back(_dev);
            }
        }
    }

    return true;
}

void kanas::dispatcher::tick(float delta_time)
{
    if(_devices.empty() || !_devices[0])
    {
        return;
    }

    core::device& _master_dev = *_devices[0];

    // multithreading
    for(const auto& _render_pass : _render_passes)
    {
        if(_render_pass)
        {
            // find command buffer
            std::shared_ptr<core::primary_command_buffer> pcb;
            if(pcb)
            {
                pcb->reset();
                pcb->record(*_render_pass);
            }
        }
    }

    // block to wait for all
    // ready for submission

    std::shared_ptr<core::queue> _queue = _master_dev.get_queue(0, 0);
    if(_queue)
    {

        core::submission_batch _batch;
        _batch.cmd_buffers;
        _batch.semaphore_to_wait_before_execution;
        _batch.semaphore_to_signal_after_execution;

        _queue->submit({_batch});
        //_queue->present();

        _queue->wait_idle();
    }

}

void kanas::dispatcher::create_render_pass(const nlohmann::json& rpd)
{
    /*core::device& _master_dev = *_devices[0];

    const auto _shadow_buf = _master_dev.create_buffer(1024, core::buffer_usage_flags().set_index_buffer());

    auto _tesla_shadow_bv = _master_dev.create_buffer_view(
            _shadow_buf,
            VK_FORMAT_A1R5G5B5_UNORM_PACK16, {0, _shadow_buf->size()}
    );

    // create half shadow bv
    // _tesla_shadow_bv
    {
        auto _tesla_half_shadow_bv = _master_dev.create_buffer_view(
                _tesla_shadow_bv->target(),
                _tesla_shadow_bv->format(), {_tesla_shadow_bv->range().offset, _tesla_shadow_bv->range().count / 2}
        );
    }

    // def attachments
    std::vector<core::attachment> _attachments
    {
            core::attachment
            {
                .format = VK_FORMAT_A2B10G10R10_UINT_PACK32,
                .initial_layout = core::image_layout::t::undefined,
                .final_layout = core::image_layout::t::color_attachment_optimal,
                .stencil_load_op = {}
            },
            core::attachment
            {

            },
    };

    std::shared_ptr<core::graphics_pipeline> _graphics_pipe = nullptr;*/

    // geometry output pass
    /*core::subpass_list _subpasses(core::subpass
    {
            .input_attachment_refs =
            {
                    core::attachment_ref{0, core::image_layout::t::color_attachment_optimal},
                    core::attachment_ref{1, core::image_layout::t::color_attachment_optimal}
            },
            .color_attachment_refs =
            {
                    core::attachment_ref{1, core::image_layout::t::color_attachment_optimal}
            },
            .resolve_attachment_refs =
            {
                    core::attachment_ref{1, core::image_layout::t::color_attachment_optimal}
            },
            .depth_stencil_attachment_ref =
            {
                    2, core::image_layout::t::depth_stencil_attachment_optimal
            },
            .preserve_attachment_refs = {},
            .pipe = _graphics_pipe,
            .lambda = [_graphics_pipe](core::command_buffer& cb, const std::shared_ptr<core::pipeline>& pipe){

                const auto _graphics_pipeline = std::dynamic_pointer_cast<core::graphics_pipeline>(pipe);

                if(!_graphics_pipeline)
                {
                    return false;
                }

                cb.cmd_barrier();
                _graphics_pipeline->cmd_bind(cb);
                _graphics_pipeline->cmd_draw(cb, 36, 1, 0, 0);

                cb.cmd_barrier();
                return true;
            }
    });

    // deferred lighting pass
    _subpasses.plus(
            core::subpass_dependency
            {
                .pre_stages = core::pipeline_stage_flags().set_fragment_shader(),
                .next_stages = core::pipeline_stage_flags().set_vertex_shader(),
                .pre_accesses = core::access_flags().set_color_attachment_write(),
                .next_accesses = core::access_flags().set_color_attachment_read(),
                .dependencies = core::dependency_flags().set_by_region()
            },
            core::subpass
            {
                .input_attachment_refs =
                {
                    core::attachment_ref{0, core::image_layout::t::color_attachment_optimal},
                    core::attachment_ref{1, core::image_layout::t::color_attachment_optimal}
                },
                .color_attachment_refs =
                {
                    core::attachment_ref{1, core::image_layout::t::color_attachment_optimal}
                },
                .resolve_attachment_refs = {},
                .depth_stencil_attachment_ref = {},
                .preserve_attachment_refs = {},
                .pipe = _graphics_pipe,
                .lambda = [](core::command_buffer& cb, const std::shared_ptr<core::pipeline>& pipe){

                    if(const auto _graphics_pipe = std::dynamic_pointer_cast<core::graphics_pipeline>(pipe))
                    {
                        _graphics_pipe->cmd_bind_index_buffer(cb, nullptr);
                        _graphics_pipe->cmd_bind_vertex_buffers(cb, 0, {}, 0);
                        _graphics_pipe->cmd_push_constants(cb);
                    }

                    return true;
                },
            }
    );

    auto _main_pass = _master_dev.create_render_pass("main_pass", _attachments, _subpasses);

    if(!_main_pass)
    {
        return;
    }*/

}




