
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_CONTROL_H
#define __LED_CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	LED_ON,
	LED_OFF,
	LED_BLINK
} led_state_t;

typedef struct {
	TimerHandle_t xSwTimerLed;
	led_state_t state;
}led_t;

void led_on(void);

void led_off(void);

void led_toggle(void);

void vCallbackSwTimerLed (TimerHandle_t xTimer);

void my_led_task(void);

#ifdef __cplusplus
}
#endif

#endif /* __LED_CONTROL_H */
