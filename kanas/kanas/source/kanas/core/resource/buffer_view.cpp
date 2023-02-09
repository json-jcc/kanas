#include "buffer_view.h"
#include "buffer.h"
#include "kanas/core/device.h"

bool kanas::core::buffer_view::allocate(const std::shared_ptr<buffer>& raw, VkFormat format, const x_range_1d<std::uint64_t>& range)
{
    if(!raw)
    {
        return false;
    }

    const bool _usage_validation = raw->usage().is_index_buffer_active();
    const bool _range_validation = raw->size() < range.offset + range.count;

    if(!_usage_validation || !_range_validation)
    {
        return false;
    }

    VkBufferViewCreateInfo _buffer_view_create_info{};
    _buffer_view_create_info.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
    _buffer_view_create_info.pNext = nullptr;
    _buffer_view_create_info.flags = {};
    _buffer_view_create_info.buffer = raw->handle();
    _buffer_view_create_info.format = format;
    _buffer_view_create_info.offset = range.offset;
    _buffer_view_create_info.range = range.count;

    if (vkCreateBufferView(dev().handle(), &_buffer_view_create_info, nullptr, &_handle) == VK_SUCCESS)
    {
        _raw = raw;
        _view_fmt = format;
        _view_range = range;

        return true;
    }

    return false;
}

kanas::core::buffer_view::buffer_view(device& owner) :
    device_object(owner)
{
}

kanas::core::buffer_view::buffer_view(kanas::core::buffer_view &&other) noexcept :
        buffer_view(other.dev())
{
    _raw = std::move(other._raw);
    _view_fmt = other._view_fmt;
    _view_range = other._view_range;
}

kanas::core::buffer_view::~buffer_view()
{
    if (is_valid())
    {
        vkDestroyBufferView(dev().handle(), handle(), nullptr);
        reset_handle();
    }
}


