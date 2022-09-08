
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LOGGER_H
#define __LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	LOG_LEVEL_DEBUG,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARN,
	LOG_LEVEL_ERROR,

}LogLevel_t;


#define LOG_DEBUG(format, ...) \
		logger_print(LOG_LEVEL_DEBUG, format, ##__VA_ARGS__);

#define LOG_INFO(format, ...) \
		logger_print(LOG_LEVEL_INFO, format, ##__VA_ARGS__);

#define LOG_WARN(format, ...) \
		logger_print(LOG_LEVEL_WARN, format, ##__VA_ARGS__);

#define LOG_ERROR(format, ...) \
		logger_print(LOG_LEVEL_WARN, format, ##__VA_ARGS__);

int logger_init(void);

int logger_print(LogLevel_t logLevel, char* format, ...);


#ifdef __cplusplus
}
#endif

#endif /* __LOGGER_H */
