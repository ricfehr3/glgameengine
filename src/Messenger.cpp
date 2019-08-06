#include <chrono>
#include <future>

#include <Messenger.h>

Messenger::Messenger()
{
}

void Messenger::run()
{
    std::string line;
    while(m_running)
    {  
        while(std::getline(std::cin, line) && m_running) //read entire lines at a time
        {
	       std::cout << line << std::endl;  
        }
    }
}

void Messenger::stop()
{
    m_running = false;
}

std::atomic<bool> Messenger::m_running = ATOMIC_VAR_INIT(true);
