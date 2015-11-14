#ifndef LOG_H
#define LOG_H

// enable to see logs
#define LOG_ENABLED

// available log levels
#define LOG_LEVEL_NONE 0x0
#define LOG_LEVEL_INFO 0x1
#define LOG_LEVEL_WARNING 0x2
#define LOG_LEVEL_ERROR 0x4
#define LOG_LEVEL_ALL 0xFFFFFFFF

// current log level
#define LOG_LEVEL (LOG_LEVEL_INFO | LOG_LEVEL_ERROR)

// helper
#define LOG_HAS_LEVEL(level) (((LOG_LEVEL & level) == level) ? TRUE : FALSE)

// core
#ifdef LOG_ENABLED
#define LOG(type, message) std::cout << type << " - File: " << __FILE__ << "\nLine: " << __LINE__ << "\nMessage: " << message << std::endl << std::endl;
#define LOG2(type, message, code) std::cout << type << " - File: " << __FILE__ << "\nLine: " << __LINE__ << "\nMessage: " << message << "\nCode: " << code << std::endl << std::endl;
#define LOG_INFO(message) if (LOG_HAS_LEVEL(LOG_LEVEL_INFO)) { LOG("Info", message); }
#define LOG_INFO_EX(message, code) if (LOG_HAS_LEVEL(LOG_LEVEL_INFO)) { LOG2("Info", message, code); }
#define LOG_WARNING(message) if (LOG_HAS_LEVEL(LOG_LEVEL_WARNING)) { LOG("Warning", message); }
#define LOG_WARNING_EX(message, code) if (LOG_HAS_LEVEL(LOG_LEVEL_WARNING)) { LOG2("Warning", message, code); }
#define LOG_ERROR(message) if (LOG_HAS_LEVEL(LOG_LEVEL_ERROR)) { LOG("Error", message); }
#define LOG_ERROR_EX(message, code) if (LOG_HAS_LEVEL(LOG_LEVEL_ERROR)) { LOG2("Error", message, code); }
#else
#define LOG(type, message)
#define LOG2(type, message, code)
#define LOG_INFO(message)
#define LOG_INFO_EX(message, code)
#define LOG_WARNING(message)
#define LOG_WARNING_EX(message, code)
#define LOG_ERROR(message)
#define LOG_ERROR_EX(message, code)
#endif

#endif // LOG_H