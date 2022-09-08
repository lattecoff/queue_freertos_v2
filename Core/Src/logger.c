/* Includes ------------------------------------------------------------------*/

#include "logger.h"

#include <stdbool.h>
#include <stdint.h>

#include <stdarg.h>

#include <stdio.h>


#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "stm32l4xx_hal.h"

/* Private define ------------------------------------------------------------*/

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[97m"

#define ANSI_COLOR_RESET   "\x1b[0m"

/* Extern variables ---------------------------------------------------------*/
extern UART_HandleTypeDef huart2;

/* Private variables --------------------------------------------------------*/
static SemaphoreHandle_t locker = NULL;
static uint32_t log_counter = 0;

static bool lock(void)
{

	return false;
}

static void unlock(void)
{

}


int logger_init(void)
{
	return -1;
}

int __io_putchar(int ch)
{
	HAL_UART_Transmit(&huart2, (uint8_t*) &ch, 1, 5);

	return 1;
}


int logger_print(LogLevel_t logLevel, char* format, ...)
{
	int res = -1;

	va_list list;
	va_start(list, format);

	if (lock())
	{
		char* color = NULL;

		printf("[%u][%u]", (unsigned int) log_counter, (unsigned int) xTaskGetTickCount());

		switch(logLevel)
		{
		case LOG_LEVEL_DEBUG:
			color = ANSI_COLOR_GREEN;
			break;
		case LOG_LEVEL_INFO:
			color = ANSI_COLOR_WHITE;
			break;
		case LOG_LEVEL_WARN:
			color = ANSI_COLOR_YELLOW;
			break;
		case LOG_LEVEL_ERROR:
			color = ANSI_COLOR_RED;
			break;
		default:
			color = ANSI_COLOR_RESET;
			break;
		}
		printf("%s", color);

		vprintf(format, list);
		va_end(list);

		printf(ANSI_COLOR_RESET);

		printf("\r\n");

		++log_counter;

		res = 0;

		unlock();
	}

	return res;
}
