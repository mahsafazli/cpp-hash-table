// ====================================================================================
// HashTable 
// Author : Mahsa Fazli
// Polynomial hash + Open addressing (linear probing) + Tombstones + Dynamic resizing
// ====================================================================================
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
using namespace std;


class HashTable {
private:
    enum State { EMPTY, OCCUPIED, DELETED };

    struct Entry {
        string key;
        string value;
        State state;
        Entry() : key(""), value(""), state(EMPTY) {}
    };

    vector<Entry> table;
    int capacity;
    int countOccupied;          // number of OCCUPIED entries
    int countDeleted;           // number of DELETED entries (tombstones)

    // Polynomial hashing parameters
    const long long p = 31;            // prime base
    const long long MOD = 1000000007;  // large prime modulo

    long long polynomialHash(const string& s) const {
        long long hashValue = 0;
        long long pPower = 1;

        for (char c : s) {
            long long x = (unsigned char)c + 1; // includes spaces too
            hashValue = (hashValue + x * pPower) % MOD;
            pPower = (pPower * p) % MOD;
        }
        return hashValue;
    }

    int indexForKey(const string& key) const {
        return (int)(polynomialHash(key) % capacity);
    }

    double loadFactor() const {
        return (double)countOccupied / capacity;
    }

    double usedFactor() const {
        // includes tombstones; if too many tombstones, performance drops
        return (double)(countOccupied + countDeleted) / capacity;
    }

    void rehash(int newCapacity) {
        vector<Entry> oldTable = table;

        table.clear();
        table.resize(newCapacity);
        capacity = newCapacity;
        countOccupied = 0;
        countDeleted = 0;

        for (int i = 0; i < (int)oldTable.size(); i++) {
            if (oldTable[i].state == OCCUPIED) {
                insert(oldTable[i].key, oldTable[i].value);
            }
        }
    }

public:
    HashTable(int cap = 11) {
        capacity = cap;
        table.resize(capacity);
        countOccupied = 0;
        countDeleted = 0;
    }

    // Task 1: show hash value
    long long getHash(const string& key) const {
        return polynomialHash(key);
    }

    // Task 2: insert (linear probing + tombstone reuse + update if exists)
    bool insert(const string& key, const string& value) {
        // Resize to keep operations efficient
        if (loadFactor() > 0.70 || usedFactor() > 0.85) {
            rehash(capacity * 2 + 1);
        }

        int start = indexForKey(key);
        int firstDeletedIndex = -1;

        for (int i = 0; i < capacity; i++) {
            int idx = (start + i) % capacity;

            if (table[idx].state == OCCUPIED) {
                if (table[idx].key == key) {
                    // Update existing key
                    table[idx].value = value;
                    return true;
                }
            }
            else if (table[idx].state == DELETED) {
                if (firstDeletedIndex == -1) firstDeletedIndex = idx;
            }
            else { // EMPTY
                int target = (firstDeletedIndex != -1) ? firstDeletedIndex : idx;

                // If we insert into a tombstone, reduce tombstone count
                if (table[target].state == DELETED) {
                    countDeleted--;
                }

                table[target].key = key;
                table[target].value = value;
                table[target].state = OCCUPIED;
                countOccupied++;
                return true;
            }
        }

        return false; // should be rare due to resizing
    }

    // Task 2: search
    bool search(const string& key, string& outValue) const {
        int start = indexForKey(key);

        for (int i = 0; i < capacity; i++) {
            int idx = (start + i) % capacity;

            if (table[idx].state == EMPTY) {
                return false; // stop only on EMPTY
            }

            if (table[idx].state == OCCUPIED && table[idx].key == key) {
                outValue = table[idx].value;
                return true;
            }
            // DELETED or OCCUPIED with different key -> keep probing
        }
        return false;
    }

    // Task 2: deletion (tombstone)
    bool remove(const string& key) {
        int start = indexForKey(key);

        for (int i = 0; i < capacity; i++) {
            int idx = (start + i) % capacity;

            if (table[idx].state == EMPTY) {
                return false; // not found
            }

            if (table[idx].state == OCCUPIED && table[idx].key == key) {
                table[idx].state = DELETED; // tombstone
                countOccupied--;
                countDeleted++;

                // Optional cleanup: if too many tombstones, rehash to clean table
                if (usedFactor() > 0.85) {
                    rehash(capacity); // same size, just cleans tombstones
                }

                return true;
            }
        }
        return false;
    }

    // show updated record
    void printRecords() const {
        const int wKey = 22;
    const int wVal = 22;

    auto line = [&]() {
        cout << "+" << string(wKey, '-') << "+" << string(wVal, '-') << "+\n";
    };

    line();
    cout << "|" << left << setw(wKey) << " Key"
         << "|" << left << setw(wVal) << " Value" << "|\n";
    line();

    bool any = false;
    for (int i = 0; i < capacity; i++) {
        if (table[i].state == OCCUPIED) {
            cout << "|" << left << setw(wKey) << (" " + table[i].key)
                 << "|" << left << setw(wVal) << (" " + table[i].value) << "|\n";
            any = true;
        }
    }

    if (!any) {
        cout << "|" << left << setw(wKey) << " (no records)"
             << "|" << left << setw(wVal) << " " << "|\n";
    }

    line();
}

    // Back-End view:
        void printBackEndTable() const {
        const int wIndex = 7;
    const int wKey   = 14;
    const int wValue = 14;
    const int wState = 12;

    auto line = [&]() {
        cout << "+"
             << string(wIndex, '-') << "+"
             << string(wKey, '-')   << "+"
             << string(wValue, '-') << "+"
             << string(wState, '-') << "+\n";
    };

    line();
    cout << "|"
         << left << setw(wIndex) << "Index"
         << "|" << setw(wKey)   << "Key"
         << "|" << setw(wValue) << "Value"
         << "|" << setw(wState) << "State"
         << "|\n";
    line();

    for (int i = 0; i < capacity; i++) {
        cout << "|"
             << left << setw(wIndex) << i
             << "|";

        if (table[i].state == EMPTY) {
            cout << setw(wKey)   << ""
                 << "|" << setw(wValue) << ""
                 << "|" << setw(wState) << "EMPTY";
        }
        else if (table[i].state == DELETED) {
            cout << setw(wKey)   << "(deleted)"
                 << "|" << setw(wValue) << ""
                 << "|" << setw(wState) << "TOMBSTONE";
        }
        else {
            cout << setw(wKey)   << table[i].key
                 << "|" << setw(wValue) << table[i].value
                 << "|" << setw(wState) << "OCCUPIED";
        }
        cout << "|\n";
    }
    line();

    }
};

