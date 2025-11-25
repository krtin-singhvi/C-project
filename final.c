#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 50
#define FILE_NAME "inventory.txt"

typedef struct Batch {
    int id;
    int qty;
    char mfg_date[LEN];
    char exp_date[LEN];
    char supplier[LEN];
    struct Batch *next;
} Batch;
typedef struct Item {
    char name[LEN];
    float price;
    struct Item *next;
    Batch * batch_head;
} Item;

typedef struct Category {
    char name[LEN];
    Item *item_head;
    struct Category *next;
} Category;

//==================================CREATE FUNCTIONS============================

Category *create_category(char name[]) {
    Category *new = malloc(sizeof(Category));
    strcpy(new->name, name);
    new->item_head = NULL;
    new->next = NULL;
    return new;
}

Item *create_item(char name[], float price){
    Item *new = malloc(sizeof(Item));

    strcpy(new->name, name);
    new->price = price;
    new->next = NULL;
    new->batch_head = NULL;
    return new;
}

Batch *create_batch(int id, int qty, char mfg_date[], char exp_date[], char supplier[]){
    Batch *new = malloc(sizeof(Batch));
    
    new->id = id;
    new->qty = qty;
    strcpy(new->mfg_date, mfg_date);
    strcpy(new->exp_date, exp_date);
    strcpy(new->supplier, supplier);
    new->next = NULL;
    return new;
} 

//==================================FIND FUNCTIONS=================================
Category *find_category(Category *c_head, char c_name[]){

    while(c_head != NULL){
        if(strcmp(c_head->name, c_name) == 0)
            return c_head;
        c_head = c_head->next;
    }
    return NULL;

}

Item *find_item(Category *c_head, char item_name[], char c_name[]){
    Category *cat = find_category(c_head, c_name);
    if(!cat) return NULL;
    Item * temp = cat->item_head;

    while (temp != NULL){
        if (strcmp(temp->name, item_name) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

//==================================ADD FUNCTIONS=====================================

Category *add_category(Category *cat_head) {
    char name[LEN];
    printf("Enter Category Name: ");
    scanf("%s", name);

    if(find_category(cat_head, name)){
        printf("Category Already Exists!\n");
        return cat_head;
    }
    Category *new = create_category(name);
    new->next = cat_head;
    cat_head = new;

    printf("Category added.\n");
    return new;
}

void add_item(Category *cat_head) {
    float price;
    char item_name[LEN], c_name[LEN];
    
    printf("Enter Category Name: ");
    scanf("%s", c_name);
    Category * cat = find_category(cat_head, c_name);
    if(!cat){
        printf("Category not found.\n");
        return;
    }

    printf("Enter Item Name: ");
    scanf("%s", item_name);
    if(find_item(cat_head, item_name, c_name)){
        printf("Item Already Exists!\n");
        return;
    }
 
    printf("Price of item: ");
    scanf("%f", &price);

    Item *new_item = create_item(item_name, price);
    new_item->next = cat->item_head;
    cat->item_head = new_item;

    printf("Item added.\n");
    return;
}

void add_batch(Category *c_head){
    int id, qty;
    char mfg_date[LEN], exp_date[LEN], supplier[LEN];
    char category_name[LEN], item_name[LEN];
    
    printf("Enter Category Name: ");
    scanf("%s", category_name);
    Category * cat = find_category(c_head, category_name);
    if(!cat){
        printf("Category not found.\n");
        return;
    }
    printf("Enter Item Name: ");
    scanf("%s", item_name);
    Item *item = find_item(c_head, item_name, category_name);
    if(!item){
        printf("Item not found.\n");
        return;
    }
    
    printf("Enter batch id: ");
    scanf("%d", &id);
    printf("Quantity supplied: ");
    scanf("%d", &qty);
    printf("Manufacturing Date: ");
    scanf("%s", mfg_date);
    printf("Expiry Date: ");
    scanf("%s", exp_date);
    printf("Supplier: ");
    scanf("%s", supplier);

    Batch *new_batch = create_batch(id, qty, mfg_date, exp_date, supplier);
    new_batch->next = item->batch_head;
    item->batch_head = new_batch;

    printf("Batch Added.\n");

    return;
}

//=======================================UPDATE FUNCTIONS===================================
void update_category(Category *c_head){
    char c_name[LEN];
    printf("Enter Category Name: ");
    scanf("%s", c_name);
    Category *cat = find_category(c_head, c_name);
    if(!cat){
        printf("Category not found.\n");
        return;
    }
    char new_name[LEN];
    printf("Enter New Name: ");
    scanf("%s", new_name);
    strcpy(cat->name, new_name);
    return;
}

void update_batch(Category * c_head){
    char c_name[LEN], item_name[LEN];
    int qty, batch_id;

    printf("Enter Category Name: ");
    scanf("%s", c_name);
    printf("Enter Item Name: ");
    scanf("%s", item_name);

    Category* cat = find_category(c_head, c_name);
    Item *item = find_item(c_head, item_name, c_name);
    if(!cat){
        printf("Category not found.\n");
        return;
    }
    if(!item){
        printf("Item not found.\n");
        return;
    }

    printf("Enter batch id: ");
    scanf("%d", &batch_id);
    Batch *b_head = item->batch_head;

    while(b_head != NULL){
        if(b_head->id == batch_id){
            printf("Enter new quantity: ");
            scanf("%d", &qty);
            b_head->qty = qty;
            printf("Batch updated.\n");
            return;
        }
        b_head = b_head->next;
    }
    printf("Batch not found.\n");
    return;
}

void update_item(Category *c_head){
    float price;
    char c_name[LEN], item_name[LEN];

    printf("Enter Category Name: ");
    scanf("%s", c_name);
    Category* cat = find_category(c_head, c_name);
    if(!cat){
        printf("Category not found.\n");
        return;
    }
    printf("Enter Item Name: ");
    scanf("%s", item_name);
    Item *item = find_item(c_head, item_name, c_name);
    if(!item){
        printf("Item not found.\n");
        return;
    }

    printf("Enter new price: ");
    scanf("%f", &price);
    item->price = price;
    return;
}
//====================================DELETE FUNCTION===============================================

Category *delete_category(Category *head) {
    if(!head){
        printf("No categories to delete.\n");
        return head;
    }
    char name[LEN];
    printf("Enter Category Name: ");
    scanf("%s", name);

    Category *temp = head;
    if (strcmp(head->name, name)==0){
        Item *i = head->item_head;
        while(i != NULL){
            Item *t = i;
            Batch *b = i->batch_head;
            while(b != NULL){
                Batch *next = b->next;
                free(b);
                b = next;  
            }
            i = i->next;
            free(t);
        }
        head = head->next;
        free(temp);
        printf("Category deleted.\n");
        return head;
    }
    
    while (temp->next != NULL) {
        if (strcmp(temp->next->name, name) == 0){
            Category *d = temp->next;
            Item *i = d->item_head;
            while(i != NULL){
                Item *t = i;
                Batch *b = i->batch_head;
                while(b != NULL){
                    Batch *next = b->next;
                    free(b);
                    b = next;  
                }
                i = i->next;
                free(t);
            }
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

void delete_item(Category *head) {
    if(!head){
        printf("No categories to delete.\n");
        return;
    }
    Category *temp = head;
    char item_name[LEN];
    printf("Enter item name: ");
    scanf("%s", item_name);

    while (temp != NULL) {

        // Case 1: deleting first node of item list
        if (temp->item_head != NULL && strcmp(temp->item_head->name, item_name) == 0) {
            Item *d = temp->item_head;
            Batch *b = d->batch_head;
            while(b != NULL){
                Batch *next = b->next;
                free(b);
                b = next;  
            }

            temp->item_head = temp->item_head->next;
            free(d);
            printf("Item deleted.\n");
            return;
        }

        // Case 2: deleting inside list
        Item *temp1 = temp->item_head;

        while (temp1 != NULL && temp1->next != NULL) {
            if (strcmp(temp1->next->name, item_name) == 0) {
                Item *d = temp1->next;
                Batch *b = d->batch_head;
                while(b != NULL){
                    Batch *next = b->next;
                    free(b);
                    b = next;  
                }
                temp1->next = temp1->next->next;
                free(d);
                printf("Item deleted.\n");
                return;
            }
            temp1 = temp1->next;
        }

        temp = temp->next;
    }

    printf("Item not found.\n");
    return;
}
void delete_batch(Category* c_head){
    if(!c_head){
        printf("No categories to delete.\n");
        return;
    }
    int id;
    printf("Enter batch id: ");
    scanf("%d", &id);

    Category * cat = c_head;
    while(cat != NULL){
        Item *item = cat->item_head;
        while(item != NULL){
            Batch *batch = item->batch_head;
            if (batch != NULL && batch->id == id){
                item->batch_head = batch->next;
                free(batch);
                printf("Batch deleted.\n");
                return;
            }
            while(batch != NULL && batch->next != NULL){
                if(batch->next->id == id){
                    Batch *temp = batch->next;
                    batch->next = batch->next->next;
                    free(temp);
                    printf("Batch deleted.\n");
                    return;
                }
                batch = batch->next;
            }
            item = item->next;
            
        }
        cat = cat->next;
    }
    printf("Batch not found.\n");

}
//=====================================================SEARCH FUNCTIONS========================================================
void search_category(Category *head){
    char c_name[LEN];
    printf("Enter Category name to search:");
    scanf("%s", c_name);
    Category* cat = find_category(head, c_name);
    
    if(cat){
        printf("CATEGORY: %s\n\n", c_name);
        Item *i = cat->item_head;
        while(i){
            printf("ITEM: %s\n", i->name);
            i = i->next;    
        }
        return;
    }
    printf("Category not found.\n");
    return;
}
void search_item(Category *head) {
    char item[LEN];
    printf("Enter item name to search: ");
    scanf("%s", item);
    Category *cat = head;
    while (cat != NULL) {
        Item *i = find_item(head, item, cat->name);
        if(i){
            printf("ITEM: %s\n", item);
            Batch *b = i->batch_head;
            while(b){
                printf("BATCH: %d %s %s %s %d\n", b->id, b->mfg_date, b->exp_date, b->supplier, b->qty);
                b = b->next;
            }
            return;
        }     
        cat = cat->next;
    }
    printf("Item not found.\n");
    return;
}
void search_batch(Category *c_head){
    int id;
    printf("Enter batch id to search: ");
    scanf("%d", &id);

    while(c_head){
        Item *i = c_head->item_head;
        while(i){
            Batch *b = i->batch_head;
            while(b){
                if(b->id == id){
                    printf("BATCH CATEGORY: %s\n", c_head->name);
                    printf("BATCH ITEM: %s\n", i->name);
                    printf("BATCH: %d %s %s %s %d\n", b->id, b->mfg_date, b->exp_date, b->supplier, b->qty);
                    return;
                }
                b = b->next;
            }
            i = i->next;
        }
        c_head = c_head->next;
    }
    printf("Batch not found\n");
    return;
}
//===============================================DISPLAY ALL ITEMS===========================================================
void display_all(Category *c_head){
    while(c_head){
        Item *i = c_head->item_head;
        printf("[CATEGORY]: %s\n", c_head->name);
        while(i){
            Batch *b = i->batch_head;
            printf("[ITEM]: %s\n", i->name);
            while(b){         
                    printf("[BATCH]: %d %s %s %s %d\n", b->id, b->mfg_date, b->exp_date, b->supplier, b->qty);
                    b = b->next;
                }
                i = i->next;
            }
            printf("\n");
            c_head = c_head->next;
        }
        return;
    }

//=============================================FILE IO=====================================================================
void save_to_file(Category *head) {
    FILE *fp = fopen(FILE_NAME, "w");
    if(!fp){
        printf("Error opening file for writing.\n");
        return;
    }

    Category *c = head;
    while(c){
        // Write Category Header
        fprintf(fp, "CATEGORY %s\n", c->name);

        Item *i = c->item_head;
        while(i){
            // Write Item Header
            fprintf(fp, "ITEM %s %.2f\n", i->name, i->price);

            Batch *b = i->batch_head;
            while(b){
                // Write Batch Data
                fprintf(fp, "BATCH %d %d %s %s %s\n",
                        b->id, b->qty, b->mfg_date, b->exp_date, b->supplier);
                b = b->next;
            }
            // Mark end of batches for this item
            fprintf(fp, "ENDITEM\n");
            i = i->next;
        }
        // Mark end of items for this category
        fprintf(fp, "ENDCATEGORY\n");
        c = c->next;
    }

    fclose(fp);
    printf("\n[System] Database saved to %s successfully.\n", FILE_NAME);
}

Category* load_from_file() {
    FILE *fp = fopen(FILE_NAME, "r");
    if(!fp){
        printf("[System] No previous data found (%s). Starting fresh.\n", FILE_NAME);
        return NULL;
    }

    Category *head = NULL;
    Category *current_category = NULL;
    Item *current_item = NULL;

    char keyword[LEN];

    // Read the first word of every line to decide what to do
    while(fscanf(fp, "%s", keyword) != EOF){

        if(strcmp(keyword, "CATEGORY") == 0){
            char cname[LEN];
            fscanf(fp, "%s", cname);
            
            Category *newc = create_category(cname);
            // Insert at HEAD of category list
            newc->next = head;
            head = newc;
            
            // Set context for incoming items
            current_category = newc; 
        }
        else if(strcmp(keyword, "ITEM") == 0){
            char iname[LEN];
            float price;
            fscanf(fp, "%s %f", iname, &price);

            Item *newi = create_item(iname, price);
            
            // Link to current category
            if(current_category != NULL) {
                newi->next = current_category->item_head;
                current_category->item_head = newi;
                current_item = newi; // Set context for incoming batches
            }
        }
        else if(strcmp(keyword, "BATCH") == 0){
            int id, qty;
            char mfg[LEN], exp[LEN], supp[LEN];
            fscanf(fp, "%d %d %s %s %s", &id, &qty, mfg, exp, supp);

            Batch *b = create_batch(id, qty, mfg, exp, supp);
            
            // Link to current item
            if(current_item != NULL) {
                b->next = current_item->batch_head;
                current_item->batch_head = b;
            }
        }
        // These keywords reset the context pointers
        else if(strcmp(keyword, "ENDITEM") == 0){
            current_item = NULL;
        }
        else if(strcmp(keyword, "ENDCATEGORY") == 0){
            current_category = NULL;
        }
    }

    fclose(fp);
    printf("[System] Data loaded successfully.\n");
    return head;
}
int main(){
    // 1. Load data immediately on startup
    Category *head = load_from_file(); 

    int choice;
    do{
        printf("\n=== INVENTORY MANAGEMENT SYSTEM ===\n");
        printf("1. Add Category\n");
        printf("2. Add Item\n");
        printf("3. Add Batch\n");
        printf("4. Update Category\n");
        printf("5. Update Item\n");
        printf("6. Update Batch\n");
        printf("7. Delete Category\n");
        printf("8. Delete Item\n");
        printf("9. Delete Batch\n");
        printf("10. Search Category\n"); // Combined for clarity
        printf("11. Search Item\n");
        printf("12. Search Batch\n");
        printf("13. Display Inventory\n");
        printf("14. Save Data\n");
        printf("15. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1: 
                head = add_category(head); 
                break;
            case 2: 
                add_item(head); 
                break;
            case 3: 
                add_batch(head); 
                break;
            case 4:
                update_category(head);
                break;
            case 5:
                update_item(head);
                break;
            case 6:
                update_batch(head);
                break;
            case 7: 
                head = delete_category(head); 
                break;
            case 8: 
                delete_item(head); 
                break;
            case 9: 
                delete_batch(head); 
                break;
            case 10:
                search_category(head);
                break;
            case 11:
                search_item(head);
                break;
            case 12:
                search_batch(head);
                break;
            case 13: 
                printf("\n--- Displaying All Data ---\n");
                display_all(head); 
                break;
            case 14: 
                save_to_file(head); 
                break;
            case 15: 
                save_to_file(head); // Auto-save on exit
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while(choice != 15);

    return 0;
}
