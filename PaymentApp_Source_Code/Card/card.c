#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTD_NO_WARNINGS
						 /*Created By Mahmoud Salah Khalifa*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<assert.h>
#include<ctype.h>
#include<stddef.h>
#include<stdbool.h>
#include<stdint.h>
#include "card.h"

					      

						/*  Testing functions first declaration*/
/*
void getCardHolderNametest();
void getCardExpiryDatetest();
void getCardPANtest();

*/


						/*The main function to recall all test functions*/
/*
void main()
{	
	int num = 0;
	EN_cardError_t result_n, result_d,result_p;
	cardData = (ST_cardData_t*)calloc(1,sizeof(ST_cardData_t));

	while (num != 8)
	{
		
		printf("\n List of choices:\n\t1-Enter Your name.\n\t2-Enter Expiration date.\n\t3-Card PAN.\n\t4-Show info\n\t5-Test cardHolderName()\n\t6-Test getCardExpiryDate()\n\t7-Test getCardPANtest()\n\t8-Exit.\n");
		printf("\n Your Choice is: ");
		scanf("%d", &num);

		switch (num)
		{
		case 1: {
			result_n = getCardHolderName(cardData);
			if (result_n == CARD_OK)
				printf("\n\n It is valied name\n\n");
			else
				printf("\n\n It is invalied....You can try again\n\n");
			break;}
		case 2: {
			result_d = getCardExpiryDate(cardData);
			if (result_d == CARD_OK)
				printf("\n\n It is valied Date\n\n");
			else
				printf("\n\n It is invalied....You can try again\n\n");
			break;}
		case 3: {
			result_p = getCardPAN(cardData);
			if (result_p == CARD_OK)
				printf("\n\n It is valied Card Pan\n\n");
			else
				printf("\n\n It is invalied....You can try again\n\n");
			break;}
		case 4: {
			printf("\nCard information:\n");
			printf("%s\t", cardData->cardHolderName);
			printf("%s\t", cardData->cardExpirationDate);
			printf("%s\n", cardData->primaryAccountNumber);
			break;}
		case 5:
		{
			getCardHolderNametest();
			break;
		}
		case 6:
		{
			getCardExpiryDatetest();
			break;
		}
		case 7:
		{
			getCardPANtest();
			break;
		}
		case 8:
			break;
		default:
			printf("\n Please enter valid choice.\n");
		}
		if (num == 8)
			break;
	}
}
*/

						/*Implemented Functions*/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	EN_cardError_t result;
	ST_cardData_t* test = calloc(1, sizeof(ST_cardData_t));
    printf("\n");
	printf(" Please Enter Your name seperated with \"-\":");
	scanf("%s", test->cardHolderName);
	

	int name_len = strlen(test->cardHolderName);

	if (name_len >= 20 && name_len <= 24)
	{
		result = CARD_OK;
		strcpy(cardData->cardHolderName,test->cardHolderName,name_len);
	}
	else if (name_len < 20)
	{
		result = WRONG_NAME;
	}
	else if (name_len > 24)
	{
		result = WRONG_NAME;
	}

	free(test);
	return result;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{	
	char month_str[3];
	
	int month_int;
	

	EN_cardError_t result;
	ST_cardData_t* test = calloc(1, sizeof(ST_cardData_t*));

	printf(" Please Enter card Expiry date: ");
	scanf("%s", test->cardExpirationDate);
	
	memcpy(month_str, &test->cardExpirationDate[0], 2);
	month_str[2] = '\0';
	month_int = atoi(month_str);
	

	int str_len = strlen(test->cardExpirationDate);
	

	if ((str_len != 5) || ((month_int>12) || (month_int<1)))
	{
		result = WRONG_EXP_DATE;

	}	
	else
	{
		result = CARD_OK;
		strcpy(cardData->cardExpirationDate, test->cardExpirationDate, str_len);
	}
	free(test);

	return result;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	EN_cardError_t result;
	ST_cardData_t* test = calloc(1, sizeof(ST_cardData_t));
	int counter = 0;

	printf(" Please Enter Card Pan: ");
	scanf("%s",test->primaryAccountNumber);

	int str_len = strlen(test->primaryAccountNumber);

	for (int i = 0;i < str_len;i++)
	{
		if (test->primaryAccountNumber[i] >= '0' && test->primaryAccountNumber[i] <= '9')
			counter++;
	}
	
	if (str_len < 16 || str_len > 19 ||counter != str_len)
	{	
		result = WRONG_PAN;
	}
	else
	{	
		result = CARD_OK;
		strcpy(cardData->primaryAccountNumber, test->primaryAccountNumber, str_len);
	}

	return result;
}


						/*Testing Functions*/
/*
void getCardHolderNametest()
{
	char tester_name[20] = "Mahmoud Salah";
	char function_name[20] = "getCardHolderName";
	printf("\n\t\t\t\t********** Running Test **********\n");
	printf(" Tester Name: %s\n", tester_name);
	printf(" Function Name: %s\n\n", function_name);

	char test_cases[3][30] = { "mahmoud-salah-khalifa-elsayed","mahmoud-salah-khalifa","mahmoud-Salah"};
	char Acutal_case[] = "mahmoud-salah-khalifa";

	for (int i = 0;i < 3;i++) {
		ST_cardData_t* test = calloc(1, sizeof(ST_cardData_t));

		strcpy(test->cardHolderName, test_cases[i], strlen(test_cases[i]));
		int name_len = strlen(test->cardHolderName);

		if (name_len >= 20 && name_len <= 24)
		{
			printf("\n\n Test Case : %s\n", test_cases[i]);
			printf(" Actual output: %s\n", Acutal_case);
			printf(" All is right\n");
		}
		else if (name_len < 20)
		{
			printf("\n\n Test Case: %s\n", test_cases[i]);
			printf(" Actual output: %s\n", Acutal_case);
			printf(" Error: too short name\n");
		}
		else if (name_len > 24)
		{
			printf("\n\n Test Case: %s\n", test_cases[i]);
			printf(" Actual output: %s\n", Acutal_case);
			printf(" Error: too long name\n");
		}
		free(test);
	}
	printf("\n\t\t\t*********  Succecful Test  *********\n");
}

void getCardExpiryDatetest()
{
	char tester_name[20] = "Mahmoud Salah";
	char function_name[20] = "getCardExpiryDate";
	printf("\n\t\t\t\t********** Running Test **********\n");
	printf(" Tester Name: %s\n", tester_name);
	printf(" Function Name: %s\n\n", function_name);
	
	char month_str[3];
	int month_int;

	char test_cases[3][30] = { "3/222","23/23","03/23" };
	char Acutal_case[] = "03/23";

	for (int i = 0;i < 3;i++) {
		ST_cardData_t* test = calloc(1, sizeof(ST_cardData_t));

		strcpy(test->cardHolderName, test_cases[i], strlen(test_cases[i]));
		int Date_len = strlen(test->cardExpirationDate);
			
		memcpy(month_str, &test_cases[i][0], 2);
		month_str[2] = '\0';
		month_int = atoi(month_str);
		
		if (Date_len != 5)
		{
			if (test_cases[i][2] == '/')
			{
				if (month_int > 0 && month_int < 12)
				{
					printf("\n\n Acutal: %s\n", test_cases[i]);
					printf(" Expected: %s\n", Acutal_case);
					printf(" All is right\n");
				}
				else
				{
					printf("\n\n Acutal: %s\n", test_cases[i]);
					printf(" Expected: %s\n", Acutal_case);
					printf(" Error: There is no month like that\n");
				}
			}
			else
			{
				printf("\n\n Acutal: %s\n", test_cases[i]);
				printf(" Expected: %s\n", Acutal_case);
				printf(" Error: wrong format\n");

			}
		}
		else
		{
			printf("\n\n Acutal: %s\n",test_cases[i]);
			printf(" Expected: %s\n", Acutal_case);
			printf(" Error: you exceeds the length\n");
		}

	}
	printf("\n\t\t\t*********  Succecful Test  *********\n");
}

void getCardPANtest()
{
	ST_cardData_t* test = calloc(1, sizeof(ST_cardData_t));
	
	char tester_name[20] = "Mahmoud Salah";
	char function_name[20] = "getCardPAN()";
	printf("\n\t\t\t\t********** Running Test **********\n");
	printf(" Tester Name: %s\n", tester_name);
	printf(" Function Name: %s\n\n", function_name);

	char test_Cases[3][25] = { "20324221234234934","2032422123","2032422123423493454456" };
	char Actual_res[] = "20324221234234934";
	int PAN_len=0;

	for (int i = 0;i < 3;i++)
	{
		PAN_len = strlen(test_Cases[i]);
		if (PAN_len > 15 && PAN_len < 20)
		{	
			printf("\n\n Actual: %s\n", test_Cases[i]);
			printf(" Expected: %s\n", Actual_res);
			printf(" All is fine\n");
		}
		else if (PAN_len > 19)
		{

			printf("\n\n Actual: %s\n", test_Cases[i]);
			printf(" Expected: %s\n",Actual_res);
			printf(" Error: The length is too long\n");
		}
		else
		{
			printf("\n\n Actual: %s\n", test_Cases[i]);
			printf(" Expected: %s\n", Actual_res);
			printf(" Error: The length is too short\n");
		}
	}
	printf("\n\t\t\t*********  Succecful Test  *********\n");
}
*/ 
