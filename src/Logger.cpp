#include <fstream>

#include <Logger.h>
#include <GameApplication.h>


GameLogger::Logger::Logger() //: m_isInit(false)
{
    
    std::cout<<"### init logger status = ["<<m_isInit<<"] ###"<<std::endl;
    //std::cout<<"### init logger status =  ###"<<std::endl;
}

GameLogger::Logger::~Logger()
{
    std::cout<<"### ~destory logger ###"<<std::endl;
}

void GameLogger::Logger::setLevel(std::string debugLevel)
{
    if(!m_isInit)
    {
        std::cout << "Error! Can't set severity level. Logger is not initialized!" << std::endl;
        return;
    }
    
    if (debugLevel == "trace")
    {
        boost::log::core::get()->set_filter
        (
            boost::log::trivial::severity >= boost::log::trivial::trace
        );
    }
    else if (debugLevel == "debug")
    {
        boost::log::core::get()->set_filter
        (
            boost::log::trivial::severity >= boost::log::trivial::debug
        );
    }
    else if (debugLevel == "info")
    {
        boost::log::core::get()->set_filter
        (
            boost::log::trivial::severity >= boost::log::trivial::info
        );
    }
    else if (debugLevel == "warning")
    {
        boost::log::core::get()->set_filter
        (
            boost::log::trivial::severity >= boost::log::trivial::warning
        );
    }
    else if (debugLevel == "error")
    {
        boost::log::core::get()->set_filter
        (
            boost::log::trivial::severity >= boost::log::trivial::error
        );
    }
}

bool GameLogger::Logger::init(const std::string& path, std::string debugLevel)
{
    if (m_isInit)
    {
        return m_isInit;
    }
    
    boost::log::add_file_log
    (
        boost::log::keywords::file_name = path,                                                                /*< file name pattern >*/
        boost::log::keywords::rotation_size = 10 * 1024 * 1024,                                                /*< rotate files every 10 MiB... >*/
        boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),  /*< ...or at midnight >*/
        boost::log::keywords::format = "[%TimeStamp%]: %Message%"                                              /*< log record format >*/
    );
    m_isInit = true;
    
    setLevel(debugLevel);
    
    boost::log::add_common_attributes();
    
    m_isInit = true;
	return m_isInit;

}

boost::log::sources::severity_logger< boost::log::trivial::severity_level > GameLogger::Logger::m_lg;
