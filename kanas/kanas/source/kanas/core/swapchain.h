#ifndef _SWAPCHAIN_H_
#define _SWAPCHAIN_H_

#include "device_object.h"


_KANAS_CORE_BEGIN


class swapchain : device_object<VkSwapchainKHR>
{

	bool allocate();

public:

	swapchain(device& dev);

	virtual ~swapchain() override;

	void test()
	{
		//VkBindImageMemorySwapchainInfoKHR BindInfo;
		
		/*vkGetSwapchainStatusKHR();
		vkGetSwapchainImagesKHR();
		VkDeviceGroupSwapchainCreateInfoKHR;
		vkCreateSharedSwapchainsKHR();
		VkImageSwapchainCreateInfoKHR;*/
	}

};



_KANAS_CORE_END


#endif