#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

class account_query {
private:
    char account_number[20];
    char firstName[20];
    char lastName[20];
    float total_Balance;
public:
    void read_data();
    void show_data();
    void write_rec();
    void read_rec();
    void search_rec();
    void edit_rec();
    void delete_rec();
};

void account_query::read_data() {
    cout << "\nEnter Account Number: ";
    cin >> account_number;
    cout << "Enter First Name: ";
    cin >> firstName;
    cout << "Enter Last Name: ";
    cin >> lastName;
    cout << "Enter Balance: ";
    cin >> total_Balance;
    cout << endl;
}

void account_query::show_data() {
    cout << "Account Number: " << account_number << endl;
    cout << "First Name: " << firstName << endl;
    cout << "Last Name: " << lastName << endl;
    cout << "Current Balance: Rs. " << total_Balance << endl;
    cout << "-------------------------------" << endl;
}

void account_query::write_rec() {
    ofstream outfile;
    outfile.open("record.txt", ios::binary | ios::app);
    if (!outfile) {
        cout << "Error in opening file!" << endl;
        return;
    }
    read_data();
    outfile.write(reinterpret_cast<char *>(this), sizeof(*this));
    outfile.close();
}

void account_query::read_rec() {
    std::ifstream infile("accounts.dat", std::ios::binary);
    if (infile.read(reinterpret_cast<char *>(this), sizeof(*this))) {
        // The read operation was successful, process the data
    } else {
        // Handle the error (e.g., end of file or failure to read)
        std::cerr << "Failed to read account record." << std::endl;
    }
}


void account_query::search_rec() {
    int n;
    ifstream infile;
    infile.open("record.txt", ios::binary);
    if (!infile) {
        cout << "\nError in opening file!" << endl;
        return;
    }
    infile.seekg(0, ios::end);
    int count = infile.tellg() / sizeof(*this);
    cout << "\nThere are " << count << " records in the file.";
    cout << "\nEnter Record Number to Search: ";
    cin >> n;
    infile.seekg((n - 1) * sizeof(*this));
    infile.read(reinterpret_cast<char *>(this), sizeof(*this));
    show_data();
    infile.close();
}

void account_query::edit_rec() {
    int n;
    fstream iofile;
    iofile.open("record.txt", ios::in | ios::binary);
    if (!iofile) {
        cout << "\nError in opening file!" << endl;
        return;
    }
    iofile.seekg(0, ios::end);
    int count = iofile.tellg() / sizeof(*this);
    cout << "\nThere are " << count << " records in the file.";
    cout << "\nEnter Record Number to Edit: ";
    cin >> n;
    iofile.seekg((n - 1) * sizeof(*this));
    iofile.read(reinterpret_cast<char *>(this), sizeof(*this));
    cout << "Record " << n << " has the following data: ";
    show_data();
    iofile.close();

    iofile.open("record.txt", ios::out | ios::in | ios::binary);
    iofile.seekp((n - 1) * sizeof(*this));
    cout << "\nEnter data to Modify: ";
    read_data();
    iofile.write(reinterpret_cast<char *>(this), sizeof(*this));
    iofile.close();
}

void account_query::delete_rec() {
    int n;
    ifstream infile;
    infile.open("record.txt", ios::binary);
    if (!infile) {
        cout << "\nError in opening file!" << endl;
        return;
    }
    infile.seekg(0, ios::end);
    int count = infile.tellg() / sizeof(*this);
    cout << "\nThere are " << count << " records in the file.";
    cout << "\nEnter Record Number to Delete: ";
    cin >> n;

    fstream tmpfile;
    tmpfile.open("tmpfile.txt", ios::out | ios::binary);
    infile.seekg(0);
    for (int i = 0; i < count; i++) {
        infile.read(reinterpret_cast<char *>(this), sizeof(*this));
        if (i == (n - 1)) continue;
        tmpfile.write(reinterpret_cast<char *>(this), sizeof(*this));
    }
    infile.close();
    tmpfile.close();
    remove("record.txt");
    rename("tmpfile.txt", "record.txt");
}

int main() {
    account_query A;
    int choice;
    cout << "***Account Information System***" << endl;
    while (true) {
        cout << "Select an option below:";
        cout << "\n1 --> Add record to file";
        cout << "\n2 --> Show record from file";
        cout << "\n3 --> Search Record from file";
        cout << "\n4 --> Update Record";
        cout << "\n5 --> Delete Record";
        cout << "\n6 --> Quit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                A.write_rec();
                break;
            case 2:
                A.read_rec();
                break;
            case 3:
                A.search_rec();
                break;
            case 4:
                A.edit_rec();
                break;
            case 5:
                A.delete_rec();
                break;
            case 6:
                exit(0);
                break;
            default:
                cout << "\nInvalid choice! Exiting..." << endl;
                exit(0);
        }
    }
    return 0;
}
