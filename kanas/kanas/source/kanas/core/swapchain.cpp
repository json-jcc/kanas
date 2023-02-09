#include "swapchain.h"
#include "device.h"
#include "surface.h"

bool kanas::core::swapchain::allocate()
{
	VkSwapchainCreateInfoKHR swapchainCreateInfo;
	swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchainCreateInfo.pNext = nullptr;
	swapchainCreateInfo.flags = {};
	swapchainCreateInfo.surface;
	swapchainCreateInfo.minImageCount;
	swapchainCreateInfo.imageFormat;
	swapchainCreateInfo.imageColorSpace;
	swapchainCreateInfo.imageExtent;
	swapchainCreateInfo.imageArrayLayers;
	swapchainCreateInfo.imageUsage;
	swapchainCreateInfo.imageSharingMode;
	swapchainCreateInfo.queueFamilyIndexCount;
	swapchainCreateInfo.pQueueFamilyIndices;
	swapchainCreateInfo.preTransform;
	swapchainCreateInfo.compositeAlpha;
	swapchainCreateInfo.presentMode;
	swapchainCreateInfo.clipped;
	swapchainCreateInfo.oldSwapchain;

	if(vkCreateSwapchainKHR(dev().handle(), &swapchainCreateInfo, nullptr, &_handle) == VK_SUCCESS)
    {
        return true;
    }

	return false;
}

kanas::core::swapchain::swapchain(device& dev) :
	device_object(dev)
{
}

kanas::core::swapchain::~swapchain()
{
}
