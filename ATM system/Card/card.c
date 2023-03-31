#include "card.h"

bool isnumber(char x) {
  return (x >= '0' && x <= '9');
  }

bool check_length(uint8_t min, uint8_t max, uint8_t* str) {
  return (strlen(str) >= min && strlen(str) <= max);
  }

void clean(char* x) {
  char* newline = strchr(x, '\n');
  if (newline != NULL) *newline = '\0'; // remove the newline char if the user input is less than the maximum limit 
  else {
    scanf("%*[^\n]");
    scanf("%*c");
    } //clear upto newline if the user input exceeds the maximum limit
  }

bool areAllAlpha(uint8_t* str) {
  for (uint8_t i = 0;i < strlen(str);i++) {
    if (!(str[i] >= 'a' && str[i] <= 'z' || str[i] >= 'A' && str[i] <= 'Z' || str[i] == ' ')) return false;
    }
  return true;
  }

bool areAllDigits(uint8_t* str) {
  for (uint8_t i = 0;i < strlen(str);i++) {
    if (!(str[i] >= '0' && str[i] <= '9')) return false;
    }
  return true;
  }

uint32_t ston(char* x, uint8_t n) {
  uint32_t out = 0, temp = 1;
  for (int i = n - 1; i >= 0;i--) {
    out += ((x[i] - 48) * temp);
    temp *= 10;
    }
  return out;
  }

bool isValidCardHolderName(char* name) {
  return (check_length(20, 24, name) && areAllAlpha(name));
  }

bool isValidCardExpiryDate(char* x) {
  return (x[5] == '\0' && x[2] == '/' && isnumber(x[0]) && isnumber(x[1]) && isnumber(x[3]) && isnumber(x[4]) && ston(&x[0], 2) < 13 && ston(&x[0], 2) > 0);
  }

bool isValidCardPAN(char* x) {
  if (!(check_length(16, 19, x)) || !areAllDigits(x))
    return false;
  return true;
  }

EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
  uint8_t name[25];
  printf("Enter the card holder name:\n");
  fgets(name, 25, stdin);
  clean(name);
  if (!isValidCardHolderName(name)) return WRONG_NAME;
  strcpy(cardData->cardHolderName, name);
  return CARD_OK;
  }

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
  uint8_t date[6];
  printf("Enter the card expiry date:\n");
  fgets(date, 6, stdin);
  clean(date);
  if (!isValidCardExpiryDate(date)) return WRONG_EXP_DATE;
  strcpy(cardData->cardExpirationDate, date);
  return CARD_OK;
  }

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
  uint8_t pan[20];
  printf("Enter the primary account number:\n");
  fgets(pan, 20, stdin);
  clean(pan);
  if (!isValidCardPAN(pan)) return WRONG_PAN;
  strcpy(cardData->primaryAccountNumber, pan);
  return CARD_OK;
  }
// ------------------------------------------- Testing ------------------------------------------------------------
// To save copying the same code over and over
// Make sure that the valid input case is the last and the valid expected value is te second element in the expected array
void test(char* test_cases[], uint8_t test_cases_number, char* expected_output[], char* under_test_name, bool(*under_test)(char*)) {
  printf("Tester Name: Hesham Hany\n");
  printf("Function Name : %s\n", under_test_name);
  for (uint8_t i = 0;i < test_cases_number;i++) {
    printf("Test Case %d:\n", i + 1);
    printf("Input Data : %s\n", test_cases[i]);
    printf("Expected result: %s\n", expected_output[i == test_cases_number - 1]);
    printf("Actual result: %s\n", expected_output[(*under_test)(test_cases[i])]);
    printf("\n");
    }
  }

void getCardHolderNameTest(void) {
  char* test_cases[] = { "", "This is too short", "This name is too long to be accepted", "special chars !_#$%^*&", "name has numbers 46547", "This name is acceptable" };
  char* expected_output[] = { "WRONG_NAME", "CARD_OK" };
  test(test_cases, 6, expected_output, "getCardHolderName", isValidCardHolderName);
  }

void getCardExpiryDateTest(void) {
  char* test_cases[] = { "", "5/25" ,"005/25" ,"25/05" ,"05//25","05/25" };
  char* expected_output[] = { "WRONG_EXP_DATE", "CARD_OK" };
  test(test_cases, 6, expected_output, "getCardExpiryDate", isValidCardExpiryDate);
  }

void getCardPANTest(void) {
  char* test_cases[] = { "", "123456789123456", "12345678912345678912", "123456xyzabc56859", "123456788912345678" };
  char* expected_output[] = { "WRONG_PAN", "CARD_OK" };
  test(test_cases, 5, expected_output, "getCardPAN", isValidCardPAN);
  }