#include <iostream>
#include <string>

using namespace std;

// Function to check if a string contains only numeric digits
bool isNumberString(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) {
            return false; // Return false if any non-digit character is found
        }
    }
    return true;
}

// Function to validate credit card number using the Luhn Algorithm
bool validateCreditCard(const string& ccNumber) {
    int len = ccNumber.length();
    int doubleEvenSum = 0;

    // Step 1: Double every second digit, starting from the right
    for (int i = len - 2; i >= 0; i -= 2) {
        int dbl = (ccNumber[i] - '0') * 2;
        if (dbl > 9) {
            dbl = (dbl / 10) + (dbl % 10); // If the result is a two-digit number, sum those digits
        }
        doubleEvenSum += dbl;
    }

    // Step 2: Add every odd placed digit from the right to the sum
    for (int i = len - 1; i >= 0; i -= 2) {
        doubleEvenSum += (ccNumber[i] - '0');
    }

    // Step 3: If the sum is divisible by 10, the card number is valid
    return (doubleEvenSum % 10 == 0);
}

int main() {
    string ccNumber;

    cout << "This program uses the Luhn Algorithm to validate a Credit Card number." << endl;
    cout << "You can enter 'exit' anytime to quit the program." << endl;

    while (true) {
        cout << "Please enter a Credit Card number to validate (or 'exit' to quit): ";
        cin >> ccNumber;

        if (ccNumber == "exit") {
            cout << "Exiting the program. Thank you!" << endl;
            break;
        }

        // Validate if the input is a valid numeric string
        if (!isNumberString(ccNumber)) {
            cout << "Invalid input! Please enter only numeric characters." << endl;
            continue;
        }

        // Check if the credit card number is valid according to the Luhn algorithm
        if (validateCreditCard(ccNumber)) {
            cout << "The Credit Card number is Valid!" << endl;
        } else {
            cout << "The Credit Card number is Invalid!" << endl;
        }
    }

    return 0;
}
