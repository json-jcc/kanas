#include "command_pool.h"
#include "command_buffer.h"
#include "device.h"
#include "physical_device.h"

kanas::core::command_pool::command_pool(device& owner) :
    device_object(owner)
{
    std::vector<VkQueueFamilyProperties> QueueFamilyProperties;
    dev().GetPhysicalDevice().GetQueueFamilyProperties(QueueFamilyProperties);

    QueueFamilyProperties[0].queueFlags;
    QueueFamilyProperties[0].timestampValidBits;

}

kanas::core::command_pool::~command_pool()
{
    if (is_valid())
    {
        vkDestroyCommandPool(dev().handle(), handle(), nullptr);

        reset_handle();
    }
}

bool kanas::core::command_pool::allocate(std::uint32_t InQueueFamilyIndex, bool bInTransientBuffer, bool bInCanBufferResetSelf)
{
    VkCommandPoolCreateFlags CommandPoolCreateFlags = 0;

    if (bInTransientBuffer)
    {
        CommandPoolCreateFlags |= VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    }
    
    if (!bInCanBufferResetSelf)
    {
        CommandPoolCreateFlags |= VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    }

    VkCommandPoolCreateInfo CommandPoolCreateInfo;
    CommandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    CommandPoolCreateInfo.pNext = nullptr;
    CommandPoolCreateInfo.flags = CommandPoolCreateFlags;
    CommandPoolCreateInfo.queueFamilyIndex = InQueueFamilyIndex;

    VkResult Result = vkCreateCommandPool(dev().handle(), &CommandPoolCreateInfo, nullptr, &_handle);

    if (Result == VkResult::VK_SUCCESS)
    {
        bCanBufferResetSelf = bInCanBufferResetSelf;
        return true;
    }

    return false;
}

bool kanas::core::command_pool::CanBufferReset() const
{
    return bCanBufferResetSelf;
}

bool kanas::core::command_pool::IsTransientBuffer() const
{
    return bTransientBuffer;
}

VkResult kanas::core::command_pool::Reset(bool bInRecycle)
{
    VkCommandPoolResetFlags CommandPoolResetFlags = 0;
    
    if (bInRecycle)
    {
        CommandPoolResetFlags |= VkCommandPoolResetFlagBits::VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT; // release resources
    }

    return vkResetCommandPool(dev().handle(), handle(), CommandPoolResetFlags);
}

kanas::core::command_buffer* kanas::core::command_pool::CreateCmdBuffer(VkCommandBufferLevel InCmdBufferLevel)
{
    const auto NewCmdBuffer = std::make_unique<command_buffer>(dev(), *this);

    /*if (NewCmdBuffer && NewCmdBuffer->allocate(InCmdBufferLevel))
    {
        CmdBuffers.emplace_back(NewCmdBuffer);
        return NewCmdBuffer.get();
    }*/

    return nullptr;
}

void kanas::core::command_pool::ReleaseCmdBuffer(command_buffer* InCmdBufferToRelease)
{
    if (InCmdBufferToRelease)
    {
        for (auto It = CmdBuffers.cbegin(); It != CmdBuffers.cend(); ++It)
        {
            if ((*It).get() == InCmdBufferToRelease)
            {
                CmdBuffers.erase(It);
                break;
            }
        }
    }
}
