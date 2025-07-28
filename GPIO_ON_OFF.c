// the idea is to locate the Green led on the STM32 F401RE board
// and turn it on or off using GPIO pins
//localisation : Port : A
//               Pin  : 5
#define PERIPH_BASE      (0X40000000UL)
#define AHB1PEIPH_OFFSET (0x00020000UL)
#define AHB1PERIPH_BASE  (PERIPH_BASE + AHB1PEIPH_OFFSET)
#define GPIOA_OFFSET     (0x0000UL)
#define GPIOA_BASE       (AHB1PERIPH_BASE + GPIOA_OFFSET) //since GPIOA is the first GPIO port 
#define RCC_OFFSET       (0x3800UL)// equivalent to 0x00003800UL in the STM32F401RE reference manual
#define RCC_BASE         (AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET  (0x30UL) // offset for RCC AHB1 peripheral clock enable register
#define RCC_AHB1EN_R     (*(volatile unsigned int *)(AHB1EN_R_OFFSET + RCC_BASE)) // RCC AHB1 peripheral clock enable register address

#define MODE_R_OFFSET    (0x00UL)
#define GPIOA_MODE_R     (*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))



#define OD_R_OFFSET      (0x14UL) // offset for GPIOA output data register
#define GPIOA_OD_R       (*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))// GPIOA output data register address
#define PIN5           (1U << 5) // bit 5 of GPIOA_ODR register corresponds to pin 5
#define LED_PIN         PIN5 // alias for better readability


#define GPIOAEN           (1U << 0) // 0x00000001u

int main(void) {

    // Enable the clock for GPIOA
    RCC_AHB1EN_R |= GPIOAEN;//   to set a specific pin to 1 , we use the or bitwise operator (|=)
    //example with real bits: x== 0x00010000U  so x |= 0x00000001U will result of 0x00010001U wo we set the bit 0 to 1
    // set PA5 as output by writing 01 to the mode register
    GPIOA_MODE_R |= (1u<< 10); // puts bit 10 to 1, which corresponds to PA5 in output mode
    GPIOA_MODE_R &= ~(1u << 11);// clears bit 11, which corresponds to PA5 in output mode

    while(1){
        GPIOA_OD_R |= LED_PIN; // turn on the LED by setting bit 5 of GPIOA_ODR
        //the |= operator sets only the fifth bit to 1, leaving other bits unchanged

    }
}

