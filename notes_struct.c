#include<stdint.h>
/*
    STRUCTURES AND UNIONS

    Structure is a data structure used to create user-defined data types in C
    It allows to combune data of different types

    struct tag_name{
        member_element-1;
        member_element-2;
        member_element-3;
        member_element-n;
    };

*/
// definition does not consume memory
struct CarModel{
    unsigned carNumber;
    uint32_t carPrice;
    uint16_t carMaxSpeed;
    float    carWeight;
};

struct DataSet{
    char  data1;
    int   data2;
    char  data3;
    short data4;
};

int main(void){
    struct CarModel carGabriel = {2021,15000,220,1330};
    struct CarModel carOther   = {4031, 35000, 160, 1900.96};

    printf("Sizeof of struct carModel is %I64u\n", sizeof(struct carModel));

    struct CarModel carMatheus = {.carWeight=90.9, .carPrice=15000};

    printf("Details of car Gabriel\n");
    printf("carNumber = %u\n", carGabriel.carNumber);
    printf("carNumber = %u\n", carGabriel.carPrice);
    printf("carNumber = %u\n", carGabriel.carMaxSpeed);
    printf("carNumber = %u\n", carGabriel.carWeight);

    struct DataSet data;

    data.data1 = 0x11;
    data.data2 = 0xFFFFEEEE;
    data.data3 = 0x22;
    data.data4 = 0xABCD;

    uint8_t *ptr;
    ptr = (uint8_t*)&data; //struct DataSet *

    uint32_t totalSize = sizeof(struct DataSet);

    for(uint32_t i=0; i< totalSize; i++){
        printf("%p  %x\n", ptr, *ptr);
        ptr++;
    }

    getchar();
}

/*
    STRUCTURE PADDING
    struct data{
        char  data1;
        int   data2;
        char  data3;
        short data4;
    };
    sizeof(struct data) = 12 bytes

    |data3|  0  |   data4   |
    ========================
    |          data2        |
    ========================
    |data1|  0  |  0  |  0  |
    ========================
    <-----4 bytes width----->

    For No Padding

    struct data{
        char  data1;
        int   data2;
        char  data3;
        short data4;
    }__attribute__((packed));


    |                       |
    ========================
    |data2|data3|   data4   |
    ========================
    |data1|data2|data2|data2|
    ========================
    <-----4 bytes width----->

    TYPEDEF WITH STRUCTURE
    rewriting CarModel structure with typedef
    typedef struct{
        unsigned carNumber;
        uint32_t carPrice;
        uint16_t carMaxSpeed;
        float carWeight;
    }CarModel_t;

    STRUCTURES AND POINTERS

    struct DataSet *pData;
    pData = &data;
    pData->data1 = 0x55; //dereferencing operator

*/

int main(void){
    struct DataSet data;

    displayMemberElements(&data);

    getchar();
    return 0;
}

void displayMemberElements(struct DataSet *pData){
    printf("data1 = %X\n", pData->data1);
    printf("data2 = %X\n", pData->data2);
    printf("data3 = %X\n", pData->data3);
    printf("data4 = %X\n", pData->data4);
}

//program exercise

#include<stdint.h>
#include<stdio.h>

struct Packet
{
    /* data */
    uint8_t crc;
    uint8_t status;
    uint16_t payload;
    uint8_t bat;
    uint8_t sensor;
    uint8_t longAddr;
    uint8_t shortAddr;
    uint8_t addrMode;

};

int main(void){

    uint32_t payload;

    printf("Write a 32 bits value: ");
    scranf("%u", &payload);





    return 0;
}