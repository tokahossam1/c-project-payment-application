#include"../card folder/card.h"

#include<string.h>


/*function implementation*/
EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
printf("please enter the card name\n");
gets(cardData->cardHolderName);
int string_length=strlen(cardData->cardHolderName);
if ((string_length<20)||(string_length>24)||(string_length==0))
    {
    return WRONG_NAME;
    }else return CARD_OK;
}

void getCardHolderNameTest(void)
{
ST_cardData_t carddata[20];
    char m=getCardHolderName(carddata);
    printf("Expected result is : %d\n",m);
    printf("Actual result is : %d\n",m);
}


EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
printf("please enter the card expiry date in the format MM/YY\n");
gets(cardData->cardExpirationDate);
int string_length=strlen(cardData->cardExpirationDate);
if ((string_length==5)&&(string_length!=0)&&(cardData->cardExpirationDate[2]=='/'))
    {if(((cardData->cardExpirationDate[0]=='1')&&((cardData->cardExpirationDate[1]>'0')&&(cardData->cardExpirationDate[1]<='2')))||
        ((cardData->cardExpirationDate[0]=='0')&&((cardData->cardExpirationDate[1]>'0')||(cardData->cardExpirationDate[1]<='9'))))

       {
        return CARD_OK;
       }else return WRONG_EXP_DATE;
    }else return WRONG_EXP_DATE;
}


void getCardExpiryDateTest (void)
{
    ST_cardData_t carddata[20];
    char m=getCardExpiryDate(carddata);
    printf("Expected result is : %d\n",m);
    printf("Actual result is : %d\n",m);
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
printf("please enter the card pan\n");
gets(cardData->primaryAccountNumber);
int string_length=strlen(cardData->primaryAccountNumber);
if ((string_length<16)||(string_length>19)||(string_length==0))
    {
    return WRONG_PAN;
    }else return CARD_OK;
}

void getCardPANTest (void)
{
ST_cardData_t carddata[20];
    char m=getCardPAN(carddata);
     printf("Expected result is : %d\n",m);
    printf("Actual result is : %d\n",m);
}

