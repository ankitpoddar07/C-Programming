#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

struct Patient {
    int patientID;
    string name;
    string disease;
    string gender;
    string contact;
    string admissionDate;
};

vector<Patient> patients;
int nextPatientID = 1001; // Start ID for patients

// Function to load patient records from file
void loadPatients() {
    ifstream inFile("patients.txt");
    if (!inFile) return; // If file doesn't exist, skip loading

    Patient p;
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string temp;

        getline(ss, temp, ',');
        p.patientID = stoi(temp);

        getline(ss, p.name, ',');
        getline(ss, p.disease, ',');
        getline(ss, p.gender, ',');
        getline(ss, p.contact, ',');
        getline(ss, p.admissionDate, ',');

        patients.push_back(p);
        nextPatientID = max(nextPatientID, p.patientID + 1); // Keep track of next patient ID
    }
    inFile.close();
}

// Function to save patient records to file
void savePatients() {
    ofstream outFile("patients.txt", ios::trunc); // Open file in truncate mode
    for (const auto& p : patients) {
        outFile << p.patientID << "," << p.name << "," << p.disease << ","
                << p.gender << "," << p.contact << "," << p.admissionDate << endl;
    }
    outFile.close();
}

// Function to add a new patient record
void addPatient() {
    Patient p;
    cout << "\nEnter patient name: ";
    cin.ignore();
    getline(cin, p.name);

    cout << "Enter disease: ";
    getline(cin, p.disease);

    cout << "Enter gender (M/F): ";
    getline(cin, p.gender);

    cout << "Enter contact number: ";
    getline(cin, p.contact);

    cout << "Enter admission date (dd-mm-yyyy): ";
    getline(cin, p.admissionDate);

    p.patientID = nextPatientID++;

    patients.push_back(p);

    cout << "\nPatient record added successfully! Patient ID: " << p.patientID << endl;

    // Save the new patient data to file
    savePatients();
}

// Function to view all patient records
void viewPatients() {
    if (patients.empty()) {
        cout << "\nNo patient records available.\n";
        return;
    }

    cout << "\nAll Patient Records:\n";
    cout << left << setw(12) << "Patient ID" << setw(20) << "Name" << setw(15)
         << "Disease" << setw(10) << "Gender" << setw(15) << "Contact" << setw(15) << "Admission Date" << endl;
    cout << string(87, '-') << endl;

    for (const auto& p : patients) {
        cout << left << setw(12) << p.patientID << setw(20) << p.name
             << setw(15) << p.disease << setw(10) << p.gender
             << setw(15) << p.contact << setw(15) << p.admissionDate << endl;
    }
}

// Function to delete a patient record
void deletePatient() {
    int id;
    cout << "\nEnter Patient ID to delete: ";
    cin >> id;

    for (auto it = patients.begin(); it != patients.end(); ++it) {
        if (it->patientID == id) {
            patients.erase(it);
            cout << "Patient record deleted successfully.\n";

            // Save updated list to file
            savePatients();
            return;
        }
    }

    cout << "Patient ID not found.\n";
}

int main() {
    int choice;

    // Load patient records from file when the program starts
    loadPatients();

    do {
        cout << "\n====== Hospital Record System ======\n";
        cout << "1. Add New Patient\n";
        cout << "2. View All Patients\n";
        cout << "3. Delete Patient Record\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: deletePatient(); break;
            case 4: cout << "Thank you for using the system!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
