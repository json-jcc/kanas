#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "kanas/core/device_object.h"

_KANAS_CORE_BEGIN

class device_memory;
class command_buffer;
class image;

class buffer : public device_object<VkBuffer>
{
	friend class device;

	bool allocate(std::uint64_t size, buffer_usage_flags usage, const concurrent_guide& guide);

    std::unique_ptr<device_memory> _mem_block;

    std::uint64_t _size{0};

    buffer_usage_flags _usage{};

public:

	explicit buffer(device& owner);

	buffer(const buffer&) = delete;
	buffer(buffer&& other) noexcept;

	buffer& operator=(const buffer&) = delete;

	~buffer() override;

public:

	void cmd_copy(command_buffer& cb, buffer& dst_buf, const std::vector<VkBufferCopy>& regions);

	void cmd_copy_to_image(command_buffer& cb, image& dst_img, const std::vector<VkBufferImageCopy>& regions);

	void cmd_fill(command_buffer& cb, std::uint64_t offset, std::uint64_t size, std::uint32_t data);

	void cmd_update(command_buffer& cb, std::uint64_t offset, std::uint64_t size, void* data);

    [[nodiscard]] std::uint64_t size() const
    {
        return _size;
    }

    [[nodiscard]] buffer_usage_flags usage() const
    {
        return _usage;
    }

};

class index_buffer final : public buffer
{
    friend class device;

    VkIndexType _index_type;

public:

    index_buffer(device& owner);

    VkIndexType index_type() const
    {
        return _index_type;
    }

};

class vertex_buffer : public buffer
{

};

class uniform_buffer : public buffer
{
    uniform_buffer();

};

_KANAS_CORE_END

#endif