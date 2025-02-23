#include <stdio.h>
#include <stdlib.h> // For system("pause")
#include <unistd.h> // For usleep() function

#define MENU_SIZE 5 // Number of items in the menu
#define SGST_RATE 9 // SGST rate in percentage
#define CGST_RATE 9 // CGST rate in percentage

// Structure to represent an item in the menu
struct MenuItem {
    char name[50];
    int price;
};

// Function to print the menu
void printMenu(const struct MenuItem menu[]) {
    printf("\n\033[1;32mWelcome to Veronica's Cafe!\033[0m\n");
    printf("--------- Menu ---------\n");
    for (int i = 0; i < MENU_SIZE; i++) {
        printf("%d. %s - $%d\n", i + 1, menu[i].name, menu[i].price);
    }
    printf("------------------------\n");
}

// Function to take orders and calculate the bill
int takeOrder(const struct MenuItem menu[], int orderedItems[], int quantities[]) {
    int totalBill = 0;
    int choice, quantity;
    char option;

    printf("\nEnter the item number and quantity (e.g., 1 2 for first item with quantity 2):\n");

    while (1) {
        printf("Item: ");
        scanf("%d", &choice);
        if (choice < 1 || choice > MENU_SIZE) {
            printf("Invalid item number. Please enter a valid item number.\n");
            continue;
        }
        choice--; // Adjusting choice for array indexing

        printf("Quantity: ");
        scanf("%d", &quantity);
        if (quantity <= 0) {
            printf("Invalid quantity. Please enter a quantity greater than zero.\n");
            continue;
        }

        orderedItems[choice] = 1; // Mark the item as ordered
        quantities[choice] = quantity; // Store the quantity ordered

        totalBill += menu[choice].price * quantity;

        printf("Do you want to order anything else? (y/n): ");
        scanf(" %c", &option);
        if (option == 'n' || option == 'N') {
            break;
        }
    }

    return totalBill;
}

// Function to display a rectangular colorful loading bar with percentage
void displayLoadingBar() {
    printf("\nProcessing your order...\n\n\n\n\n");

    int width = 25; // Width of the loading bar
    int sleepTime = 100000; // Sleep time in microseconds (100000 microseconds = 0.1 second)
    int color = 32; // ANSI color code (green)

    for (int i = 0; i <= width; i++) {
        printf("\033[1;%dm", color); // Set color for the current block
        printf("[");
        for (int j = 0; j < i; j++) {
            printf(":");
        }
        for (int j = i; j < width; j++) {
            printf(" ");
        }
        printf("] %d%%", (i * 100) / width); // Print percentage
        printf("\r");
        fflush(stdout);
        usleep(sleepTime); // Sleep for sleepTime microseconds
    }

    printf("\033[0m\n\n\n\n\n"); // Reset color after loading bar
}

// Function to calculate SGST
int calculateSGST(int totalBill) {
    return (totalBill * SGST_RATE) / 100;
}

// Function to calculate CGST
int calculateCGST(int totalBill) {
    return (totalBill * CGST_RATE) / 100;
}

// Function to generate invoice
void generateInvoice(const struct MenuItem menu[], const int orderedItems[], const int quantities[], int totalBill) {
    printf("\nVeronica's Cafe\n123, Cafe Street, Mumbai-9xx001");
    printf("\nEmail: info@veroscafe.com");
    printf("\nGSTIN: 95876015056493xx\n");
    printf("\n\033[1;33m--------------- INVOICE ---------------\033[0m\n");
    printf("Item Purchased\t\tQuantity\tPrice\n");
    for (int i = 0; i < MENU_SIZE; i++) {
        if (orderedItems[i]) {
            printf("%s\t\t%d\t\t$%d\n", menu[i].name, quantities[i], menu[i].price * quantities[i]);
        }
    }
    printf("\033[1;33m----------------------------------------\033[0m\n");
    printf("\033[1;33mSubtotal\t\t\t\t$%d\033[0m\n", totalBill);
    int sgst = calculateSGST(totalBill);
    printf("\033[1;33mSGST (%d%%)\t\t\t\t$%d\033[0m\n", SGST_RATE, sgst);
    int cgst = calculateCGST(totalBill);
    printf("\033[1;33mCGST (%d%%)\t\t\t\t$%d\033[0m\n", CGST_RATE, cgst);
    printf("\033[1;33m----------------------------------------\033[0m\n");
    printf("\033[1;33mTotal Bill\t\t\t\t$%d\033[0m\n", totalBill + sgst + cgst);
    printf("\033[1;33m----------------------------------------\033[0m\n");
}

int main() {
    // Define menu items
    struct MenuItem menu[MENU_SIZE] = {
        {"Americano", 200},
        {"Espresso", 150},
        {"Latte", 130},
        {"Cappuccino", 100},
        {"Hot Chocolate", 250}
    };

    // Array to track ordered items and their quantities
    int orderedItems[MENU_SIZE] = {0}; // Initialize all to 0 (not ordered)
    int quantities[MENU_SIZE] = {0}; // Initialize all to 0 (quantity)

    printMenu(menu);
    int totalBill = takeOrder(menu, orderedItems, quantities);

    displayLoadingBar(); // Display loading bar after taking the order

    generateInvoice(menu, orderedItems, quantities, totalBill); // Generate invoice

    printf("\nThank you for visiting Veronica's Cafe!");
    printf("\nCOPYRIGHT (C) Veronica's Cafe 1998.");
    printf("\nALL RIGHTS RESERVED\n\n");

    // Pause before closing console window (for Windows)
    system("pause");
    return 0;
}




