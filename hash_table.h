/*****************************************
* Shahrood User ID:  -
* Submitted for Data Structure Course
* Department of Computer Engineering and IT
* Shahrood University of Technology
*
* By submitting this file, I affirm that
* I am the author of all modifications to
* the provided code.
*****************************************/

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <string>
#include "linked_list.h"

using namespace std;

/*
 * Structure
 * for storing a word with it's meaning
 */
struct Item{
    string word;
    string meaning;
};

class HashTable {

public:

    /*
     * Inputs: (2 string) one is word and another is it's meaning
     * Gets a random index of hash function and push the item into
     * the linked list in index in the array(table)
     */
    void insert(string const &, string const &);

    /*
     * Searches for given word
     * Gets the index of the word and navigates the linked list
     * in index in the table to find the corresponding meaning
     */
    string lookup(string const &);

    /*
     * Constructor
     * Creates a new array of linked lists
     */
    HashTable(int const &);

    /*
     * Deletes the table
     */
    ~HashTable();

private:

    // Stores the capacity of the array
    int capacity;

    // Stores linked lists
    DoubleLinkedList<Item> *table;

    /*
     * Calculates an integer proportional to the input
     */
    int hashFunction(const string&) const;
};

// n is the maximum number of words
HashTable::HashTable(int const & n) :
        capacity(n * 2) // Just a sample --> Load Factor = (n/2n) = 0.5
{

    table = new DoubleLinkedList<Item>[capacity];

}

HashTable::~HashTable()
{
    delete [] table;

}

void HashTable::insert(string const &word, string const &meaning) {

    int index = hashFunction(word);

    Item item;
    item.word = word;
    item.meaning = meaning;

    table[index].pushBack(item);
}

string HashTable::lookup(string const &word) {

    int index = hashFunction(word);

    bool found = !table[index].empty(); // If the linked list is empty, such a word doesn't exist

    if (!found) return "NOT FOUND";

    for (auto ptr = table[index].begin(); ptr != nullptr; ptr = ptr->next()) {
        string newWord = ptr->value().word;
        if (newWord == word) return ptr->value().meaning;
    }

    return "NOT FOUND";
}

int HashTable::hashFunction(const string& key) const {
    int hash = 7;
    int index;

    for (int i = 0; i < key.length(); i++)
    {
        hash += ((int) key[i]) * 31;
    }

    index = hash % capacity;
    return index;

}

#endif