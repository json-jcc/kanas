#include "image.h"
#include "image_view.h"
#include "kanas/core/physical_device.h"
#include "kanas/core/device.h"
#include "kanas/core/device_memory.h"
#include "kanas/core/resource/buffer.h"
#include "kanas/core/command_buffer.h"

bool kanas::core::image::allocate(VkImageType type, VkFormat format, VkExtent3D extent, std::uint32_t mips, std::uint32_t layers, VkSampleCountFlagBits samples, VkImageTiling tiling, image_usage_flags usage, VkImageLayout initial_layout, std::shared_ptr<concurrent_guide> concurrent_guide)
{
    image_create_flags _img_create_flags;
    //VkImageType _type;
    //VkExtent3D _extent;

    // image_1d
    type = VK_IMAGE_TYPE_1D;
    extent.width = 1024;
    extent.height = 1;
    extent.depth = 1;
    mips = 4;
    layers = 1;

    // image_2d


    _img_create_flags.set_array_2d();

	VkImageCreateInfo ImageCreateInfo{};
	ImageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	ImageCreateInfo.pNext = nullptr;
	ImageCreateInfo.flags = {};
	ImageCreateInfo.imageType = type;
	ImageCreateInfo.format = format;
	ImageCreateInfo.extent = extent;
	ImageCreateInfo.mipLevels = mips;
	ImageCreateInfo.arrayLayers = layers;
	ImageCreateInfo.samples = samples;
	ImageCreateInfo.tiling = tiling;
	ImageCreateInfo.usage = usage.raw();

    //VkImageFormatProperties _imageFormatProperties;


	if (concurrent_guide && concurrent_guide->DoesSupportConcurrency())
	{
		std::vector<std::uint32_t> ConcurrentQueueFamilyIndices;
        concurrent_guide->GetConcurrentFamilyIndices(ConcurrentQueueFamilyIndices);
		ImageCreateInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
		ImageCreateInfo.queueFamilyIndexCount = static_cast<std::uint32_t>(ConcurrentQueueFamilyIndices.size());
		ImageCreateInfo.pQueueFamilyIndices = ConcurrentQueueFamilyIndices.data();
	}
	else {
		ImageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		ImageCreateInfo.queueFamilyIndexCount = 0;
		ImageCreateInfo.pQueueFamilyIndices = nullptr;
	}
	
	ImageCreateInfo.initialLayout = initial_layout;

	if (vkCreateImage(dev().handle(), &ImageCreateInfo, nullptr, &_handle) == VK_SUCCESS)
	{
		VkMemoryRequirements _memoryRequirements;
		vkGetImageMemoryRequirements(dev().handle(), handle(), &_memoryRequirements);

		const std::uint64_t MemAllocSize = _memoryRequirements.size;
		const std::uint32_t MemTypeIndex = 0;

		std::unique_ptr<device_memory> _new_mem = std::make_unique<device_memory>(dev());
		if (_new_mem && _new_mem->allocate(MemAllocSize, MemTypeIndex))
		{
			const VkDeviceSize MemOffset = 0;
			if (vkBindImageMemory(dev().handle(), handle(), _new_mem->handle(), MemOffset) == VK_SUCCESS)
			{
				_mem_block = std::move(_new_mem);
				return true;
			}
		}
	}

	return false;
}

kanas::core::image::image(device& owner) :
	device_object(owner)
{
}

kanas::core::image::image(image&& other) noexcept :
	device_object(other.dev())
{
}

kanas::core::image::~image()
{
	if (is_valid())
	{
		vkDestroyImage(dev().handle(), handle(), nullptr);
		reset_handle();
	}
}

void kanas::core::image::cmd_clear_color(kanas::core::command_buffer &cb, const VkClearColorValue &value, const std::vector<VkImageSubresourceRange> &ranges)
{
	vkCmdClearColorImage(cb.handle(), handle(), _layout, &value, static_cast<std::uint32_t>(ranges.size()), ranges.data());
}

void kanas::core::image::cmd_clear_depth_stencil(command_buffer& cb, const VkClearDepthStencilValue& value, const std::vector<VkImageSubresourceRange>& ranges)
{
	vkCmdClearDepthStencilImage(cb.handle(), handle(), _layout, &value, static_cast<std::uint32_t>(ranges.size()), ranges.data());
}

void kanas::core::image::cmd_copy_to_buffer(command_buffer& cb, buffer& dst_buf, const std::vector<VkBufferImageCopy>& regions)
{
	vkCmdCopyImageToBuffer(cb.handle(), handle(), _layout, dst_buf.handle(), static_cast<std::uint32_t>(regions.size()), regions.data());
}

void kanas::core::image::cmd_copy(command_buffer& cb, image& dst_img, const std::vector<VkImageCopy>& regions)
{
	vkCmdCopyImage(cb.handle(), handle(), _layout, dst_img.handle(), dst_img.layout(), static_cast<std::uint32_t>(regions.size()), regions.data());
}

void kanas::core::image::cmd_blit(command_buffer& cb, image& dst_img, const std::vector<VkImageBlit>& regions, VkFilter filter)
{
	vkCmdBlitImage(cb.handle(), handle(), _layout, dst_img.handle(), dst_img.layout(), static_cast<std::uint32_t>(regions.size()), regions.data(), filter);
}

void kanas::core::image::cmd_resolve(command_buffer& cb, image& dst_img, const std::vector<VkImageResolve>& regions)
{
	vkCmdResolveImage(cb.handle(), handle(), _layout, dst_img.handle(), dst_img.layout(), static_cast<std::uint32_t>(regions.size()), regions.data());
}
