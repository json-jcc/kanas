#pragma once

#include<iostream>
#include<vector>

struct component
{
    
};

struct entity
{
    std::uint64_t id;
    
    std::vector<component> components;
};

class system
{
public:

    virtual void update() = 0;
};


class system_example : public system
{
public:

    virtual void update() override
    {
        
    }
};
