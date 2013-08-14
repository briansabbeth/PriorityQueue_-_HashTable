ReadMe
Author: Brian Sabbeth
To compile: make all
    To run: ./a4

---------------------------------------------------------------------
FILES
1) main.cpp
2) IOHandler.cpp, IOHandler.h
3) BinomialNode.h (external struct)
4) BinomialQueue.h
5) QuadraticProbing.h, QuadraticProbing.cpp
6)Tokenizer.h, Tokenizer.cpp
7)dsexceptions.h
---------------------------------------------------------------------


---------------------------------------------------------------------
1) Main:  Handles all terminal IO
---------------------------------------------------------------------
2) IOHandler: Interface for all classes input and output.
              Creates new BinaryNodes
              Instantiates QuadraticProbing, BinomialQueue
              Inserts pointers to BinaryNodes into both classes

     Handles:
         Enters document.txt into Hashtable and BinomialQueue
         Gets the assignment and comparison count from BinomialQueue
         Removal from keys & nodes from both classes by percolating both
         elements and lines up to the root of the tree, Then deleting min.
         The removed element is searched, if not found returns true.
         Handles delete min in QuadProbing & from BinomialQueue
         Handles find() by searching in Hashtable, getting the address
         The address returned by find()in Hashtable is used to retrieve
         lines. The lines are returned to main and output as required.
----------------------------------------------------------------------


----------------------------------------------------------------------
3) BinomialNode: BinomialQueue-Struct.
                 Created in IOHandler.
                 Destroyed in BinomialQueue.
                 Accessed by HashTable.

     Handles:
          LineNumbers are pushed back into list<int> lines
          If the line number is already there it does not push_back
          Ex. If word appears on line 4 two times, push_back once.
     Modifications:
          Added List<int>lines, BinomialNode * parent, line push_back feature.
         *For readability and ease of implementation I did not templatize this struct.
          The linenumbers are a list of integers; The Comparable is a String.
-------------------------------------------------------------------------


-------------------------------------------------------------------------
4) BinomialQueue: Modified BinomialQueue
                  Inserted into by IOHandler(pointers to nodes)

     Modifications:
        Struct(BinomialNode) is removed.
        Constructor takes the Struct.
        Function: combineTrees() now handles pointing pointers to parents.
        Function: merge() now counts the number of comparisons and assignments.
        Function: deleteMin now returns a list.  This was useful for outputting deletions
        Function: fastInsert(): calls private fastInsert.  Sets count to 0
        Function fast insert: Recursively looks for an index of theTrees that is NULL
        along the way merges trees and inserts them into the found NULL area.
        *This will only work after the BinomialQueue has already been assembled.
-------------------------------------------------------------------------


-------------------------------------------------------------------------
5)QuadraticProbing: HashTable
                    Inserted into by IOHandler(KEY word)

          Modifications:
              struct HashEntry: includes pointer to BinomialNode (template Value)
              BinomialNode* find(string key).
                    *The way that the files are arranged this is a public function
                     which returns a node.

