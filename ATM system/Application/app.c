#include "app.h"

void appStart(void) {
  // Initialize the transactions array to zero
  extern ST_transaction_t transactionsDB[255];
  memset(transactionsDB, 0, 255 * sizeof(ST_transaction_t));
  // ------------------------------------------------------------------------------------------------
  ST_cardData_t user;

  getCardHolderName(&user);
  getCardPAN(&user);
  getCardExpiryDate(&user);
  // ------------------------------------------------------------------------------------------------
  ST_terminalData_t terminal;
  float maxAmount = 10000;

  getTransactionDate(&terminal);
  if (isCardExpired(&user, &terminal) == EXPIRED_CARD) {
    printf("Error: EXPIRED_CARD\n");
    return;
    }
  setMaxAmount(&terminal, maxAmount);
  getTransactionAmount(&terminal);
  if (isBelowMaxAmount(&terminal) == EXCEED_MAX_AMOUNT) {
    printf("Error: EXCEED_MAX_AMOUNT\n");
    return;
    }
  // ------------------------------------------------------------------------------------------------
  ST_transaction_t transaction;
  transaction.cardHolderData = user;
  transaction.terminalData = terminal;

  receiveTransactionData(&transaction);
  saveTransaction(&transaction);

  listSavedTransactions();

  }

void appTest() {
  // getCardHolderNameTest();
  // getCardExpiryDateTest();
  // getCardPANTest();
// // ----------------------------------------------------------------------------------
  // getTransactionDateTest();
  // isCardExpiredTest();
  // getTransactionAmountTest();
  // isBelowMaxAmountTest();
  // setMaxAmountTest();
// // ----------------------------------------------------------------------------------
  // receiveTransactionDataTest();
  // isValidAccountTest();
  // isBlockedAccountTest();
  // isAmountAvailableTest();
  // saveTransactionTest();
  // listSavedTransactionsTest();
  }