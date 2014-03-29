

README:
1) The descrbed Task
2) Implementation

====================================================================================================

The Task:       
               
Implement a binomial queue (bq) linked with a hash-table. You can use code 
provided in the textbook. The bq is used for fast access of the minimum element and the hash-table 
for fast access within the elements in the bq. 
 
(1) Implement the binomial queue. For testing use the strings in the document file used in the 
previous assignment. These would be the keys to be inserted into the priority queue. Each 
node should also hold as value the line numbers in which the words reside in the input 
document. Implement a hash-table of the keys that are already in the priority queue. So, for 
any pair <key,p>, where p is the pointer of the the node that holds key in the priority queue, 
hash on the key, and store the pair <key,p> in your hash table. Also note that for every 
insertion, deleteMin, or merge the hash-table needs to be updated as well. As part of this 
implementation you have to create a private function 
 <Pointer to bq node> find( <Type of Key> key). 
 This function will return the pointer p that points to the node of bq that holds the key, or 
NULL if key is not in the bq. 


(2) Count and print out the total number of comparisons and assignments executed for the 
insertions of all the N elements into the binomial queue. 


(3) Test the deleteMin() operation by applying a sequence of 10 deleteMin() and by printing out 
the result (i.e. key deleted along with associated line numbers). 


(4) Test the function find() as follows: Prompt the user to input a string key. Execute the private 
function find(key). If find returns a pointer to a node that indeed holds key printout that 
find() was successful; printout the set of line numbers as well. Otherwise, printout that find() 
did not find the key. 


(5) You are ready to implement now the remove(key) operation. For a given key, find its 
position p (p is a pointer) in the priority queue using the hash table. If the key is found delete 
it from the bq (Hint: your code should percolate the key up all the way to the root and then 
delete the root). Test your implementation by applying a sequence of remove(key) 
operations, and verify their correctness. For instance after remove(key), find(key) should 
return “not found”. Prompt the user 5 times to input a key. Execute then the remove(key) 
operation and verify (by printing whether the removal was successful or not). 


(6) Write a faster insert(key) function for the binomial queue. In order to achieve that you have 
to modify the merge() function and make it specific to the merging of one element only




=================================================================================================


ReadMe
Author: Brian Sabbeth
To compile: make all
    To run: ./a4
--------------------------------------------------------------------------------
FILES
1) main.cpp
2) IOHandler.cpp, IOHandler.h
3) BinomialNode.h (external struct)
4) BinomialQueue.h
5) QuadraticProbing.h, QuadraticProbing.cpp
6)Tokenizer.h, Tokenizer.cpp
7)dsexceptions.h
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
1) Main:  Handles all terminal IO
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
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
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
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
         *For readability and ease of I did not templatize this struct.
          The linenumbers are a list of integers; The Comparable is a String.
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
4) BinomialQueue: Modified BinomialQueue
                  Inserted into by IOHandler(pointers to nodes)
     Modifications:
        Struct(BinomialNode) is removed.
        Constructor takes the Struct.
        Function: combineTrees() now handles pointing pointers to parents.
        Function: merge() now counts the number of comparisons and assignments.
        Function: deleteMin returns a list.  Useful for outputting deletions
        Function: fastInsert(): calls private fastInsert.  Sets count to 0
        Function fast insert: Recursively looks for an index of the Trees = NULL
        along the way merges trees and inserts them into the found NULL area.
        *This will only work after the BinomialQueue has already been assembled.
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
5)QuadraticProbing: HashTable
          Inserted into by IOHandler(KEY word)
          Modifications:
           struct HashEntry: includes pointer to BinomialNode (template Value)
           BinomialNode* find(string key).
              *The way that the files are arranged this is a public function
               which returns a node.
               
 
               
==================================================================================================


