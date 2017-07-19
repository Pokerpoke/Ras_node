#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>

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

#endif // !_LOGGER_H_