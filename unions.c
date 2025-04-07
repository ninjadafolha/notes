//union allows storage of different datatypes in the same memory location. It can assume only one number at a time. 
// Good to save memory space.
// Union size if of the largest variable defined.

#include <stdio.h>
#include <stdint.h>

union Example{
    uint8_t var1;
    uint16_t var2;
    uint8_t var3[20];
};


int main()
{
    union Example exmp;
    exmp.var1 = 10;
    printf("%d\n", exmp.var1);
    printf("Size of var1: %lu\n", sizeof(exmp.var1));
    exmp.var2 = 20;
    printf("%d\n", exmp.var2);
    printf("Size of var2: %lu\n", sizeof(exmp.var2));
    sprintf(exmp.var3, "string test");
    printf("%s\n", exmp.var3);
    printf("Size of var3: %lu\n", sizeof(exmp.var3));
    
    printf("Union size: %lu\n", sizeof(exmp));
    

    return 0;
}
