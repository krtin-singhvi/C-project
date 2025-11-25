# Inventory Management System

## 1. Project Description

This project is a **simple inventory management system** written in C.
It lets you store and manage:

* **Categories** (like Electronics, Food, etc.)
* **Items** inside each category
* **Batches** of each item (different supplies of the same item)

You can add, update, delete, search, and display everything.
The program also **saves all data into a file** (`inventory.txt`) so the inventory is restored next time you run it.

---

## 2. What the Program Can Do

### **Main features**

* Add a new category
* Add an item under any category
* Add batches for a particular item
* Update category name, item price, or batch quantity
* Delete a category, an item, or a batch
* Search for a category, item, or batch
* Display the entire inventory in a clean format
* Save everything to a file
* Load saved data automatically when the program starts
* Auto-save when exiting

### **What information is stored**

* **Category:** only the name
* **Item:** name + price
* **Batch:** batch ID, quantity, manufacturing date, expiry date, supplier name

---

## 3. How the Program Works

### **Data Structure**

We used **linked lists** because they allow easy adding and deleting of data without fixed limits.

* Categories are stored as a linked list.
* Each category has a linked list of items.
* Each item has a linked list of batches.

### **Creating Things**

There are functions that create:

* A category
* An item
* A batch

Each one uses `malloc()` to make space in memory.

### **Finding Things**

Before adding or updating anything, the program checks whether the category or item exists.

### **Adding**

* When you add a category, item, or batch, it gets added to the **front** of the list.
* The program prevents adding duplicates.

### **Updating**

* You can change a category’s name, an item’s price, or a batch’s quantity.
* These updates directly modify the data inside the linked list.

### **Deleting**

* Categories are deleted along with all their items and batches.
* Items are deleted with their batches.
* Batches are deleted one at a time.

Memory is freed properly to avoid leaks.

### **Searching**

* Search category → shows all items under it
* Search item → shows all its batches
* Search batch → shows its category + item + details

### **Displaying**

`display_all()` prints everything in a neat order:

```
[CATEGORY]  
[ITEM]
[BATCH]  
```

### **File Saving and Loading**

Data is saved in a simple text format:

```
CATEGORY <name>
ITEM <name> <price>
BATCH <id> <qty> <mfg> <exp> <supplier>
ENDITEM
ENDCATEGORY
```

* **save_to_file()** writes everything into `inventory.txt`.
* **load_from_file()** reads it back and rebuilds the full inventory when the program starts.

### **Main Menu**

The `main()` function:

* Loads data
* Shows a menu
* Lets the user choose actions
* Saves when exiting

---

## 4. Contributions

**Krtin Singhvi (IE2025019)**
Worked on all the **Update, Delete, and Search** features.
Handled how categories, items, and batches are changed, removed, or looked up.

**Avaneesh Kumar Punjabi (IE2025007)**
Built the **Create, Find, Add, and Display** functions.
Basically handled how data is created, linked together, and shown to the user.

**Ved Savjani (BE2025029)**
Made the **File I/O system**.
Responsible for saving data to `inventory.txt` and loading it back when the program starts.

---

## 5. Short Explanation of Each Function

### **Creation Functions**

**create_category(char name[])**
Creates a new category, sets its name, and initializes its item list to empty.
Returns the newly created category node.

**create_item(char name[], float price)**
Makes a new item with the given name and price.
Also sets its batch list to empty and returns it.

**create_batch(int id, int qty, char mfg_date[], char exp_date[], char supplier[])**
Creates a batch with all its details like ID, quantity, and dates.
Returns the batch node ready to be linked to an item.

---

### **Find Functions**

**find_category(Category *c_head, char c_name[])**
Searches through the category list and returns the category with the matching name.
If it doesn't exist, returns NULL.

**find_item(Category *c_head, char item_name[], char c_name[])**
First finds the category, then looks for the item inside that category.
Returns the item node or NULL if not found.

---

### **Add Functions**

**add_category(Category *cat_head)**
Takes a category name from the user and adds it if it does not already exist.
Returns the new head of the category list.

**add_item(Category *cat_head)**
Asks for category name, then item name and price, and adds the new item under the correct category.
Makes sure the item does not already exist.

**add_batch(Category *c_head)**
Asks for category, item, and full batch details.
Adds the new batch at the beginning of that item’s batch list.

---

### **Update Functions**

**update_category(Category *c_head)**
Lets the user rename a category.
If the category doesn’t exist, prints an error.

**update_batch(Category *c_head)**
Searches for a specific batch using category → item → batch ID.
Updates only the quantity of that batch.

**update_item(Category *c_head)**
Lets the user update the price of an existing item.
Searches for the category and item before applying the change.

---

### **Delete Functions**

**delete_category(Category *head)**
Deletes the entire category and frees all its items and batches properly.
Returns the new head of the category list.

**delete_item(Category *head)**
Deletes an item from whichever category it belongs to.
Also frees all batches under that item.

**delete_batch(Category *c_head)**
Searches the entire inventory for a batch by ID.
Deletes the batch and frees its memory.

---

### **Search Functions**

**search_category(Category *head)**
Prints all items under a specific category.
If the category is not found, notifies the user.

**search_item(Category *head)**
Searches for an item across all categories.
If found, prints all batches belonging to that item.

**search_batch(Category *c_head)**
Searches every category and item for a matching batch ID.
Prints the batch details along with the category and item it belongs to.

---

### **Display Function**

**display_all(Category *c_head)**
Prints the entire inventory in a structured way: Categories → Items → Batches.
Helps the user see everything stored so far.

---

### **File I/O Functions**

**save_to_file(Category *head)**
Writes all categories, items, and batches into `inventory.txt` in a simple readable format.
Ensures your inventory is not lost when you close the program.

**load_from_file()**
Reads data from `inventory.txt` (if it exists) and rebuilds the entire inventory structure.
If the file doesn’t exist, starts with an empty inventory.

---

### **Main Function**

**main()**
Starts by loading saved data, then shows a menu and handles all user choices in a loop.
Auto-saves all data before exiting to prevent data loss.

