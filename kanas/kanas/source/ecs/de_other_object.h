#pragma once
#ifndef DE_OTHER_OBJECT_H
#define DE_OTHER_OBJECT_H

#include <vector>

struct triangle
{

};


enum class primitive_t
{
	point,
	line,
	triangle,
	rectangle,
	patch,
};

class primitives
{
	primitive_t type;
};


template<typename Primitive>
struct primitives_proxy
{
	std::vector<Primitive> data;

};


class de_other_object
{

public:

	de_other_object();

	virtual ~de_other_object();

	virtual void init() noexcept;

	virtual void drive(float delta_time) noexcept;

	virtual void deinit() noexcept;

private:

};

#endif