#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

struct Reservation {
    int reservationID;
    string customerName;
    string destination;
    int numberOfPeople;
    string travelDate;
};

vector<Reservation> reservations;
int nextReservationID = 1001;

vector<string> destinations = {
    "Manali", "Goa", "Jaipur", "Kerala", "Kashmir"
};

void showDestinations() {
    cout << "\nAvailable Tour Destinations:\n";
    for (int i = 0; i < destinations.size(); ++i) {
        cout << i + 1 << ". " << destinations[i] << endl;
    }
    cout << endl;
}

void bookReservation() {
    string name, date;
    int choice, people;

    cout << "\nEnter customer name: ";
    cin.ignore();
    getline(cin, name);

    showDestinations();
    cout << "Choose destination (1-" << destinations.size() << "): ";
    cin >> choice;

    if (choice < 1 || choice > destinations.size()) {
        cout << "Invalid destination choice.\n";
        return;
    }

    cout << "Enter number of people: ";
    cin >> people;
    cout << "Enter travel date (dd-mm-yyyy): ";
    cin >> date;

    Reservation r;
    r.reservationID = nextReservationID++;
    r.customerName = name;
    r.destination = destinations[choice - 1];
    r.numberOfPeople = people;
    r.travelDate = date;

    reservations.push_back(r);
    cout << "\nReservation successful! Your Reservation ID is " << r.reservationID << "\n";

    // Save to file after booking
    ofstream outFile("reservations.txt", ios::app); // Open file in append mode
    outFile << r.reservationID << "," << r.customerName << "," << r.destination << "," 
            << r.numberOfPeople << "," << r.travelDate << endl;
    outFile.close();
}

void loadReservations() {
    ifstream inFile("reservations.txt");
    if (!inFile) return; // If file does not exist, do nothing

    Reservation r;
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string temp;
        
        getline(ss, temp, ',');
        r.reservationID = stoi(temp);
        
        getline(ss, r.customerName, ',');
        getline(ss, r.destination, ',');
        
        getline(ss, temp, ',');
        r.numberOfPeople = stoi(temp);
        
        getline(ss, r.travelDate, ',');

        reservations.push_back(r);
        nextReservationID = max(nextReservationID, r.reservationID + 1); // Keep track of next ID
    }
    inFile.close();
}

void viewReservations() {
    if (reservations.empty()) {
        cout << "\nNo reservations found.\n";
        return;
    }

    cout << "\nAll Reservations:\n";
    cout << left << setw(12) << "Res. ID" << setw(20) << "Name" << setw(15)
         << "Destination" << setw(10) << "People" << setw(15) << "Travel Date" << endl;
    cout << string(70, '-') << endl;

    for (const auto& r : reservations) {
        cout << left << setw(12) << r.reservationID << setw(20) << r.customerName
             << setw(15) << r.destination << setw(10) << r.numberOfPeople
             << setw(15) << r.travelDate << endl;
    }
}

void cancelReservation() {
    int id;
    cout << "\nEnter Reservation ID to cancel: ";
    cin >> id;

    for (auto it = reservations.begin(); it != reservations.end(); ++it) {
        if (it->reservationID == id) {
            reservations.erase(it);
            cout << "Reservation cancelled successfully.\n";

            // Rewrite the reservations to the file (without the cancelled reservation)
            ofstream outFile("reservations.txt", ios::trunc); // Open file in truncate mode
            for (const auto& r : reservations) {
                outFile << r.reservationID << "," << r.customerName << "," << r.destination << "," 
                        << r.numberOfPeople << "," << r.travelDate << endl;
            }
            outFile.close();
            return;
        }
    }

    cout << "Reservation ID not found.\n";
}

int main() {
    int choice;

    // Load reservations from file when program starts
    loadReservations();

    do {
        cout << "\n====== Tourist Reservation System ======\n";
        cout << "1. View Destinations\n";
        cout << "2. Book a Reservation\n";
        cout << "3. View Reservations\n";
        cout << "4. Cancel Reservation\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: showDestinations(); break;
            case 2: bookReservation(); break;
            case 3: viewReservations(); break;
            case 4: cancelReservation(); break;
            case 5: cout << "Thank you for using the system!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
// This code implements a simple tourist management system where users can view destinations, book reservations, view all reservations, and cancel reservations. The data is stored in a text file for persistence.
// The program uses structures to manage reservation data and provides a user-friendly interface for interaction.