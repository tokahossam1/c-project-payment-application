#include <stdio.h>
#include <stdlib.h>
#include"../card folder/card.h"
#include"../terminal folder/terminal.h"
#include"../server folder/server.h"

#include<string.h>

ST_cardData_t USER_CARD_DATA[20];
ST_terminalData_t USER_TERM_DATA[20];
extern accountsDB[255];
EN_transStat_t transactionState;
ST_transaction transaction;
extern transactionDB[255];

void intro(void){

    char m=getCardHolderName(USER_CARD_DATA);
    char z=getCardExpiryDate(USER_CARD_DATA);
    char x=getCardPAN(USER_CARD_DATA);
 if((m==0)&&(x==0)&&(z==0)){
        printf("\n");
    printf("SUCCESSFUL PROCESS\n");

 }else{
     printf("\n");
     printf("INCORRECT DATA\n\n");
     intro();
     printf("\n");
 }
 }

 void intro_terminal(void){
 char m=getTransactionDate(USER_TERM_DATA);
 char x=isCardExpired(USER_CARD_DATA,USER_TERM_DATA);
 char z=getTransactionAmount(USER_TERM_DATA);
 if(m==0&&z==0){
    if(x!=0){
        printf("Card is Expired\n");
 }
 }else{
  printf("INCORRECT TRANSACTION DATE\n");
  intro_terminal();
  printf("\n");
 }
 }

void intro_server(void)
{
char m=isValidAccount(USER_CARD_DATA,accountsDB);
char z=isBlockedAccount(accountsDB);
char s=isAmountAvailable(USER_TERM_DATA,accountsDB);
if(m!=0)
    {
        printf("\ninvalid account\n");
        return;
    }
 if(z!=0)
    {
    printf("\naccount is blocked\n");
    return;
    }
 if(s!=0)
 {
     printf("amount is not available\n");
     return;
 }

//for saving

	transaction.cardHolderData = *USER_CARD_DATA;
	transaction.terminalData = *USER_TERM_DATA;

	transactionState = recieveTransactionData(&transaction);
	if (transactionState == INTERNAL_SERVER_ERROR) {
		printf("Internal Server Error! Transaction Not saved.\n");
	}
	else if (transactionState == DECLINED_STOLEN_CARD) {
		printf("Declined! Stolen card!\n");
	}
	else if (transactionState == DECLINED_INSUFFECIENT_FUND) {
		printf("Declined! Insufficient Fund!\n");
	}
	else {
		printf("Transaction approved and saved.\n");
	}
}
void appStart(void){
intro();
intro_terminal();
intro_server();
}

int main()
{
appStart();


    //FOR TESTING EACH FN

    /*getCardExpiryDateTest();
    printf("\n");
    getCardExpiryDateTest();
    printf("\n");
    getCardExpiryDateTest();
    printf("\n");
   /* getCardHolderNameTest();
    printf("\n");
    getCardHolderNameTest();
    printf("\n");
    getCardHolderNameTest();
    */
   /* getCardPANTest ();
    printf("\n");
    getCardPANTest ();
    printf("\n");
    getCardPANTest ();
    printf("\n");
    */
    //testing terminal
    /*
    getTransactionDateTest();
    printf("\n");
    getTransactionDateTest();
    printf("\n");
    getTransactionDateTest();
    printf("\n");
    getTransactionDateTest();
    printf("\n");
    */
    /*char arr[13]="20/23/2022";
    char *transaction_day;
    transaction_day=strtok(arr,"/");
char *transaction_month=strtok(NULL,"/");

char *transaction_year=strtok(NULL,"/0")+2;
printf("%s\n",transaction_day);
printf("%s\n",transaction_month);
printf("%s\n",transaction_year);
//turn char to numbers
int trans_day= atoi(transaction_day);
int trans_month= atoi(transaction_month);
int trans_year=atoi(transaction_year);
printf("%d",trans_day);
*/
/*
isCardExpriedTest();
printf("\n");
isCardExpriedTest();
printf("\n");
isCardExpriedTest();
printf("\n");
*/
/*
getTransactionAmountTest();
printf("\n");
getTransactionAmountTest();
printf("\n");
*/
/*
setMaxAmountTest();
printf("\n");
setMaxAmountTest();
printf("\n");
setMaxAmountTest();
printf("\n");
*/
/*
isBelowMaxAmountTest();
printf("\n");
isBelowMaxAmountTest();
printf("\n");
isBelowMaxAmountTest();
printf("\n");
*/
/*
isValidAccountTest();
printf("\n");
isValidAccountTest();
printf("\n");
isValidAccountTest();
printf("\n");
*/
/*
isBlockedAccountTest();
printf("\n");
isBlockedAccountTest();
printf("\n");
isBlockedAccountTest();
printf("\n");
*/
/*
isValidAccountTest();
isAmountAvailableTest();
printf("\n");

isAmountAvailableTest();
printf("\n");

saveTransactionTest();

//saveTransactionTest();
//listSavedTransactions();
recieveTransactionDatatest();
printf("\n\n");

recieveTransactionDatatest();
printf("\n\n");
recieveTransactionDatatest();
*/

    return 0;
}

