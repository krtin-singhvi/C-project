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

### Creation

`create_category()` – Makes a new category and returns it.
`create_item()` – Makes a new item with a name and price.
`create_batch()` – Makes a new batch with id, qty, dates, and supplier.

### Finding

`find_category()` – Looks for a category by name.
`find_item()` – Looks for an item inside a category.

### Adding

`add_category()` – Adds a new category if it doesn’t already exist.
`add_item()` – Adds a new item to a category.
`add_batch()` – Adds a new batch to an item.

### Updating

`update_category()` – Changes the category’s name.
`update_item()` – Changes the item’s price.
`update_batch()` – Changes the quantity of a batch.

### Deleting

`delete_category()` – Removes a category and everything inside it.
`delete_item()` – Removes an item and all its batches.
`delete_batch()` – Removes a batch by ID.

### Searching

`search_category()` – Shows all items in that category.
`search_item()` – Shows all batches of that item.
`search_batch()` – Shows details of a batch.

### Display

`display_all()` – Prints the entire inventory.

### File I/O

`save_to_file()` – Saves everything to `inventory.txt`.
`load_from_file()` – Loads data back from the file.

### Main

`main()` – Runs the menu, handles user choices, loads on start, saves on exit.

---

If you want, I can turn this into a **downloadable README.md file**.
