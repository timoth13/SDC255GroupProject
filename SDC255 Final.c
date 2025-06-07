#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_RECORDS 100
#define MAX_DATE 11
#define MAX_DESC 51
#define MAX_CAT 21

// Struct Definitions
typedef struct {
    char date[MAX_DATE];
    char description[MAX_DESC];
    float amount;
} Income;

typedef struct {
    char date[MAX_DATE];
    char description[MAX_DESC];
    char category[MAX_CAT];
    float amount;
} Expense;

// Function Prototypes
int menu();
int addIncome(Income incomes[], int count);
int addExpense(Expense expenses[], int count);
void displayTransactions(Income incomes[], int incomeCount, Expense expenses[], int expenseCount);
void displayIncomeSummary(Income incomes[], int incomeCount);
void displayExpenseSummary(Expense expenses[], int expenseCount);
void exportToFile(Income incomes[], int incomeCount, Expense expenses[], int expenseCount);
void loadFromFile(Income incomes[], int *incomeCount, Expense expenses[], int *expenseCount);
void flushInput();
void clearScreen();

int main() {
    Income incomes[MAX_RECORDS];
    Expense expenses[MAX_RECORDS];
    int incomeCount = 0;
    int expenseCount = 0;

    loadFromFile(incomes, &incomeCount, expenses, &expenseCount);

    int option;
    do {
        option = menu();
        switch(option) {
            case 1: incomeCount = addIncome(incomes, incomeCount); break;
            case 2: expenseCount = addExpense(expenses, expenseCount); break;
            case 3: displayTransactions(incomes, incomeCount, expenses, expenseCount); break;
            case 4: displayIncomeSummary(incomes, incomeCount); break;
            case 5: displayExpenseSummary(expenses, expenseCount); break;
            case 6: exportToFile(incomes, incomeCount, expenses, expenseCount); break;
            case 7: break;
            default: printf("Press enter to continue. \n");
            		 getchar();
        }
    } while (option != 7);

    exportToFile(incomes, incomeCount, expenses, expenseCount);

    printf("Exiting application. Goodbye.\n");
    return 0;
}

int menu() {
    int option;
    clearScreen();
    printf("=== Personal Finance Tracker ===\n");
    printf("1. Add Income\n");
    printf("2. Add Expense\n");
    printf("3. Display All Transactions\n");
    printf("4. Display Income Summary\n");
    printf("5. Display Expense Summary\n");
    printf("6. Export Transactions to File\n");
    printf("7. Exit\n");
    printf("Select option: ");
    if(scanf("%d", &option)==0){
    	printf("Invalid input, please enter a number.");
	};
    flushInput();
    return option;
}

int addIncome(Income incomes[], int count) {
	int correct=0;
    if (count >= MAX_RECORDS) {
        printf("Income list full. Cannot add more entries.\n");
        return count;
    }

    printf("Enter date (YYYY-MM-DD): ");
    int len;

    while(correct==0){
		fgets(incomes[count].date, MAX_DATE, stdin);
		len = strlen(incomes[count].date);
	    if (len > 0 && incomes[count].date[len - 1] == '\n') {
	        incomes[count].date[len - 1] = '\0';
    	}
    	correct=checkDateFormat(incomes[count].date);
    	flushInput();
	}
    
    printf("Enter description: ");
    fgets(incomes[count].description, MAX_DESC, stdin);
    len = strlen(incomes[count].description);
    //get rid of \n..fgets includes \n
	if (len > 0 && incomes[count].description[len - 1] == '\n') {
        incomes[count].description[len - 1] = '\0';
    }
    flushInput();

    printf("Enter amount: ");
		do {
			if (scanf("%f", &incomes[count].amount)==1 && incomes[count].amount>0){
	    	break;
		}
		else{
			printf("Invalid input. Please enter a positive number.\n");
		}
	}while(1);

    printf("Income entry added successfully.\n");
    printf("Press enter to continue.\n");
    getchar();
    return count + 1;
}

int addExpense(Expense expenses[], int count) {
	int correct=0;
	if (count >= MAX_RECORDS) {
	        printf("Expense list full. Cannot add more entries.\n");
	        return count;
	    }

    printf("Enter date (YYYY-MM-DD): ");

    int len;
    
    while(correct==0){
    	fgets(expenses[count].date, MAX_DATE, stdin);
    	len = strlen(expenses[count].date);
	    if (len > 0 && expenses[count].date[len - 1] == '\n') {
	        expenses[count].date[len - 1] = '\0';
	    }
	    correct=checkDateFormat(expenses[count].date);
	    flushInput();
	}
    
    printf("Enter description: ");
    fgets(expenses[count].description, MAX_DESC, stdin);
    len = strlen(expenses[count].description);
    //get rid of \n..fgets includes \n
	if (len > 0 && expenses[count].description[len - 1] == '\n') {
        expenses[count].description[len - 1] = '\0';
    }
    flushInput();
    
    printf("Enter category: ");
    fgets(expenses[count].category, MAX_CAT, stdin);
    len = strlen(expenses[count].category);
    //get rid of \n..fgets includes \n
	if (len > 0 && expenses[count].category[len - 1] == '\n') {
        expenses[count].category[len - 1] = '\0';
    }
    flushInput();

    printf("Enter amount: ");
		do {
			if (scanf("%f", &expenses[count].amount)==1 && expenses[count].amount>0){
	    	break;
		}
		else{
			printf("Invalid input. Please enter a positive number.\n");
		}
	}while(1);


    printf("Expenses entry added successfully.\n");
    printf("Press enter to continue.\n");
    getchar();
    return count + 1;
}

void displayTransactions(Income incomes[], int incomeCount, Expense expenses[], int expenseCount) {
	int i;
	printf("\nIncome Transactions\n");
    for (i = 0; i < incomeCount; i++){
    	printf("%s %s $%.2f\n", incomes[i].date, incomes[i].description, incomes[i].amount);
    }
    
     printf("\nExpense Transactions\n");
    for (i = 0; i < expenseCount; i++){
    	printf("%s %s %s $%.2f\n", expenses[i].date, expenses[i].description, expenses[i].category, expenses[i].amount);
    }
    printf("\nPress enter to continue.\n");
    getchar();
}

void displayIncomeSummary(Income incomes[], int incomeCount) {
	float total = 0;
	int i;
    printf("Income Summary\n");
    for (i = 0; i < incomeCount; i++){
    	total += incomes[i].amount;
	}
	
	printf("\nTotal Income: $%.2f\nTotal Records: %d\n", total, incomeCount);
	printf("Press enter to continue.\n");
    getchar();
}

void displayExpenseSummary(Expense expenses[], int expenseCount) {
	float total = 0;
	int i;
    printf("Expense Summary\n");
    for (i = 0; i < expenseCount; i++){
    	total += expenses[i].amount;
	}
	
	printf("\nTotal Expense: $%.2f\nTotal Records: %d\n", total, expenseCount);
	printf("Press enter to continue.\n");
	getchar();
}

void exportToFile(Income incomes[], int incomeCount, Expense expenses[], int expenseCount) {
	printf("Edit once file save validation\n");
    printf("Press enter to continue.\n");
    getchar();
}

void loadFromFile(Income incomes[], int *incomeCount, Expense expenses[], int *expenseCount) {
	printf("Edit once file load validation");
    printf("Press enter to continue.\n");
    getchar();
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void flushInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int checkDateFormat(const char *date){
	int i;
	for(i = 0; i <10; i++){
		if (i==4||i==7){
			if(date[i] != '-'){
				printf("Invalid date format, use (YYYY-MM-DD): ");
				return 0;
			}
		}
		if (i!=4 && i!=7){
			if(isdigit(date[i])==0){
				printf("Invalid date format, use (YYYY-MM-DD): ");
				return 0;
			}
		}
	}
	
	int year = atoi(&date[0]);
	int month = atoi(&date[5]);
	int day = atoi(&date[8]);
	int maxDay;
	
	if (month < 1 || month > 12){
		printf("Month must be between 1 and 12, use (YYYY-MM-DD): ");
		return 0;
	}
	
	switch(month){
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12: maxDay=31;
				break;
		case 4:
		case 6:
		case 9:
		case 11: maxDay=30;
				break;
		case 2: if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)){
					maxDay = 29;
				}
				else{
					maxDay = 28;
				}
			break;
		default: return 0;
		}
		
	if ( day < 1 || day > maxDay){
		printf("Must use valid day in the month, use (YYYY-MM-DD): ");
		return 0;
	}
	
	return 1;
}
