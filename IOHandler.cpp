/**
// TreeHandler class
// Author:Brian Sabbeth
// Created on: March 12th 2013
// Description:  Interface for AvlTree and main
// Purpose:   Utilize an AVL.  Gets words and line numbers from file
//            & adds to AVL.
//*/


#include "IOHandler.h"



bool IOHandler::read()
{

    //function variables
    std::stringstream stream;
    std::string line;//for getline
    std::string token;//for tokenization
    std::ifstream myfile("words.txt");
    locale loc;//make everything lowercase
    Tokenizer str;

    //now handle the file
    if (myfile.is_open())
    {
        while(myfile.good())
        {
            while (getline (myfile,line))
            {
                stream.clear() ;  // reset any error state.
                stream.str("") ;  // reset stream
                lineNumber++;
                //Just incase of strange un-alpha-numeric characters
                for(int i = 0; i<line.size(); i++)
                {
                    if (charIsGood(line[i]))
                    {
                        stream<<tolower(line[i],loc);//makelowercase, put in stream
                    }
                }
                str.set(stream.str()," .:-,_");//deliminators
                while ((token = str.next()) != "")//tokenizer
                {
                    insert(token, lineNumber);
                }
            }
        }
        return true;
    }
    //end of if (if the file is good)
    else
        return false;
}

void IOHandler::outputScannedIndices()
{
    bqueue.scanIndices();
}

void IOHandler::fastInsert(string w)
{
    //this node has no lines so line is set to 0;
    binNode= new BinomialNode( w,0, NULL, NULL, NULL );
    hTable.insert(w, binNode, 0);
    bqueue.fastInsert(binNode);
    bqueue.scanIndices();
}


void IOHandler::insert(std::string word, int lineNum)
{
    binNode =  new BinomialNode( word,lineNum, NULL, NULL, NULL );
    if(hTable.insert(word, binNode, lineNum))
    {
        bqueue.insert(binNode);
    }
}


int IOHandler:: getCount()
{
    return bqueue.getCount();
}


list<int> IOHandler:: find(std::string word)
{
    list<int>lines;
    BinomialNode * foundNode = hTable.find(word);

    if (foundNode == NULL )
    {
        lines.push_back(-1);
        return lines;
    }
    else
    {
        lines = foundNode->lines;
        return lines;
    }

}
list<int> IOHandler::deleteMin()
{

    hTable.remove(minString);
    return bqueue.deleteMin();


}
///The trace has been commented out and kept in the event you would like to trace the
///    nodes changing as they percolate their elements and line numbers to the top.
bool IOHandler::removeKey(const string & stringInput)
{
    /*make a temporary node pointer that will be set to find*/
    BinomialNode * tempNode;
    /*finds the minimul string will help with termination of percolation*/
    string minString = bqueue.findMin();
    //TRACE//cout<<"Min-string : "<<minString<<endl;
    /*if the string is not in the hashtable we output null*/
    if (!hTable.contains(stringInput)||tempNode==NULL)
        return 0;

    tempNode = hTable.find(stringInput);
    //TRACE// cout<<"element "<<tempNode->element<<endl;
    tempNode->element = "0";
    //TRACE//cout<<"Tempnode now = "<<tempNode->element<<endl;
    while (tempNode->parent!= NULL && tempNode->element != minString)
    {
        //TRACE//cout<<"path->"<<tempNode->parent->element<<endl;
        swap(tempNode->element, tempNode->parent->element);
        swap(tempNode->lines, tempNode->parent->lines);
        //TRACE// cout<<"swapped->"<<tempNode->element<<" "<<tempNode->parent->element<<endl;
        //TRACE// cout<<"minstring->"<<bqueue.findMin()<<endl;
        tempNode = tempNode->parent;
    }
    bqueue.deleteMin();
    hTable.remove(stringInput);
    if (hTable.find(stringInput)==NULL)
    {
        return 1;
    }
    return 0;
}


string IOHandler::getMinString()
{
    return minString = bqueue.findMin();
}
void IOHandler:: swap(string & a, string & b)
{
    string temp = a;
    a = b;
    b = temp;

}

void IOHandler:: swap(list<int> & a, list<int> & b)
{
    list<int> temp = a;
    a = b;
    b = temp;

}




///private
bool IOHandler :: charIsGood(char c)
{
    if ((c >= ' ' && c <='z'))
    {
        return true;
    }
    else
        // std::cout<<"FALSE";
        return false;
}

