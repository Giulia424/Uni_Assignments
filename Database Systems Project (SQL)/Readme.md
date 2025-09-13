Built a SQL Server database system for restaurant operations management, handling menu administration, order processing, and ingredient tracking.
Created interactive Power BI dashboards for data visualization and integrated real-time reporting capabilities for operational decision-making.


# RestoDB - Restaurant Management Database System

RestoDB is a comprehensive database management system designed for restaurant operations. The system optimizes menu administration, inventory monitoring, and customer order management.

## Project Overview

RestoDB enables restaurant staff to efficiently track available dishes, ingredients used, customer orders, and order status. The system manages a diverse menu organized by dish categories (appetizers, main courses, desserts, beverages) and tracks all ingredients used in menu items.

## Database Structure

### Core Tables

1. **Meniu (Menu)** - Stores information about available restaurant menus
   - Menu name, description, start/end dates
   - Examples: "Lunch Menu", "Vegetarian Menu", "Kids Menu", "Drinks Menu"

2. **Preparat (Dish)** - Contains information about available dishes
   - Unique name, description, price, category
   - Categories: Aperitiv, Fel principal, Desert, Bautura

3. **Comanda (Order)** - Stores customer orders
   - Table number, order date, order status
   - Status: In procesare, Finalizata, Anulata

4. **Preparat_Comanda** - Links orders to dishes (many-to-many)
   - Quantities and unit prices for each dish in an order

5. **Ingredient** - Manages restaurant ingredient inventory
   - Ingredient name, unit of measurement, available stock

6. **Ingrediente_Preparat** - Associates dishes with their ingredients
   - Quantity of each ingredient used in a dish

### Database Diagram
The system uses a relational model with proper foreign key relationships ensuring data integrity across all tables.

## Key Features

### Data Integrity Constraints
- **PRIMARY KEY**: Ensures record uniqueness across all tables
- **FOREIGN KEY**: Maintains referential integrity with CASCADE/SET NULL options
- **CHECK constraints**: 
  - Dish categories limited to valid values
  - Order status validation
  - Positive quantities only
- **NOT NULL**: Required fields cannot be empty

### Sample Data
The database includes comprehensive test data:
- 4 different menus (Lunch, Vegetarian, Kids, Drinks)
- 33 dishes across all categories
- 20 sample orders with various statuses
- 53 ingredients with detailed descriptions
- Complete ingredient-dish relationships

## SQL Reports & Analysis

The system includes 4 analytical reports of increasing complexity:

### Report 1: Frequent Appetizers (Complexity 4)
- **File**: `Raport1.sql`
- **Features**: 2 JOINs, WHERE, GROUP BY
- Shows most frequently ordered appetizers grouped by menu and category

### Report 2: Total Sales by Menu (Complexity 6)
- **File**: `Raport2.sql`
- **Features**: 3 JOINs, WHERE, GROUP BY, HAVING
- Calculates total revenue per menu (>100) for completed orders within menu validity period

### Report 3: Revenue by Category (Complexity 7)
- **File**: `Raport3.sql`
- **Features**: 3 JOINs, 2 WHERE clauses, GROUP BY, HAVING
- Analyzes revenue by menu and dish category for orders with >3 items and >50 total revenue

### Report 4: Revenue by Ingredient (Complexity 7)
- **File**: `Raport4.sql`
- **Features**: 4 JOINs, WHERE, GROUP BY, HAVING
- Calculates revenue contribution per ingredient for completed orders, showing ingredients used in multiple dishes

## Power BI Integration

The project includes Power BI visualizations with:
- Interactive dashboards for restaurant performance analysis
- Sales analysis and dish popularity metrics
- Menu efficiency visualization
- Data connection via SQL Server gateway

##  Setup Guide

###  Setup: Complete Script
For a single-file setup, you can run `RestoDB.sql` which contains the complete database creation and data insertion in one script.

