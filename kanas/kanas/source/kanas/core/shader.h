#ifndef SHADER_H
#define SHADER_H

#include "types.h"

_KANAS_CORE_BEGIN

class shader_module;

class shader
{

	std::string name_{};

	std::shared_ptr<shader_module> module_{};

public:

	shader();

	virtual ~shader();

};


_KANAS_CORE_END

#endif