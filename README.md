Expense Tracking System

Overview

The Expense Tracking System is a menu-driven application designed to track family expenses efficiently. It allows users to add, update, and delete expenses while maintaining a structured record of individuals, families, and their financial transactions. The system is implemented using linked lists with double pointers for efficient management of dynamic memory.

Features

User Management: Add users with unique User IDs, names, and income details.

Expense Tracking: Record expenses categorized into Rent, Utility, Grocery, Stationary, and Leisure.

Family Management: Group users into families (1-4 members) and track their collective financials.

Sorted Storage: Users and expenses are stored in a sorted manner based on User ID and Expense ID.

Expense Analysis:

Track total expenses and compare them with family income.

Retrieve category-wise expense reports sorted by individual contribution.

Identify the highest expense day for a family.

Retrieve individual expense details sorted by category in descending order.

Update and Delete Functionality: Modify or remove users, families, and expenses with automatic updates across linked records.

Data Structures Used

The application is built using linked lists, with the following node structures:

1. Individual Node

User ID (unique identifier)

User Name

Income

2. Family Node

Family ID

Family Name

List of individuals (linked to Individual Node)

Total Family Income (sum of all individual incomes)

Total Monthly Family Expense (sum of all members' expenses)

3. Expense Node

Expense ID (unique identifier)

User ID (linked to Individual Node)

Expense Category (Rent, Utility, Grocery, Stationary, Leisure)

Expense Amount

Date of Expense

Functions Implemented

AddUser() - Adds a new user and maintains a sorted list based on User ID.

AddExpense() - Records an expense, maintaining sorted expenses under each user.

CreateFamily() - Assigns users to families and updates collective financials.

Update_or_delete_individual_Family_details() - Modifies or removes users and families, ensuring consistency.

Update_delete_expense() - Modifies or removes an expense, updating all affected records.

Get_total_expense() - Calculates and displays total family expense, checking if it exceeds income.

Get_categorical_expense(category) - Shows category-wise expenses and individual contributions.

Get_highest_expense_day() - Identifies the day with the highest family expense.

Get_individual_expense(UserID) - Displays total and category-wise expenses for a user in descending order.

Implementation Highlights

Menu-Driven System: Users interact through a menu-based interface.

Use of Double Pointers: Enhances efficient memory management and sorting operations.

Dynamic Updates: Modifications to users and expenses reflect instantly across related records.

Efficient Searching: Family and user records are searched using an O(n²) approach to maintain integrity
