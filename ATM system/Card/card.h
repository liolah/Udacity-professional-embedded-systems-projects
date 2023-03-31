#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct ST_cardData_t
  {
  uint8_t cardHolderName[25];
  uint8_t primaryAccountNumber[20];
  uint8_t cardExpirationDate[6];
  } ST_cardData_t;

typedef enum EN_cardError_t
  {
  CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
  } EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);

// Additional helper functions
// Takes a pointer and the number of digits in the number and return the number
uint32_t ston(char* x, uint8_t n);
void clean(char* x);
bool isnumber(char x);
void test(char* test_cases[], uint8_t test_cases_number, char* expected_output[], char* under_test_name, bool(*under_test)(char*));

#endif