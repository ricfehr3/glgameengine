#include <MessageBase.h>
#include <sstream>

MessageBase::MessageBase()
{
    setArgNumber();
}

int MessageBase::getMessageArgs()
{

}

bool MessageBase::matchFormat(std::string incomingMsg)
{

}

void MessageBase::setArgNumber()
{
    std::stringstream ss(m_messageFormat);
    std::string word;
    while(ss >> word)
    {
        std::cout << word << std::endl;
    }   
    m_argNumber = 69;
}
