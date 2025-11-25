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
Creates a new item with the given name and price.
Initializes its batch list and returns the item.

**create_batch(int id, int qty, char mfg_date[], char exp_date[], char supplier[])**
Creates a batch with ID, quantity, dates, and supplier.
Returns the batch node.

---

### **Find Functions**

**find_category(Category *c_head, char c_name[])**
Searches through the category list for a matching name.
Returns the category or NULL if not found.

**find_item(Category *c_head, char item_name[], char c_name[])**
Looks for a category first, then searches for the item inside it.
Returns the item or NULL.

---

### **Add Functions**

**add_category(Category *cat_head)**
Takes category name from the user and adds it if it doesn't already exist.
Returns the updated head of the category list.

**add_item(Category *cat_head)**
Adds a new item under a valid category after taking its name and price.
Prevents duplicate items.

**add_batch(Category *c_head)**
Adds a new batch to an item inside a category.
Collects full batch details from the user.

---

### **Update Functions**

**update_category(Category *c_head)**
Renames a category if it exists.
Prints an error otherwise.

**update_batch(Category *c_head)**
Searches for a batch by category → item → batch ID.
Updates only the quantity.

**update_item(Category *c_head)**
Changes the price of an item under a category.
Updates only if both exist.

---

### **Delete Functions**

**delete_category(Category *head)**
Deletes the entire category and frees all its items and batches.
Returns the new head of the list.

**delete_item(Category *head)**
Finds and deletes an item from any category.
Also deletes all its batches.

**delete_batch(Category *c_head)**
Searches for a batch by ID across all items and categories.
Deletes it and frees its memory.

---

### **Search Functions**

**search_category(Category *head)**
Prints all items inside a specific category.
Shows an error if the category doesn't exist.

**search_item(Category *head)**
Looks for an item across all categories.
Prints all its batches if found.

**search_batch(Category *c_head)**
Searches through the entire inventory for a batch ID.
Prints its full details with category and item names.

---

### **Display Function**

**display_all(Category *c_head)**
Prints all categories, items, and batches in a clear structure.
Gives a complete view of the inventory.

---

### **File I/O Functions**

**save_to_file(Category *head)**
Writes the entire inventory to `inventory.txt` in a simple text format.
Makes sure data is saved even after closing the program.

**load_from_file()**
Reads from `inventory.txt` and rebuilds all categories, items, and batches.
If the file doesn’t exist, begins with an empty inventory.

---

### **Main Function**

**main()**
Loads existing data, shows the menu, handles user choices, and saves before exiting.
Runs the whole program loop.

---

