// ==================================================================================================
// Testing --> Validates insert, search, delete and shows updated record each time 
// Author : Mahsa Fazli
// ==================================================================================================
#include <iostream>
#include <string>
using namespace std;
#include "A2-hashing.cpp"

int main() {
    HashTable ht;

   //Testing Task 1:
    cout << "\n+++ Task 1 +++\n";
    string s;
    cout << "\nEnter a string: ";
    getline(cin, s);
    cout << "\nPolynomial hash value = " << ht.getHash(s) << "\n\n";

    //Task 2 and 3: Separate Test Program
    cout << "+++ Task 2 & 3 +++\n";
    // Step 1: Insert multiple pairs (preset) and show updated record
    cout << "\n*Step 1: Multiple key-value pairs have been already inserted (are preset) as:\n ";
    ht.insert("mahsa", "student");
    ht.insert("ali", "TA");
    ht.insert("sara", "prof");
    ht.insert("john", "staff");
    ht.insert("mary", "admin");
    ht.printRecords();

    // Step 2,3: Interactive testing loop
    cout << "\n*Step 2 and 3: You can interact :\n";
    while (true) {
        cout << "\n===== Testing Menu =====\n";
        cout << "1) Insert a key-value pair\n";
        cout << "2) Search for a key\n";
        cout << "3) Delete a key\n";
        cout << "4) Show updated record\n";
        cout << "5) Show back-end table (includes tombstones)\n";
        cout << "0) Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 0) {
            cout << "Exiting tester.\n";
            break;
        }
        else if (choice == 1) {
            string key, value;
            cout << "Enter key: ";
            getline(cin, key);
            cout << "Enter value: ";
            getline(cin, value);

            if (ht.insert(key, value)) {
                cout << "Inserted/Updated successfully.\n";
            } else {
                cout << "Insert failed.\n";
            }
            ht.printRecords();
        }
        else if (choice == 2) {
            string key, value;
            cout << "Enter key to search: ";
            getline(cin, key);

            if (ht.search(key, value)) {
                cout << "Found: " << key << " -> " << value << "\n";
            } else {
                cout << "Key not found.\n";
            }
        }
        else if (choice == 3) {
            string key;
            cout << "Enter key to delete: ";
            getline(cin, key);

            if (ht.remove(key)) {
                cout << "Deleted successfully (tombstone placed).\n";
            } else {
                cout << "Key not found.\n";
            }
            ht.printRecords();
        }
        else if (choice == 4) {
            ht.printRecords();
        }
        else if (choice == 5) {
            ht.printBackEndTable();
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}

