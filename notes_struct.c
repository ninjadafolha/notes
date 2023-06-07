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

}
