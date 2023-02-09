#pragma once

#include <vector>
#include <memory>
#include <string_view>
#include <unordered_map>

class de_other_object;

/**
*/
class de_other_side
{
public:

	de_other_side();

	virtual ~de_other_side();

	void drive(std::float_t delta_time) noexcept;

	void capture(std::shared_ptr<de_other_object> object) noexcept;

	void freed(std::shared_ptr<de_other_object> object) noexcept;

private:

	std::vector<std::shared_ptr<de_other_object>> objects;

	std::unordered_map<std::string_view, std::shared_ptr<de_other_object>> name_to_object;

};

