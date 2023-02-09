#include "network_dispatcher.h"

bool network_dispatcher::initialize() noexcept
{
    return true;
}

void network_dispatcher::run() noexcept
{
    std::cout << "network dispatcher is running." << std::endl;
    while (!_should_exit)
    {

    }

    std::cout << "network dispatcher has exited." << std::endl;
}

void network_dispatcher::notify_to_exit() noexcept
{
    _should_exit = true;
}
