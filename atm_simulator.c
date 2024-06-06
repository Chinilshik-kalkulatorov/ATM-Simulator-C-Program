#include <stdio.h>
#include <string.h>

// Structure to store card information
struct Card {
    char pin[5];
    float balance;
    int attempts;
};

// Initialize cards
struct Card cards[2] = {
    {"1234", 1234.60, 0},
    {"5678", 848.50, 0}
};

// Function prototypes
void displayMenu(int cardIndex);
void changePin(int cardIndex);
void checkBalance(int cardIndex);
void withdrawMoney(int cardIndex);
void depositMoney(int cardIndex);
void logTransaction(const char *transaction);
void ejectCard(int *cardIndex);

int main() {
    int cardIndex = -1;
    char input[10];
    FILE *file = fopen("transactions.txt", "a");

    while (1) {
        if (cardIndex == -1) {
            printf("Select Card (1 or 2): ");
            fgets(input, 10, stdin);
            if (input[0] == '1' || input[0] == '2') {
                cardIndex = input[0] - '1';
            } else {
                printf("Invalid card selection.\n");
                continue;
            }
        }

        printf("Enter PIN: ");
        fgets(input, 10, stdin);
        input[strcspn(input, "\n")] = 0;  // Remove newline character

        if (strcmp(cards[cardIndex].pin, input) == 0) {
            cards[cardIndex].attempts = 0;
            displayMenu(cardIndex);
        } else {
            cards[cardIndex].attempts++;
            if (cards[cardIndex].attempts >= 3) {
                printf("Card retained. Contact the bank.\n");
                cardIndex = -1;
                continue;
            } else {
                printf("Incorrect PIN. Try again.\n");
            }
        }
    }

    fclose(file);
    return 0;
}

void displayMenu(int cardIndex) {
    char input[10];
    while (1) {
        printf("\n1. Change PIN\n2. Check Balance\n3. Withdraw Money\n4. Deposit Money\n5. Eject Card\n6. Quit\n");
        printf("Select an option: ");
        fgets(input, 10, stdin);

        switch (input[0]) {
            case '1':
                changePin(cardIndex);
                break;
            case '2':
                checkBalance(cardIndex);
                break;
            case '3':
                withdrawMoney(cardIndex);
                break;
            case '4':
                depositMoney(cardIndex);
                break;
            case '5':
                ejectCard(&cardIndex);
                if (cardIndex == -1) return;
                break;
            case '6':
                printf("Quitting...\n");
                return;
            default:
                printf("Invalid option. Try again.\n");
        }
    }
}

void changePin(int cardIndex) {
    char newPin[5];
    printf("Enter new PIN: ");
    fgets(newPin, 5, stdin);
    newPin[strcspn(newPin, "\n")] = 0;  // Remove newline character
    strcpy(cards[cardIndex].pin, newPin);
    printf("PIN changed successfully.\n");
    logTransaction("Changed PIN");
}

void checkBalance(int cardIndex) {
    printf("Current balance: £%.2f\n", cards[cardIndex].balance);
    logTransaction("Checked Balance");
}

void withdrawMoney(int cardIndex) {
    float amount;
    printf("Enter amount to withdraw (multiples of 5, 10, 20): ");
    scanf("%f", &amount);
    getchar();  // Clear newline character from input buffer

    if ((int)amount % 5 == 0 && amount <= cards[cardIndex].balance) {
        cards[cardIndex].balance -= amount;
        printf("Withdrawal successful. New balance: £%.2f\n", cards[cardIndex].balance);
        logTransaction("Withdrew Money");
    } else {
        printf("Invalid amount or insufficient balance.\n");
    }
}

void depositMoney(int cardIndex) {
    float amount;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
    getchar();  // Clear newline character from input buffer

    cards[cardIndex].balance += amount;
    printf("Deposit successful. New balance: £%.2f\n", cards[cardIndex].balance);
    logTransaction("Deposited Money");
}

void logTransaction(const char *transaction) {
    FILE *file = fopen("transactions.txt", "a");
    fprintf(file, "%s\n", transaction);
    fclose(file);
}

void ejectCard(int *cardIndex) {
    printf("Card ejected.\n");
    *cardIndex = -1;
}
