#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Structure to hold customer information
struct Customer {
    int customerID;
    string name;
    double unitsConsumed;
    double totalBill;
};

// Vector to store customer data
vector<Customer> customers;
int nextCustomerID = 1001;  // Start ID for customers

// Function to load customer data from a file
void loadCustomers() {
    ifstream inFile("customers.txt");
    if (!inFile) return; // If file doesn't exist, skip loading

    Customer c;
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string temp;

        // Read customer information
        getline(ss, temp, ',');
        c.customerID = stoi(temp);

        getline(ss, c.name, ',');
        getline(ss, temp, ',');
        c.unitsConsumed = stod(temp);

        getline(ss, temp, ',');
        c.totalBill = stod(temp);

        customers.push_back(c);
        nextCustomerID = max(nextCustomerID, c.customerID + 1); // Keep track of the next customer ID
    }
    inFile.close();
}

// Function to save customer data to a file
void saveCustomers() {
    ofstream outFile("customers.txt", ios::trunc); // Open file in truncate mode
    for (const auto& c : customers) {
        outFile << c.customerID << "," << c.name << "," << c.unitsConsumed << ","
                << c.totalBill << endl;
    }
    outFile.close();
}

// Function to calculate the electricity bill based on consumption
double calculateBill(double units) {
    double bill = 0.0;

    // Tariff rates (example)
    if (units <= 100) {
        bill = units * 5.0;   // Rate for 0-100 units
    } else if (units <= 300) {
        bill = 100 * 5.0 + (units - 100) * 7.0; // Rate for 101-300 units
    } else {
        bill = 100 * 5.0 + 200 * 7.0 + (units - 300) * 10.0; // Rate for 301+ units
    }

    return bill;
}

// Function to add a new customer
void addCustomer() {
    Customer c;
    cout << "\nEnter customer name: ";
    cin.ignore();
    getline(cin, c.name);

    cout << "Enter units consumed: ";
    cin >> c.unitsConsumed;

    c.customerID = nextCustomerID++;  // Generate unique ID for the customer
    c.totalBill = calculateBill(c.unitsConsumed);

    customers.push_back(c);

    cout << "\nCustomer added successfully! Customer ID: " << c.customerID << endl;

    // Save customer data to file
    saveCustomers();
}

// Function to view all customer records
void viewCustomers() {
    if (customers.empty()) {
        cout << "\nNo customer records available.\n";
        return;
    }

    cout << "\nAll Customer Records:\n";
    cout << left << setw(12) << "Customer ID" << setw(20) << "Name" << setw(15)
         << "Units Consumed" << setw(15) << "Total Bill" << endl;
    cout << string(72, '-') << endl;

    for (const auto& c : customers) {
        cout << left << setw(12) << c.customerID << setw(20) << c.name
             << setw(15) << c.unitsConsumed << setw(15) << c.totalBill << endl;
    }
}

// Function to delete a customer record
void deleteCustomer() {
    int id;
    cout << "\nEnter Customer ID to delete: ";
    cin >> id;

    for (auto it = customers.begin(); it != customers.end(); ++it) {
        if (it->customerID == id) {
            customers.erase(it);
            cout << "Customer record deleted successfully.\n";

            // Save updated data to file
            saveCustomers();
            return;
        }
    }

    cout << "Customer ID not found.\n";
}

// Function to search for a customer by ID
void searchCustomer() {
    int id;
    cout << "\nEnter Customer ID to search: ";
    cin >> id;

    for (const auto& c : customers) {
        if (c.customerID == id) {
            cout << "\nCustomer Found:\n";
            cout << "Customer ID: " << c.customerID << endl;
            cout << "Name: " << c.name << endl;
            cout << "Units Consumed: " << c.unitsConsumed << endl;
            cout << "Total Bill: " << c.totalBill << endl;
            return;
        }
    }

    cout << "Customer ID not found.\n";
}

int main() {
    int choice;

    // Load customer data from file when the program starts
    loadCustomers();

    do {
        cout << "\n====== Electricity Bill Generator ======\n";
        cout << "1. Add New Customer\n";
        cout << "2. View All Customers\n";
        cout << "3. Delete Customer Record\n";
        cout << "4. Search Customer by ID\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addCustomer(); break;
            case 2: viewCustomers(); break;
            case 3: deleteCustomer(); break;
            case 4: searchCustomer(); break;
            case 5: cout << "Thank you for using the system!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
