#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "kanas/core/device_object.h"

_KANAS_CORE_BEGIN

class command_buffer;
class buffer;
class image_view;
class device_memory;

class image : public device_object<VkImage>
{
	friend class device;

	bool allocate(VkImageType type, VkFormat format,
                  VkExtent3D extent, std::uint32_t mips, std::uint32_t layers,
                  VkSampleCountFlagBits samples, VkImageTiling tiling,
                  image_usage_flags usage, VkImageLayout initial_layout,
                  std::shared_ptr<concurrent_guide> concurrent_guide = nullptr);

    void allocate_image_1d(VkFormat format, uint32_t width, uint32_t mips, VkSampleCountFlagBits samples, VkImageTiling tiling, image_usage_flags usage)
    {
        VkImageCreateInfo ImageCreateInfo{};
        ImageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        ImageCreateInfo.pNext = nullptr;
        ImageCreateInfo.flags = {};
        ImageCreateInfo.imageType = VK_IMAGE_TYPE_1D;
        ImageCreateInfo.format = format;
        ImageCreateInfo.extent = {width, 1, 1};
        ImageCreateInfo.mipLevels = mips;
        ImageCreateInfo.arrayLayers = 1;
        ImageCreateInfo.samples = samples;
        ImageCreateInfo.tiling = tiling;
        ImageCreateInfo.usage = usage.raw();
    }

    void allocate_image_1d_array(VkFormat format,
                                 uint32_t width, uint32_t layers,
                                 uint32_t mips, VkSampleCountFlagBits samples, VkImageTiling tiling, image_usage_flags usage)
    {
        VkImageCreateInfo ImageCreateInfo{};
        ImageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        ImageCreateInfo.pNext = nullptr;
        ImageCreateInfo.flags = {};
        ImageCreateInfo.imageType = VK_IMAGE_TYPE_1D;
        ImageCreateInfo.format = format;
        ImageCreateInfo.extent = {width, 1, 1};
        ImageCreateInfo.mipLevels = mips;
        ImageCreateInfo.arrayLayers = layers;
        ImageCreateInfo.samples = samples;
        ImageCreateInfo.tiling = tiling;
        ImageCreateInfo.usage = usage.raw();
    }

    void allocate_image_2d_array(VkFormat format,
                                 uint32_t width, uint32_t height, uint32_t layers,
                                 uint32_t mips, VkSampleCountFlagBits samples, VkImageTiling tiling, image_usage_flags usage)
    {
        VkImageCreateInfo ImageCreateInfo{};
        ImageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        ImageCreateInfo.pNext = nullptr;
        ImageCreateInfo.flags = image_create_flags().set_array_2d().raw();
        ImageCreateInfo.imageType = VK_IMAGE_TYPE_3D;
        ImageCreateInfo.format = format;
        ImageCreateInfo.extent = {width, height, layers};
        ImageCreateInfo.mipLevels = mips;
        ImageCreateInfo.arrayLayers = 1;
        ImageCreateInfo.samples = samples;
        ImageCreateInfo.tiling = tiling;
        ImageCreateInfo.usage = usage.raw();
    }

    void allocate_image_3d()
    {}

    void allocate_image_cube(VkFormat format, uint32_t width, uint32_t mips, VkSampleCountFlagBits samples, VkImageTiling tiling, image_usage_flags usage)
    {
        VkImageCreateInfo ImageCreateInfo{};
        ImageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        ImageCreateInfo.pNext = nullptr;
        ImageCreateInfo.flags = image_create_flags().set_cube_compatible().raw();
        ImageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
        ImageCreateInfo.format = format;
        ImageCreateInfo.extent = {width, width, 1};
        ImageCreateInfo.mipLevels = mips;
        ImageCreateInfo.arrayLayers = 6;
        ImageCreateInfo.samples = samples;
        ImageCreateInfo.tiling = tiling;
        ImageCreateInfo.usage = usage.raw();
    }

public:

	explicit image(device& owner);

	image(const image&) = delete;
	image(image&& other) noexcept ;

	image& operator=(const image&) = delete;

	~image() override;

public:

	void cmd_clear_color(command_buffer& cb, const VkClearColorValue& value, const std::vector<VkImageSubresourceRange>& ranges);

	void cmd_clear_depth_stencil(command_buffer& cb, const VkClearDepthStencilValue& value, const std::vector<VkImageSubresourceRange>& ranges);

	void cmd_copy_to_buffer(command_buffer& cb, buffer& dst_buf, const std::vector<VkBufferImageCopy>& regions);

	void cmd_copy(command_buffer& cb, image& dst_img, const std::vector<VkImageCopy>& regions);

	void cmd_blit(command_buffer& cb, image& dst_img, const std::vector<VkImageBlit>& regions, VkFilter filter);

	void cmd_resolve(command_buffer& cb, image& dst_img, const std::vector<VkImageResolve>& regions);

private:

	std::unique_ptr<device_memory> _mem_block;

	VkImageLayout _layout;

public:

	[[nodiscard]] VkImageLayout layout() const
    {
        return _layout;
    }

	/*VK_IMAGE_USAGE_TRANSFER_SRC_BIT = 0x00000001,
    VK_IMAGE_USAGE_TRANSFER_DST_BIT = 0x00000002,
    VK_IMAGE_USAGE_SAMPLED_BIT = 0x00000004,
    VK_IMAGE_USAGE_STORAGE_BIT = 0x00000008,
    VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT = 0x00000010,
    VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT = 0x00000020,
    VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT = 0x00000040,
    VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT = 0x00000080,*/
};

class image_1d : public image
{};

class image_2d : protected image
{};

class image_3d : protected image
{};

class image_1d_array : protected image
{};

class image_2d_array : protected image
{};

class image_cube : protected image
{};



// TransferSrc
// TransferDst
// Sampled
// Storage
// ColorAttachment
// DepthStencilAttachment
// TransientAttachment
// InputAttachment

_KANAS_CORE_END

#endif