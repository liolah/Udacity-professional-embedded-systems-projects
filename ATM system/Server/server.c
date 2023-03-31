#include "server.h"

ST_transaction_t transactionsDB[255];

ST_accountsDB_t accountsDB[255] = { {10000.0, RUNNING, "11111111111111111"},
                                    {200.0, RUNNING, "22222222222222222"},
                                    {500.0, BLOCKED, "33333333333333333"},
                                    {4500.0, RUNNING, "44444444444444444"},
                                    {78868.0, RUNNING, "55555555555555555"} };

uint32_t seq_num = 0;

EN_transState_t receiveTransactionData(ST_transaction_t* transData) {
  if (seq_num > 254) {
    transData->transState = INTERNAL_SERVER_ERROR;
    printf("Error: INTERNAL_SERVER_ERROR\n");
    return INTERNAL_SERVER_ERROR;
    }

  ST_accountsDB_t account;

  if (isValidAccount(&transData->cardHolderData, &account) == ACCOUNT_NOT_FOUND) {
    transData->transState = FRAUD_CARD;
    printf("Error: FRAUD_CARD\n");
    return FRAUD_CARD;
    }

  if (isBlockedAccount(&account) == BLOCKED_ACCOUNT) {
    transData->transState = DECLINED_STOLEN_CARD;
    printf("Error: DECLINED_STOLEN_CARD\n");
    return DECLINED_STOLEN_CARD;
    }

  if (isAmountAvailable(&transData->terminalData, &account) == LOW_BALANCE) {
    transData->transState = DECLINED_INSUFFICIENT_FUND;
    printf("Error: DECLINED_INSUFFICIENT_FUND\n");
    return DECLINED_INSUFFICIENT_FUND;
    }

  printf("APPROVED\n");
  account.balance -= transData->terminalData.transAmount;
  transData->terminalData.maxTransAmount -= transData->terminalData.transAmount;
  setMaxAmount(&(transData->terminalData), transData->terminalData.maxTransAmount);
  transData->transState = APPROVED;
  return APPROVED;
  }

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {
  for (uint8_t i = 0;i < 255;i++) {
    if (strcmp(cardData->primaryAccountNumber, accountsDB[i].primaryAccountNumber) == 0) {
      *accountRefrence = accountsDB[i];
      return SERVER_OK;
      }
    }
  accountRefrence = NULL;
  return ACCOUNT_NOT_FOUND;
  }

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
  if (accountRefrence->state == BLOCKED) return BLOCKED_ACCOUNT;
  return SERVER_OK;
  }
// returns 
bool exceedAmount(float x, float limit) {
  return (x > limit);
  }

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
  if (exceedAmount(termData->transAmount, accountRefrence->balance)) return LOW_BALANCE;
  return SERVER_OK;
  }

EN_serverError_t saveTransaction(ST_transaction_t* transData) {
  transData->transactionSequenceNumber = seq_num;
  transactionsDB[seq_num] = *transData;
  seq_num++;
  return SERVER_OK;
  }

void listSavedTransactions(void) {
  char* transaction_states[] = { "APPROVED", "DECLINED_INSUFFICIENT_FUND", "DECLINED_STOLEN_CARD", "FRAUD_CARD", "INTERNAL_SERVER_ERROR" };
  for (uint8_t i = 0;i < seq_num;i++) {
    printf("#########################\n");
    printf("Transaction Sequence Number: %d\n", transactionsDB[i].transactionSequenceNumber);
    printf("Transaction Date: %s\n", transactionsDB[i].terminalData.transactionDate);
    printf("Transaction Amount: %0.2f\n", transactionsDB[i].terminalData.transAmount);
    printf("Transaction State: %s\n", transaction_states[transactionsDB[i].transState]);
    printf("Terminal Max Amount: %0.2f\n", transactionsDB[i].terminalData.maxTransAmount);
    printf("Cardholder Name: %s\n", transactionsDB[i].cardHolderData.cardHolderName);
    printf("PAN: %s\n", transactionsDB[i].cardHolderData.primaryAccountNumber);
    printf("Card Expiration Date: %s\n", transactionsDB[i].cardHolderData.cardExpirationDate);
    printf("#########################\n");
    printf("\n");
    }
  }
// ----------------------------------------------------- Testing --------------------------------------------
ST_cardData_t test_cases[] = { {"Hesham Hany", "798465153278945613", "02/26"}, {"Nour Magdy", "11111111111111111", "10/25"} };
ST_accountsDB_t x;
ST_transaction_t samples[] = { {{"User 1", "11111111111111111","11/26"},{500,20000,"10/05/2023"}},
  {{"User 2", "22222222222222222","11/27"},{10000,100000,"12/05/2023"}},
  {{"User 3", "33333333333333333","12/23"},{1000,50000,"10/06/2023"}},
  {{"User 4", "66666666666666666","10/20"},{7000,30000,"10/05/2024"}},
  {{"User 5", "55555555555555555","03/24"},{9000,50000,"15/05/2023"}} };
char* input_text[] = { "{{\"User 1\", \"11111111111111111\",\"11/26\"},{500,20000,\"10/05/2023\"}}",
"{{\"User 2\", \"22222222222222222\",\"11/27\"},{10000,100000,\"12/05/2023\"}}",
"{{\"User 3\", \"33333333333333333\",\"12/23\"},{1000,500,\"10/06/2023\"}}",
"{{\"User 4\", \"66666666666666666\",\"10/20\"},{7000,30000,\"10/05/2024\"}}",
"{{\"User 5\", \"55555555555555555\",\"03/24\"},{9000,50000,\"15/05/2023\"}}" };

void receiveTransactionDataTest(void) {
  char* expected_output[] = { "APPROVED", "DECLINED_INSUFFICIENT_FUND", "DECLINED_STOLEN_CARD", "FRAUD_CARD", "INTERNAL_SERVER_ERROR" };
  printf("Tester Name: Hesham Hany\n");
  printf("Function Name : receiveTransactionData\n");
  for (uint8_t i = 0;i < 5;i++) {
    if (i == 4) seq_num = 255;
    printf("Test Case %d:\n", i + 1);
    printf("Input Data : %s\n", input_text[i]);
    printf("Expected result: %s\n", expected_output[i]);
    printf("Actual result: ");
    receiveTransactionData(&samples[i]);
    printf("\n");
    }
  }

void isValidAccountTest(void) {
  char* expected_output[] = { "ACCOUNT_NOT_FOUND","SERVER_OK" };
  printf("Tester Name: Hesham Hany\n");
  printf("Function Name : isValidAccount\n");
  for (uint8_t i = 0;i < 2;i++) {
    printf("Test Case %d:\n", i + 1);
    printf("Input Data : Name: %s - PAN: %s\n", test_cases[i].cardHolderName, test_cases[i].primaryAccountNumber);
    printf("Expected result: %s\n", expected_output[i]);
    printf("Actual result: ");
    printf("%s\n", expected_output[isValidAccount(&test_cases[i], &x) == SERVER_OK]);
    printf("\n");
    }
  }

void isBlockedAccountTest(void) {
  ST_accountsDB_t input[] = { {100000.0, BLOCKED, "11111111111111111"} , {2000.0, RUNNING, "22222222222222222"} };
  char* input_text[] = { "{100000.0, BLOCKED, \"11111111111111111\"}","{2000.0, RUNNING, \"22222222222222222\"}" };
  char* expected_output[] = { "BLOCKED_ACCOUNT","SERVER_OK" };
  printf("Tester Name: Hesham Hany\n");
  printf("Function Name : isBlockedAccount\n");
  for (uint8_t i = 0;i < 2;i++) {
    printf("Test Case %d:\n", i + 1);
    printf("Input Data : %s\n", input_text[i]);
    printf("Expected result: %s\n", expected_output[i]);
    printf("Actual result: ");
    printf("%s\n", expected_output[isBlockedAccount(&input[i]) == SERVER_OK]);
    printf("\n");
    }
  }

void isAmountAvailableTest(void) {
  float balance = 1000;
  float test_cases[] = { 1500,500 };
  char* expected_output[] = { "LOW_BALANCE", "TERMINAL_OK" };
  printf("Tester Name: Hesham Hany\n");
  printf("Function Name : isBelowMaxAmount\n");
  for (uint8_t i = 0;i < 2;i++) {
    printf("Test Case %d:\n", i + 1);
    printf("Input Data : Balance: %0.2f - Amount: %0.2f\n", balance, test_cases[i]);
    printf("Expected result: %s\n", expected_output[i]);
    printf("Actual result: ");
    printf("%s\n", expected_output[!exceedAmount(test_cases[i], balance)]);
    printf("\n");
    }
  }

void saveTransactionTest(void) {
  ST_transaction_t test = { {"Hesham Hany", "11111111111111111","11/26"},{500,20000,"10/05/2023"}, 0 };
  char* test_text = "{ {\"Hesham Hany\", \"11111111111111111\",\"11/26\"},{500,20000,\"10/05/2023\"}, 0 }";
  char* expected_output = "#########################\nTransaction Sequence Number : 0\nTransaction Date : 10/05/2023\nTransaction Amount : 500.00\nTransaction State : APPROVED\nTerminal Max Amount : 20000.00\nCardholder Name : Hesham Hany\nPAN : 11111111111111111\nCard Expiration Date : 11/26\n#########################\n";
  printf("Tester Name: Hesham Hany\n");
  printf("Function Name : saveTransaction\n");
  printf("Test Case: 1\n");
  printf("Input Data: %s\n", test_text);
  saveTransaction(&test);
  printf("Expected result: \n%s\n", expected_output);
  printf("Actual result: \n");
  listSavedTransactions();
  printf("\n");
  }

void listSavedTransactionsTest(void) {
  ST_transaction_t test = { {"Hesham Hany", "11111111111111111","11/26"},{500,20000,"10/05/2023"}, 0 };
  char* test_text = "{ {\"Hesham Hany\", \"11111111111111111\",\"11/26\"},{500,20000,\"10/05/2023\"}, 0 }";
  char* expected_output = "#########################\nTransaction Sequence Number : 0\nTransaction Date : 10/05/2023\nTransaction Amount : 500.00\nTransaction State : APPROVED\nTerminal Max Amount : 20000.00\nCardholder Name : Hesham Hany\nPAN : 11111111111111111\nCard Expiration Date : 11/26\n#########################\n";
  printf("Tester Name: Hesham Hany\n");
  printf("Function Name : saveTransaction\n");
  printf("Test Case: 1\n");
  printf("Input Data: %s\n", test_text);
  saveTransaction(&test);
  printf("Expected result: \n%s\n", expected_output);
  printf("Actual result: \n");
  listSavedTransactions();
  printf("\n");
  }
