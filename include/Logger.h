#ifndef LOGGER_H
#define LOGGER_H

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/thread.hpp>

#include <string>

class GameApplication;

namespace GameLogger
{

class Logger
{
public:
    friend class ::GameApplication;
	
	static boost::log::sources::severity_logger< boost::log::trivial::severity_level > m_lg;
    void setLevel(std::string debugLevel);
    
private:
    Logger();
    ~Logger();
    bool init(const std::string& path, std::string debugLevel);
    
    bool m_isInit;
    
    
};

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__ ":" TOSTRING(__LINE__)
#define TID pthread_self()
#define PID getpid()

#define GLOG_TRACE(str) {BOOST_LOG_SEV(GameLogger::Logger::m_lg,boost::log::trivial::trace) <<"TRACE: "<< AT << "|" << TID << "|-" << str;}
#define GLOG_DEBUG(str) {BOOST_LOG_SEV(GameLogger::Logger::m_lg,boost::log::trivial::debug) <<"DEBUG: "<< AT << "|" << TID << "|-" << str;}
#define GLOG_INFO(str) {BOOST_LOG_SEV(GameLogger::Logger::m_lg,boost::log::trivial::info) <<"INFO: "<< AT << "|" << TID << "|-" << str;}
#define GLOG_WARN(str) {BOOST_LOG_SEV(GameLogger::Logger::m_lg,boost::log::trivial::warning)<<"WARN: " << AT << "|" << TID << "|-" << str;}
#define GLOG_ERROR(str) {BOOST_LOG_SEV(GameLogger::Logger::m_lg,boost::log::trivial::error)<<"ERROR: " << AT << "|" << TID << "|-" << str;}

}

#endif
