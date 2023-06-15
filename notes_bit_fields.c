/*
    RCC AHB1 peripheral clock enable register (RCC_AHB1ENR)

    struct with bit-field
*/

typedef struct{
    uint32_t gpioa_en:1;
    uint32_t gpiob_en:1;
    uint32_t gpioc_en:1;
    uint32_t gpiod_en:1;
    uint32_t gpioe_en:1;
    uint32_t gpiof_en:1;
    uint32_t gpiog_en:1;
    uint32_t gpioh_en:1;
    uint32_t gpioi_en:1;
    uint32_t reserved1:3;
    uint32_t CRCE:1;
    uint32_t reserved2:5;
    uint32_t BKPSRAMEN:1;
    uint32_t reserved3:1;
    ...continue
}RCC_AHB1ENR_t;

typedef struct 
{
    /* data */
    ... do the same as before
}GPIOx_MODE_t;

/* way to access these structure*/

GPIOx_MODE_t *pGpioMode;
pGpioMode = (GPIOx_MODE_t*) 0x40020C00;

