#include "stm32f4xx.h"
#include "delay.h"

// Dummy delay function
void delay(int count);
void delay(int count) {
    for (int i = 1; i <= count; i++) {
    }
}

//_______________________________
void displayDigit(int digit);
void displayDigit(int digit) {
    // Define a lookup table for segment values (for common cathode display)
    const uint8_t segmentValues[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

    // Set corresponding GPIO pins based on the segment value
    GPIOA->ODR |= (segmentValues[digit] << GPIO_ODR_OD0_Pos);

    // Delay
    _delay_ms(250);

    // Clear all GPIO pins
    GPIOA->ODR &= ~(0x7F << GPIO_ODR_OD0_Pos);

    // Delay
    _delay_ms(250);
}
//_______________________________

int main(void) {
    SystemCoreClockUpdate();
    sysTickInit();

    // Enable the clock for GPIOA and GPIOB
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN; 

    // Configure GPIOA pins as output for the seven-segment display
    GPIOA->MODER |= GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0 | GPIO_MODER_MODE2_0 |
                    GPIO_MODER_MODE3_0 | GPIO_MODER_MODE4_0 | GPIO_MODER_MODE5_0 |
                    GPIO_MODER_MODE6_0;

    // Configure GPIOB pins as input for the buttons
    GPIOB->MODER &= ~(GPIO_MODER_MODE1_1 | GPIO_MODER_MODE2_1);

    while (1) {
        // Check if Button Button1 is pressed
        if (GPIOB->IDR & GPIO_IDR_ID1) {
            // Display digits 0 to 9
            for (int digit = 0; digit <= 9; digit++) {
                displayDigit(digit);
            }
        }

        // Check if Button B2 is pressed
        if (GPIOB->IDR & GPIO_IDR_ID2) {
            // Display digits 9 to 0
            for (int digit = 9; digit >= 0; digit--) {
                displayDigit(digit);
            }
        }
    }
}
