#include"server.h"
#include"../card folder/card.h"
#include"../terminal folder/terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
ST_accountsDB_t accountsDB[255]={{2000.0,RUNNING, "898937461543685100"},
                                 {100000.0,RUNNING,"58070707604387500"},
                                 {1500.0, BLOCKED, "34246774739201752"},
                                 {12332.0,RUNNING, "19281380284118122"},
                                 {2500.0,BLOCKED, "63636734463231122"}};

ST_transaction transactionDB[255]={{ {"TOKA hossam eldin Hassan","1928138028411812","12/20"},{123,1244,"23/12/22"},DECLINED_STOLEN_CARD,0},
                                   {{"0",0,0},{0,0,0},0},{{"hany hany eldin Hassan","28028411812","12/20"},{123,1244,"23/12/22"},0},
                                   {{"noha hossam eldin Hassan","34246774739201752","12/20"},{123,1244,"23/12/22"},APPROVED,0},
                                  { {"ahmed seif eldin Hassan","63636734463231122","12/20"},{123,1244,"23/12/22"},APPROVED,0}};



EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence){
int i=0;
for(i=0;i<5;i++){
    if(strcmp(cardData->primaryAccountNumber,accountRefrence[i].primaryAccountNumber))
        {
        continue;
        }else {
        indexofaccount=i;
        return SERVER_OK;
        }
}
return ACCOUNT_NOT_FOUND;
}

void isValidAccountTest(void){
printf("please enter Account number\n");
ST_cardData_t arr_for_acc_no[15];
gets(arr_for_acc_no[0].primaryAccountNumber);
char m=isValidAccount(arr_for_acc_no, accountsDB);
printf("Expected result for valid account : %d\n",m);
printf("Actual result for valid account : %d\n",m);
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
      if((*(accountRefrence+indexofaccount)).state==RUNNING)
        {
        return SERVER_OK;
        }

else{
 return BLOCKED_ACCOUNT;
}
}


void isBlockedAccountTest(void)
{
    isValidAccountTest();
char m=isBlockedAccount(accountsDB);
printf("index of account : %d \n",indexofaccount);
printf("Expected result is : %d\n",m);
printf("Actual result is : %d\n",m);
}


EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{

    if(termData->transAmount > accountRefrence[indexofaccount].balance)
        {
        return LOW_BALANCE;
        }else return SERVER_OK;
        }


void isAmountAvailableTest(void)
{
    ST_terminalData_t terminaldata[20];
    printf("please enter trans amount\n");
    scanf("%f",&terminaldata->transAmount);
      char z=isAmountAvailable(terminaldata,accountsDB);
      printf("Expected result is : %d\n",z);
      printf("Actual result is : %d\n",z);
}


EN_transStat_t recieveTransactionData(ST_transaction *transData)
{
 EN_serverError_t transSaveState;
	if (isValidAccount(&transData->cardHolderData,accountsDB)) {
		transData->transState = DECLINED_STOLEN_CARD;
		transSaveState = saveTransaction(transData);
		if (transSaveState == SAVING_FAILED) {
			return INTERNAL_SERVER_ERROR;
		}
		else {
			return DECLINED_STOLEN_CARD;
		}
	} else if (isAmountAvailable(&transData->terminalData,accountsDB)) {
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		transSaveState = saveTransaction(transData);
		if (transSaveState == SAVING_FAILED) {
			return INTERNAL_SERVER_ERROR;
		}
		else {
			return DECLINED_INSUFFECIENT_FUND;
		}
	}
	else {
		transData->transState = APPROVED;
		float oldBalance = accountsDB[indexofaccount].balance;
		accountsDB[indexofaccount].balance -= transData->terminalData.transAmount;
		float newBalance = accountsDB[indexofaccount].balance;
		printf("Old Balance = %f\nNew Balance = %f\n", oldBalance, newBalance);
		transSaveState = saveTransaction(transData);
		if (transSaveState == SAVING_FAILED) {
			return INTERNAL_SERVER_ERROR;
		}
		else {
			return APPROVED;
		}
	}
}

void recieveTransactionDatatest(void){
ST_transaction transdata[20];
printf("please enter account number\n");
gets(transdata->cardHolderData.primaryAccountNumber);
char m =recieveTransactionData(&transdata);
if (m == FRAUD_CARD) {
		printf("FRAUD_CARD\n");
	}
	else if (m == DECLINED_STOLEN_CARD) {
		printf("DECLINED_STOLEN_CARD\n");
	}
	else if (m == DECLINED_INSUFFECIENT_FUND) {
		printf("DECLINED_INSUFFECIENT_FUND\n");
	}
	else {
		printf(" approved .\n");

	}

}


EN_serverError_t saveTransaction(ST_transaction *transData)
{

seq_no++;
transData->transactionSequenceNumber=seq_no;
static i=0;
if(i<255){
        transactionDB[i]=*transData;
        i++;
        transactionDB[i].transactionSequenceNumber=seq_no;
        printf("\nseq number = %d\n",seq_no);
        return SERVER_OK;
}
return SAVING_FAILED;
}

void saveTransactionTest(void)
{
ST_transaction array[10];
printf("please enter account holder name\n");
gets(array->cardHolderData.cardHolderName);
printf("please enter account number\n");
gets(array->cardHolderData.primaryAccountNumber);
printf("please enter card expiry date\n");
gets(array->cardHolderData.cardExpirationDate);
printf("please enter trans amount\n");
scanf("%f",&array->terminalData.transAmount);
printf("please enter trans date\n");
gets(&array->terminalData.transactionDate);
printf("please enter the max amount\n");
scanf("%f",&array->terminalData.maxTransAmount);
array->transState=RUNNING;
array->transactionSequenceNumber=seq_no;

char m=saveTransaction(&array);
if(m==0){printf("saved\n");}else printf("not saved\n");
printf("%d\n",m);
printf("\ntransaction list\n");
listSavedTransactions();
}


void listSavedTransactions(void)
{
//while(transactionDB[i].cardHolderData.cardHolderName!=NULL){
        printf("transaction sequence= %d\n",transactionDB[seq_no].transactionSequenceNumber);
        printf("transaction date : %s\n",transactionDB[i].terminalData.transactionDate);
        printf("transaction amount : %f\n",transactionDB[i].terminalData.transAmount);
        printf("transaction state : %s\n",transactionDB[i].transState);
        printf("max trans amount : %f\n",transactionDB[i].terminalData.maxTransAmount);
        printf("card holder name : %s\n",transactionDB[i].cardHolderData.cardHolderName);
        printf("pan : %s\n",transactionDB[i].cardHolderData.primaryAccountNumber);
        printf("card expiry date : %s\n",transactionDB[i].cardHolderData.cardExpirationDate);
i++;


}
