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

    uint32_t pValue;
    struct Packet packet;
    struct Packet *pData = &packet;

    printf("Write a 32 bits value: ");
    scanf("%X", &pValue);
    //printf("%u\n", (unsigned)payload);

    pData->crc        = (uint8_t)((pValue >> 0) & 0x3);
    pData->status     = (uint8_t)((pValue >> 2) & 0x1);
    pData->payload    = (uint16_t)((pValue >> 3) & 0xFFF);
    pData->bat        = (uint8_t)((pValue >> 15) & 0x7);
    pData->sensor     = (uint8_t)((pValue >> 18) & 0x7);
    pData->longAddr   = (uint8_t)((pValue >> 21) & 0xFF);
    pData->shortAddr  = (uint8_t)((pValue >> 29) & 0x3);
    pData->addrMode   = (uint8_t)((pValue >> 31) & 0x1);

    printf("%x\n", pData->crc);
    printf("%x\n", pData->status);
    printf("%x\n", pData->payload);
    printf("%x\n", pData->bat);
    printf("%x\n", pData->sensor);
    printf("%x\n", pData->longAddr);
    printf("%x\n", pData->shortAddr);
    printf("%x\n", pData->addrMode);

    return 0;
}

