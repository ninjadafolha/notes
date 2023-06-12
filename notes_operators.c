// && is a logical AND operator
// & is a bitwise AND operator
/*

char A = 40;
char B = 30;
char C;

C = A & B; //AND
A 00101000
B 00011110
  --------
C 00001000

C = A || B; //OR
A 00101000
B 00011110
  --------
C 00111110

C = !A;
A 00101000
  --------
C 11010111

C = A ^ B; //XOR
A 00101000
B 00011110
  --------
C 00110110

 In embedded C, most of the time will be doing
- Testing of bits (&)
- Setting of bits (|)
- Clearing of bits (~ and &)
- T0ggling of bits (^)

*/


int main(void){
    int A = 1;
    int B = 2:

    printf("%d", &(A&B));
    printf("%d", &(A|B));
    printf("%d", &(A^B));
    printf("%d", &(~A));
}

/*
Bit-Masking
[input] number     00101110
[mask]  mask_value 00000001
                   --------
[output]           00000000

Use and operation to test even and odd

if(number & 1){
    print(number odd)
}else{
    print(number even)
}

*/

int main(void){
    int32_t number = 5;

    if(number & 1){
        printf("number is odd");
    }else{
        printf("number is even");
    }
}

// & is used to TEST and CLEAR
// | is used to SET

uint32_t number, output;
output = number | (number_to_set_bits);

/*

Toggling of bits

Led_state = Led_state ^ 0x01

Led_state 00000001
[mask]    00000001
------------------
Led_state 00000000
[mask]    00000001
------------------
Led_state 00000001
...

*/

/*
    HARDWARE CONNECTION

    PD12 (green)  = LED4
    PD13 (orange) = LED3
    PD14 (red)    = LED5
    PD15 (blue)   = LED6

    What is a port? Each port has 16 pins where you can connect external peripherals

    To control pin use GPIO D Peripheral -> It also has set of registers which are used to control pin's mode.
    You can access this registers using memory address.

    What are processor addresseble memory location?

    ARM Cortex     Data Memory      Code Memory
        |               |                  |
    <----------- System bus (AHB) ----------->
        |           |           |          |
      GPIOD      TIMERS        ADC        I2C

    Since address bus width is 32 bits,
    Processor put address ranging from 0x0000_0000 to 0xFFFF_FFFF on the adress bus

    Memory Map of ARM Cortex Mx Processor

    ------------------------------------ 0xFFFFFFFF
    |              System               |
    ------------------------------------ 0xE0100000
    | Private peripheral bus - External |
    ------------------------------------ 0xE0040000
    | Private peripheral bus - Internal |
    ------------------------------------ 0xE0000000
    |          External Device          |
    ------------------------------------ 0xA0000000
    |          External RAM             |
    ------------------------------------ 0x60000000
    |           Peripheral              |
    ------------------------------------ 0x40000000
    |               SRAM                |
    ------------------------------------ 0x20000000
    |               Code                |
    ------------------------------------ 0x00 

    GPIOD: 0x4002 0C00 - 0x4002 0FFF

    How to enable the peripheral clock?
    - Use the peripheral clock control registers 
    - 0x4002 3800 + 0x30 and set 3 bit position (GPIODEN)
        - 0x40023830
    - for pin 12 looking at fields 24 and 25
        - 0x40020C00 + 0x00 ==> 0x40020C00
    - 0x40020C00 + 0x14 ==> 0x40020C14

    uint32_t* enable_clock = 0x40023830;
    uint32_t* enable_port  = 0x40020C00;
    uint32_t* set_high     = 0x40020C14;
*/

#include<stdint.h>

int main(void){
    uint32_t *enable_clock = (uint32_t*)0x40023830;
    uint32_t *enable_mode  = (uint32_t*)0x40020C00;
    uint32_t *set_high     = (uint32_t*)0x40020C14;

    //1. enable the clock for GPIOD peripheral in the AHN1ENR
    //*enable_clock = *enable_clock | 0x08;
    // can use short notation of the above
    *enable_clock |= 0x08;

    //2. configure the mode of the IO pin as output
    //a. clear the 24th and 25th bit positions
    *enable_mode &= 0xFCFFFFFF;
    //b. make 24th and 25th as 1 (SET)
    *enable_mode |= 0x01000000;

    //3. Set 12th bit of the output data register to make I/O pin-12 as HIGH
    *set_high |= 0x1000;
    
    while(1);
}

/*
*   Bitwise Operators 

    Right shift operator (>>)
    ex.:
    char a = 111;
    char b = a >> 4;
    writing in binary a = 01101111
    a >> 1 = 00110111
    a >> 2 = 00011011
    a >> 3 = 00001101
    a >> 4 = 00000110 so 
    b = 00000110 (0x06)

    Left shift operator (<<0)
    ex.: same values as before
    a << 1 = 11011110
    a << 2 = 10111100
    a << 3 = 01111000
    a << 4 = 11110000 
    b = 11110000 (0xF0 or 240)

    Use the shift operator to set the 4th bit
    -> shift the number by the number you want to set so 1 << 4
    In that way you can find the mask value, then
    if Data = 0x08
    Data = Data | (1<<4) = 0x18;

    Use the shift operator to clear the 4th bit
    -> Use same structure as before and then negate the mask
    if Data = 0x18;
    Data = Data & ~(1 << 4) = 0x08;
    
*/


//rewrite the previous program to turn on Led
#include<stdint.h>

int main(void){
    uint32_t *enable_clock = (uint32_t*)0x40023830;
    uint32_t *enable_mode  = (uint32_t*)0x40020C00;
    uint32_t *set_high     = (uint32_t*)0x40020C14;

    //1. enable the clock for GPIOD peripheral in the AHN1ENR
    //*enable_clock = *enable_clock | 0x08;
    // can use short notation of the above
    *enable_clock |= (1 << 3);

    //2. configure the mode of the IO pin as output
    //a. clear the 24th and 25th bit positions
    *enable_mode &= ~( 3 << 24); // 3 in binary is 11 cleaning 24 and 25
    //b. make 24th as 1 (SET)
    *enable_mode |= (1 << 24);

    //3. Set 12th bit of the output data register to make I/O pin-12 as HIGH
    *set_high |= (1 << 12);
    
    while(1);
}

/*
    Extract Bit
    Data = 1011010000010000
    1) first shift it by 9 (>>9)
    Data = 0000000001011010
    2) Mas the new value
    Data   = 0000000001011010
    mask   = 0000000000111111
    output = 0000000000011010

    uint16_t Data = 0xB410;
    uint8_t output;

    output = (uint8_t)((Data >> 9) & 0x003F)
*/

/*
    TYPE QUALIFIERS IN C

    - const
    - volatile

    1) const is a type qualifier used to enforce read-only feature on variables.
    uint8_t data1 = 10;
    data1 = 50; //allowed

    uint8_t const data2 = 10;
    data2 = 50; //compile-time-error

    const uint8_t data = 10; -> I prefer this method
    uint8_t const data = 10; 

    -> you can still modify the content of the variable by using its address 

*/

int main(void){
    const uint8_t data = 10;

    data = 50; //it will show an error

    uint8_t *ptr = (uint8_t*)&data; //cast needed to transforme to uint8_t * 
    *ptr = 50; // this is allowed
    
}

//modifying a global const will show and error once it will be placed in the read-only section of the memory

/*
uint8_t const *pData = (uint8_t*) 0x40000000;
-> here the pointer pData is modifiable but the data pointed by the pData cannot be modified.
Allowed:
pData = (uint8_t*) 0x50000000;
pData = (uint8_t*) 0x60000000;
pData = (uint8_t*) 0x70000000;

Not Allowed:
*pData = 50;


uint8_t *const pData = (uint8_t *) 0x40000000;
-> Pointer pData is read-only but the data pointed by pData can be modified.
-> pData is a read only pointer pointing to modifiable data

Not allowed:
pData = (uint8_t*)0x50000000;
Allowed:
*pData = 50;

uint8_t const *const pData = (uint8_t*)0x40000000;
-> pointer pData is read-only and the data pointed by pData is also read-only.
ex.: read status register (you should not change anything inside the state register)

*/


// IMPLEMENT BLINKING LED BY ACCESSING THE REGISTERS
#include<stdint.h>

int main(void){

    uint32_t *pClkCtrlReg   = (uint32_t*)0x40023830;
    uint32_t *pPortDModeReg = (uint32_t*)0x40020C00;
    uint32_t *pPortDOutReg  = (uint32_t*)0x40020C14;

    uint32_t *pPortAModeReg = (uint32_t*)0x40020000; 
    uint32_t *pPortAInReg   = (uint32_t*)0x40020010;

    //1. enable the clock for GPIOD, GPIOA peripherals in the AHN1ENR
    //*enable_clock = *enable_clock | 0x08;
    // can use short notation of the above
    *pClkCtrlReg |= (1 << 3);
    *pClkCtrlReg |= (1 << 0);

    //2. configure the mode of the IO pin as output
    //a. clear the 24th and 25th bit positions
    //configuring PD12 as output
    *pPortDModeReg &= ~( 3 << 24); // 3 in binary is 11 cleaning 24 and 25
    //b. make 24th as 1 (SET)
    *pPortDModeReg |= (1 << 24);

    //configure PA0 as input (GPIOA MODE REGISTER)
    *pPortAModeReg &= ~(3<<0);
    uint8_t pinStatus = (uint8_t)(*pPortAInReg & 0x1);

    while(){
        if(pinStatus){
            // turn on LED
            *pPortDOutReg |= (1 << 12);

        }else{
            // turn off LED
            *pPortDOutReg &= ~(1 << 12);
        }
    }
    
    //3. Set 12th bit of the output data register to make I/O pin-12 as HIGH
    //*set_high |= (1 << 12);
    
}

/*
    OPTIMIZATION AND VOLATILE QUALIFIER
    you can supply: -O0, -O1, -O2, -O3

    -> Use to instruct the compiler not to invoke any optimazation on the variable operation.
    Ex.:
    uint8_t volatile data1;
    uint8_t volatile data2;
    
    data1 = 50;
    data1 = data2;

    Use volatile when your code is dealing with:
    1- memory-mapped peripheral registers of the MCU
    2- Multiple tasks accessing global variables(read/write) in an RTOS multithread application
    3- When a global variable is used to share data between the main code and an ISR code.

    case 1: volatile data
    volatile uint8_t my_data;

    case 2: non-volatile pointer to volatile data
    uint8_t volatile *pStatusReg;
    - This is a perfect case of accessing memory-mapped registers.

    case 3: volatile pointer to non-volatile data
    uint8_t *volatile pStatusReg;
    case 4: volatile pointer to volatile data
    uint8_t volatile *volatile pSatatusReg;

*/


// FIXING THE CODE FOR A -O2 OPTIMIZATION
#include<stdint.h>

int main(void){

    uint32_t volatile *pClkCtrlReg   = (uint32_t*)0x40023830;
    uint32_t volatile *pPortDModeReg = (uint32_t*)0x40020C00;
    uint32_t volatile *pPortDOutReg  = (uint32_t*)0x40020C14;

    uint32_t volatile *pPortAModeReg = (uint32_t*)0x40020000; 
    uint32_t volatile *pPortAInReg   = (uint32_t*)0x40020010;

    //1. enable the clock for GPIOD, GPIOA peripherals in the AHN1ENR
    //*enable_clock = *enable_clock | 0x08;
    // can use short notation of the above
    *pClkCtrlReg |= (1 << 3);
    *pClkCtrlReg |= (1 << 0);

    //2. configure the mode of the IO pin as output
    //a. clear the 24th and 25th bit positions
    //configuring PD12 as output
    *pPortDModeReg &= ~( 3 << 24); // 3 in binary is 11 cleaning 24 and 25
    //b. make 24th as 1 (SET)
    *pPortDModeReg |= (1 << 24);

    //configure PA0 as input (GPIOA MODE REGISTER)
    *pPortAModeReg &= ~(3<<0);
    
    while(){
        //read the pin status of the pin PA0
        uint8_t pinStatus = (uint8_t)(*pPortAInReg & 0x1);
        if(pinStatus){
            // turn on LED
            *pPortDOutReg |= (1 << 12);

        }else{
            // turn off LED
            *pPortDOutReg &= ~(1 << 12);
        }
    }
    
    //3. Set 12th bit of the output data register to make I/O pin-12 as HIGH
    //*set_high |= (1 << 12);
    
}

/*
    UNIONS 

    A union is similar to a structure except all its members start at the same location in memory

    struct address{
        uint16_t shortAddr;
        uint32_t longAddr;
    };

    union address{
        uint16_t shortAddr;
        uint32_t longAddr;
    }

    helps to save memory, ex.: when implementing RX TX 
*/