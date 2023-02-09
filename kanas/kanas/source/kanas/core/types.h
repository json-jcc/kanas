#ifndef _KANAS_CORE_TYPES_H_
#define _KANAS_CORE_TYPES_H_

#include "flags.h"
#include "enumerators.h"

_KANAS_CORE_BEGIN

// Basic structs

template<typename T>
struct x_range_1d
{
    T offset;
    T count;
};

template<typename T>
struct x_range_2d
{
    T offset_x;
    T offset_y;
    T count;
};

template<typename T>
struct x_range_3d
{
    T offset_x;
    T offset_y;
    T offset_z;
    T count;
};

using range = x_range_1d<std::uint32_t>;



// vulkan about

struct concurrent_guide
{
    void GetConcurrentFamilyIndices(std::vector<std::uint32_t>& OutFamilyIndices) const
    {
    }

    bool DoesSupportConcurrency() const
    {
        return false;
    }

    concurrent_guide();

    concurrent_guide(const std::vector<std::shared_ptr<class queue>>& InQueues) :
            ConcurrentQueues(InQueues)
    {
    }

private:

    std::vector<std::shared_ptr<class queue>> ConcurrentQueues;

};


struct attachment
{
    VkFormat format{};
    sample_count samples{};
    attachment_load_op load_op{};
    attachment_store_op store_op{};
    attachment_load_op stencil_load_op{};
    attachment_store_op stencil_store_op{};
    image_layout initial_layout{};
    image_layout final_layout{};

};

struct attachment_ref
{
    std::uint32_t index{ UINT32_MAX };
    image_layout layout{ image_layout::t::undefined };
};

_KANAS_CORE_END

#endif