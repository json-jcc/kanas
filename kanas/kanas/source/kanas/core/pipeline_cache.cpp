#include "pipeline_cache.h"
#include "device.h"

kanas::core::pipeline_cache::pipeline_cache(device& owner) :
    device_object(owner)
{
}

kanas::core::pipeline_cache::~pipeline_cache()
{
    if (is_valid())
    {
        vkDestroyPipelineCache(dev().handle(), handle(), nullptr);
        
        reset_handle();
    }
}

bool kanas::core::pipeline_cache::allocate()
{
    VkPipelineCacheCreateInfo _create_info;
    _create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
    _create_info.pNext = nullptr;
    _create_info.flags;
    _create_info.initialDataSize = 0;
    _create_info.pInitialData = nullptr;

    if (vkCreatePipelineCache(dev().handle(), &_create_info, nullptr, &_handle) == VK_SUCCESS)
    {
        return true;
    }

    return false;
}

bool kanas::core::pipeline_cache::allocate(const std::vector<std::uint8_t>& InCacheData)
{
    VkPipelineCacheCreateInfo _create_info;
    _create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
    _create_info.pNext = nullptr;
    _create_info.flags;
    _create_info.initialDataSize = InCacheData.size();
    _create_info.pInitialData = InCacheData.data();

    if (vkCreatePipelineCache(dev().handle(), &_create_info, nullptr, &_handle) == VK_SUCCESS)
    {
        return true;
    }

    return false;
}

/*void kanas::core::pipeline_cache::GetCacheData(std::vector<std::uint8_t>& OutData)
{
    const std::uint64_t CacheDataSize = GetCacheDataSize();
    OutData.resize(CacheDataSize);
	vkGetpipeline_cacheData(get_device().get_handle(), handle, nullptr, OutData.data());
}

std::uint64_t kanas::core::pipeline_cache::GetCacheDataSize() const
{
    std::uint64_t CacheDataSize = 0;
    vkGetpipeline_cacheData(get_device().get_handle(), handle, &CacheDataSize, nullptr);
    return CacheDataSize;
}*/
