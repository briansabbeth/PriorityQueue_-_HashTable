#ifndef BINOMIALQUEUE_H_INCLUDED
#define BINOMIALQUEUE_H_INCLUDED
#include "QuadraticProbing.h"
#include <iostream>
#include <vector>
#include "dsexceptions.h"
#include "BinomialNode.h"
using namespace std;

// Binomial queue class
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// deleteMin( )           --> Return and remove smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void merge( rhs )      --> Absorb rhs into this heap
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable, typename Value>
class BinomialQueue
{
public:
    BinomialQueue( ) : theTrees( DEFAULT_TREES )
    {
        for( int i = 0; i < theTrees.size( ); i++ )
            theTrees[ i ] = NULL;
        currentSize = 0;
    }
   //Changed constructor to take a newly created binomial node
   //The struct used to be instantiated here.
    BinomialQueue(BinomialNode * node) : theTrees( 1 ), currentSize( 1 )
    {
        theTrees[ 0 ] = node;
    }

    BinomialQueue( const BinomialQueue & rhs ) : currentSize( 0 )
    {
        *this = rhs;
    }

    ~BinomialQueue( )
    {
        makeEmpty( );
    }

    /**
     * Return true if empty; false otherwise.
     */
    bool isEmpty( ) const
    {
        return currentSize == 0;
    }

    /**
     * Returns minimum item.
     * Throws UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException( );

        return theTrees[ findMinIndex( ) ]->element;
    }
    //return the comparison counter for number of comparisons in the merge
    int getCount()
    {
        return comparisonCounter;
    }

    /**
     * Insert item x into the priority queue; allows duplicates.
     *////////////////replace BinomialQueue tmp(x,y) with binomial node
    void insert( BinomialNode * node)
    {
        BinomialQueue tmp( node);
        merge( tmp );
    }

    /**
     * Scans through the array of indexes
     * Outputs the array index
     * This is the helper function to show the index of the array
     *     after the fastInsert has been performed.
     * returns 0;
     */
    void scanIndices()
    {
        for (int i = 0; i<theTrees.size(); i++)

            if (theTrees[i])
                cout<<theTrees[i]->element <<" ";
            else
                cout<<"NULL ";
        cout<<endl;
    }
    /**
     * Remove the smallest item from the priority queue.
     * Throws UnderflowException if empty.
     * Augmented to return a list of line numbers
     *           This was for the assignment, since it asked for line numbers
     */
    list<Value>  deleteMin( )
    {
        Comparable x;
        return deleteMin( x );
    }

    /**
     * Remove the minimum item and place in minItem.
     * Throws UnderflowException if empty.
     * As above, returns a list: minItem->list
     */
    list<Value> deleteMin( Comparable & minItem )
    {
        if( isEmpty( ) )
            throw UnderflowException( );

        int minIndex = findMinIndex( );
        minItem = theTrees[ minIndex ]->element;
        list<Value>minList = theTrees[ minIndex ]->lines;
        BinomialNode *oldRoot = theTrees[ minIndex ];
        BinomialNode *deletedTree = oldRoot->leftChild;
        delete oldRoot;

        // Construct H''
        BinomialQueue deletedQueue;
        deletedQueue.theTrees.resize( minIndex + 1 );
        deletedQueue.currentSize = ( 1 << minIndex ) - 1;
        for( int j = minIndex - 1; j >= 0; j-- )
        {
            deletedQueue.theTrees[ j ] = deletedTree;
            deletedTree = deletedTree->nextSibling;
            deletedQueue.theTrees[ j ]->nextSibling = NULL;
        }

        // Construct H'
        theTrees[ minIndex ] = NULL;
        currentSize -= deletedQueue.currentSize + 1;

        merge( deletedQueue );
        return minList;
    }

    /**
     * Make the priority queue logically empty.
     */
    void makeEmpty( )
    {
        currentSize = 0;
        for( int i = 0; i < theTrees.size( ); i++ )
            makeEmpty( theTrees[ i ] );
    }


    //Public fastInsert
    //increment the current size
    //call private fastInsert(node, 0)->0 is the first index and will be privatly incremented
    void fastInsert(BinomialNode * node)
    {
        currentSize++;

        fastInsert(node, 0);
    }
    /**
     * Merge rhs into the priority queue.
     * rhs becomes empty. rhs must be different from this.
     * Exercise 6.35 needed to make this operation more efficient.
     * Only Changes are incrementing the count.
     */
    void merge( BinomialQueue & rhs )
    {
        if( this == &rhs )    // Avoid aliasing problems
        {
            comparisonCounter++;
            return;
        }

        currentSize += rhs.currentSize;
        comparisonCounter++;

        if( currentSize > capacity( ) )
        {
            comparisonCounter++;

            int oldNumTrees = theTrees.size( );
            comparisonCounter++;

            int newNumTrees = max( theTrees.size( ), rhs.theTrees.size( ) ) + 1;
            comparisonCounter+=2;

            theTrees.resize( newNumTrees );
            for( int i = oldNumTrees; i < newNumTrees; i++ )
            {
                comparisonCounter+=4;
                theTrees[ i ] = NULL;
            }

        }
        comparisonCounter++;

        BinomialNode *carry = NULL;
        for( int i = 0, j = 1; j <= currentSize; i++, j *= 2 )
        {
            comparisonCounter+=5;
            BinomialNode *t1 = theTrees[ i ];
            comparisonCounter++;
            BinomialNode *t2 = i < rhs.theTrees.size( ) ? rhs.theTrees[ i ] : NULL;
            comparisonCounter+=2;
            int whichCase = t1 == NULL ? 0 : 1;
            comparisonCounter+=2;
            whichCase += t2 == NULL ? 0 : 2;
            whichCase += carry == NULL ? 0 : 4;

            switch( whichCase )
            {
            case 0: /* No trees */

            case 1: /* Only this */
                break;
            case 2: /* Only rhs */
                theTrees[ i ] = t2;
                comparisonCounter++;
                rhs.theTrees[ i ] = NULL;
                comparisonCounter++;
                comparisonCounter+=2;
                break;
            case 4: /* Only carry */
                comparisonCounter+=2;
                theTrees[ i ] = carry;
                comparisonCounter++;
                carry = NULL;
                comparisonCounter++;
                break;
            case 3: /* this and rhs */
                comparisonCounter+=2;
                carry = combineTrees( t1, t2 );
                comparisonCounter++;
                theTrees[ i ] = rhs.theTrees[ i ] = NULL;
                comparisonCounter+=2;
                break;
            case 5: /* this and carry */
                comparisonCounter+=2;

                carry = combineTrees( t1, carry );
                comparisonCounter++;
                theTrees[ i ] = NULL;
                comparisonCounter++;
                break;
            case 6: /* rhs and carry */
                comparisonCounter++;

                carry = combineTrees( t2, carry );
                rhs.theTrees[ i ] = NULL;
                break;
            case 7: /* All three */
                comparisonCounter+=2;
                theTrees[ i ] = carry;
                comparisonCounter++;
                carry = combineTrees( t1, t2 );
                comparisonCounter++;
                rhs.theTrees[ i ] = NULL;
                comparisonCounter++;
                break;
            }
        }

        for( int k = 0; k < rhs.theTrees.size( ); k++ )
        {
            comparisonCounter+=3;//=0;<rhd;=NULL
            rhs.theTrees[ k ] = NULL;
        }

        rhs.currentSize = 0;
    }

    const BinomialQueue & operator= ( const BinomialQueue & rhs )
    {
        if( this != &rhs )
        {
            makeEmpty( );
            theTrees.resize( rhs.theTrees.size( ) );  // Just in case
            for( int i = 0; i < rhs.theTrees.size( ); i++ )
                theTrees[ i ] = clone( rhs.theTrees[ i ] );
            currentSize = rhs.currentSize;
        }
        return *this;
    }

private:

    int comparisonCounter;
    enum { DEFAULT_TREES = 1 };

    int currentSize;                  // Number of items in the priority queue
    vector<BinomialNode *> theTrees;  // An array of tree roots

    /**
     * Find index of tree containing the smallest item in the priority queue.
     * The priority queue must not be empty.
     * Return the index of tree containing the smallest item.
     */
    int findMinIndex( ) const
    {
        int i;
        int minIndex;

        for( i = 0; theTrees[ i ] == NULL; i++ )
            ;

        for( minIndex = i; i < theTrees.size( ); i++ )
            if( theTrees[ i ] != NULL &&
                    theTrees[ i ]->element < theTrees[ minIndex ]->element )
                minIndex = i;

        return minIndex;
    }

    /**
     * Return the capacity.
     */
    int capacity( ) const
    {
        return ( 1 << theTrees.size( ) ) - 1;
    }

    /**
    * If the we count up to the trees.size then we must push back a node into the forest
    *     the node that we push back will be the root of a tree
    * If theTrees[count] == NULL -> BASE CASE
    *     put the single node or tree root into the index
    * ELSE combine trees save the new root in a temporary BinomialNode
    *     set the old root to NULL
    *     fastInsert(oldRoot, count +1)
    */

    void fastInsert(BinomialNode* node, int count)
    {
        if (count==theTrees.size())
            theTrees.push_back(node);

        if (theTrees[count]==NULL)
        {
            theTrees[count]=node;
        }
        else
        {

            BinomialNode* temp = combineTrees(theTrees[count],node);
            theTrees[count]=NULL;
            return fastInsert(temp, count+1);
        }
    }



    /**
         * Return the result of merging equal-sized t1 and t2.
         * Counts comparisons
         * Sets parent pointers
         */
    BinomialNode * combineTrees( BinomialNode *t1, BinomialNode *t2 )
    {

        if( t2->element < t1->element )
            return combineTrees( t2, t1 );
        t2->nextSibling = t1->leftChild;
        t2->parent = t1;

        t1->leftChild = t2;
        t1->parent = NULL;
        comparisonCounter+=5;
        return t1;
    }

    /**
     * Make a binomial tree logically empty, and free memory.
     */
    void makeEmpty( BinomialNode * & t )
    {
        if( t != NULL )
        {
            makeEmpty( t->leftChild );
            makeEmpty( t->nextSibling );
            delete t;
            t = NULL;
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinomialNode * clone( BinomialNode * t ) const
    {
        if( t == NULL )
            return NULL;
        else
            return new BinomialNode( t->element, t->lineNum ,clone( t->leftChild ), clone( t->nextSibling ) );
    }
};
#endif // BINOMIALQUEUE_H_INCLUDED
