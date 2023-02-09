#ifndef NETWORK_DISPATCHER_H
#define NETWORK_DISPATCHER_H

#include "public/stl.h"

class network_dispatcher
{
public:
	network_dispatcher() = default;
	network_dispatcher(const network_dispatcher&) = delete;
	network_dispatcher& operator=(const network_dispatcher&) = delete;

	~network_dispatcher() = default;

public:

	bool initialize() noexcept;

	void run() noexcept;

	void notify_to_exit() noexcept;

private:

	std::atomic_bool _should_exit = false;

};

#endif