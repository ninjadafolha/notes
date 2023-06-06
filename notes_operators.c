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

    uint16_t = 0xB410;
    uint8_t output;

    output = (uint8_t)((Data >> 9) & 0x003F)
*/