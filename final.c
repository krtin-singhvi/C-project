#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 50
#define FILE "inventory.txt"

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

Category *create_category(char name[]){
    Category *new = malloc(sizeof(Category));
    strcpy(new->name, name);
    new->items = NULL;
    new->next = NULL;
    return new;
}

void add_category(Category *head){
    char name[LEN];
    printf("Enter category name: ");
    scanf("%s", name);
    for(; head->next != NULL; head = head->next){
        if (strcmp(head->name, name) == 0)
            printf("Category already exists!\n");
    }
    head->next = create_category(name);

}

Category *find_category(Category *head){
    char name[LEN];
    scanf("%s", name);
    for(Category * temp = head; temp->next != NULL; temp = temp->next){
        if (strcmp(temp->name, name) == 0)
            return temp;
    }
   return NULL; 
}

Category *delete_category(char name[], Category *head){
    for(; head->next != NULL; head = head->next){
        if (strcmp(head->next->name, name) == 0){
            Category *temp = head->next;
            head->next = head->next->next;
            free(temp);
        }
}

void view_categories(Category *head){
    for(int i = 1; head != NULL; head = head->next, i++)
        printf("%d. %s\n",i, head->name);
}

//ITEM FUNCTIONS

Item * create_item(int id, char name[], int qty, float price, char mfg_date[], char exp_date[] ,char supplier[]) {
    Item * new = malloc(sizeof(Item));
    strcpy(new->name,name);
    new->id=id;
    new->qty=qty;
    new->price=price;
    strcpy(new->mfg_date,mfg_date);
    strcpy(new->exp_date,exp_date);
    strcpy(new->supplier,supplier);
    new->next=NULL;
    return new;
}

void add_item(Category *head, char category_name[]){
    Category * cat = find_category(head);
    if (!cat) {
        return;
    }
    int id;
    printf("Enter item id : ");
    scanf("%d", &id);
    char name[LEN];
    printf("Enter product name:");
    scanf("%s", name);
    int qty;
    printf("Quantity supplied: ");
    scanf("%d", &qty);
    float price;
    printf("Price of item : ");
    scanf("%f" , &price);
    char mfg_date[LEN];
    printf("Manufacturing Date :");
    scanf("%s", mfg_date);
    char exp_date[LEN];
    printf("Expiry Date : ");
    scanf("%s", exp_date);
    char supplier[LEN];
    printf("Supplier : ");
    scanf("%s", supplier);

    Item * checker = cat->items;
    while (checker!=NULL) {
        if (checker->id==id) {
            printf("Item with this ID already exists.\n");
        }
        checker=checker->next;
    }
    Item * new = create_item(id,name,qty,price,mfg_date,exp_date,supplier)
    new->next=cat->items;
    cat->items=new;
}

void update_item(char item[], Category * head){
    Category * temp = head;
    Item * temp1=temp->items;
    int qty;
    scanf("%d", &qty);
    int price;
    scanf("%d", &price);
    int choice;
    printf("What do you want to change?\n");
    printf("1)Change only price.\n");
    printf("2)Increase quantity.\n");
    printf("3)Decrease quantity.\n");
    printf("4)Increase quantity and change price.\n");
    printf("5)Decrease quantity and change price.\n");
    printf("\n");
    printf("Enter your choice : ")
    scanf("%d", &choice);

    while(temp!=NULL) {
                while (temp1!=NULL) {
                    if (strcmp(temp1->name,item)==0) {
                        temp1->price=price;
                        return;
                    }
                    temp1=temp1->next;
                }
                temp=temp->next;
            }
            
    switch(choice) {
        case 1 : {
            while(temp!=NULL) {
                while (temp1!=NULL) {
                    if (strcmp(temp1->name,item)==0) {
                        temp1->price=price;
                        return;
                    }
                    temp1=temp1->next;
                }
                temp=temp->next;
            }
        }
        case 2 : {
             while(temp!=NULL) {
                while (temp1!=NULL) {
                    if (strcmp(temp1->name,item)==0) {
                        temp1->qty+=qty;
                        return;
                    }
                    temp1=temp1->next;
                }
                temp=temp->next;
            }
        }
        case 3 : {
            while(temp!=NULL) {
                while (temp1!=NULL) {
                    if (strcmp(temp1->name,item)==0) {
                        temp1->qty-=qty;
                        return;
                    }
                    temp1=temp1->next;
                }
                temp=temp->next;
            }
        }
        case 4 : {
            while(temp!=NULL) {
                while (temp1!=NULL) {
                    if (strcmp(temp1->name,item)==0) {
                        temp1->qty+=qty;
                        temp1->price=price;
                        return;
                    }
                    temp1=temp1->next;
                }
                temp=temp->next;
            }
        }
        case 5 : {
            ase 4 : {
            while(temp!=NULL) {
                while (temp1!=NULL) {
                    if (strcmp(temp1->name,item)==0) {
                        temp1->qty+=qty;
                        temp1->price=price;
                        return;
                    }
                    temp1=temp1->next;
                }
                temp=temp->next;
            }
        }
        }
    }
}

void delete_item(char item[], Category * head){
    Category * 

}
void view_items(char category_name[]);

char *search_item(int id);