#ifndef SUBPASS_LIST_H
#define SUBPASS_LIST_H

#include "device_object.h"

_KANAS_CORE_BEGIN

struct subpass_dependency
{
    pipeline_stage_flags pre_stages;
    pipeline_stage_flags next_stages;
    access_flags pre_accesses;
    access_flags next_accesses;
    dependency_flags dependencies;
};

class subpass;

class subpass_list
{
    std::shared_ptr<subpass> _default_subpass;

    std::vector<std::pair<subpass_dependency, std::shared_ptr<subpass>>> _next_subpasses;

public:

    explicit subpass_list(std::shared_ptr<subpass> default_subpass) :
            _default_subpass(std::move(default_subpass))
    {}

    subpass_list(const subpass_list&) = default;
    subpass_list& operator=(const subpass_list&) = default;

    subpass_list(subpass_list&& other) noexcept
    {
        _default_subpass = other._default_subpass;
        _next_subpasses = std::move(other._next_subpasses);
    }

    ~subpass_list() = default;

    void plus(const subpass_dependency& dependency, const std::shared_ptr<subpass>& next_subpass)
    {
        _next_subpasses.emplace_back(dependency, next_subpass);
    }

    void plus(subpass_dependency&& dependency,  std::shared_ptr<subpass>&& next_subpass)
    {
        _next_subpasses.emplace_back(dependency, next_subpass);
    }

    void pop_back()
    {
        _next_subpasses.pop_back();
    }

    void reserve(const std::size_t new_capacity)
    {
        if(new_capacity > 1)
        {
            _next_subpasses.reserve(new_capacity - 1);
        }
    }

    [[nodiscard]] std::size_t capacity() const
    {
        return 1 + _next_subpasses.capacity();
    }

    void shrink_to_fit()
    {
        _next_subpasses.shrink_to_fit();
    }

    [[nodiscard]] std::size_t size() const
    {
        return 1 + _next_subpasses.size();
    }

    void get_subpasses(std::vector<std::shared_ptr<subpass>>& out_subpasses) const
    {
        out_subpasses.reserve(1 + _next_subpasses.size());
        out_subpasses.push_back(_default_subpass);

        for(const auto& val : _next_subpasses | std::views::values)
        {
            out_subpasses.push_back(val);
        }
    }

    void get_dependencies(std::vector<subpass_dependency>& out_dependencies) const
    {
        out_dependencies.reserve(_next_subpasses.size());

        for(const auto& _next_subpass : _next_subpasses)
        {
            out_dependencies.push_back(_next_subpass.first);
        }
    }

};

_KANAS_CORE_END

#endif
