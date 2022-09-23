/* Includes ------------------------------------------------------------------*/
#include "string.h"

#include "FreeRTOSConfig.h"

#include "stm32l4xx_hal.h"

#include "main.h"

#include "FreeRTOS.h"

#include "timers.h"

#include "queue.h"

#include "led_control.h"
/* Private define ------------------------------------------------------------*/
extern char cmd_led_on[];
extern char cmd_led_off[];
extern char cmd_led_blink[];

extern xQueueHandle xLedCmdQueue;

TaskHandle_t xLedTask = NULL;
led_t Led;
/* Extern variables ---------------------------------------------------------*/

/* Private variables --------------------------------------------------------*/


/* Public Functions ---------------------------------------------------------*/

void led_on(void)
{
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
}


void led_off(void)
{
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
}

void led_toggle(void)
{
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}

void vCallbackSwTimerLed (TimerHandle_t xTimer)
{
	led_toggle();
}

void my_led_task(void)
{
	//static uint8_t flashSeries = 0;
//	static char buff[16] = {'\0'};
	uint8_t itemQReceive = 0;


	  xLedCmdQueue = xQueueCreate( 5, sizeof(Led.state) );
	  if (xLedCmdQueue != NULL)
	  {
	  	;
	  }
	  else
	  {
	  	; // Очередь не была создана.
	  }

	///xQueueReceive(xLedCmdQueue, &itemQReceive, pdMS_TO_TICKS(100));

	for(;;)
	{
		if (xQueueReceive(xLedCmdQueue, &itemQReceive, pdMS_TO_TICKS(100)) == pdPASS )
		{
			if ((led_state_t)itemQReceive == LED_ON)
			{
				if (Led.xSwTimerLed)
					xTimerStop(Led.xSwTimerLed, 0 );

				led_on();
			}

			else if ((led_state_t)itemQReceive == LED_OFF)
			{
				if (Led.xSwTimerLed)
					xTimerStop(Led.xSwTimerLed, 0 );

				led_off();
			}

			else if ((led_state_t)itemQReceive == LED_BLINK)
			{
				if (Led.xSwTimerLed == NULL)
				{
					Led.xSwTimerLed = xTimerCreate ("SwTimerLed", pdMS_TO_TICKS(300), pdTRUE, 0, my_led_flash_task);
					xTimerStart( Led.xSwTimerLed, 0 );
					led_off();
				}
				else
				{
					xTimerStart( Led.xSwTimerLed, 0);
				}
			}
		}
	}
}

void my_led_flash_task(void)
{
	static uint8_t flashSeries = 0;


	flashSeries++;
	if ((flashSeries & 1) == 0)
	{
		led_on();
	}
	else
	{
		if (flashSeries <= 5)
		{
			xTimerChangePeriod( Led.xSwTimerLed, pdMS_TO_TICKS(400), 100 );
		}
		else
		{
			flashSeries = 0;
			xTimerChangePeriod( Led.xSwTimerLed, pdMS_TO_TICKS(3000), 100 );
		}

		led_off();
	}
}
