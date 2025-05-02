#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <limits>

using namespace std;

// Class to represent a Bus
class Bus {
public:
    string busNumber;
    string driverName;
    int capacity;
    vector<string> routeStops;
    vector<string> assignedStudents;

    Bus(string num, string driver, int cap, vector<string> stops)
        : busNumber(num), driverName(driver), capacity(cap), routeStops(stops) {}

    void displayInfo() const {
        cout << "\nBus Number: " << busNumber
             << "\nDriver: " << driverName
             << "\nCapacity: " << capacity << " students"
             << "\nCurrent Load: " << assignedStudents.size() << " students"
             << "\nRoute Stops: ";
        for (const auto& stop : routeStops) {
            cout << stop << " -> ";
        }
        cout << "END\n";
    }

    bool isFull() const {
        return assignedStudents.size() >= capacity;
    }
};

// Class to represent a Student
class Student {
public:
    string id;
    string name;
    string address;
    string pickupStop;
    string assignedBus;

    Student(string studentId, string studentName, string studentAddress, string stop)
        : id(studentId), name(studentName), address(studentAddress), pickupStop(stop) {}

    void displayInfo() const {
        cout << "\nStudent ID: " << id
             << "\nName: " << name
             << "\nAddress: " << address
             << "\nPickup Stop: " << pickupStop
             << "\nAssigned Bus: " << (assignedBus.empty() ? "Not assigned" : assignedBus) << "\n";
    }
};

// Transport Management System class
class TransportSystem {
private:
    vector<Bus> buses;
    vector<Student> students;
    map<string, vector<string>> stopToBusesMap;

public:
    void addBus() {
        string num, driver;
        int cap;
        vector<string> stops;
        string stop;
        int numStops;

        cout << "\nEnter Bus Number: ";
        cin >> num;
        cin.ignore();

        cout << "Enter Driver Name: ";
        getline(cin, driver);

        cout << "Enter Bus Capacity: ";
        cin >> cap;
        cin.ignore();

        cout << "Enter number of stops: ";
        cin >> numStops;
        cin.ignore();

        cout << "Enter " << numStops << " stops (one per line):\n";
        for (int i = 0; i < numStops; i++) {
            getline(cin, stop);
            stops.push_back(stop);
        }

        buses.emplace_back(num, driver, cap, stops);
        updateStopMap(num, stops);
        cout << "Bus added successfully!\n";
    }

    void updateStopMap(const string& busNum, const vector<string>& stops) {
        for (const auto& stop : stops) {
            stopToBusesMap[stop].push_back(busNum);
        }
    }

    void addStudent() {
        string id, name, address, stop;

        cout << "\nEnter Student ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Student Name: ";
        getline(cin, name);

        cout << "Enter Student Address: ";
        getline(cin, address);

        cout << "Enter Pickup Stop: ";
        getline(cin, stop);

        students.emplace_back(id, name, address, stop);
        cout << "Student added successfully!\n";
    }

    void assignBusToStudent() {
        if (students.empty()) {
            cout << "No students available!\n";
            return;
        }

        if (buses.empty()) {
            cout << "No buses available!\n";
            return;
        }

        string studentId;
        cout << "Enter Student ID to assign bus: ";
        cin >> studentId;

        auto studentIt = find_if(students.begin(), students.end(),
            [&studentId](const Student& s) { return s.id == studentId; });

        if (studentIt == students.end()) {
            cout << "Student not found!\n";
            return;
        }

        string stop = studentIt->pickupStop;
        if (stopToBusesMap.find(stop) == stopToBusesMap.end()) {
            cout << "No buses available for this stop!\n";
            return;
        }

        vector<string> availableBuses = stopToBusesMap[stop];
        vector<Bus*> busesForStop;

        // Find buses that go to this stop and have capacity
        for (auto& bus : buses) {
            if (find(availableBuses.begin(), availableBuses.end(), bus.busNumber) != availableBuses.end() && !bus.isFull()) {
                busesForStop.push_back(&bus);
            }
        }

        if (busesForStop.empty()) {
            cout << "No available buses with capacity for this stop!\n";
            return;
        }

        cout << "\nAvailable Buses for stop " << stop << ":\n";
        for (int i = 0; i < busesForStop.size(); i++) {
            cout << i + 1 << ". Bus " << busesForStop[i]->busNumber 
                 << " (Driver: " << busesForStop[i]->driverName 
                 << ", Available Seats: " << busesForStop[i]->capacity - busesForStop[i]->assignedStudents.size() << ")\n";
        }

        int choice;
        cout << "Select bus to assign (1-" << busesForStop.size() << "): ";
        cin >> choice;

        if (choice < 1 || choice > busesForStop.size()) {
            cout << "Invalid choice!\n";
            return;
        }

        Bus* selectedBus = busesForStop[choice - 1];
        selectedBus->assignedStudents.push_back(studentId);
        studentIt->assignedBus = selectedBus->busNumber;
        cout << "Student " << studentIt->name << " assigned to Bus " << selectedBus->busNumber << " successfully!\n";
    }

    void displayAllBuses() const {
        if (buses.empty()) {
            cout << "No buses available!\n";
            return;
        }

        cout << "\n===== ALL BUSES =====\n";
        for (const auto& bus : buses) {
            bus.displayInfo();
            if (!bus.assignedStudents.empty()) {
                cout << "Assigned Students (" << bus.assignedStudents.size() << "): ";
                for (const auto& student : bus.assignedStudents) {
                    cout << student << " ";
                }
                cout << "\n";
            }
            cout << "------------------------\n";
        }
    }

    void displayAllStudents() const {
        if (students.empty()) {
            cout << "No students available!\n";
            return;
        }

        cout << "\n===== ALL STUDENTS =====\n";
        for (const auto& student : students) {
            student.displayInfo();
            cout << "------------------------\n";
        }
    }

    void displayBusDetails() const {
        if (buses.empty()) {
            cout << "No buses available!\n";
            return;
        }

        string busNum;
        cout << "Enter Bus Number: ";
        cin >> busNum;

        auto it = find_if(buses.begin(), buses.end(),
            [&busNum](const Bus& b) { return b.busNumber == busNum; });

        if (it == buses.end()) {
            cout << "Bus not found!\n";
            return;
        }

        it->displayInfo();
        if (!it->assignedStudents.empty()) {
            cout << "\nAssigned Students:\n";
            for (const auto& studentId : it->assignedStudents) {
                auto studentIt = find_if(students.begin(), students.end(),
                    [&studentId](const Student& s) { return s.id == studentId; });
                if (studentIt != students.end()) {
                    cout << "ID: " << studentIt->id << ", Name: " << studentIt->name 
                         << ", Pickup: " << studentIt->pickupStop << "\n";
                }
            }
        }
    }

    void displayStudentDetails() const {
        if (students.empty()) {
            cout << "No students available!\n";
            return;
        }

        string studentId;
        cout << "Enter Student ID: ";
        cin >> studentId;

        auto it = find_if(students.begin(), students.end(),
            [&studentId](const Student& s) { return s.id == studentId; });

        if (it == students.end()) {
            cout << "Student not found!\n";
            return;
        }

        it->displayInfo();
        if (!it->assignedBus.empty()) {
            auto busIt = find_if(buses.begin(), buses.end(),
                [&it](const Bus& b) { return b.busNumber == it->assignedBus; });
            if (busIt != buses.end()) {
                cout << "Bus Details:\n";
                cout << "Number: " << busIt->busNumber << "\n";
                cout << "Driver: " << busIt->driverName << "\n";
                cout << "Route: ";
                for (const auto& stop : busIt->routeStops) {
                    cout << stop << " -> ";
                }
                cout << "END\n";
            }
        }
    }

    void saveDataToFile() const {
        ofstream busFile("buses.txt"), studentFile("students.txt");

        // Save buses data
        for (const auto& bus : buses) {
            busFile << bus.busNumber << "," << bus.driverName << "," << bus.capacity << ",";
            for (const auto& stop : bus.routeStops) {
                busFile << stop << ";";
            }
            busFile << ",";
            for (const auto& student : bus.assignedStudents) {
                busFile << student << ";";
            }
            busFile << "\n";
        }

        // Save students data
        for (const auto& student : students) {
            studentFile << student.id << "," << student.name << "," 
                       << student.address << "," << student.pickupStop << ","
                       << student.assignedBus << "\n";
        }

        cout << "Data saved to files successfully!\n";
    }

    void loadDataFromFile() {
        ifstream busFile("buses.txt"), studentFile("students.txt");
        string line;

        // Load buses data
        buses.clear();
        stopToBusesMap.clear();
        while (getline(busFile, line)) {
            size_t pos = 0;
            vector<string> tokens;
            while ((pos = line.find(',')) != string::npos) {
                tokens.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            tokens.push_back(line);

            if (tokens.size() >= 4) {
                string busNum = tokens[0];
                string driver = tokens[1];
                int capacity = stoi(tokens[2]);

                // Parse stops
                vector<string> stops;
                string stopToken;
                istringstream stopStream(tokens[3]);
                while (getline(stopStream, stopToken, ';')) {
                    if (!stopToken.empty()) stops.push_back(stopToken);
                }

                // Create bus
                buses.emplace_back(busNum, driver, capacity, stops);
                updateStopMap(busNum, stops);

                // Parse assigned students if exists
                if (tokens.size() > 4) {
                    string studentToken;
                    istringstream studentStream(tokens[4]);
                    while (getline(studentStream, studentToken, ';')) {
                        if (!studentToken.empty()) {
                            buses.back().assignedStudents.push_back(studentToken);
                        }
                    }
                }
            }
        }

        // Load students data
        students.clear();
        while (getline(studentFile, line)) {
            size_t pos = 0;
            vector<string> tokens;
            while ((pos = line.find(',')) != string::npos) {
                tokens.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            tokens.push_back(line);

            if (tokens.size() >= 5) {
                students.emplace_back(tokens[0], tokens[1], tokens[2], tokens[3]);
                students.back().assignedBus = tokens[4];
            }
        }

        cout << "Data loaded from files successfully!\n";
    }

    void showMenu() {
        cout << "\n===== STUDENT TRANSPORT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add New Bus\n";
        cout << "2. Add New Student\n";
        cout << "3. Assign Bus to Student\n";
        cout << "4. Display All Buses\n";
        cout << "5. Display All Students\n";
        cout << "6. Display Bus Details\n";
        cout << "7. Display Student Details\n";
        cout << "8. Save Data to File\n";
        cout << "9. Load Data from File\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
    }
};

int main() {
    TransportSystem system;
    int choice;

    do {
        system.showMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: system.addBus(); break;
            case 2: system.addStudent(); break;
            case 3: system.assignBusToStudent(); break;
            case 4: system.displayAllBuses(); break;
            case 5: system.displayAllStudents(); break;
            case 6: system.displayBusDetails(); break;
            case 7: system.displayStudentDetails(); break;
            case 8: system.saveDataToFile(); break;
            case 9: system.loadDataFromFile(); break;
            case 0: cout << "Exiting system...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}