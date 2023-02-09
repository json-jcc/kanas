#include "de_other_side.h"
#include "de_other_object.h"

de_other_side::de_other_side()
{
}

de_other_side::~de_other_side()
{
}

void de_other_side::drive(std::float_t delta_time) noexcept
{
	for (const auto& object : objects)
	{
		if (object)
		{
			object->drive(delta_time);
		}
	}
}

void de_other_side::capture(std::shared_ptr<de_other_object> object) noexcept
{

}

void de_other_side::freed(std::shared_ptr<de_other_object> object) noexcept
{
}
