#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>

#ifndef AN_LOG_EMERG
#define AN_LOG_EMERG log4cpp::Priority::EMERG
#endif // !AN_LOG_EMERG
#ifndef AN_LOG_FATAL
#define AN_LOG_FATAL log4cpp::Priority::FATAL
#endif // !AN_LOG_FATAL
#ifndef AN_LOG_ALERT
#define AN_LOG_ALERT log4cpp::Priority::ALERT
#endif // !AN_LOG_ALERT
#ifndef AN_LOG_CRIT
#define AN_LOG_CRIT log4cpp::Priority::CRIT
#endif // !AN_LOG_CRIT
#ifndef AN_LOG_ERROR
#define AN_LOG_ERROR log4cpp::Priority::ERROR
#endif // !AN_LOG_ERROR
#ifndef AN_LOG_WARN
#define AN_LOG_WARN log4cpp::Priority::WARN
#endif // !AN_LOG_WARN
#ifndef AN_LOG_NOTICE
#define AN_LOG_NOTICE log4cpp::Priority::NOTICE
#endif // !AN_LOG_NOTICE
#ifndef AN_LOG_INFO
#define AN_LOG_INFO log4cpp::Priority::INFO
#endif // !AN_LOG_INFO
#ifndef AN_LOG_DEBUG
#define AN_LOG_DEBUG log4cpp::Priority::DEBUG
#endif // !AN_LOG_DEBUG
#ifndef AN_LOG_NOTSET
#define AN_LOG_NOTSET log4cpp::Priority::NOTSET
#endif // !AN_LOG_NOTSET

#define LOG(__level) log4cpp::Category::getRoot() << log4cpp::Priority::__level << "\n\t" << __FILE__ << " " << __LINE__ << " "

inline void logger_init()
{
	// log4cpp::Appender *appender = new log4cpp::FileAppender("root", "/var/log/test.log");
	log4cpp::Appender *appender = new log4cpp::FileAppender("root", "test.log");
	// log4cpp::Appender *appender = new log4cpp::OstreamAppender("root", &std::cout);

	log4cpp::PatternLayout *patternLayout = new log4cpp::PatternLayout();
	patternLayout->setConversionPattern("%d [%p] - %m%n");

	appender->setLayout(patternLayout);

	log4cpp::Category &root = log4cpp::Category::getRoot();
	root.setPriority(log4cpp::Priority::NOTICE);
	root.addAppender(appender);
}

inline void logger_init(const char *log_path)
{
	// log4cpp::Appender *appender = new log4cpp::FileAppender("root", "/var/log/test.log");
	log4cpp::Appender *appender = new log4cpp::FileAppender("root", log_path);
	// log4cpp::Appender *appender = new log4cpp::OstreamAppender("root", &std::cout);

	log4cpp::PatternLayout *patternLayout = new log4cpp::PatternLayout();
	patternLayout->setConversionPattern("%d [%p] - %m%n");

	appender->setLayout(patternLayout);

	log4cpp::Category &root = log4cpp::Category::getRoot();
	root.setPriority(log4cpp::Priority::NOTICE);
	root.addAppender(appender);
}

inline void logger_init(const char *log_path, log4cpp::Priority::PriorityLevel p_level)
{
	// log4cpp::Appender *appender = new log4cpp::FileAppender("root", "/var/log/test.log");
	log4cpp::Appender *appender = new log4cpp::FileAppender("root", log_path);
	// log4cpp::Appender *appender = new log4cpp::OstreamAppender("root", &std::cout);

	log4cpp::PatternLayout *patternLayout = new log4cpp::PatternLayout();
	patternLayout->setConversionPattern("%d [%p] - %m%n");

	appender->setLayout(patternLayout);

	log4cpp::Category &root = log4cpp::Category::getRoot();
	// root.setPriority(log4cpp::Priority::NOTICE);
	root.setPriority(p_level);
	root.addAppender(appender);
}

inline void logger_init(log4cpp::Priority::PriorityLevel p_level)
{
	// log4cpp::Appender *appender = new log4cpp::FileAppender("root", "/var/log/test.log");
	// log4cpp::Appender *appender = new log4cpp::FileAppender("root", log_path);
	log4cpp::Appender *appender = new log4cpp::OstreamAppender("root", &std::cout);

	log4cpp::PatternLayout *patternLayout = new log4cpp::PatternLayout();
	patternLayout->setConversionPattern("%d [%p] - %m%n");

	appender->setLayout(patternLayout);

	log4cpp::Category &root = log4cpp::Category::getRoot();
	root.setPriority(p_level);
	root.addAppender(appender);
}

#endif // !_LOGGER_H_