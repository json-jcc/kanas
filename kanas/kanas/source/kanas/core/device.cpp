#include "device.h"
#include "physical_device.h"
#include "kanas/core/synchronization/fence.h"
#include "kanas/core/synchronization/semaphore.h"
#include "kanas/core/synchronization/Event.h"
#include "kanas/core/resource/buffer.h"
#include "kanas/core/resource/buffer_view.h"
#include "kanas/core/resource/image.h"
#include "kanas/core/resource/image_view.h"
#include "framebuffer.h"
#include "shader_module.h"
#include "sampler.h"
#include "descriptor_pool.h"
#include "command_pool.h"
#include "render_pass.h"
#include "command_buffer.h"
#include "device_memory.h"
#include "queue.h"

bool kanas::core::device::allocate()
{
    VkDeviceCreateFlags DeviceCreateFlags{};

    std::vector<VkDeviceQueueCreateInfo> QueueCreateInfos;

    std::vector<VkQueueFamilyProperties> PropertiesArr;
    GetPhysicalDevice().GetQueueFamilyProperties(PropertiesArr);

    for (const auto& Properties : PropertiesArr)
    {
        Properties.queueCount;
        Properties.queueFlags;
        Properties.minImageTransferGranularity;
        Properties.timestampValidBits;

        const bool bIsProtectedQueue = false;
        VkDeviceQueueCreateFlags QueueCreateFlags{};
        if (bIsProtectedQueue)
        {
            QueueCreateFlags |= VK_DEVICE_QUEUE_CREATE_PROTECTED_BIT;
        }

        VkDeviceQueueCreateInfo QueueCreateInfo{};
        QueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        QueueCreateInfo.pNext = nullptr;
        QueueCreateInfo.flags = QueueCreateFlags;
        QueueCreateInfo.queueFamilyIndex;
        QueueCreateInfo.queueCount;
        QueueCreateInfo.pQueuePriorities;

        QueueCreateInfos.emplace_back(QueueCreateInfo);
    }

    std::vector<const char*> EnabledLayerNames;
    std::vector<const char*> EnabledExtensionNames;

    VkPhysicalDeviceFeatures Features;
    GetPhysicalDevice().GetFeatures(Features);

    VkDeviceCreateInfo DeviceCreateInfo;
    DeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    DeviceCreateInfo.pNext = nullptr;
    DeviceCreateInfo.flags = DeviceCreateFlags;
    DeviceCreateInfo.queueCreateInfoCount = static_cast<std::uint32_t>(QueueCreateInfos.size());
    DeviceCreateInfo.pQueueCreateInfos = QueueCreateInfos.data();
    DeviceCreateInfo.enabledLayerCount = static_cast<std::uint32_t>(EnabledLayerNames.size());
    DeviceCreateInfo.ppEnabledLayerNames = EnabledLayerNames.data();
    DeviceCreateInfo.enabledExtensionCount = static_cast<std::uint32_t>(EnabledExtensionNames.size());
    DeviceCreateInfo.ppEnabledExtensionNames = EnabledExtensionNames.data();
    DeviceCreateInfo.pEnabledFeatures = &Features;

    const VkResult Result = vkCreateDevice(GPU.handle(), &DeviceCreateInfo, nullptr, &_handle);

    if (Result == VK_SUCCESS)
    {
        return true;
    }

    return false;
}

kanas::core::device::device(physical_device& InPhysicalDevice) :
    GPU(InPhysicalDevice)
{
}

kanas::core::device::~device()
{

}

std::shared_ptr<kanas::core::queue> kanas::core::device::get_queue(std::uint32_t queue_family_index, std::uint32_t queue_index)
{
    std::shared_ptr<queue> _new_queue = std::make_shared<queue>(*this);

    if (_new_queue && _new_queue->allocate(queue_family_index, queue_index))
    {
        return _new_queue;
    }

    return nullptr;
}

std::shared_ptr<kanas::core::buffer> kanas::core::device::create_buffer(std::uint64_t size, buffer_usage_flags usage, const concurrent_guide& guide)
{
    if (const auto _new_buffer = std::make_shared<buffer>(*this))
    {
        if (_new_buffer->allocate(size, usage, guide))
        {
            return _new_buffer;
        }
    }

    return nullptr;
}

std::shared_ptr<kanas::core::buffer_view> kanas::core::device::create_buffer_view(const std::shared_ptr<buffer>& target, VkFormat fmt, const x_range_1d<std::uint64_t>& range)
{
    if (const auto _new_buffer_view = std::make_shared<buffer_view>(*this))
    {
        if (_new_buffer_view->allocate(target, fmt, range))
        {
            return _new_buffer_view;
        }
    }

    return nullptr;
}

std::shared_ptr<kanas::core::fence> kanas::core::device::create_fence(bool IsDefaultSignaled)
{
    auto _new_fence = std::make_shared<fence>(*this);
    if (_new_fence && _new_fence->allocate(IsDefaultSignaled))
    {
        return _new_fence;
    }
    return nullptr;
}

std::shared_ptr<kanas::core::semaphore> kanas::core::device::create_semaphore()
{
    auto _new_semaphore = std::make_shared<semaphore>(*this);
    if (_new_semaphore && _new_semaphore->allocate(VK_SEMAPHORE_TYPE_BINARY, 0))
    {
        return _new_semaphore;
    }
    return nullptr;
}

