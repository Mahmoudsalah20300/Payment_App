#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTD_NO_WARNINGS

						
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<assert.h>
#include<stdbool.h>
#include<stdint.h>
#include "server.h"



EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{	
	EN_serverError_t result = ACCOUNT_NOT_FOUND;
	int counter = 0;
	int cmp = -3;
	while (strlen(accountsDB[counter].primaryAccountNumber) != 0)
	{
		cmp = strcmp(cardData->primaryAccountNumber, accountsDB[counter].primaryAccountNumber);
		
		if (cmp == 0)
		{
			strcpy(accountRefrence->primaryAccountNumber, accountsDB[counter].primaryAccountNumber);	
			result = SERVER_OK;
			break;
		}
		else
		{
			counter++;
		}
	}

	return result;
}

EN_serverError_t isBlockedaccount(ST_accountsDB_t* accountRefrence)
{	
	EN_serverError_t result;
	int cmp =-3;
	int counter = 0;
	
	
		while (true)
		{
			cmp = strcmp(accountsDB[counter].primaryAccountNumber, accountRefrence->primaryAccountNumber);
			if (cmp == 0)
			{
				if (accountsDB[counter].state == RUNNING)
				{
					accountRefrence->state == RUNNING;
					result = SERVER_OK;
					break;
				}
				else
				{
					result = BLOCKED_ACCOUNT;
					accountRefrence->state = BLOCKED;
					break;
				}
			}
			else
			{
				counter++;
			}
		}

	return result;
}

EN_serverError_t isAmountAvaliable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	EN_serverError_t result;
	int cmp = -3;
	int counter = 0;

	while (true)
	{
		cmp = strcmp(accountsDB[counter].primaryAccountNumber, accountRefrence->primaryAccountNumber);
		if (cmp == 0)
		{
			if (accountsDB[counter].balance >= termData->transAmount)
			{
				result = SERVER_OK;
				accountRefrence->balance = termData->transAmount;
				break;
			}
			else
			{
				result = LOW_BALANCE;
				break;
			}
		}
		else
		{
			counter++;
		}
	}

	return result;
}

EN_transStat_t recieveTranactionData(ST_transaction_t* transData)
{
    EN_transStat_t result;
    EN_accountState_t R_1, R_2, R_3;

    R_1 = isValidAccount(cardData, accountRefrence);
    R_2 = isBlockedaccount(accountRefrence);
    R_3 = isAmountAvaliable(termData, accountRefrence);

    if (R_1 != SERVER_OK && R_2 == SERVER_OK && R_3 == SERVER_OK)
    {
        result = FRAUD_CARD;
    }
    else if (R_2 != SERVER_OK && R_1 == SERVER_OK && R_3 == SERVER_OK)
    {
        result = DECLINED_STOLEN_CARD;
    }
    else if (R_3 != SERVER_OK && R_1 == SERVER_OK && R_2 == SERVER_OK)
    {
        result = DECLINED_INSUFFECIENT_FUND;
    }
    else if (R_1 == SERVER_OK && R_2 == SERVER_OK && R_3 == SERVER_OK)
    {
        result = APPROVED;
    }
    else
    {
        result = INTERNAL_SERVER_ERROR;
    }

    /*Get Card Data*/
    strcpy(transData->CardHolderData.cardHolderName, cardData->cardHolderName);
    strcpy(transData->CardHolderData.cardExpirationDate, cardData->cardExpirationDate);
    strcpy(transData->CardHolderData.primaryAccountNumber, cardData->primaryAccountNumber);

    /*Get Terminl Data*/
    transData->terminalData.maxTransAmount = termData->maxTransAmount;
    transData->terminalData.transAmount = termData->transAmount;
    strcpy(transData->terminalData.transactionDate, termData->transactionDate);

    /*Get Account state*/
    transData->transState = accountRefrence->state;

    return result;
}

EN_serverError_t saveTranaction(ST_transaction_t* transData)
{   
    int counter = 1;
    int sequence = 13453;
    strcpy(transactions[counter].CardHolderData.cardHolderName, transData->CardHolderData.cardHolderName);
    strcpy(transactions[counter].CardHolderData.cardExpirationDate,transData->CardHolderData.cardExpirationDate);
    strcpy(transactions[counter].CardHolderData.primaryAccountNumber, transData->CardHolderData.primaryAccountNumber);

    transactions[counter].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
    transactions[counter].terminalData.transAmount = transData->terminalData.transAmount;
    strcpy(transactions[counter].terminalData.transactionDate, transData->terminalData.transactionDate);
    transData->transactionsequenceNumber = sequence;

    transactions[counter].transactionsequenceNumber = sequence;

    transactions[counter].transState = transData->transState;
    
    counter++;
    sequence++;
    listSavedTransactions();

    return SERVER_OK;
}

void listSavedTransactions()
{
	printf("####################################\n\n");
	printf(" Transaction Sequence Number: %d\n\n", transData->transactionsequenceNumber);
	printf(" Transaction Date: %s\n\n",transData->terminalData.transactionDate);
	printf(" Transaction Amount: %0.2f\n\n", transData->terminalData.transAmount);
	printf(" Transaction State: %d\n\n",transData->transState);
	printf(" Terminal Max Amount: %0.2f\n\n",transData->terminalData.maxTransAmount);
	printf(" Card Holder Name: %s\n\n",transData->CardHolderData.cardHolderName);
	printf(" PAN: %s\n\n", transData->CardHolderData.primaryAccountNumber);
	printf(" Card Expiration Date: %s\n\n",transData->CardHolderData.cardExpirationDate);
	printf("####################################");
}


                            /*Test Functions*/
/*
void isValidAccounttest()
{
    uint8_t testcases[3][19] = { "78654789521365548","203042343","45478952136542648" };
    EN_serverError_t Expected[3] = {SERVER_OK,ACCOUNT_NOT_FOUND,SERVER_OK};
    printf("\n\t\t\t\t\t********************** Start Test **********************\n");
    printf("\n Tester Name: Mahmoud Salah khalifa");
    printf("\n Function Name: isValidAccounttest()\n\n");
    printf("\t\t\tFOUND = 0, ACCOUNT NOT FOUND = 3");
    EN_serverError_t result = ACCOUNT_NOT_FOUND;
    int counter = 0;
    int cmp = -3;

    for (int i = 0;i < 3;i++)
    {
        printf("\n\n Test Case %d:\n",i+1);
        printf(" Input Data: %s\n",testcases[i]);
        counter = 0;
        cmp = -3;
        result = ACCOUNT_NOT_FOUND;

        while (strlen(accountsDB[counter].primaryAccountNumber) != 0)
        {
            cmp = strcmp(testcases[i], accountsDB[counter].primaryAccountNumber);
           
            if (cmp == 0)
            {
                result = SERVER_OK;
                break;
            }
            else
            {    
                counter++;
            }
        }
        printf(" Actual Result: %d\n", result);
        printf(" Expected Result: %d", Expected[i]);
    }
    printf("\n\n");
}
*/

/*
void isAmountAvaliabletest()
{
    float testcases[3] = { 1200,1500,600};
    EN_serverError_t Expected[3] = {SERVER_OK,LOW_BALANCE,SERVER_OK};
    EN_serverError_t result;
    int cmp = -3;
    int counter = 0;
    printf("\n\t\t\t\t\t********************** Start Test **********************\n");
    printf("\n Tester Name: Mahmoud Salah khalifa");
    printf("\n Function Name: isAmountAvaliabletest()\n\n");
    printf("\t\t\tACCEPTED = 0, LOW BALANCE = 4, BALANCE is %0.2f", accountsDB[0].balance);

    for (int i = 0;i < 3;i++)
    {
        printf("\n\n Test Case %d:\n",i+1);
        printf(" Input Data: %0.2f\n", testcases[i]);
       if (accountsDB[0].balance >= testcases[i])
       {
            result = SERVER_OK;             
       }
       else
       {
           result = LOW_BALANCE;
       } 
       printf(" Actual Result: %d\n", result);
       printf(" Expected Result: %d", Expected[i]);
    }
    printf("\n\n");
}
*/

/*
void isBlockedaccounttest()
{
    EN_serverError_t result;
    EN_accountState_t testcases[2] = {RUNNING,BLOCKED};
    EN_serverError_t Expexted[2] = { SERVER_OK,BLOCKED_ACCOUNT };
        
    printf("\n\t\t\t\t\t********************** Start Test **********************\n");
    printf("\n Tester Name: Mahmoud Salah khalifa");
    printf("\n Function Name: isBlockedaccounttest()\n\n");
    printf("\t\t\tOK = 0, BLOCKED ACCOUNT = 5, (RUNNING = 0, BLOCKED = 1)");

    for (int i = 0;i < 2;i++)
    {   
        printf("\n\n Test Caes %d:\n",i+1);
        printf(" Input Data: %d\n",testcases[i]);
        if (testcases[i] == RUNNING)
        {
            result = SERVER_OK;
        }
        else
        {
            result = BLOCKED_ACCOUNT;
        }
        printf(" Actual Result: %d\n",result);
        printf(" Expected Result: %d",Expexted[i]);
    }
    printf("\n\n");
}
*/

/*
void recieveTranactionDatatest()
{   
    EN_serverError_t R_1, R_2, R_3;
    EN_serverError_t testcases[5][3] = {{3,0,0},{0,5,0},{0,0,4},{0,0,0},{8,10,23}};
    EN_transStat_t Expected[5] = {FRAUD_CARD,DECLINED_STOLEN_CARD,DECLINED_INSUFFECIENT_FUND,APPROVED,INTERNAL_SERVER_ERROR};
    EN_transStat_t result;
    printf("\n\t\t\t\t\t********************** Start Test **********************\n");
    printf("\n Tester Name: Mahmoud Salah khalifa");
    printf("\n Function Name: recieveTranactionDatatest()\n");
    printf("\t\t\t\tIn input(R_1,R_2,R_3) -> SERVER_OK = 0, Invalied Account = 3, Blocked = 5, Invalid Amount = 4 , Server Error = otherwise \n");
    printf("\t\t\t\tIn Output-> Approved = 0, Insffecient fund = 1, Stolen Card = 2, Dosen't Exist = 3, Server Error = 4\n\n");
    for (int i = 0;i < 5;i++)
    {
        R_1 = testcases[i][0];
        R_2 = testcases[i][1];
        R_3 = testcases[i][2];
        printf(" Test Case %d:", i+1);
        printf("\n Input Data: %d %d %d",R_1,R_2,R_3);

        if (R_1 != SERVER_OK && R_2==SERVER_OK && R_3==SERVER_OK)
        {
            result = FRAUD_CARD;
        }
        else if (R_2 != SERVER_OK && R_1 == SERVER_OK && R_3 == SERVER_OK)
        {
            result = DECLINED_STOLEN_CARD;
        }
        else if (R_3 != SERVER_OK && R_1 == SERVER_OK && R_2 == SERVER_OK)
        {
            result = DECLINED_INSUFFECIENT_FUND;
        }
        else if (R_1 == SERVER_OK && R_2 == SERVER_OK && R_3 == SERVER_OK)
        {
            result = APPROVED;
        }
        else
        {
            result = INTERNAL_SERVER_ERROR;
        }
        printf("\n Actual Result: %d", result);
        printf("\n Expected Result: %d\n\n",Expected[i]);
    }
    printf("\n\n");
}
*/

/*
void saveTransactiontest()
{
        float max = 0;
        int saved = 0;
        int not_saved = 1;
       
        int F_1 = getCardHolderName(cardData);
        int F_2 = getCardExpiryDate(cardData);
        int F_3 = getCardPAN(cardData);
        int F_4 = setMaxAmount(termData, max);
        int F_5 = getTransactionDate(termData);
        int F_6 = getTransactionAmount(termData);
        int F_7 = isValidAccount(cardData, accountRefrence);
        int F_8 = isBlockedaccount(accountRefrence);
        int F_9 = isAmountAvaliable(termData, accountRefrence);
        int F_10 = recieveTranactionData(transData);
        int F_11 = saveTranaction(transData);


}
*/

