/**
//
// Author:Brian Sabbeth
// Created on: April 19th 2013
// Description:  Interface for HashTable, BinomialNode BinomialQueue and main
// Purpose:   Utilize an BinaryQueue & Hashtable.  Gets words and line numbers from file
//            & adds to AVL.
//
*/

#ifndef IOHANDLER_H
#define IOHANDLER_H
#include <sstream>//for tokenization
#include <string>//for string manipulatiom
#include <fstream>//for file reading
#include <iostream>//file reading and I/O
#include "Tokenizer.h"//tokenizing strings from getline
#include "BinomialQueue.h"//where the strings are stored
#include "QuadraticProbing.h"
#include <list>//holds the line numbers
#include <locale>//for case sensativity

/**
/******************PUBLIC OPERATIONS*********************
readFile(char* file)->  inserts file
*/
class IOHandler
{
public:
    /**
    * Constructor only sets line number to zero
    */
    IOHandler()
    {
        lineNumber = 0;
        read();
    };

    /**
    * Takes a char* file. If no file returns false.
    * Increments the line number (starting at 1)
    * Checks that the individual characters are acceptable per charIsGood().
    * Breaks the string into 'word' strings via tokenizer
    *   set to specific deliminators
    * returns true (only because the file is good.) */
    //bool read(char* file);
    bool read();

    /**
    * Creates a new Binary Node
    * Calls the function fastinsert in the binaryqueue, where it is added
    * adds it to the hashtable
    */
    void fastInsert(string insert);
    /***
    * finds the word in the hashtfable & gets its address
    * resets the element to zero
    * uses the address to percolate the lineNumbers & the word up the tree
    * calls delete min and deletes the node.
    */
    bool removeKey(const string & stringInput);

    /**
    * Takes the string
    * Calls the Hashtable and gets the node using find() from hashtable.
    * Pushes the lines back.
    */
    list<int> find(std::string word);
    /**
    *returns the count of comparisons from the hashtable.
    */
    int getCount();

    /**
    * returns the list that was returned
    * after running the BinomialQueue's delete min function
    */
    list<int> deleteMin();
    /**
    * finds the string with the minimum value in the hashtable
    * sets member minstring to it.
    */
    string getMinString();

    /**
    * Runs scanIndices in BinomialQueue.
    * For output only.
    */
    void outputScannedIndices();
    virtual ~IOHandler()
    {
        /**unused as nothing added to heap*/
    };

private:

    /**
    *swaps chars while percolating
    */
    void swap(string & a, string &b);


    /**
    *swaps lists while percolating
    */
    void swap(list<int>&a, list<int>&b);


    /**
        * Takes chars from read().
        * Returns true if (char c) falls between ASCII 'A'=65 and 'z'=122
        * Numbers are not a problem
        * If not returns false and char is not added to sstream.
        * (Needed this because of possible incoding issue after downloading the
        *   file and causeing unrecognizable characters to be found)*/

    bool charIsGood(char c);

    /**
    * Takes the tokenized word and line number from read().
    * If a node containing that word doesnt exists
    *    it adds STL List to node.
    * If a node containing that word does exist
    *    it pushes back the line number it is on to the list previously created
    *
    */
    void insert(std::string word, int lineNum);



    ///line number for the input to the bin.queue
    int lineNumber;
    ///pointers to binomial nodes
    BinomialNode * binNode;
    ///queue instantiation
    BinomialQueue  <string, int> bqueue;
    ///hashtable instantiation
    HashTable <string, BinomialNode> hTable;
    ///smallest string used for control
    string minString;
};

#endif // IOHANDLER_H
