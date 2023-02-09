#include "image_view.h"
#include "image.h"
#include "kanas/core/device.h"

bool kanas::core::image_view::allocate(std::shared_ptr<image> InImage, VkImageViewType InViewType, VkFormat InFormat, const VkComponentMapping& InComponents, const VkImageSubresourceRange& InSubresourceRange)
{
	if (!InImage)
	{
		return false;
	}

	VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DEFERRED_BIT_EXT; // FragmentDensityMapDeferred
	VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DYNAMIC_BIT_EXT; // FragmentDensityMapDynamic

	VkImageViewCreateInfo ImageViewCreateInfo{};
	ImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	ImageViewCreateInfo.pNext = nullptr;
	ImageViewCreateInfo.flags = {};
	ImageViewCreateInfo.image = InImage->handle();
	ImageViewCreateInfo.viewType = InViewType;
	ImageViewCreateInfo.format = InFormat;
	ImageViewCreateInfo.components = InComponents;
	ImageViewCreateInfo.subresourceRange = InSubresourceRange;

	const VkResult Result = vkCreateImageView(dev().handle(), &ImageViewCreateInfo, nullptr, &_handle);

	if (Result == VkResult::VK_SUCCESS)
	{
		Image = InImage;

		return true;
	}

	return false;
}

kanas::core::image_view::image_view(device& owner) :
	device_object(owner)
{
}

kanas::core::image_view::image_view(image_view&& Other) :
	device_object(Other.dev())
{
	_handle = Other.handle();

	Other.reset_handle();
}

kanas::core::image_view::~image_view()
{
	if (is_valid())
	{
		vkDestroyImageView(dev().handle(), handle(), nullptr);

		reset_handle();
	}
}
/*

kanas::core::image_view_1d::image_view_1d()
{

}

kanas::core::image_view_1d::~image_view_1d()
{

}

bool kanas::core::image_view_1d::allocate_view_1d(
        std::shared_ptr<image_1d> img,
        const range& layers_range, const range& mips_range,
        VkFormat format, image_aspect_flags aspects)
{
    VkComponentMapping _mapping;
    _mapping.r = VK_COMPONENT_SWIZZLE_R;
    _mapping.b = VK_COMPONENT_SWIZZLE_R;
    _mapping.b = VK_COMPONENT_SWIZZLE_R;
    _mapping.a = VK_COMPONENT_SWIZZLE_R;

    VkImageSubresourceRange _range;
    _range.aspectMask = aspects.raw();
    _range.baseArrayLayer = layers_range.offset;
    _range.layerCount = layers_range.count;
    _range.baseMipLevel = mips_range.count;
    _range.levelCount = mips_range.count;

    allocate(img, VK_IMAGE_VIEW_TYPE_1D, format, _mapping, _range);
}



*/

