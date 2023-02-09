#ifndef _BUFFER_VIEW_H_
#define _BUFFER_VIEW_H_

#include "kanas/core/device_object.h"

_KANAS_CORE_BEGIN

class buffer;

class buffer_view final : public device_object<VkBufferView>
{
	friend class device;

	bool allocate(const std::shared_ptr<buffer>& raw, VkFormat fmt, const x_range_1d<std::uint64_t>& range);

public:

	explicit buffer_view(device& owner);

	buffer_view(const buffer_view&) = delete;
	buffer_view(buffer_view&& other) noexcept ;

	buffer_view& operator=(const buffer_view&) = delete;

	~buffer_view() override;

private:

	std::shared_ptr<buffer> _raw{};

    VkFormat _view_fmt{};

    x_range_1d<std::uint64_t> _view_range{};

public:

    [[nodiscard]] std::shared_ptr<buffer> target() const
    {
        return _raw;
    }

    [[nodiscard]] VkFormat format() const
    {
        return _view_fmt;
    }

    [[nodiscard]] const x_range_1d<std::uint64_t>& range() const
    {
        return _view_range;
    }

};

_KANAS_CORE_END

#endif