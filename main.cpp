#include <cstdlib>
#include <iostream>
#include <bitset>
using namespace std;

#define BIMODAL_TABLE_SIZE 4096
#define BANK_TABLE_SIZE 1024
#define GLOBAL_HISTORY_LENGTH 80

// int global_history[GLOBAL_HISTORY_LENGTH];
bitset<GLOBAL_HISTORY_LENGTH> GHR;
bitset<GLOBAL_HISTORY_LENGTH> temp;
bitset<GLOBAL_HISTORY_LENGTH> mask;
bitset<GLOBAL_HISTORY_LENGTH> CSR1_mask;
bitset<GLOBAL_HISTORY_LENGTH> CSR2_mask;

// Track X bank
uint8_t bank_chosen;
uint8_t bank_pred;
uint16_t tag;
uint16_t index0;
uint16_t index1;
uint16_t index2;
uint16_t index3;
uint16_t index4;

struct BimodalCell {
    uint8_t counter;
    uint8_t m;
    uint8_t msb;
};

struct BankCell {
    uint8_t counter;
    uint8_t tag;
    uint8_t u;
    uint8_t msb;
};

// 4 bits -> 3 for counter, 1 for m
BimodalCell bimodal_table[BIMODAL_TABLE_SIZE];

// 12 bits -> 3 for counter, 8 for tag, 1 for u
BankCell bank1_table[BANK_TABLE_SIZE];
BankCell bank2_table[BANK_TABLE_SIZE];
BankCell bank3_table[BANK_TABLE_SIZE];
BankCell bank4_table[BANK_TABLE_SIZE];

int main() {

    for(int i = 0; i < BIMODAL_TABLE_SIZE; i++) {
        bimodal_table[i].counter = 0;
        bimodal_table[i].m = 0;
        bimodal_table[i].msb = 0;
    }

    for(int i = 0; i < BANK_TABLE_SIZE; i++) {
        bank1_table[i].counter = 0;
        bank1_table[i].u = 0;
        bank1_table[i].msb = 0;
        bank1_table[i].tag = 0;

        bank2_table[i].counter = 0;
        bank2_table[i].u = 0;
        bank2_table[i].msb = 0;
        bank2_table[i].tag = 0;
        
        bank3_table[i].counter = 0;
        bank3_table[i].u = 0;
        bank3_table[i].msb = 0;
        bank3_table[i].tag = 0;
        
        bank4_table[i].counter = 0;
        bank4_table[i].u = 0;
        bank4_table[i].msb = 0;
        bank4_table[i].tag = 0;
    }

    for(int i = 0; i < GLOBAL_HISTORY_LENGTH; i++) {

        if (i > 9) {
            mask.set(i, 0);
        } else {
            mask.set(i, 1);
        }

        if (i > 7) {
            CSR1_mask.set(i, 0);
        } else {
            CSR1_mask.set(i, 1);
        }
        
        if (i > 6) {
            CSR2_mask.set(i, 0);
        } else {
            CSR2_mask.set(i, 1);
        }
    }
    
    bank_chosen = 0;
    bank_pred = 0;
    tag = 0;

    GHR.reset();
    temp.reset();

    for(int i = 0; i < GLOBAL_HISTORY_LENGTH; i++) {

        if (i%4) {
            GHR.set(i, 0);
        } else {
            GHR.set(i, 1);
        }
    }

    cout << GHR << endl;
    cout << temp << endl;

    temp = GHR;

    temp.set(1, 1);
    temp.set(2, 1);
    temp.set(3, 1);

    cout << temp << endl;
    cout << GHR << endl;
}