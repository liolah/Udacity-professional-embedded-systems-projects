#include "terminal.h"

bool isValidTransactionDate(char* x) {
  return (strlen(x) == 10 && x[2] == '/' && x[5] == '/' && isnumber(x[0]) && isnumber(x[1]) && isnumber(x[3]) && isnumber(x[4]) && isnumber(x[6]) && isnumber(x[7]) && isnumber(x[8]) && isnumber(x[9]) && ston(&x[0], 2) < 32 && ston(&x[3], 2) < 13 && ston(&x[0], 2) > 0 && ston(&x[3], 2) > 0);
  }

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
  uint8_t date[11];
  printf("Enter the transaction date:\n");
  fgets(date, 11, stdin);
  clean(date);
  if (!isValidTransactionDate(date))
    return WRONG_DATE;
  strcpy(termData->transactionDate, date);
  return TERMINAL_OK;
  }

bool expired(char* x, char* y) {
  return (ston(&(x[0]), 2) + ston(&(x[3]), 2) * 12 < ston(&(y[3]), 2) + ston(&(y[8]), 2) * 12);
  }

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
  if (expired(cardData->cardExpirationDate, termData->transactionDate))
    return EXPIRED_CARD;
  return TERMINAL_OK;
  }

bool isValidTransactionAmount(float x) {
  return (x > 0);
  }

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
  float amount;
  printf("Enter the transaction amount:\n");
  scanf("%f", &amount);
  if (!isValidTransactionAmount(amount))
    return INVALID_AMOUNT;
  termData->transAmount = amount;
  return TERMINAL_OK;
  }

bool acceptableAmount(float x, float limit) {
  return (x <= limit);
  }

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
  if (!acceptableAmount(termData->transAmount, termData->maxTransAmount))
    return EXCEED_MAX_AMOUNT;
  return TERMINAL_OK;
  }

bool isValidMaxTransactionAmount(float x) {
  return (x > 0);
  }

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount) {
  if (!isValidMaxTransactionAmount(maxAmount))
    return INVALID_MAX_AMOUNT;
  termData->maxTransAmount = maxAmount;
  return TERMINAL_OK;
  }

void getTransactionDateTest(void) {
  char* test_cases[] = { "", "25/6/22", "2022/06/25", "25/06/2022" };
  char* expected_output[] = { "WRONG_DATE", "TERMINAL_OK" };
  test(test_cases, 4, expected_output, "getTransactionDate", isValidTransactionDate);
  }

void isCardExpiredTest(void) {
  char* test_cases[][2] = { {"06/20", "25/05/2025"}, {"06/22", "25/11/2020"} };
  char* expected_output[] = { "EXPIRED_CARD", "TERMINAL_OK" };
  printf("Tester Name: Hesham Hany\n");
  printf("Function Name : isCardExpired\n");
  for (uint8_t i = 0; i < 2; i++) {
    printf("Test Case %d:\n", i + 1);
    printf("Input Data : Exp_date: %s, Current_date: %s\n", test_cases[i][0], test_cases[i][1]);
    printf("Expected result: %s\n", expected_output[i]);
    printf("Actual result: %s\n", expected_output[expired(test_cases[i][0], test_cases[i][1]) == TERMINAL_OK]);
    printf("\n");
    }
  }

void getTransactionAmountTest(void) {
  float test_cases[] = { 0, -32.5, 162.3 };
  char* expected_output[] = { "INVALID_AMOUNT", "TERMINAL_OK" };
  printf("Tester Name: Hesham Hany\n");
  printf("Function Name : getTransactionAmount\n");
  for (uint8_t i = 0; i < 3; i++) {
    printf("Test Case %d:\n", i + 1);
    printf("Input Data : %0.2f\n", test_cases[i]);
    printf("Expected result: %s\n", expected_output[i == 2]);
    printf("Actual result: %s\n", expected_output[isValidTransactionAmount(test_cases[i])]);
    printf("\n");
    }
  }

void isBelowMaxAmountTest(void) {
  float max = 1000;
  float test_cases[] = { 1500, 500 };
  char* expected_output[] = { "EXCEED_MAX_AMOUNT", "TERMINAL_OK" };
  printf("Tester Name: Hesham Hany\n");
  printf("Function Name : isBelowMaxAmount\n");
  for (uint8_t i = 0; i < 2; i++) {
    printf("Test Case %d:\n", i + 1);
    printf("Input Data : %0.2f\n", test_cases[i]);
    printf("Expected result: %s\n", expected_output[i]);
    printf("Actual result: %s\n", expected_output[acceptableAmount(test_cases[i], max)]);
    printf("\n");
    }
  }

void setMaxAmountTest(void) {
  float test_cases[] = { 0, -32.5, 162.3 };
  char* expected_output[] = { "INVALID_MAX_AMOUNT", "TERMINAL_OK" };
  printf("Tester Name: Hesham Hany\n");
  printf("Function Name : setMaxAmount\n");
  for (uint8_t i = 0; i < 3; i++) {
    printf("Test Case %d:\n", i + 1);
    printf("Input Data : %0.2f\n", test_cases[i]);
    printf("Expected result: %s\n", expected_output[i == 2]);
    printf("Actual result: %s\n", expected_output[isValidMaxTransactionAmount(test_cases[i])]);
    printf("\n");
    }
  }