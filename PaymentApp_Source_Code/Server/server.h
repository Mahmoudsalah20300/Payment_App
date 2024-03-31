										/*Created By Mahmoud Salah Khalifa*/
/*Add a header Guard to the Server lib*/

#ifndef server
#define server
#include "../General.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND,
	DECLINED_STOLEN_CARD,FRAUD_CARD,INTERNAL_SERVER_ERROR

}EN_transStat_t;

typedef struct ST_transaction_t
{
	ST_cardData_t CardHolderData;
	ST_terminalData_t terminalData;
	EN_transStat_t transState;
	uint32_t transactionsequenceNumber;

}ST_transaction_t;

typedef enum EN_serverError_t
{
	SERVER_OK, SAVING_FAILED,TRANSACTION_NOT_FOUND
	,ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT

}EN_serverError_t;

ST_transaction_t* transData;


typedef enum EN_accountState_t
{
	RUNNING,
	BLOCKED
}EN_accountState_t;

typedef struct ST_accountsDB_t
{
	float balance;
	EN_accountState_t state;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;


ST_accountsDB_t accountsDB[255];
ST_transaction_t transactions[255];


ST_accountsDB_t* accountRefrence;

EN_transStat_t recieveTranactionData(ST_transaction_t* transData);
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence);
EN_serverError_t isBlockedaccount(ST_accountsDB_t*accountRefrence);
EN_serverError_t isAmountAvaliable(ST_terminalData_t* termData,ST_accountsDB_t* accountRefrence);
EN_serverError_t saveTranaction(ST_transaction_t* transData);
void listSavedTransactions(viod);

#endif

