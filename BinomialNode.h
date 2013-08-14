/**
* Co-Author: Brian Sabbeth
* BinomialNode, struct
* Uses:  Node for insertion into the BinomialQueue
* Modifications: Parent Node for percolation to the min value in BinomialQueue's forest
*                Constructor: For encapsulation,
*                             if lines.back() != lineNumber
*                                 pushes_back line numbers into lines-list.
*/
#ifndef BINOMIALNODE_H
#define BINOMIALNODE_H
#include <list>
#include <string>
#include <iostream>
using namespace std;

struct BinomialNode
{
    string    element;
    list<int> lines;
    BinomialNode *leftChild;
    BinomialNode *nextSibling;
    BinomialNode *parent;

    int lineNum;

    BinomialNode( const string & theElement, const int & theLineNum,
                  BinomialNode *lt, BinomialNode *rt, BinomialNode * par)
        : element( theElement ),lineNum (theLineNum), leftChild( lt ), nextSibling( rt ), parent(par)
    {
        if (lines.back()!= lineNum)
            lines.push_back(lineNum);
    }

};
#endif
