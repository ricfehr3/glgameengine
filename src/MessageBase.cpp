#include <MessageBase.h>
#include <Logger.h>
#include <sstream>

MessageBase::MessageBase()
{
    setArgNumber();
}

int MessageBase::getMessageArgs()
{
    return m_argNumber;
}

bool MessageBase::matchFormat(std::string incomingMsg)
{

}

void MessageBase::setArgNumber()
{
    std::stringstream ss(m_messageFormat);
    std::string word;
    int iter = 0;
    while(ss >> word)
    {
        iter++;
    }   
    m_argNumber = iter;
}
