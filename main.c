#include <stdio.h>
#define MAX_PRODUCTS 20
#define NAME_LENGTH 30

int productIDs[MAX_PRODUCTS];
int quantities[MAX_PRODUCTS];
int prices[MAX_PRODUCTS];
char productNames[MAX_PRODUCTS][NAME_LENGTH]; // For product names
int productCount = 0;
int rack[3][3];

int findProductIndex(int id);
void addProduct();
void searchProduct();
void updateQuantity();
void rackReport();
void calculateStockValuesreport();
void displayAllProducts();
void initializeRack();

int main() {
    int choice;
    initializeRack();
    do {
        printf("\n==== Warehouse Menu ====\n");
        printf("1. Add Product\n");
        printf("2. Search Product (By ID)\n");
        printf("3. Update Quantity\n");
        printf("4. Generate Rack Report\n");
        printf("5. Calculate Stock Value for Each Product\n");
        printf("6. Display All Products\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();  // consume newline

        if (choice == 1)
         {
            addProduct();
        } 
        else if (choice == 2) 
        {
            searchProduct();
        } else if (choice == 3) {
            updateQuantity();
        } else if (choice == 4) {
            rackReport();
        } else if (choice == 5) {
            calculateStockValuesreport();
        } else if (choice == 6) {
            displayAllProducts();
        } else if (choice == 0) {
            printf("Exiting program......\n");
        } else {
            printf("Invalid choice. Try again\n");
        }
    } while (choice != 0);
    return 0;
}

int findProductIndex(int id) {
    for (int i = 0; i < productCount; i++) {
        if (productIDs[i] == id) {
            return i;
        }
    }
    return -1;
}

void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("Warehouse full. Cannot add more products.\n");
        return;
    }
    int id, qty, price, idx;
    char name[NAME_LENGTH];

    printf("Enter Product ID (number): ");
    scanf("%d", &id);
    getchar();  // consume newline
    idx = findProductIndex(id);
    if (idx != -1) {
        printf("Duplicate Product ID! Not allowed.\n");
        return;
    }

    printf("Enter Product Name (max 29 chars, no spaces): ");
    scanf("%29s", name);
    // copy to global array
    for(int i=0; i < NAME_LENGTH; i++) {
        productNames[productCount][i] = name[i];
        if(name[i] == '\0') break;
    }

    printf("Enter Quantity (positive): ");
    scanf("%d", &qty);
    if (qty <= 0) {
        printf("Invalid quantity. Must be positive\n");
        return;
    }

    printf("Enter Price per unit (positive): ");
    scanf("%d", &price);
    if (price <= 0) {
        printf("Invalid price.\n");
        return;
    }

    productIDs[productCount] = id;
    quantities[productCount] = qty;
    prices[productCount] = price;
    productCount++;
    printf("Product added successfully.\n");
}

void searchProduct() {
    int id;
    printf("Enter Product ID to search: ");
    scanf("%d", &id);
    int idx = findProductIndex(id);
    if (idx == -1) {
        printf("Not Found.\n");
    } else {
        printf("ID: %d, Name: %s, Quantity: %d, Price: %d\n", productIDs[idx], productNames[idx], quantities[idx], prices[idx]);
    }
}

void updateQuantity() {
    int id, idx, ch, amt;
    printf("Enter Product ID to update: ");
    scanf("%d", &id);

    idx = findProductIndex(id);
    if (idx == -1) {
        printf("Not Found.\n");
        return;
    }
    printf("1. Increase Quantity\n2. Decrease Quantity\nEnter your choice to update: ");
    scanf("%d", &ch);

    printf("Enter Amount: ");
    scanf("%d", &amt);

    if (ch == 1) {
        if (amt > 0) {
            quantities[idx] += amt;
            printf("Updated Quantity: %d\n", quantities[idx]);
        } else {
            printf("Invalid amount.\n");
        }
    } else if (ch == 2) {
        if (amt > 0 && quantities[idx] >= amt) {
            quantities[idx] -= amt;
            printf("Updated Quantity: %d\n", quantities[idx]);
        } else {
            printf("Cannot decrease. Invalid amount or insufficient quantity.\n");
        }
    } else {
        printf("Invalid choice.\n");
    }
}

void initializeRack() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            rack[i][j] = 0;
}

void rackReport() {
    int i, j, max, min, total = 0;
    int maxRow = 0, maxCol = 0, minRow = 0, minCol = 0;

    printf("Enter 3x3 rack matrix (item counts):\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            scanf("%d", &rack[i][j]);
        }
    }
    max = min = rack[0][0];
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            total += rack[i][j];
            if (rack[i][j] > max) {
                max = rack[i][j];
                maxRow = i;
                maxCol = j;
            }
            if (rack[i][j] < min) {
                min = rack[i][j];
                minRow = i;
                minCol = j;
            }
        }
    }

    printf("Rack Matrix:\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d\t", rack[i][j]);
        }
        printf("\n");
    }
    printf("Maximum stock: %d at (%d,%d)\n", max, maxRow, maxCol);
    printf("Minimum stock: %d at (%d,%d)\n", min, minRow, minCol);
    printf("Total stock across racks: %d\n", total);
}

void calculateStockValuesreport() {
    if (productCount == 0) {
        printf("No products available.\n");
        return;
    }

    int stockValue[MAX_PRODUCTS];
    int maxValue, minValue, maxIdx = 0, minIdx = 0, totalValue = 0;

    for (int i = 0; i < productCount; i++) {
        stockValue[i] = quantities[i] * prices[i];
    }
    maxValue = minValue = stockValue[0];
    totalValue = stockValue[0];
    for (int i = 1; i < productCount; i++) {
        totalValue += stockValue[i];
       (stockValue > maxValue) ? (maxValue = stockValue, maxIdx = i) : 0;
        (stockValue < minValue) ? (minValue = stockValue, minIdx = i) : 0;
    }

    printf("\nProduct ID\tName\tStock Value\n");
    for (int i = 0; i < productCount; ++i) {
        printf("%d\t\t%s\t%d\n", productIDs[i], productNames[i], stockValue[i]);
    }
    printf("Product with highest stock value: ID %d, Name %s, Value %d\n", productIDs[maxIdx], productNames[maxIdx], maxValue);
    printf("Product with lowest stock value: ID %d, Name %s, Value %d\n", productIDs[minIdx], productNames[minIdx], minValue);
    printf("Total warehouse value: %d\n", totalValue);
}

void displayAllProducts() {
    if (productCount == 0) {
        printf("No products to display.\n");
        return;
    }

    for (int i = 0; i < productCount; ++i) {
        int stockValue = quantities[i] * prices[i];
        printf("\nProduct id %d prouduct name %s  product quantity %d  product price%d  stock value%d\n", productIDs[i], productNames[i], quantities[i], prices[i], stockValue);
    }
}
