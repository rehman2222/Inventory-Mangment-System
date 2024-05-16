#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum ProductCategory {
    ELECTRONICS,
    CLOTHING,
    GROCERY,
    OTHER
};

struct Product {
    int productId;
    char name[50];
    float price;
    int quantity;
    enum ProductCategory category;  
};

void displayProduct(struct Product *product) {
    printf("\n\tProduct ID: %d\n", product->productId);
    printf("\n\tName: %s\n", product->name);
    printf("\n\tPrice: $%.2f\n", product->price);
    printf("\n\tQuantity: %d\n", product->quantity);

    switch (product->category) {
        case ELECTRONICS:
            printf("\n\tCategory: Electronics\n");
            break;
        case CLOTHING:
            printf("\n\tCategory: Clothing\n");
            break;
        case GROCERY:
            printf("\n\tCategory: Grocery\n");
            break;
        case OTHER:
            printf("\n\tCategory: Other\n");
            break;
        default:
            printf("\n\tCategory: Unknown\n");
    }

    printf("\n");
}

void addProduct(struct Product *inventory, int *numProducts) {
    printf("\n\tEnter product name: ");
    scanf("%s", &inventory[*numProducts].name);
    printf("\n\tEnter product price: ");
    scanf("%f", &inventory[*numProducts].price);
    printf("\n\tEnter initial quantity: ");
    scanf("%d", &inventory[*numProducts].quantity);

    printf("\n\tEnter product category (0: Electronics, 1: Clothing, 2: Grocery, 3: Other): ");
    scanf("%d", (int*)&inventory[*numProducts].category);

    inventory[*numProducts].productId = *numProducts + 1;
    (*numProducts)++;
}

void displayInventory(struct Product *inventory, int numProducts) {
    for (int i = 0; i < numProducts; i++) {
        displayProduct(&inventory[i]);
    }
}

void saveToFile(struct Product *inventory, int numProducts) {
    FILE *file = fopen("inventory.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numProducts; i++) {
    fprintf(file, "ID|\tName|\tPrice|\tQuantity|\tCategory|\n %d|\t%s|\t%.2f|\t  %d|\t  %d|\n",
            inventory[i].productId, inventory[i].name, inventory[i].price, inventory[i].quantity, inventory[i].category);


    }

    fclose(file);
    printf("\n\tInventory data saved to file.\n");
}

int loadFromFile(struct Product *inventory) {
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf("\n\tError opening file for reading.\n");
        return 0;
    }

    int count = 0;
    while (1) {
        int result = fscanf(file, "%d %49s %f %d",
                            &inventory[count].productId, inventory[count].name,
                            &inventory[count].price, &inventory[count].quantity);

        if (result == EOF) {
            break;
        } else if (result != 4) {
            printf("Error reading data from the file.\n");
            break;
        }

        count++;
    }

    fclose(file);
    return count;
}

int main() {
    
    const int maxProducts = 100;

    printf("\n\t <<========= Inventory Management System =========>>\n");
    struct Product *inventory = (struct Product *)malloc(maxProducts * sizeof(struct Product));
    if (inventory == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    
    int numProducts = 0;

    
    numProducts = loadFromFile(inventory);

    
    int choice;
    do {
        printf("\n\t1. Add Product\n");
        printf("\n\t2. Display Inventory\n");
        printf("\n\t3. Save Inventory to File\n");
        printf("\n\t4. Exit\n");
        printf("\n\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                
                addProduct(inventory, &numProducts);
                break;
            case 2:
                
                displayInventory(inventory, numProducts);
                break;
            case 3:
                
                saveToFile(inventory, numProducts);
                break;
            case 4:
                
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    
    free(inventory);

    return 0;
}