#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

using namespace std;

// Wine structure
struct Wine {
    string id;
    string name;
    string type; // red, white, rose, sparkling
    string origin;
    int year;
    double price;
    int quantity;
    
    void display() const {
        cout << left << setw(8) << id 
             << setw(25) << name 
             << setw(10) << type 
             << setw(15) << origin 
             << setw(6) << year 
             << setw(10) << fixed << setprecision(2) << price 
             << setw(8) << quantity << endl;
    }
};

// Customer structure
struct Customer {
    string id;
    string name;
    string phone;
    vector<pair<string, int>> purchaseHistory; // wine ID and quantity
    
    void display() const {
        cout << "\nCustomer ID: " << id
             << "\nName: " << name
             << "\nPhone: " << phone
             << "\nTotal Purchases: " << purchaseHistory.size() << endl;
    }
};

// Sales record
struct Sale {
    string invoiceNumber;
    string customerId;
    string date;
    vector<pair<string, int>> items; // wine ID and quantity
    double totalAmount;
    
    void display() const {
        cout << "\nInvoice #: " << invoiceNumber
             << "\nDate: " << date
             << "\nCustomer ID: " << customerId
             << "\nTotal Amount: $" << fixed << setprecision(2) << totalAmount << endl;
    }
};

class WineShop {
private:
    vector<Wine> inventory;
    vector<Customer> customers;
    vector<Sale> sales;
    int nextInvoiceNumber = 1001;

    // Helper functions
    string generateId() {
        static int nextId = 1;
        return "W" + to_string(nextId++);
    }
    
    string generateCustomerId() {
        static int nextCustId = 1;
        return "C" + to_string(nextCustId++);
    }
    
    Wine* findWine(const string& id) {
        for (auto& wine : inventory) {
            if (wine.id == id) return &wine;
        }
        return nullptr;
    }
    
    Customer* findCustomer(const string& id) {
        for (auto& customer : customers) {
            if (customer.id == id) return &customer;
        }
        return nullptr;
    }

public:
    // Inventory management
    void addWine() {
        Wine wine;
        wine.id = generateId();
        
        cout << "\nEnter Wine Details:\n";
        cout << "Name: ";
        cin.ignore();
        getline(cin, wine.name);
        
        cout << "Type (red/white/rose/sparkling): ";
        cin >> wine.type;
        
        cout << "Origin: ";
        cin.ignore();
        getline(cin, wine.origin);
        
        cout << "Year: ";
        cin >> wine.year;
        
        cout << "Price: ";
        cin >> wine.price;
        
        cout << "Quantity: ";
        cin >> wine.quantity;
        
        inventory.push_back(wine);
        cout << "Wine added successfully! ID: " << wine.id << endl;
    }
    
    void displayInventory() {
        if (inventory.empty()) {
            cout << "\nInventory is empty!\n";
            return;
        }
        
        cout << "\n===== WINE INVENTORY =====\n";
        cout << left << setw(8) << "ID" 
             << setw(25) << "Name" 
             << setw(10) << "Type" 
             << setw(15) << "Origin" 
             << setw(6) << "Year" 
             << setw(10) << "Price" 
             << setw(8) << "Qty" << endl;
        cout << string(80, '-') << endl;
        
        for (const auto& wine : inventory) {
            wine.display();
        }
    }
    
    void searchWine() {
        string term;
        cout << "\nEnter search term (ID/name/type/origin): ";
        cin.ignore();
        getline(cin, term);
        
        transform(term.begin(), term.end(), term.begin(), ::tolower);
        
        cout << "\n===== SEARCH RESULTS =====\n";
        bool found = false;
        
        for (const auto& wine : inventory) {
            string id = wine.id;
            string name = wine.name;
            string type = wine.type;
            string origin = wine.origin;
            
            transform(id.begin(), id.end(), id.begin(), ::tolower);
            transform(name.begin(), name.end(), name.begin(), ::tolower);
            transform(type.begin(), type.end(), type.begin(), ::tolower);
            transform(origin.begin(), origin.end(), origin.begin(), ::tolower);
            
            if (id.find(term) != string::npos || 
                name.find(term) != string::npos || 
                type.find(term) != string::npos || 
                origin.find(term) != string::npos) {
                wine.display();
                found = true;
            }
        }
        
        if (!found) {
            cout << "No matching wines found.\n";
        }
    }
    
    // Customer management
    void addCustomer() {
        Customer customer;
        customer.id = generateCustomerId();
        
        cout << "\nEnter Customer Details:\n";
        cout << "Name: ";
        cin.ignore();
        getline(cin, customer.name);
        
        cout << "Phone: ";
        cin >> customer.phone;
        
        customers.push_back(customer);
        cout << "Customer added successfully! ID: " << customer.id << endl;
    }
    
    void displayCustomers() {
        if (customers.empty()) {
            cout << "\nNo customers registered!\n";
            return;
        }
        
        cout << "\n===== CUSTOMERS =====\n";
        for (const auto& customer : customers) {
            customer.display();
            cout << "----------------------\n";
        }
    }
    
    // Sales management
    void makeSale() {
        if (inventory.empty()) {
            cout << "\nCannot make sale - inventory is empty!\n";
            return;
        }
        
        if (customers.empty()) {
            cout << "\nNo customers registered! Add a customer first.\n";
            return;
        }
        
        string customerId;
        cout << "\nEnter Customer ID: ";
        cin >> customerId;
        
        Customer* customer = findCustomer(customerId);
        if (!customer) {
            cout << "Customer not found!\n";
            return;
        }
        
        Sale sale;
        sale.invoiceNumber = "INV" + to_string(nextInvoiceNumber++);
        sale.customerId = customerId;
        sale.totalAmount = 0.0;
        
        cout << "Enter today's date (DD/MM/YYYY): ";
        cin >> sale.date;
        
        char addMore;
        do {
            displayInventory();
            string wineId;
            int quantity;
            
            cout << "\nEnter Wine ID to sell: ";
            cin >> wineId;
            
            Wine* wine = findWine(wineId);
            if (!wine) {
                cout << "Wine not found!\n";
                continue;
            }
            
            cout << "Available quantity: " << wine->quantity << endl;
            cout << "Enter quantity to sell: ";
            cin >> quantity;
            
            if (quantity <= 0) {
                cout << "Invalid quantity!\n";
                continue;
            }
            
            if (quantity > wine->quantity) {
                cout << "Not enough stock available!\n";
                continue;
            }
            
            // Update wine quantity
            wine->quantity -= quantity;
            
            // Add to sale
            sale.items.emplace_back(wineId, quantity);
            sale.totalAmount += (wine->price * quantity);
            
            // Add to customer's purchase history
            customer->purchaseHistory.emplace_back(wineId, quantity);
            
            cout << "Added " << quantity << " bottle(s) of " << wine->name << " to sale.\n";
            
            cout << "Add another item? (y/n): ";
            cin >> addMore;
        } while (addMore == 'y' || addMore == 'Y');
        
        sales.push_back(sale);
        
        // Print receipt
        cout << "\n===== SALE RECEIPT =====\n";
        cout << "Invoice #: " << sale.invoiceNumber << endl;
        cout << "Date: " << sale.date << endl;
        cout << "Customer: " << customer->name << endl;
        cout << "------------------------\n";
        
        for (const auto& item : sale.items) {
            Wine* wine = findWine(item.first);
            cout << wine->name << " (" << wine->year << ") - " 
                 << item.second << " x $" << wine->price 
                 << " = $" << (item.second * wine->price) << endl;
        }
        
        cout << "------------------------\n";
        cout << "TOTAL: $" << sale.totalAmount << endl;
        cout << "Thank you for your purchase!\n";
    }
    
    void displaySales() {
        if (sales.empty()) {
            cout << "\nNo sales recorded yet!\n";
            return;
        }
        
        cout << "\n===== SALES HISTORY =====\n";
        for (const auto& sale : sales) {
            sale.display();
            cout << "Items:\n";
            
            for (const auto& item : sale.items) {
                Wine* wine = findWine(item.first);
                if (wine) {
                    cout << " - " << wine->name << ": " << item.second 
                         << " x $" << wine->price << endl;
                }
            }
            cout << "------------------------\n";
        }
    }
    
    // Data persistence
    void saveData() {
        ofstream wineFile("wines.dat"), customerFile("customers.dat"), salesFile("sales.dat");
        
        // Save wines
        for (const auto& wine : inventory) {
            wineFile << wine.id << "," << wine.name << "," << wine.type << ","
                    << wine.origin << "," << wine.year << "," << wine.price << ","
                    << wine.quantity << "\n";
        }
        
        // Save customers
        for (const auto& customer : customers) {
            customerFile << customer.id << "," << customer.name << "," << customer.phone;
            for (const auto& purchase : customer.purchaseHistory) {
                customerFile << "," << purchase.first << ":" << purchase.second;
            }
            customerFile << "\n";
        }
        
        // Save sales
        for (const auto& sale : sales) {
            salesFile << sale.invoiceNumber << "," << sale.customerId << ","
                     << sale.date << "," << sale.totalAmount;
            for (const auto& item : sale.items) {
                salesFile << "," << item.first << ":" << item.second;
            }
            salesFile << "\n";
        }
        
        cout << "\nAll data saved successfully!\n";
    }
    
    void loadData() {
        ifstream wineFile("wines.dat"), customerFile("customers.dat"), salesFile("sales.dat");
        string line;
        
        // Load wines
        inventory.clear();
        while (getline(wineFile, line)) {
            size_t pos = 0;
            vector<string> tokens;
            while ((pos = line.find(',')) != string::npos) {
                tokens.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            tokens.push_back(line);
            
            if (tokens.size() == 7) {
                Wine wine;
                wine.id = tokens[0];
                wine.name = tokens[1];
                wine.type = tokens[2];
                wine.origin = tokens[3];
                wine.year = stoi(tokens[4]);
                wine.price = stod(tokens[5]);
                wine.quantity = stoi(tokens[6]);
                inventory.push_back(wine);
            }
        }
        
        // Load customers
        customers.clear();
        while (getline(customerFile, line)) {
            size_t pos = 0;
            vector<string> tokens;
            while ((pos = line.find(',')) != string::npos) {
                tokens.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            tokens.push_back(line);
            
            if (tokens.size() >= 3) {
                Customer customer;
                customer.id = tokens[0];
                customer.name = tokens[1];
                customer.phone = tokens[2];
                
                for (size_t i = 3; i < tokens.size(); i++) {
                    size_t colonPos = tokens[i].find(':');
                    if (colonPos != string::npos) {
                        string wineId = tokens[i].substr(0, colonPos);
                        int quantity = stoi(tokens[i].substr(colonPos + 1));
                        customer.purchaseHistory.emplace_back(wineId, quantity);
                    }
                }
                
                customers.push_back(customer);
            }
        }
        
        // Load sales
        sales.clear();
        while (getline(salesFile, line)) {
            size_t pos = 0;
            vector<string> tokens;
            while ((pos = line.find(',')) != string::npos) {
                tokens.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            tokens.push_back(line);
            
            if (tokens.size() >= 4) {
                Sale sale;
                sale.invoiceNumber = tokens[0];
                sale.customerId = tokens[1];
                sale.date = tokens[2];
                sale.totalAmount = stod(tokens[3]);
                
                for (size_t i = 4; i < tokens.size(); i++) {
                    size_t colonPos = tokens[i].find(':');
                    if (colonPos != string::npos) {
                        string wineId = tokens[i].substr(0, colonPos);
                        int quantity = stoi(tokens[i].substr(colonPos + 1));
                        sale.items.emplace_back(wineId, quantity);
                    }
                }
                
                sales.push_back(sale);
                // Update next invoice number
                string invNum = sale.invoiceNumber.substr(3);
                int num = stoi(invNum);
                if (num >= nextInvoiceNumber) {
                    nextInvoiceNumber = num + 1;
                }
            }
        }
        
        cout << "\nAll data loaded successfully!\n";
    }
    
    // Reports
    void generateInventoryReport() {
        if (inventory.empty()) {
            cout << "\nInventory is empty!\n";
            return;
        }
        
        ofstream report("inventory_report.txt");
        report << "===== WINE INVENTORY REPORT =====\n\n";
        report << left << setw(8) << "ID" << setw(25) << "Name" << setw(10) << "Type" 
              << setw(15) << "Origin" << setw(6) << "Year" << setw(10) << "Price" 
              << setw(8) << "Qty" << endl;
        report << string(80, '-') << endl;
        
        for (const auto& wine : inventory) {
            report << left << setw(8) << wine.id 
                  << setw(25) << wine.name 
                  << setw(10) << wine.type 
                  << setw(15) << wine.origin 
                  << setw(6) << wine.year 
                  << setw(10) << fixed << setprecision(2) << wine.price 
                  << setw(8) << wine.quantity << endl;
        }
        
        // Calculate totals
        int totalBottles = 0;
        double totalValue = 0.0;
        
        for (const auto& wine : inventory) {
            totalBottles += wine.quantity;
            totalValue += (wine.price * wine.quantity);
        }
        
        report << "\n===== SUMMARY =====\n";
        report << "Total unique wines: " << inventory.size() << endl;
        report << "Total bottles in stock: " << totalBottles << endl;
        report << "Total inventory value: $" << fixed << setprecision(2) << totalValue << endl;
        
        cout << "\nInventory report generated as 'inventory_report.txt'\n";
    }
    
    void showMenu() {
        cout << "\n===== WINE SHOP MANAGEMENT SYSTEM =====\n";
        cout << "1. Add New Wine to Inventory\n";
        cout << "2. Display Inventory\n";
        cout << "3. Search Wine\n";
        cout << "4. Add New Customer\n";
        cout << "5. Display Customers\n";
        cout << "6. Make a Sale\n";
        cout << "7. Display Sales History\n";
        cout << "8. Generate Inventory Report\n";
        cout << "9. Save All Data\n";
        cout << "10. Load All Data\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
    }
};

int main() {
    WineShop shop;
    int choice;
    
    do {
        shop.showMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: shop.addWine(); break;
            case 2: shop.displayInventory(); break;
            case 3: shop.searchWine(); break;
            case 4: shop.addCustomer(); break;
            case 5: shop.displayCustomers(); break;
            case 6: shop.makeSale(); break;
            case 7: shop.displaySales(); break;
            case 8: shop.generateInventoryReport(); break;
            case 9: shop.saveData(); break;
            case 10: shop.loadData(); break;
            case 0: cout << "Exiting system...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);
    
    return 0;
}