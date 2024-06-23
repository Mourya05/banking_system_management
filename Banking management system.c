#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold transaction information
struct Transaction {
    char type[10];
    float amount;
    float balance_after;
};

// Structure to hold bank account information
struct BankAccount {
    char name[50];
    int account_number;
    float balance;
    struct Transaction transactions[100];
    int transaction_count;
};

// Function prototypes
void createAccount(struct BankAccount *accounts, int *num_accounts);
void deposit(struct BankAccount *accounts, int num_accounts);
void withdraw(struct BankAccount *accounts, int num_accounts);
void checkBalance(struct BankAccount *accounts, int num_accounts);
void logTransaction(struct BankAccount *account, const char *type, float amount);
void displayTransactionHistory(struct BankAccount *accounts, int num_accounts);
void displayAllAccounts(struct BankAccount *accounts, int num_accounts);
void addDummyData(struct BankAccount *accounts, int *num_accounts);
void saveAccountsToFile(struct BankAccount *accounts, int num_accounts);
void loadAccountsFromFile(struct BankAccount *accounts, int *num_accounts);

#define FILENAME "accounts.dat"

int main() {
    struct BankAccount accounts[100]; // Array to store bank accounts
    int num_accounts = 0; // Number of accounts currently in the system
    int choice;

    // Load data from file
    loadAccountsFromFile(accounts, &num_accounts);

    // Adding dummy data (only if file is empty)
    if (num_accounts == 0) {
        addDummyData(accounts, &num_accounts);
    }

    do {
        printf("\nBanking System Menu:\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Check Balance\n");
        printf("5. Transaction History\n");
        printf("6. Display All Accounts\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                createAccount(accounts, &num_accounts);
                break;
            case 2:
                deposit(accounts, num_accounts);
                break;
            case 3:
                withdraw(accounts, num_accounts);
                break;
            case 4:
                checkBalance(accounts, num_accounts);
                break;
            case 5:
                displayTransactionHistory(accounts, num_accounts);
                break;
            case 6:
                displayAllAccounts(accounts, num_accounts);
                break;
            case 7:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 7.\n");
        }
    } while(choice != 7);

    // Save data to file before exiting
    saveAccountsToFile(accounts, num_accounts);

    return 0;
}

// Function to create a new bank account
void createAccount(struct BankAccount *accounts, int *num_accounts) {
    int choice;
    if (*num_accounts >= 100) {
        printf("Cannot create more accounts. Maximum limit reached.\n");
        return;
    }

    struct BankAccount newAccount;
    printf("You will be asked to deposit 1000 after creating your account as it is the minimum balance. Is that okay? (1 to continue and 0 to exit): ");
    scanf("%d",&choice);
    while(choice !=1 && choice !=0){
        printf("Invalid choice");
        scanf("%d",&choice);
    }
    if (choice == 1){
        printf("Enter name: ");
    scanf("%s", newAccount.name);
    printf("Enter account number: ");
    scanf("%d", &newAccount.account_number);
    printf("Enter account balance: ");
    scanf("%f",&newAccount.balance);
    while(newAccount.balance < 1000){
        printf("Please enter amount greater than or equal to 1000: ");
        scanf("%f",&newAccount.balance);
    }
    newAccount.transaction_count = 0;

    accounts[*num_accounts] = newAccount;
    (*num_accounts)++;
    printf("Account created successfully.\n");    
    }

    else{
        printf("We are sorry but we can't proceed any further");
    }
    
}

// Function to deposit money into an account
void deposit(struct BankAccount *accounts, int num_accounts) {
    int account_number;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &account_number);

    int i;
    for (i = 0; i < num_accounts; i++) {
        if (accounts[i].account_number == account_number) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            if (amount > 0) {
                accounts[i].balance += amount;
                logTransaction(&accounts[i], "Deposit", amount);
                printf("Deposit successful. New balance: %.2f\n", accounts[i].balance);
            }
            else {
                printf("Invalid amount. Please enter a positive value.\n");
            }
            return;
        }
    }

    printf("Account not found.\n");
}

// Function to withdraw money from an account
void withdraw(struct BankAccount *accounts, int num_accounts) {
    int account_number;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &account_number);

    int i;
    for (i = 0; i < num_accounts; i++) {
        if (accounts[i].account_number == account_number) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if (amount > 0 && amount <= accounts[i].balance) {
                if (accounts[i].balance - amount >= 1000){
                    accounts[i].balance -= amount;
                    logTransaction(&accounts[i], "Withdraw", amount);
                    printf("Withdrawal successful. New balance: %.2f\n", accounts[i].balance);
                }

                else{
                    printf("Withdrawl unsuccessful(Minimum balance required is 1000rs)");
                }
                
            }
            else {
                printf("Invalid amount or insufficient balance.\n");
            }
            return;
        }
    }

    printf("Account not found.\n");
}

// Function to check balance of an account
void checkBalance(struct BankAccount *accounts, int num_accounts) {
    int account_number;
    printf("Enter account number: ");
    scanf("%d", &account_number);

    int i;
    for (i = 0; i < num_accounts; i++) {
        if (accounts[i].account_number == account_number) {
            printf("Account balance: %.2f\n", accounts[i].balance);
            return;
        }
    }

    printf("Account not found.\n");
}

// Function to log a transaction in the account's transaction history
void logTransaction(struct BankAccount *account, const char *type, float amount) {
    struct Transaction newTransaction;
    strcpy(newTransaction.type, type);
    newTransaction.amount = amount;
    newTransaction.balance_after = account->balance;

    account->transactions[account->transaction_count] = newTransaction;
    account->transaction_count++;
}

// Function to display the transaction history of an account
void displayTransactionHistory(struct BankAccount *accounts, int num_accounts) {
    int account_number;
    printf("Enter account number: ");
    scanf("%d", &account_number);

    int i;
    for (i = 0; i < num_accounts; i++) {
        if (accounts[i].account_number == account_number) {
            printf("Transaction History for Account %d:\n", account_number);
            printf("%-12s %-10s %-15s\n", "Type", "Amount", "Balance After");
            printf("----------------------------------------\n");
            for (int j = 0; j < accounts[i].transaction_count; j++) {
                struct Transaction t = accounts[i].transactions[j];
                printf("%-12s %-10.2f %-15.2f\n", t.type, t.amount, t.balance_after);
            }
            return;
        }
    }

    printf("Account not found.\n");
}

// Function to display all accounts present in the bank
void displayAllAccounts(struct BankAccount *accounts, int num_accounts) {
    printf("\nList of all accounts:\n");
    printf("%-10s %-20s %-10s\n", "Acc. No.", "Name", "Balance");
    printf("----------------------------------------\n");
    for (int i = 0; i < num_accounts; i++) {
        printf("%-10d %-20s %-10.2f\n", accounts[i].account_number, accounts[i].name, accounts[i].balance);
    }
}

// Function to add dummy data to the bank
void addDummyData(struct BankAccount *accounts, int *num_accounts) {
    struct BankAccount account1 = {"Alice", 1001, 5000.0, {}, 0};
    struct BankAccount account2 = {"Bob", 1002, 3000.0, {}, 0};
    struct BankAccount account3 = {"Charlie", 1003, 7000.0, {}, 0};
    struct BankAccount account4 = {"David", 1004, 1000.0, {}, 0};

    accounts[(*num_accounts)++] = account1;
    accounts[(*num_accounts)++] = account2;
    accounts[(*num_accounts)++] = account3;
    accounts[(*num_accounts)++] = account4;

    // Adding some transactions for these accounts
    logTransaction(&accounts[0], "Deposit", 5000.0);
    logTransaction(&accounts[1], "Deposit", 3000.0);
    logTransaction(&accounts[2], "Deposit", 7000.0);
    logTransaction(&accounts[3], "Deposit", 1000.0);

    accounts[0].balance -= 500.0;
    logTransaction(&accounts[0], "Withdraw", 500.0);

    accounts[1].balance -= 200.0;
    logTransaction(&accounts[1], "Withdraw", 200.0);

    accounts[2].balance += 1000.0;
    logTransaction(&accounts[2], "Deposit", 1000.0);

    accounts[3].balance -= 500.0;
    logTransaction(&accounts[3], "Withdraw", 500.0);
}

// Function to save accounts data to a file
void saveAccountsToFile(struct BankAccount *accounts, int num_accounts) {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("Could not open file %s for writing.\n", FILENAME);
        return;
    }

    fwrite(&num_accounts, sizeof(int), 1, file);
    fwrite(accounts, sizeof(struct BankAccount), num_accounts, file);

    fclose(file);
}

// Function to load accounts data from a file
void loadAccountsFromFile(struct BankAccount *accounts, int *num_accounts) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("No existing data file found. Starting with an empty list.\n");
        return;
    }

    fread(num_accounts, sizeof(int), 1, file);
    fread(accounts, sizeof(struct BankAccount), *num_accounts, file);

    fclose(file);
}
