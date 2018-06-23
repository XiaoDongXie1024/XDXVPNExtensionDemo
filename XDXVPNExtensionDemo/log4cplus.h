
#ifndef XDX_IOS
#define XDX_IOS
#endif

int XDX_IOS_FLAG_FATAL  = 0x10;
int XDX_IOS_FLAG_ERROR  = 0x08;
int XDX_IOS_FLAG_WARN   = 0x04;
int XDX_IOS_FLAG_INFO   = 0x02;
int XDX_IOS_FLAG_DEBUG  = 0x01;

int XDX_IOS_LOG_LEVEL   = XDX_IOS_FLAG_DEBUG|XDX_IOS_FLAG_INFO|XDX_IOS_FLAG_WARN|XDX_IOS_FLAG_ERROR|XDX_IOS_FLAG_FATAL;;


#ifndef _LOG4CPLUS_H_
#define _LOG4CPLUS_H_

#ifdef WIN32
#ifndef FD_SETSIZE
#define FD_SETSIZE 1024
#endif
#endif //  WIN32

#include <cstdio>
#include <cstring>

#if (defined (_MSC_VER) && _MSC_VER >= 1900) || (defined(__cplusplus) && __cplusplus>= 201103L)
#define __STDC_FORMAT_MACROS
#include <cinttypes>
#endif

#define LOG4CPLUS_DISABLE_DLL_RUNTIME_WARNING
#define LOG4CPLUS_STATIC

#ifdef XDX_ANDROID
#include <android/log.h>
#ifndef LOG_TAG
#define  LOG_TAG    "XDXJNI"
#endif
//#define ANDROID_DEBUG 1
extern int XDX_ANDROID_LOG_LEVEL;
extern int XDX_ANDROID_FLAG_FATAL;
extern int XDX_ANDROID_FLAG_ERROR;
extern int XDX_ANDROID_FLAG_WARN;
extern int XDX_ANDROID_FLAG_INFO;
extern int XDX_ANDROID_FLAG_DEBUG;

class XDXLog{
public:
    static void Init(void * configuration = NULL){}
    static void Destroy(){}
};

#define LOGF(...)  \
do {    \
if (XDX_ANDROID_LOG_LEVEL & XDX_ANDROID_FLAG_FATAL) {    \
__android_log_print(ANDROID_LOG_FATAL,LOG_TAG,__VA_ARGS__);    \
}    \
} while(0)
#define  LOGE(...)  \
do {    \
if (XDX_ANDROID_LOG_LEVEL & XDX_ANDROID_FLAG_ERROR) {    \
__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__);    \
}    \
} while(0)
#define  LOGW(...)  \
do {    \
if (XDX_ANDROID_LOG_LEVEL & XDX_ANDROID_FLAG_WARN) {    \
__android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__);    \
}    \
} while(0)
#define LOGI(...)  \
do {    \
if (XDX_ANDROID_LOG_LEVEL & XDX_ANDROID_FLAG_INFO) {    \
__android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__);    \
}    \
} while(0)
#define LOGD(...)  \
do {    \
if (XDX_ANDROID_LOG_LEVEL & XDX_ANDROID_FLAG_DEBUG) {    \
__android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__);    \
}    \
} while(0)
#define LOGV(...)  \
do {    \
__android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__);    \
} while(0)

#define DEBUG_PRINTF(...)  \
do {    \
if (XDX_ANDROID_LOG_LEVEL & XDX_ANDROID_FLAG_DEBUG) {    \
__android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__);    \
}    \
} while(0)
#define  ALWAYS_PRINTF(...)  \
do {    \
__android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__);    \
} while(0)





#define log4cplus_fatal(category, ...) \
do { \
if (XDX_ANDROID_LOG_LEVEL & XDX_ANDROID_FLAG_FATAL) {    \
__android_log_print(ANDROID_LOG_FATAL,category,__VA_ARGS__); \
}    \
}while(0)

#define log4cplus_error(category, ...) \
do { \
if (XDX_ANDROID_LOG_LEVEL & XDX_ANDROID_FLAG_ERROR) {    \
__android_log_print(ANDROID_LOG_ERROR,category,__VA_ARGS__); \
}    \
}while(0)

#define log4cplus_warn(category, ...) \
do { \
if (XDX_ANDROID_LOG_LEVEL & XDX_ANDROID_FLAG_WARN) {    \
__android_log_print(ANDROID_LOG_WARN,category,__VA_ARGS__); \
}    \
}while(0)

#define log4cplus_info(category, ...) \
do { \
if (XDX_ANDROID_LOG_LEVEL & XDX_ANDROID_FLAG_INFO) {    \
__android_log_print(ANDROID_LOG_INFO,category,__VA_ARGS__); \
}    \
}while(0)

#define log4cplus_debug(category, ...) \
do { \
if (XDX_ANDROID_LOG_LEVEL & XDX_ANDROID_FLAG_DEBUG) {    \
__android_log_print(ANDROID_LOG_DEBUG,category,__VA_ARGS__); \
}    \
}while(0)

inline void log4cplus_init(const char* configuration = NULL){}
inline void log4cplus_destroy(){}

#define LOG4CPLUS_ERROR_STR(...) (void)0
#define LOG4CPLUS_WARN_STR(...) (void)0
#define LOG4CPLUS_INFO_STR(...) (void)0
#define LOG4CPLUS_DEBUG_STR(...) (void)0

#elif defined(XDX_NOT_USED)
#include <log4cplus/logger.h>
#include <log4cplus/tchar.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/helpers/sleep.h>
#include <log4cplus/loggingmacros.h>

static log4cplus::ConfigureAndWatchThread* configureThread = NULL;
static log4cplus::Logger main_logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("misc"));

inline void log4cplus_init( const log4cplus::tchar * configuration = NULL)
{
    log4cplus::initialize ();
    log4cplus::helpers::LogLog::getLogLog()->setInternalDebugging(false);
    log4cplus::Logger root = log4cplus::Logger::getRoot();
    try
    {
        if (!configureThread)
        {
            configureThread = new log4cplus::ConfigureAndWatchThread(
                                                                     (configuration ? configuration : LOG4CPLUS_TEXT("log4cplus.properties")),
                                                                     5 * 1000);
        }
    }
    catch(...) {
    }
}

inline void log4cplus_destroy()
{
    if(configureThread) {
        delete configureThread;
        configureThread = NULL;
    }
    log4cplus::Logger::shutdown();
    log4cplus::threadCleanup();
}

#define log4cplus_fatal(category, logFmt, ...) \
do { \
LOG4CPLUS_FATAL_FMT(main_logger, logFmt, ##__VA_ARGS__); \
}while(0)

#define log4cplus_error(category, logFmt, ...) \
do { \
LOG4CPLUS_ERROR_FMT(main_logger, logFmt, ##__VA_ARGS__); \
}while(0)

#define log4cplus_warn(category, logFmt, ...) \
do { \
LOG4CPLUS_WARN_FMT(main_logger, logFmt, ##__VA_ARGS__); \
}while(0)

#define log4cplus_info(category, logFmt, ...) \
do { \
LOG4CPLUS_INFO_FMT(main_logger, logFmt, ##__VA_ARGS__); \
}while(0)

#define log4cplus_debug(category, logFmt, ...) \
do { \
LOG4CPLUS_DEBUG_FMT(main_logger, logFmt, ##__VA_ARGS__); \
}while(0)

///////////////////MAC ABOVE////////////////////////////////
#elif defined(XDX_IOS)
#include <syslog.h>

extern int XDX_IOS_LOG_LEVEL;
extern int XDX_IOS_FLAG_FATAL;
extern int XDX_IOS_FLAG_ERROR;
extern int XDX_IOS_FLAG_WARN;
extern int XDX_IOS_FLAG_INFO;
extern int XDX_IOS_FLAG_DEBUG;
class XDXLog{
public:
    static void Init(void * configuration = NULL){}
    static void Destroy(){}
};

#define log4cplus_fatal(category, logFmt, ...) \
do { \
if(XDX_IOS_LOG_LEVEL & XDX_IOS_FLAG_FATAL) \
syslog(LOG_CRIT, "%s:" logFmt, #category,##__VA_ARGS__); \
}while(0)

#define log4cplus_error(category, logFmt, ...) \
do { \
if(XDX_IOS_LOG_LEVEL & XDX_IOS_FLAG_ERROR) \
syslog(LOG_ERR, "%s:" logFmt, #category,##__VA_ARGS__); \
}while(0)

#define log4cplus_warn(category, logFmt, ...) \
do { \
if(XDX_IOS_LOG_LEVEL & XDX_IOS_FLAG_WARN) \
syslog(LOG_WARNING, "%s:" logFmt, #category,##__VA_ARGS__); \
}while(0)

#define log4cplus_info(category, logFmt, ...) \
do { \
if(XDX_IOS_LOG_LEVEL & XDX_IOS_FLAG_INFO) \
syslog(LOG_WARNING, "%s:" logFmt, #category,##__VA_ARGS__); \
}while(0)

#define log4cplus_debug(category, logFmt, ...) \
do { \
if(XDX_IOS_LOG_LEVEL & XDX_IOS_FLAG_DEBUG) \
syslog(LOG_WARNING, "%s:" logFmt, #category,##__VA_ARGS__); \
}while(0)

inline void log4cplus_init(const char* configuration = NULL){
    openlog("XDXTransporterT", LOG_NDELAY|LOG_PID|LOG_CONS, LOG_USER);
}

inline void log4cplus_destroy(){
    closelog();
}

#elif defined(XDX_MAC)
#include <syslog.h>

extern int XDX_MAC_LOG_LEVEL;
extern int XDX_MAC_FLAG_FATAL;
extern int XDX_MAC_FLAG_ERROR;
extern int XDX_MAC_FLAG_WARN;
extern int XDX_MAC_FLAG_INFO;
extern int XDX_MAC_FLAG_DEBUG;

class XDXLog{
public:
    static void Init(void * configuration = NULL){}
    static void Destroy(){}
};


#define log4cplus_fatal(category, logFmt, ...) \
do { \
if(XDX_MAC_LOG_LEVEL & XDX_MAC_FLAG_FATAL) \
syslog(LOG_CRIT, "<Critical:> %s:" logFmt, #category,##__VA_ARGS__); \
}while(0)

#define log4cplus_error(category, logFmt, ...) \
do { \
if(XDX_MAC_LOG_LEVEL & XDX_MAC_FLAG_ERROR) \
syslog(LOG_ERR, "<Error:> %s:" logFmt, #category,##__VA_ARGS__); \
}while(0)

#define log4cplus_warn(category, logFmt, ...) \
do { \
if(XDX_MAC_LOG_LEVEL & XDX_MAC_FLAG_WARN) \
syslog(LOG_WARNING, "<Warning:> %s:" logFmt, #category,##__VA_ARGS__); \
}while(0)

#define log4cplus_info(category, logFmt, ...) \
do { \
if(XDX_MAC_LOG_LEVEL & XDX_MAC_FLAG_INFO) \
syslog(LOG_WARNING, "<Info:> %s:" logFmt, #category,##__VA_ARGS__); \
}while(0)

#define log4cplus_debug(category, logFmt, ...) \
do { \
if(XDX_MAC_LOG_LEVEL & XDX_MAC_FLAG_DEBUG) \
syslog(LOG_WARNING, "<Debug:> %s:" logFmt, #category,##__VA_ARGS__); \
}while(0)

inline void log4cplus_init(const char* configuration = NULL){
    openlog("XDXTransporterT", LOG_NDELAY|LOG_PID|LOG_CONS, LOG_USER);
}

inline void log4cplus_destroy(){
    closelog();
}

#else
#include <log4cplus/logger.h>
#include <log4cplus/tchar.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/helpers/sleep.h>
#include <log4cplus/loggingmacros.h>
#include <fstream>
//safe version for multiply .so/.dll in one process
class XDXLog
{
private:
    static log4cplus::ConfigureAndWatchThread * getConfigureThreads(const log4cplus::tchar * configFileName = NULL)
    {
        static log4cplus::ConfigureAndWatchThread * watchDog = NULL;
        if (!watchDog)
        {
            const log4cplus::tchar * sFileName = configFileName ? configFileName : LOG4CPLUS_TEXT("log4cplus.properties");
            watchDog = new log4cplus::ConfigureAndWatchThread(sFileName, 1 * 1000);
        }
        
        return watchDog;
    }
    
    static int & getCounter()
    {
        static int counter = 0;
        return counter;
    }
    
public:
    static void Init(const log4cplus::tchar * configuration = NULL)
    {
        if (getCounter()++ == 0)
        {
            log4cplus::initialize();
            log4cplus::helpers::LogLog::getLogLog()->setInternalDebugging(false);
            log4cplus::Logger::getRoot();
            getConfigureThreads(configuration);
            
            std::ofstream output("log4cplustest.log", std::ios::app);
            output << __FILE__ << ":" << __LINE__ << ":" << "log4cplus::initialize " << getCounter() << std::endl;
            output.close();
        }
    }
    
    static void Destroy()
    {
        if (--getCounter() == 0)
        {
            std::ofstream output("log4cplustest.log", std::ios::app);
            output << __FILE__ << ":" << __LINE__ << ":" << "log4cplus::shutdown " << getCounter() << std::endl;
            output.close();
            
            if (log4cplus::ConfigureAndWatchThread * watchDog = getConfigureThreads())
            {
                delete watchDog;
                watchDog = NULL;
            }
            log4cplus::Logger::shutdown();
            log4cplus::threadCleanup();
        }
    }
};

#define log4cplus_fatal(category, logFmt, ...) \
do { \
log4cplus::Logger logger =  log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(category)); \
LOG4CPLUS_FATAL_FMT(logger, logFmt, ##__VA_ARGS__); \
}while(0)

#define log4cplus_error(category, logFmt, ...) \
do { \
log4cplus::Logger logger =  log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(category)); \
LOG4CPLUS_ERROR_FMT(logger, logFmt, ##__VA_ARGS__); \
}while(0)

#define log4cplus_warn(category, logFmt, ...) \
do { \
log4cplus::Logger logger =  log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(category)); \
LOG4CPLUS_WARN_FMT(logger, logFmt, ##__VA_ARGS__); \
}while(0)

#define log4cplus_info(category, logFmt, ...) \
do { \
log4cplus::Logger logger =  log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(category)); \
LOG4CPLUS_INFO_FMT(logger, logFmt, ##__VA_ARGS__); \
}while(0)

#define log4cplus_debug(category, logFmt, ...) \
do { \
log4cplus::Logger logger =  log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(category)); \
LOG4CPLUS_DEBUG_FMT(logger, logFmt, ##__VA_ARGS__); \
}while(0)
#endif
#endif
