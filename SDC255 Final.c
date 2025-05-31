#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
            default: printf("Invalid option.\n");
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
    scanf("%d", &option);
    flushInput();
    return option;
}

int addIncome(Income incomes[], int count) {
    if (count >= MAX_RECORDS) {
        printf("Income list full. Cannot add more entries.\n");
        return count;
    }

    printf("Enter date (YYYY-MM-DD): ");
    fgets(incomes[count].date, MAX_DATE, stdin);
    int len = strlen(incomes[count].date);
    //get rid of \n..fgets includes \n
    
    if (len > 0 && incomes[count].date[len - 1] == '\n') {
        incomes[count].date[len - 1] = '\0';
    }

    flushInput();
    
    printf("Enter description: ");
    fgets(incomes[count].description, MAX_DESC, stdin);
    len = strlen(incomes[count].description);
    //get rid of \n..fgets includes \n
	if (len > 0 && incomes[count].description[len - 1] == '\n') {
        incomes[count].description[len - 1] = '\0';
    }

    printf("Enter amount: ");
    scanf("%f", &incomes[count].amount);
    flushInput();

    printf("Income entry added successfully.\n");
    return count + 1;
}

int addExpense(Expense expenses[], int count) {
    printf("[Stub] Add Expense\n");
    return count;
}

void displayTransactions(Income incomes[], int incomeCount, Expense expenses[], int expenseCount) {
    printf("[Stub] Display Transactions\n");
}

void displayIncomeSummary(Income incomes[], int incomeCount) {
    printf("[Stub] Display Income Summary\n");
}

void displayExpenseSummary(Expense expenses[], int expenseCount) {
    printf("[Stub] Display Expense Summary\n");
}

void exportToFile(Income incomes[], int incomeCount, Expense expenses[], int expenseCount) {
    printf("[Stub] Export to File\n");
}

void loadFromFile(Income incomes[], int *incomeCount, Expense expenses[], int *expenseCount) {
    printf("[Stub] Load from File\n");
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

