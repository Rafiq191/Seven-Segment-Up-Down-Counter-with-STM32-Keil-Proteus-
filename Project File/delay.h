#include "stm32f4xx.h"                  // Device header
#define AUTO_RELOAD_VALUE 1000

void _delay_ms(unsigned int delay);
void sysTickInit(void);
void SysTick_Handler(void);
unsigned int mills(void);
