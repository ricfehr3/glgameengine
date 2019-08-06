#ifndef MESSENGER_H
#define MESSENGER_H

#include <iostream>
#include <string>
#include <atomic>

class Messenger
{
public:
    Messenger();
    void run();
    void stop();
    
private:
    static std::atomic<bool> m_running;
};

#endif
