#include "delay.h"

static unsigned volatile int Ticks, DelayCount;
void SysTick_Handler(void)  
{                               /* SysTick interrupt Handler. */
  Ticks++;     
	DelayCount++;
}

unsigned int mills(void)
{
	return Ticks;
}

void sysTickInit(void)
{
	uint32_t returnCode;
  returnCode = SysTick_Config(SystemCoreClock / AUTO_RELOAD_VALUE);     
	/* Configure SysTick to generate an interrupt every millisecond */
  
  if (returnCode != 0)  {         /* Check return code for errors */
    // Error Handling 
  }
}

void _delay_ms(uint32_t delay)
{
	DelayCount = 0;
	while(1)
	{
		if(DelayCount == delay) break;
	}
}
