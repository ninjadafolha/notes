/*
    ARRAYS

    uint8_t studentsAge[100];
    prinft("Size of an array = %u\n", sizeof(studentAge));

*/

//write a program to that initializes and array with 10 items to 0xff and prints the values

int main(void){
    //form 1
    uint8_t dataArray[10] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

    //form 2
    uint8_t dataArray[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

    //form 3
    int len = 10;
    uint8_t dataArray[len];

    return 0;
}

int main(void){

    uint8_t dataArray[10] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    printf("2nd data item = %x\n",*(dataArray+1)); //will return 0xff
    *(dataArray+1) = 0x9; //accessing elements to and array
    printf("2nd data item = %x\n",*(dataArray+1)); // will return 0x9

    //better way to do it
    dataArray[1] = 0x9;

    array_display(dataArray, (sizeof(dataArray)/sizeof(uint8_t)));
}

//passing array to a function
void array_display(uint8_t const *const dataArray_rx, uint32_t nItems){

    for (uint32_t i = 0; i < nItems; i++)
    {
        printf("%x\t", dataArray_rx[i]);
    }
    

}