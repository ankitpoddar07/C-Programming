#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

const string FILENAME = "AddressBook.txt";

struct Contact {
    string fname, lname, address, contact;
};

void returnToMainMenu() {
    system("pause");
    system("cls");
}

vector<Contact> loadContacts() {
    ifstream inFile(FILENAME);
    vector<Contact> contacts;
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        Contact c;
        ss >> c.fname >> c.lname >> c.address >> c.contact;
        if (!c.fname.empty())
            contacts.push_back(c);
    }
    return contacts;
}

void saveContacts(const vector<Contact>& contacts) {
    ofstream outFile(FILENAME);
    for (const auto& c : contacts) {
        outFile << c.fname << " " << c.lname << " " << c.address << " " << c.contact << endl;
    }
}

void addContact() {
    system("cls");
    Contact c;
    cout << "--- Add New Contact ---" << endl;
    cout << "Enter First Name: ";
    getline(cin, c.fname);
    cout << "Enter Last Name: ";
    getline(cin, c.lname);
    cout << "Enter Address: ";
    getline(cin, c.address);
    cout << "Enter Contact Number: ";
    getline(cin, c.contact);

    ofstream outFile(FILENAME, ios::app);
    outFile << c.fname << " " << c.lname << " " << c.address << " " << c.contact << endl;
    outFile.close();
    cout << "Contact added successfully.\n";
    returnToMainMenu();
}

void viewContacts() {
    system("cls");
    vector<Contact> contacts = loadContacts();
    cout << "--- All Contacts ---\n";
    for (size_t i = 0; i < contacts.size(); ++i) {
        cout << i + 1 << ". " << contacts[i].fname << " " << contacts[i].lname
             << ", " << contacts[i].address << ", " << contacts[i].contact << endl;
    }
    if (contacts.empty())
        cout << "No contacts found.\n";
    returnToMainMenu();
}

void searchContact() {
    system("cls");
    vector<Contact> contacts = loadContacts();
    string query;
    cout << "--- Search Contact ---\n";
    cout << "Enter First Name or Last Name to search: ";
    getline(cin, query);

    bool found = false;
    for (const auto& c : contacts) {
        if (c.fname == query || c.lname == query) {
            cout << "Found: " << c.fname << " " << c.lname
                 << ", " << c.address << ", " << c.contact << endl;
            found = true;
        }
    }

    if (!found)
        cout << "No contact found with that name.\n";
    returnToMainMenu();
}

void editContact() {
    system("cls");
    vector<Contact> contacts = loadContacts();
    string name;
    cout << "--- Edit Contact ---\n";
    cout << "Enter First Name of contact to edit: ";
    getline(cin, name);

    bool found = false;
    for (auto& c : contacts) {
        if (c.fname == name) {
            cout << "Editing " << c.fname << " " << c.lname << endl;
            cout << "Enter new First Name: ";
            getline(cin, c.fname);
            cout << "Enter new Last Name: ";
            getline(cin, c.lname);
            cout << "Enter new Address: ";
            getline(cin, c.address);
            cout << "Enter new Contact Number: ";
            getline(cin, c.contact);
            found = true;
            break;
        }
    }

    if (found) {
        saveContacts(contacts);
        cout << "Contact updated successfully.\n";
    } else {
        cout << "Contact not found.\n";
    }

    returnToMainMenu();
}

void deleteContact() {
    system("cls");
    vector<Contact> contacts = loadContacts();
    string name;
    cout << "--- Delete Contact ---\n";
    cout << "Enter First Name of contact to delete: ";
    getline(cin, name);

    auto it = remove_if(contacts.begin(), contacts.end(), [&](Contact& c) {
        return c.fname == name;
    });

    if (it != contacts.end()) {
        contacts.erase(it, contacts.end());
        saveContacts(contacts);
        cout << "Contact deleted successfully.\n";
    } else {
        cout << "Contact not found.\n";
    }

    returnToMainMenu();
}

int main() {
    system("cls");
    int option;
    bool run = true;
    while (run) {
        cout << "========== Address Book ==========" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. View Contacts" << endl;
        cout << "3. Search Contact" << endl;
        cout << "4. Edit Contact" << endl;
        cout << "5. Delete Contact" << endl;
        cout << "6. Exit" << endl;
        cout << "Choose an option: ";

        if (!(cin >> option)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        cin.ignore(); // flush newline
        switch (option) {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: searchContact(); break;
            case 4: editContact(); break;
            case 5: deleteContact(); break;
            case 6: run = false; break;
            default: cout << "Invalid option. Try again.\n";
        }
        system("cls");
    }

    cout << "Goodbye!" << endl;
    return 0;
}
