#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

// Structure to store student information
struct Student {
    string name;
    int rollNo;
    float marks[5]; // Marks for 5 subjects
    float percentage;
    char grade;
};

// Function to calculate percentage and grade
void calculateGrade(Student &s) {
    float total = 0;
    for (int i = 0; i < 5; ++i)
        total += s.marks[i];

    s.percentage = total / 5.0;

    if (s.percentage >= 90)
        s.grade = 'A';
    else if (s.percentage >= 80)
        s.grade = 'B';
    else if (s.percentage >= 70)
        s.grade = 'C';
    else if (s.percentage >= 60)
        s.grade = 'D';
    else
        s.grade = 'F';
}

// Function to display report
void displayReport(const vector<Student> &students) {
    cout << "\n------------------- STUDENT GRADE REPORT -------------------\n";
    cout << left << setw(15) << "Name"
         << setw(10) << "Roll No"
         << setw(15) << "Percentage"
         << setw(10) << "Grade" << endl;
    cout << "-----------------------------------------------------------\n";

    for (const auto &s : students) {
        cout << left << setw(15) << s.name
             << setw(10) << s.rollNo
             << setw(15) << fixed << setprecision(2) << s.percentage
             << setw(10) << s.grade << endl;
    }

    cout << "-----------------------------------------------------------\n";
}

int main() {
    vector<Student> students;
    int n;

    cout << "Enter number of students: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        Student s;
        cout << "\nEnter details for student " << i + 1 << ":\n";
        cout << "Name: ";
        cin.ignore();
        getline(cin, s.name);

        cout << "Roll No: ";
        cin >> s.rollNo;

        cout << "Enter marks for 5 subjects:\n";
        for (int j = 0; j < 5; ++j) {
            cout << "Subject " << j + 1 << ": ";
            cin >> s.marks[j];
        }

        calculateGrade(s);
        students.push_back(s);
    }

    displayReport(students);

    return 0;
}
// This program collects student information, calculates their percentage and grade, and displays a report.
// It uses structures to store student data and functions to perform calculations and display results.