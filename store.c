#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct product {
    char Name[50];
    float Price;
    int Quantity;
    char Supplier[50];
    char Manufacture[10];
    char Expiry[10];
    struct product * next;
} Product;

Product * add_product(Product * head) {
    Product * new = malloc(sizeof(Product));
    printf("What is the name of the new product?\n");
    scanf("%s", new->Name);
    printf("What is the price of the new product?\n");
    scanf("%f", &new->Price);
    printf("Quantity supplied ?\n");
    scanf("%d", &new->Quantity);
    printf("Who is the supplier?\n");
    scanf("%s", new->Supplier);
    printf("Manufacturing Date in DD/MM/YYYY format:\n");
    scanf("%s", new->Manufacture);
    printf("Expiry Date in DD/MM/YYYY format:\n");
    scanf("%s", new->Expiry);
    new->next=NULL;
    
    if (head==NULL) {
        return new;
    }
    
    Product * temp=head;
    while (temp->next!=NULL) {
        temp=temp->next;
    }
    temp->next=new;
    return head;
}

void view_product(Product * head) {
    Product * temp = head;

    if (temp == NULL) {
        printf("No products in inventory.\n");
        return;
    }

    while (temp != NULL) {
        printf("\n");
        printf("Name: %s\n", temp->Name);
        printf("Price: %.2f\n", temp->Price);
        printf("Quantity: %d\n", temp->Quantity);
        printf("Supplier: %s\n", temp->Supplier);
        printf("MFD: %s\n", temp->Manufacture);
        printf("EXP: %s\n", temp->Expiry);
        printf("------------------------------\n");
        temp = temp->next;
    }
}

int search_product(Product * head, char product[]) {
    Product * temp=head;
    while (temp!=NULL) {
        if (strcmp(temp->Name,product)==0) {
            printf("Product in stock\n");
            return 1;
        }
        temp=temp->next;
    }
    printf("Product not in stock.\n");
    return 0;
}

Product * update_product(Product * head,char product[],int quantity) {
    Product * temp=head;
    while (temp!=NULL) {
        if (strcmp(temp->Name,product)==0) {
            temp->Quantity+=quantity;
            printf("Stock added.\n");
            return head;
        }
        temp=temp->next;
    }
    return head;
}

Product * buy_product(Product * head,char product[],int quantity) {
    Product * temp=head;
    while (temp!=NULL) {
        if (strcmp(temp->Name,product)==0) {
            temp->Quantity-=quantity;
            printf("Stock reduced.\n");
        }
        temp=temp->next;
    }
    return head;
}

int main() {

    Product * head = NULL;
    int choice;

    while (1) {

        printf("\n_______THE INVENTORY________\n");
        printf("1) Add new product\n");
        printf("2) View all products\n");
        printf("3) Search for a product\n");
        printf("4) Add stock to existing product\n");
        printf("5) Buy stock of existing product\n");
        printf("6) Exit\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        switch (choice) {

            case 1: {
                head = add_product(head);
                break;
            }

            case 2: {
                view_product(head);
                break;
            }

            case 3: {
                char name[50];
                printf("Enter product name: ");
                scanf("%s", name);
                search_product(head, name);
                break;
            }

            case 4: {
                char name[50];
                int qty;
                printf("Enter product name: ");
                scanf("%s", name);
                printf("Enter quantity to add: ");
                scanf("%d", &qty);
                head = update_product(head, name, qty);
                break;
            }

            case 5: {
                char name[50];
                int qty;
                printf("Enter product name: ");
                scanf("%s", name);
                printf("Enter quantity to buy: ");
                scanf("%d", &qty);
                head = buy_product(head, name, qty);
                break;
            }

            case 6: {
                printf("Exiting program...\n");
                return 0;
            }

            default: {
                printf("Invalid choice. Try again.\n");
                break;
            }
        }
    }

    return 0;
}
