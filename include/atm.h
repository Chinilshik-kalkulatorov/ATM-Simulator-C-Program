#ifndef ATM_H
#define ATM_H

#include <stdio.h>
#include <string.h>

// Structure to store card information
struct Card {
    char pin[5];
    float balance;
    int attempts;
};

// Initialize cards
extern struct Card cards[2];

// Function prototypes
void displayMenu(int cardPointer);
void changePin(int cardPointer);
void checkBalance(int cardPointer);
void withdrawMoney(int cardPointer);
void depositMoney(int cardPointer);
void logTransaction(const char *transaction);
void ejectCard(int *cardPointer);

#endif // ATM_H
