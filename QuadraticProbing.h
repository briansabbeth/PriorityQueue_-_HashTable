/**
 Co Author: Brian Sabbeth
 Modifications: Struct takes a binomialnode, line numbers and a word.
                public: find() returns an address which can be used
                        outside of class
 Uses:  Handles the fast lookups of BinomialQueue, that are not minValues.
        Also handled deletions of non-min-values.
        Where nodes are founds using  hashtable then percolated to the min
*/

#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H
#include "BinomialNode.h"
#include <vector>
#include <string>
using namespace std;

int nextPrime( int n );

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hash( string str ) --> Global method to hash strings

template <typename HashedObj, typename HashedVal>
class HashTable
{
public:
    explicit HashTable( int size = 3000 ) : array( nextPrime( size ) )
    {
        makeEmpty( );
    }


    HashedVal* find(const HashedObj &x) const
    {
        int currentPos = findPos(x);
        if (!contains(x))
            return NULL;
        else
            return array[findPos(x)].binNode;
    }

    bool contains( const HashedObj & x ) const
    {
        return isActive( findPos( x ) );
    }

    void makeEmpty( )
    {
        currentSize = 0;
        for( int i = 0; i < array.size( ); i++ )
            array[ i ].info = EMPTY;
    }
    /**
    * Insert:
    * Takes a string, lineNumbers and Node-address.
    * If the string already exists the line number gets pushed back into the node
    *      & if the lineNumber is already in the lines-list it does not get pushed back
    *      Returns false.
    * Else the hashTable array  = the HashEntry (string, address, line numbers)
    *      Returns true.
    */
    bool insert( const HashedObj & x, HashedVal *v, int lineNumber )
    {
        // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )//if x is not active push the linenumber back
        {
            if (array[currentPos].binNode->lines.back() != lineNumber)
                array[ currentPos ].binNode->lines.push_back(lineNumber);
            return false;
        }

        array[ currentPos ] = HashEntry( x,v,ACTIVE );

        // Rehash; see Section 5.5
        if( ++currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }

    //overloaded for rehashing only.
    bool insert( const HashedObj & x, HashedVal *v)
    {
        // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )//if x is not active push the linenumber back
        {
            return false;
        }

        array[ currentPos ] = HashEntry( x,v,ACTIVE );

        // Rehash; see Section 5.5
        if( ++currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }

    bool remove( const HashedObj & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;

        array[ currentPos ].info = DELETED;
        //cout<<array[currentPos].info<<endl;
        return true;
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };

private:
    struct HashEntry
    {
        HashedObj element;//word
        EntryType info;//deleted, active, or empty
        HashedVal *binNode;// address of  BinomialNode
        HashEntry( const HashedObj & e = HashedObj( ), HashedVal* b = NULL, EntryType i = EMPTY )
            : element( e ), binNode (b), info( i ) { }
    };

    vector<HashEntry> array;
    int currentSize;

    bool isActive( int currentPos ) const
    {
        return array[ currentPos ].info == ACTIVE;
    }

    int findPos( const HashedObj & x ) const
    {
        int offset = 1;
        int currentPos = myhash( x );

        // Assuming table is half-empty, and table length is prime,
        // this loop terminates
        while( array[ currentPos ].info != EMPTY &&
                array[ currentPos ].element != x )
        {
            currentPos += offset;  // Compute ith probe
            offset += 2;
            if( currentPos >= array.size( ) )
                currentPos -= array.size( );
        }

        return currentPos;
    }

    void rehash( )
    {
        vector<HashEntry> oldArray = array;

        // Create new double-sized, empty table
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        for( int j = 0; j < array.size( ); j++ )
            array[ j ].info = EMPTY;

        // Copy table over
        currentSize = 0;
        for( int i = 0; i < oldArray.size( ); i++ )
            if( oldArray[ i ].info == ACTIVE )
                insert( oldArray[ i ].element, oldArray[ i ].binNode );
    }
    int myhash( const HashedObj & x ) const
    {
        int hashVal = hash( x );

        hashVal %= array.size( );
        if( hashVal < 0 )
            hashVal += array.size( );

        return hashVal;
    }
};

int hash( const string & key );
int hash( int key );

#endif
