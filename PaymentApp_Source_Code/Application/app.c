#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTD_NO_WARNINGS
                                /*Created By Mahmoud Salah Khalifa*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<assert.h>
#include<stdbool.h>
#include<stdint.h>
#include "../General.h"
#include "../Card/card.h"
#include "../Server/server.h"
#include "../Terminal/terminal.h"
#include "app.h"


void appStart()
{
    float max = 0;

    accountsDB[0].balance = 1200, accountsDB[0].state = RUNNING, strcpy(accountsDB[0].primaryAccountNumber, "96654789213654265");
    accountsDB[1].balance = 1900.14, accountsDB[1].state = BLOCKED, strcpy(accountsDB[1].primaryAccountNumber, "22654789521365426");
    accountsDB[2].balance = 120, accountsDB[2].state = RUNNING, strcpy(accountsDB[2].primaryAccountNumber, "33654789521365426");
    accountsDB[3].balance = 12000, accountsDB[3].state = RUNNING, strcpy(accountsDB[3].primaryAccountNumber, "45654797411366548");
    accountsDB[4].balance = 0, accountsDB[4].state = BLOCKED, strcpy(accountsDB[4].primaryAccountNumber, "78654789521365548");
    accountsDB[5].balance = 10, accountsDB[5].state = RUNNING, strcpy(accountsDB[5].primaryAccountNumber, "45654789525426548");
    accountsDB[6].balance = 1210.78, accountsDB[6].state = BLOCKED, strcpy(accountsDB[6].primaryAccountNumber, "89678952136542658");
    accountsDB[7].balance = 1200.34, accountsDB[7].state = RUNNING, strcpy(accountsDB[7].primaryAccountNumber, "45478952136542648");


    int F_1, F_2, F_3, F_4, F_5, F_6, F_7, F_8, F_9, F_10,F_11,F_12,F_13;
    
    F_1 = getCardHolderName(cardData);
    F_2 = getCardExpiryDate(cardData);
    F_3 = getCardPAN(cardData);
    
    
    F_5 = getTransactionDate(termData);
    F_4 = isCardExpired(cardData, termData);
    F_6 = setMaxAmount(termData, max);
    F_7 = getTransactionAmount(termData);
    F_8 = isBelowMaxAmount(termData);

    F_9 = isValidAccount(cardData,accountRefrence);
    F_10 = isBlockedaccount(accountRefrence);
    F_11 = isAmountAvaliable(termData, accountRefrence);
    F_12 = recieveTranactionData(transData);
    F_13 = saveTranaction(transData);
    printf("\n");

    if (F_1 == 0 && F_2 == 0 && F_3 == 0 &&F_5 == 0 && F_4 == 0 &&  F_6 == 0 && F_7 == 0 && F_8 == 0 && F_9 == 0 && F_10 == 0 && F_11 == 0 & F_12 == 0 && F_13 == 0)
        printf("\t\t\t\t\t\tApproved Transaction\n\n");
    else
        printf("\t\t\t\t\t\tError, Make sure that your data is correct\n\n");

}



void main()
{
    printf("\n\t\t\t\tTester Name: Mahmoud Salah Khalifa\n");
    printf("\t\t\t\tTesting the app\n\n");
    for (int i = 0;i < 5;i++) 
    {
        printf("-------------------------------------------------\n");
        termData = calloc(1, sizeof(ST_terminalData_t));
        cardData = calloc(1, sizeof(ST_cardData_t));
        accountRefrence = calloc(1, sizeof(ST_accountsDB_t));
        transData = calloc(1, sizeof(ST_transaction_t));

        if (i + 1 == 1)
        {
            
            printf(" Story %d: Approved Transaction Story\n",i+1);
            appStart();
        }
        if (i + 1 == 2)
        {
            printf(" Story %d: Withdraw an amount of money that exceeds the maximum allowed amount\n",i+1);
            appStart();

        }
        if (i + 1 == 3)
        {
            printf(" Story %d: Withdraw an amount of money less than the maximum allowed and larger than the amount in my balance\n",i+1);
            appStart();
        }
        if (i + 1 == 4)
        {
            printf("Story %d: Expired card\n",i+1);
            appStart();
        }
        if (i + 1 == 5)
        {
            printf("Story %d: Stolen card\n",i+1);
            appStart();
        }

        free(termData);
        free(cardData);
        free(accountRefrence);
        free(transData);
    }
}

