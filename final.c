#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 50
#define FILE_NAME "inventory.txt"

typedef struct Item {
    int id;
    char name[LEN];
    int qty;
    float price;
    char mfg_date[LEN];
    char exp_date[LEN];
    char supplier[LEN];
    struct Item *next;
} Item;

typedef struct Category {
    char name[LEN];
    Item *items;
    struct Category *next;
} Category;

// CATEGORY FUNCTIONS

Category *create_category(char name[]) {
    Category *new = malloc(sizeof(Category));
    strcpy(new->name, name);
    new->items = NULL;
    new->next = NULL;
    return new;
}

void add_category(Category *head) {
    char name[LEN];
    printf("Enter category name: ");
    scanf("%s", name);

    Category *temp = head;

    while (temp->next != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("Category already exists!\n");
            return;
        }
        temp = temp->next;
    }

    if (strcmp(temp->name, name) == 0) {
        printf("Category already exists!\n");
        return;
    }

    temp->next = create_category(name);
}

Category *find_category(Category *head) {
    char name[LEN];
    printf("Enter category name: ");
    scanf("%s", name);

    for (Category *temp = head; temp != NULL; temp = temp->next) {
        if (strcmp(temp->name, name) == 0)
            return temp;
    }

    printf("Category not found.\n");
    return NULL;
}

Category *delete_category(char name[], Category *head) {
    Category *temp = head;

    while (temp->next != NULL) {
        if (strcmp(temp->next->name, name) == 0) {
            Category *d = temp->next;
            temp->next = temp->next->next;

            free(d);
            printf("Category deleted.\n");
            return head;
        }
        temp = temp->next;
    }

    printf("Category not found.\n");
    return head;
}

void view_categories(Category *head) {
    int i = 1;
    for (; head != NULL; head = head->next, i++)
        printf("%d. %s\n", i, head->name);
}


// ITEM FUNCTIONS

Item *create_item(int id, char name[], int qty, float price, char mfg_date[],
                  char exp_date[], char supplier[]) {
    Item *new = malloc(sizeof(Item));

    new->id = id;
    strcpy(new->name, name);
    new->qty = qty;
    new->price = price;
    strcpy(new->mfg_date, mfg_date);
    strcpy(new->exp_date, exp_date);
    strcpy(new->supplier, supplier);

    new->next = NULL;
    return new;
}

void add_item(Category *head) {
    Category *cat = find_category(head);
    if (!cat) return;

    int id;
    char name[LEN], mfg_date[LEN], exp_date[LEN], supplier[LEN];
    int qty;
    float price;

    printf("Enter item id: ");
    scanf("%d", &id);

    printf("Enter product name: ");
    scanf("%s", name);

    printf("Quantity supplied: ");
    scanf("%d", &qty);

    printf("Price of item: ");
    scanf("%f", &price);

    printf("Manufacturing Date: ");
    scanf("%s", mfg_date);

    printf("Expiry Date: ");
    scanf("%s", exp_date);

    printf("Supplier: ");
    scanf("%s", supplier);

    // Check ID duplicate
    Item *checker = cat->items;
    while (checker != NULL) {
        if (checker->id == id) {
            printf("Item with this ID already exists.\n");
            return;
        }
        checker = checker->next;
    }

    Item *new = create_item(id, name, qty, price, mfg_date, exp_date, supplier);

    new->next = cat->items;
    cat->items = new;

    printf("Item added.\n");
}

Item *search_item(char item[], Category *head) {
    Category *temp = head;

    while (temp != NULL) {
        Item *temp1 = temp->items;

        while (temp1 != NULL) {
            if (strcmp(temp1->name, item) == 0) {
                return temp1;
            }
            temp1 = temp1->next;
        }
        temp = temp->next;
    }
    printf("Item not found.\n");
    return NULL;
}

void update_item(char name[], Category *head) {
    int qty;
    float price;
    int choice;

    Item *change = search_item(name, head);
    if (!change) return;

    printf("What do you want to change?\n");
    printf("1) Change price\n");
    printf("2) Increase quantity\n");
    printf("3) Decrease quantity\n");
    printf("4) Increase quantity & change price\n");
    printf("5) Decrease quantity & change price\n");
    printf("Enter your choice: ");

    scanf("%d", &choice);

    switch (choice) {
    case 1:
        printf("New price: ");
        scanf("%f", &price);
        change->price = price;
        break;

    case 2:
        printf("Quantity added: ");
        scanf("%d", &qty);
        change->qty += qty;
        break;

    case 3:
        printf("Quantity removed: ");
        scanf("%d", &qty);
        change->qty -= qty;
        break;

    case 4:
        printf("Quantity added: ");
        scanf("%d", &qty);
        change->qty += qty;
        printf("New price: ");
        scanf("%f", &price);
        change->price = price;
        break;

    case 5:
        printf("Quantity removed: ");
        scanf("%d", &qty);
        change->qty -= qty;
        printf("New price: ");
        scanf("%f", &price);
        change->price = price;
        break;
    }

    printf("Item updated.\n");
}

Item *delete_item(char item[], Category *head) {
    Category *temp = head;

    while (temp != NULL) {

        // Case 1: deleting first node of item list
        if (temp->items != NULL && strcmp(temp->items->name, item) == 0) {
            Item *d = temp->items;
            temp->items = temp->items->next;
            free(d);
            printf("Item deleted.\n");
            return NULL;
        }

        // Case 2: deleting inside list
        Item *temp1 = temp->items;

        while (temp1 != NULL && temp1->next != NULL) {
            if (strcmp(temp1->next->name, item) == 0) {
                Item *d = temp1->next;
                temp1->next = temp1->next->next;
                free(d);
                printf("Item deleted.\n");
                return temp1;
            }
            temp1 = temp1->next;
        }

        temp = temp->next;
    }

    printf("Item not found.\n");
    return NULL;
}

void view_items(Category *head) {
    Category *temp = head;

    while (temp != NULL) {
        Item *temp1 = temp->items;

        while (temp1 != NULL) {
            printf("\n------------------\n");
            printf("Product ID: %d\n", temp1->id);
            printf("Product Name: %s\n", temp1->name);
            printf("Product Price: %.2f\n", temp1->price);
            printf("Quantity Available: %d\n", temp1->qty);
            printf("Manufactured On: %s\n", temp1->mfg_date);
            printf("Expires On: %s\n", temp1->exp_date);
            printf("Supplied By: %s\n", temp1->supplier);
            printf("------------------\n");
            temp1 = temp1->next;
        }

        temp = temp->next;
    }
}
