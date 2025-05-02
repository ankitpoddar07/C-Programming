#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Complaint {
    int complaintID;
    string customerName;
    string complaintDetails;
    string status; // "Pending" or "Resolved"
};

// Global vector to hold complaints in memory
vector<Complaint> complaints;
int nextComplaintID = 1001; // Start ID for new complaints

// Function to add a new complaint
void addComplaint() {
    Complaint newComplaint;
    newComplaint.complaintID = nextComplaintID++;

    cout << "Enter customer name: ";
    cin.ignore();
    getline(cin, newComplaint.customerName);

    cout << "Enter complaint details: ";
    getline(cin, newComplaint.complaintDetails);

    newComplaint.status = "Pending"; // Default status is "Pending"

    complaints.push_back(newComplaint);

    // Save to file
    ofstream file("complaints.txt", ios::app);
    if (file.is_open()) {
        file << newComplaint.complaintID << ","
             << newComplaint.customerName << ","
             << newComplaint.complaintDetails << ","
             << newComplaint.status << "\n";
        file.close();
    }

    cout << "\nComplaint filed successfully! Your Complaint ID is " << newComplaint.complaintID << endl;
}

// Function to view all complaints
void viewComplaints() {
    if (complaints.empty()) {
        cout << "\nNo complaints available.\n";
        return;
    }

    cout << "\nComplaint List:\n";
    for (const auto& complaint : complaints) {
        cout << "Complaint ID: " << complaint.complaintID
             << ", Customer Name: " << complaint.customerName
             << ", Details: " << complaint.complaintDetails
             << ", Status: " << complaint.status << endl;
    }
}

// Function to search for a complaint by ID
void searchComplaintByID() {
    int id;
    cout << "\nEnter Complaint ID to search: ";
    cin >> id;

    bool found = false;
    for (const auto& complaint : complaints) {
        if (complaint.complaintID == id) {
            cout << "\nComplaint Found:\n";
            cout << "Complaint ID: " << complaint.complaintID
                 << ", Customer Name: " << complaint.customerName
                 << ", Details: " << complaint.complaintDetails
                 << ", Status: " << complaint.status << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nComplaint ID not found.\n";
    }
}

// Function to resolve a complaint
void resolveComplaint() {
    int id;
    cout << "\nEnter Complaint ID to resolve: ";
    cin >> id;

    bool found = false;
    for (auto& complaint : complaints) {
        if (complaint.complaintID == id) {
            complaint.status = "Resolved";
            found = true;
            cout << "Complaint ID " << id << " marked as resolved.\n";
            break;
        }
    }

    if (!found) {
        cout << "\nComplaint ID not found.\n";
    }
}

// Function to load complaints from the file
void loadComplaintsFromFile() {
    ifstream file("complaints.txt");
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        Complaint c;
        string status;

        getline(ss, line, ',');
        c.complaintID = stoi(line);
        
        getline(ss, c.customerName, ',');
        getline(ss, c.complaintDetails, ',');
        getline(ss, status, ',');
        c.status = status;

        complaints.push_back(c);
    }

    file.close();
}

int main() {
    loadComplaintsFromFile(); // Load complaints from the file on program start

    int choice;

    do {
        cout << "\n====== Complaint Management System ======\n";
        cout << "1. File a Complaint\n";
        cout << "2. View All Complaints\n";
        cout << "3. Search Complaint by ID\n";
        cout << "4. Resolve a Complaint\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addComplaint(); break;
            case 2: viewComplaints(); break;
            case 3: searchComplaintByID(); break;
            case 4: resolveComplaint(); break;
            case 5: cout << "Thank you for using the system!\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
