
#include"../card folder/card.h"
#include"../terminal folder/terminal.h"
#include<string.h>
#include<stdio.h>

/*functions implementation*/
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
printf("please enter the transaction date in the format DD/MM/20YY\n");
gets(termData->transactionDate);
int string_length=strlen(termData->transactionDate);
if ((string_length==10)&&(string_length!=0)&&(termData->transactionDate[2]=='/')&&(termData->transactionDate[5]=='/')&&(termData->transactionDate[6]=='2')&&(termData->transactionDate[7]=='0'))
    {if(((termData->transactionDate[3]=='1')&&((termData->transactionDate[4]>='0')&&(termData->transactionDate[4]<='2')))||
        ((termData->transactionDate[3]=='0')&&((termData->transactionDate[4]>='0')||(termData->transactionDate[4]<='9'))))
       {if((((termData->transactionDate[0]<='2')&&(termData->transactionDate[0]>='0'))&&((termData->transactionDate[1]>'0')&&(termData->transactionDate[1]<='9')))
       ||(((termData->transactionDate[4]%2==0)||(termData->transactionDate[4]=='0'))&&(termData->transactionDate[0]=='3')&&((termData->transactionDate[1]>'0')&&(termData->transactionDate[1]<='1'))))
       {
           return TERMINAL_OK;
       }else return WRONG_DATE;
       }else return WRONG_DATE;
    }else return WRONG_DATE;
}
void getTransactionDateTest(void)
{
    ST_terminalData_t terminaldata[20];
    char m=getTransactionDate(terminaldata);
    printf("Expected result is : %d\n",m);
    printf("Actual result is : %d\n",m);
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
//variables to save part of date in it
char *transaction_month=0;
char *expiry_month=0;
char *transaction_year=0;
char *expiry_year=0;
char *transaction_day=0;

//copy each part of date in this variables
transaction_day=strtok(termData->transactionDate,"/");
transaction_month=strtok(NULL,"/");
transaction_year=strtok(NULL,"/0")+2;
expiry_month=strtok(cardData->cardExpirationDate,"/");
expiry_year=strtok(NULL,"/0");

//turn char to numbers
int trans_day= atoi(transaction_day);
int trans_month= atoi(transaction_month);
int trans_year=atoi(transaction_year);
int exp_month=atoi(expiry_month);
int exp_year=atoi(expiry_year);

if(exp_year<trans_year){
    return EXPIRED_CARD;
}if(exp_year==trans_year)
{if(trans_month>=exp_month){
    return EXPIRED_CARD;
}else {return TERMINAL_OK;}
}else {return TERMINAL_OK;}
}

void isCardExpriedTest(void){
printf("please enter expiry date\n");
ST_cardData_t arr_exp[15];
ST_terminalData_t arr_trans[15];
gets(arr_exp->cardExpirationDate);
printf("please enter trans date\n");
gets(arr_trans->transactionDate);
 char m=isCardExpired(arr_exp, arr_trans);
    printf("Expected result is : %d\n",m);
    printf("Actual result is : %d\n",m);
}


EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
printf("please enter the terminal amount\n");
scanf("%f",&termData->transAmount);
if(termData->transAmount<=0){
    return INVALID_AMOUNT;
}else return TERMINAL_OK;
}

void getTransactionAmountTest(void){
ST_terminalData_t terminaldata[20];
    char m=getTransactionAmount(terminaldata);
    printf("Expected result is : %d\n",m);
    printf("Actual result is : %d\n",m);
}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
if(termData->maxTransAmount>=termData->transAmount){
    return TERMINAL_OK;
}else return EXCEED_MAX_AMOUNT;
}


void isBelowMaxAmountTest(void)
{
float z=0;
ST_terminalData_t terminaldata[20];
    char m=setMaxAmount(terminaldata,z);
    char l=getTransactionAmount(terminaldata);
    if(l==0&&m==0)
        {
            char x=isBelowMaxAmount(terminaldata);
    printf("Expected result is : %d\n",x);
    printf("Actual result is : %d\n",x);
        }else printf("incorrect data");
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{
printf("please enter the max amount\n");
scanf("%f",&termData->maxTransAmount);
if(termData->maxTransAmount<=0){
    return INVALID_MAX_AMOUNT;
}else return TERMINAL_OK;
}

void setMaxAmountTest(void){
    float z=0;
ST_terminalData_t terminaldata[20];
    char m=setMaxAmount(terminaldata,z);
    printf("Expected result is : %d\n",m);
    printf("Actual result is : %d\n",m);
    }
