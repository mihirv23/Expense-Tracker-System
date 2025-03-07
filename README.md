# Expense Tracking System

## Overview

The **Expense Tracking System** is a menu-driven application designed to track family expenses efficiently. It allows users to **add, update, and delete expenses** while maintaining a structured record of **individuals, families, and their financial transactions**. 

The system is implemented using **linked lists** with **double pointers** for efficient management of dynamic memory.

## Features

- **User Management**: Add users with unique IDs, names, and income details.
- **Expense Tracking**: Categorize expenses into Rent, Utilities, Groceries, Stationary, and Leisure.
- **Family Structure**: Users belong to families (1–4 members), and family expenses are automatically calculated.
- **Sorting & Organization**: Expenses are stored in a sorted manner based on User ID and Expense ID.
- **Dynamic Updates**: Modify and delete individual or family details while ensuring consistency.
- **Expense Analysis**:
  - Get total monthly family expense and compare it with family income.
  - View expenses by category and individual contributions.
  - Identify the highest expense day of the month.

## Implementation Details

The project is implemented using **linked lists** with **double pointers** for efficient dynamic memory allocation and management. 

### **Data Structures Used**
1. **Individual Node**:
   - `User ID`
   - `User Name`
   - `Income`

2. **Family Node**:
   - `Family ID`
   - `Family Name`
   - `List of Individuals` (linked list reference)
   - `Total Family Income`
   - `Total Monthly Family Expense`

3. **Expense Node**:
   - `Expense ID`
   - `User ID` (Reference to Individual)
   - `Expense Category` (Rent, Utility, Grocery, etc.)
   - `Expense Amount`
   - `Date of Expense`

## Functions Implemented

### `void addUser(user** u1)`
- Adds a new user and stores users **sorted by User ID**.

### `void addExpense(expense** e1, user** u1, fam** f1)`
- Adds an expense entry linked to a user and updates the family expense.

### `void createFamily(fam** f1, user** u1)`
- Forms a family with a minimum of **1** and a maximum of **4** members.
- Updates **total family expense** upon creation.

### `void update_or_delete_individual_Family_details(fam** f1, user** u1)`
- Updates individual or family details.
- If an individual is deleted and is the **only member**, the family is automatically deleted.

### `void update_delete_expense(expense** e1, user** u1, fam** f1)`
- Modifies or removes an expense while ensuring **data consistency**.

### `void get_total_expense(fam* f1)`
- Calculates the **total family expense** and compares it to **family income**.

### `void get_categorical_expense(fam* f1, string category)`
- Displays **category-wise family expenses** along with **individual contributions**.

### `void get_highest_expense_day(expense* e1)`
- Finds the **day with the highest expenses** in the month.

### `void get_individual_expense(user* u1, int userID)`
- Prints the **total individual expense** for the month, sorted by category.

## How to Run the Program

1. Compile the program using a C compiler (e.g., GCC) and run the executable:  
   ```sh
   gcc expense_tracker.c -o expense_tracker
   ./expense_tracker



## Use the Menu-Driven Interface

Once the program starts, follow the on-screen **menu options** to:  

- ✅ **Add users and expenses**  
- ✅ **Create and modify families**  
- ✅ **View categorized reports and analytics**  
- ✅ **Delete or update details when required**  

## 🚀 Future Enhancements

- 🔹 **Graphical User Interface (GUI):** Implement a Tkinter (Python) or Web Dashboard  
- 🔹 **Database Integration:** Store data persistently using MySQL or SQLite  
- 🔹 **Expense Trends & Reports:** Generate monthly spending analysis with charts  
- 🔹 **Export & Import Data:** Allow users to save and load expense data from files  
- 🔹 **User Authentication:** Implement login system for different users  

