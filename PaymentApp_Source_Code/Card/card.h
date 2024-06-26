									/*Created By Mahmoud Salah Khalifa*/
/*Set a file Guard to the Card lib*/

#ifndef Card 
#define Card
#include "../General.h"

typedef struct ST_cardData_t
{
	uint8_t cardHolderName[30];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;
	

typedef enum EN_cardError_t
{
	CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN

}EN_cardError_t;

ST_cardData_t* cardData;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

#endif 
