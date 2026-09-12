# C++ Hash Table Implementation

## Project Overview

This project implements a custom hash table in C++ using polynomial string hashing and open addressing with linear probing for collision resolution.

The implementation supports insertion, searching, deletion, key updates, tombstone handling, dynamic resizing, and rehashing. A separate testing program provides interactive functionality for validating the hash table operations.

This project was originally developed as part of my Data Structures coursework.

## Features

- Polynomial hash function for string keys
- Custom `HashTable` implementation
- Key-value pair insertion
- Search and value retrieval
- Key deletion
- Updating existing key-value pairs
- Open addressing with linear probing
- Collision resolution
- Tombstone-based deletion
- Dynamic resizing and rehashing
- Load-factor monitoring
- Interactive testing of hash table operations

## Polynomial Hashing

String keys are hashed using a polynomial hash function with:

- Prime base `p = 31`
- Large prime modulus `M = 1,000,000,007`
- Character-based polynomial accumulation

The hash function processes each character of the key to generate a deterministic hash value.

## Hash Table Implementation

The hash table uses a `std::vector` of entries. Each table slot has one of three states:

- `EMPTY` — the slot has never been occupied
- `OCCUPIED` — the slot contains a valid key-value pair
- `DELETED` — the slot previously contained an entry and acts as a tombstone

### Linear Probing

When a collision occurs, subsequent positions in the table are examined until an appropriate slot is found.

Deleted slots can be reused for future insertions while still allowing searches to continue through the probe chain.

If an existing key is inserted again, its associated value is updated rather than creating a duplicate entry.

### Dynamic Resizing and Rehashing

The implementation monitors the table's load factor to maintain efficient operations.

When the load factor exceeds the configured threshold, the table expands and existing entries are rehashed into the new table.

The implementation also monitors used slots, including tombstones, allowing rehashing to clean up accumulated deleted entries that could otherwise increase probing time.

## Testing

A separate test program validates the functionality of the hash table through multiple operations, including:

- Inserting multiple key-value pairs
- Updating an existing record
- Searching for stored keys
- Accepting user-provided keys and values for insertion
- Accepting user-provided keys for deletion
- Displaying the updated hash table after operations

These tests demonstrate the behavior and correctness of insertion, searching, updating, and deletion.

## Time Complexity

Let:

- `L` = length of the string key
- `N` = number of elements in the hash table

| Operation | Best Case | Average Case | Worst Case |
| Hashing   |    O(L)   |     O(L)     |    O(L)    |
| Insert    |    O(L)   |     O(L)     |  O(L + N)  |
| Search    |    O(L)   |     O(L)     |  O(L + N)  |
| Delete    |    O(L)   |     O(L)     |  O(L + N)  |

The polynomial hash function requires O(L) time because every character of the key must be processed.

With a controlled load factor, hash table operations require an expected constant number of probes. Including the cost of hashing the string, their expected overall complexity is O(L).

In the worst case, linear probing may examine a large portion of the table, resulting in O(L + N).

## Concepts Demonstrated

- Hash Tables
- Polynomial Hashing
- Open Addressing
- Linear Probing
- Collision Resolution
- Tombstones
- Dynamic Resizing
- Rehashing
- Load Factors
- Object-Oriented Programming
- Algorithm Complexity Analysis
- Functional Testing

## Technologies

- C++
- C++ Standard Library
- `std::vector`

## Author

Mahsa Fazli
