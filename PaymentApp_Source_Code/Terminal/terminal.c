									/*Created By Mahmoud Salah Khalifa*/
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTD_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<assert.h>
#include<ctype.h>
#include<stddef.h>
#include<stdbool.h>
#include<stdint.h>	
#include "terminal.h"




EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
	EN_terminalError_t result;
	ST_terminalData_t* test;
	test = malloc(sizeof(ST_terminalData_t));
	printf(" Please enter transaction date: ");
	scanf("%s",test->transactionDate);
	
	int date_len = strlen(test->transactionDate);

	if (date_len == 10)
	{
		
		if (test->transactionDate[2] == '/' && test->transactionDate[5] == '/')
		{
			
			/*Convert day to int to check if it's valid*/
			char day_str[3];
			int day_int;
			memcpy(day_str, &test->transactionDate[0], 2);
			day_str[2] = '\0';
			day_int = atoi(day_str);
			
			if (day_int > 0 && day_int < 31)
			{
				/*Convert month to int to check if it's valid*/
				char month_str[3];
				int month_int;
				memcpy(month_str, &test->transactionDate[3], 2);
				month_str[2] = '\0';
				month_int = atoi(month_str);
				
				if (month_int >= 1 && month_int <= 12 )
				{
					char year_str[5];
					int year_int;
					memcpy(year_str, &test->transactionDate[6], 4);
					year_str[4] = '\0';
					year_int = strlen(year_str);
						
					if (year_int == 4)
					{
						
						result = TERMINAL_OK;
						strcpy(termData->transactionDate, test->transactionDate);
						
					}
					else
					{
						result = WRONG_DATE;
					}
				}
				else
				{
					result = WRONG_DATE;
				}
			}
			else
			{
				result = WRONG_DATE;
			}

		}
		else
		{
			result = WRONG_DATE;
		}
	}
	else
	{
		result = WRONG_DATE;
	}

	return result;
}


EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	EN_terminalError_t result;
	
	/*Get Expiration month and year*/
	char Exp_year[3];
	char Exp_month[3];
	int Ex_year;
	int Ex_month;
	memcpy(Exp_month, &cardData->cardExpirationDate[0], 2);
	Exp_month[2] = '\0';
	Ex_month = atoi(Exp_month);
    
	memcpy(Exp_year, &cardData->cardExpirationDate[3], 2);
	Exp_year[2] = '\0';
	Ex_year = atoi(Exp_year);
   
	
	/*Get current transaction date*/
	char Tra_year[3];
	char Tra_month[3];
	int Tr_year;
	int Tr_month;
	memcpy(Tra_month, &termData->transactionDate[3], 2);
	Tra_month[2] = '\0';
	Tr_month = atoi(Tra_month);
	memcpy(Tra_year, &termData->transactionDate[8], 2);
	Tra_year[2] = '\0';
	Tr_year = atoi(Tra_year);
	

	if (Tr_year < Ex_year)
	{
		result = TERMINAL_OK;
	}
	else if (Tr_year == Ex_year)
	{
		if (Tr_month < Ex_month)
		{
			result = TERMINAL_OK;
		}
		else
		{
			result = EXPIRED_CARD;
		}
	}
	else
	{
		result = EXPIRED_CARD;
	}

	return result;
}


EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{   

	EN_terminalError_t result;
    
	ST_terminalData_t* test;
	test = calloc(1,sizeof(ST_terminalData_t));
    
	printf(" Please enter Transaction Amount: ");
	scanf("%f", &test->transAmount);
    
	if (test->transAmount <= 0)
		result = INVALID_AMOUNT;
    else
    {
        result = CARD_OK;
        termData->transAmount = test->transAmount;
    }
    return result;
}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t result;

	if (termData->transAmount <= termData->maxTransAmount)
		result = TERMINAL_OK;
	else
		result = EXCEED_MAX_AMOUNT;

	return result;
}


EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float MaxAmount)
{
	EN_terminalError_t result;
    printf(" Enter the maximum: ");
    scanf("%f",&MaxAmount);

	if (MaxAmount <= 0)
		result = INVALID_MAX_AMOUNT;
	else
	{
		result = TERMINAL_OK;
		termData->maxTransAmount = MaxAmount;
	}
	return result;
}

					
					/*Test Function: getTransactionDateTest() */
/*
void getTransactionDateTest()
{	
	ST_terminalData_t* test;
	EN_terminalError_t result;
	char test_cases[5][11] = {"20/11/23","20-11-2023","33/11/2023","20/14/2023","20/11/2023"};
	EN_terminalError_t Expected[5] = {WRONG_DATE,WRONG_DATE,WRONG_DATE,WRONG_DATE,TERMINAL_OK};

	printf("\n\t\t\t\t***************** Start Test *****************\n");
	printf("  Tester Name: Mahmoud Salah Khalifa\n");
	printf("  Function Name: getTransactionDateTest()\n\t\t\t\tCARD_OK = 0, WRONG_DATE = 1");

	for (int i = 0;i < 5;i++)
	{
		printf("\n  Test Case %d:\n", i + 1);
		printf("  Input Data: %s",test_cases[i]);
		test = calloc(1, sizeof(ST_terminalData_t));
		strcpy(test->transactionDate, test_cases[i],strlen(test_cases[i]));

		int date_len = strlen(test->transactionDate);

		if (date_len == 10)
		{

			if (test->transactionDate[2] == '/' && test->transactionDate[5] == '/')
			{

				
				char day_str[3];
				int day_int;
				memcpy(day_str, &test->transactionDate[0], 2);
				day_str[2] = '\0';
				day_int = atoi(day_str);

				if (day_int > 0 && day_int < 31)
				{
					
					char month_str[3];
					int month_int;
					memcpy(month_str, &test->transactionDate[3], 2);
					month_str[2] = '\0';
					month_int = atoi(month_str);

					if (month_int >= 1 && month_int <= 12)
					{
						char year_str[5];
						int year_int;
						memcpy(year_str, &test->transactionDate[6], 4);
						year_str[4] = '\0';
						year_int = strlen(year_str);

						if (year_int == 4)
						{

							result = TERMINAL_OK;

						}
						else
						{
							result = WRONG_DATE;
						}
					}
					else
					{
						result = WRONG_DATE;
					}
				}
				else
				{
					result = WRONG_DATE;
				}

			}
			else
			{
				result = WRONG_DATE;
			}
		}
		else
		{
			result = WRONG_DATE;
		}
		printf("\n  Expected Result : %d\n", Expected[i]);
		printf("  Actual Result: %d\n", result);
	}
}
*/


					/*Test Function: isCardExpiredTest()*/
/*
void isCardExpiredTest()
{
	EN_terminalError_t result;

	printf("\n\t\t\t\t***************** Start Test *****************\n");
	printf("  Tester Name: Mahmoud Salah Khalifa\n");
	printf("  Function Name: isCardExpiredTest()\n");
	printf("\t\t\t\t EXPIRED CARD = 2 ,TERMINAL OK = 0, Exipred Date = 03/22");

	char test_cases[4][11] = {"13/12/2022","13/03/2022","13/12/2021","13/01/2022"};
	EN_terminalError_t Expected[4] = { EXPIRED_CARD,EXPIRED_CARD,TERMINAL_OK,TERMINAL_OK };
	char* Exp_date = "03/22";
	
	
	char Exp_year[3];
	char Exp_month[3];
	int Ex_year;
	int Ex_month;
	memcpy(Exp_month, &Exp_date[0], 2);
	Exp_month[2] = '\0';
	Ex_month = atoi(Exp_month);
	memcpy(Exp_year, &Exp_date[3], 2);
	Exp_year[2] = '\0';
	Ex_year = atoi(Exp_year);

	char Tra_year[3];
	char Tra_month[3];
	int Tr_year;
	int Tr_month;
	
	for (int i = 0;i < 4;i++)
	{	
		printf("\n\n  Test Case %d:\n", i + 1);
		printf("  Input Data: %s",test_cases[i]);
		memcpy(Tra_month, &test_cases[i][3], 2);
		Tra_month[2] = '\0';
		Tr_month = atoi(Tra_month);
		memcpy(Tra_year, &test_cases[i][8], 2);
		Tra_year[2] = '\0';
		Tr_year = atoi(Tra_year);

		if (Tr_year < Ex_year)
		{
			result = TERMINAL_OK;
		}
		else if (Tr_year == Ex_year)
		{
			if (Tr_month < Ex_month)
			{
				result = TERMINAL_OK;
			}
			else
			{
				result = EXPIRED_CARD;
			}
		}
		else
		{
			result = EXPIRED_CARD;
		}

		printf("\n  Actual Result: %d\n", result);
		printf("  Expected Result: %d", Expected[i]);
	}
	printf("\n");
}
*/

					/*Test Function: getTransactionAmounttest()*/

/*
void getTransactionAmounttest()
{
	printf("\n\n\t\t\t\t\t\t***************** START TEST *****************\n\n");
	printf("  Tester Name: Mahmoud Salah Khalifa\n");
	printf("  Function Name: getTransactionAmounttest()\n");
	printf("\t\t\t\t\t\t WRONG AMOUNT = 4, TERMINAL OK = 0\n");
	EN_terminalError_t result;
	
	float test_cases[3] = { -2, 0, 2.4 };
	EN_terminalError_t Expected[3] = { INVALID_AMOUNT,INVALID_AMOUNT,TERMINAL_OK };
	
	for (int i = 0;i < 3;i++)
	{	
		printf("\n\n  Test Case %d:\n", i + 1);
		printf("  Input Data: %0.2f\n",test_cases[i]);
		
		if (test_cases[i] <= 0)
			result = INVALID_AMOUNT;
		else
			result = CARD_OK;

		printf("  Expected Result : %d\n",Expected[i]);
		printf("  Actual Result: %d", result);
	}
	printf("\n\n");
}
*/

					/*Test Function: isBelowMaxAmountTest()*/
/*
void isBelowMaxAmountTest()
{
	printf("\n\n\t\t\t\t\t\t***************** START TEST *****************\n\n");
	printf("  Tester Name: Mahmoud Salah Khalifa\n");
	printf("  Function Name: isBelowMaxAmountTest()\n");
	printf("\n\t\t\t\t EXCEED MAX AMOUNT = 5, TERMINAL OK = 0, Max Amount = 500.0");
	EN_terminalError_t result;
	float max_amount = 500.0;
	float testcases[3] = {501.3,500.0,499.5};
	EN_terminalError_t Expected[3] = { EXCEED_MAX_AMOUNT ,TERMINAL_OK };
	for (int i = 0;i < 3;i++)
	{
		printf("\n\n  Test Case %d:\n", i + 1);
		printf("  Input Data: %0.2f\n", testcases[i]);

		if (testcases[i] <= max_amount)
			result = TERMINAL_OK;
		else
			result = EXCEED_MAX_AMOUNT;
	
		printf("  Expexted Result: %d\n", Expected[i]);
		printf("  Actual Result: %d",result);
	}
	printf("\n");
}
 */  

					/*Test Function: setMaxAmountTest()*/
/*
void setMaxAmountTest()
{
	printf("\n\n\t\t\t\t\t\t***************** START TEST *****************\n\n");
	printf("  Tester Name: Mahmoud Salah Khalifa\n");
	printf("  Function Name: setMaxAmountTest()\n");
	printf("\n\t\t\t\t INVALIED MAX AMOUNT = 6, TERMINAL OK = 0\n");

	float testcases[3] = { -30.25,0.0,26.5};
	EN_terminalError_t Expected[3] = {INVALID_MAX_AMOUNT,INVALID_MAX_AMOUNT,TERMINAL_OK};
	EN_terminalError_t result;

	for (int i = 0;i < 3;i++)
	{
		printf("\n\n  Test Case %d:\n", i + 1);
		printf("  Input Data: %0.2f\n", testcases[i]);

		if (testcases[i] <= 0)
			result = INVALID_MAX_AMOUNT;
		else
		{
			result = TERMINAL_OK;
		}

		printf("  Expexted Result: %d\n", Expected[i]);
		printf("  Actual Result: %d", result);
	}
	printf("\n\n");
}
*/

