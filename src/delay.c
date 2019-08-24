#include "../../RTOS_TEST/inc/delay.h"

// For store tick counts in us
static __IO uint32_t usTicks;

// SysTick_Handler function will be called every 1 us
void SysTick_Handler() {
	if (usTicks != 0) usTicks--;
}

void DelayInit() {
	// Update SystemCoreClock value
	SystemCoreClockUpdate();
	// Configure the SysTick timer to overflow every 1 us
	// SysTick_Config(72MHz / 1M)-> 72. CPU speed is 72MHZ thus 72/72MHz = 1uS
	SysTick_Config(SystemCoreClock / 1000000); // System core clock is 72MHz, this is divided by 1MHz
}

void DelayUs(uint32_t us) {
	// Reload us values
	usTicks = us;
	// Wait until usTicks reach Zero
	while(usTicks);
}

void DelayMs(uint32_t ms) {
	// Wait until ms reach zero
	while(ms--) DelayUs(1000);
	
}
