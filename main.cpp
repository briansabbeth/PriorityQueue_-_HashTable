#include <iostream>

using namespace std;
#include "IOHandler.h"
#include <list>


//takes io
//calls iohandler to delete string
//removes the string via percolation
//return 0
void removeString(IOHandler& io);//

//takes the io
//calls the deleteMin 5 times
//uses the deleteMin's returned node to output lines.
//returns 0
void deleteMin(IOHandler& io);

//takes io
//requests user input to search for in hash tabele.
//outputs the line number that the word was written on
void find(IOHandler& io);

//takes io
//returns get count from iohandler
void getCount(IOHandler& io);


//quickly inserts a single node after binomial queue is created
//if successful outputs success
//returns 0
void fastInsert(IOHandler& io);
//IOHandler io;
int main()
{
  IOHandler io;//creates the ioHandler class
  getCount(io);
  deleteMin(io);
  find(io);
  removeString(io);
  fastInsert(io);
    return 0;
}

void getCount(IOHandler& io)
{
    cout<<endl;
    cout<<"\nPART 2 TESTING FUNCTION: getCount()"<<endl;

    cout<<"Total comparisons and assignments: "<<io.getCount()<<endl;

}

void find(IOHandler& io)
{

    cout<<endl<<endl;
    cout<<"\nPART 4 TESTING FUNCTION: find()"<<endl;

    string ans;

    do
    {
        string searchKey;
        cout<<"Please enter a key to find: ";
        cin>>searchKey;
        cout<<"KEY:     \""<< searchKey <<"\""<<endl;
        list<int> outputList = io.find(searchKey);

        if (outputList.front() == -1)
            cout<<"STATUS:"<< "    NULL"<<endl;
        else
        {
            cout<<"STATUS:   "<<"found. "<<endl;
            cout<<"LINES: ";

            for (std::list<int>::iterator it = outputList.begin(); it != outputList.end(); it++)
            {
                if (*it!= outputList.back())
                    cout << *it << ",";
                else cout<<*it<<" ";
            }
            cout<<endl;
        }
        cout<<"To search again enter 'y' else hit any key: ";
        cin>>ans;
        cout<<endl;

    }
    while (ans == "y");
}

void deleteMin(IOHandler& io)
{
    cout<<endl<<endl;
    cout<<"\nPART 3 TESTING FUNCTION: deleteMin()"<<endl;

    for(int i = 1; i<11; i++)
    {
        cout<<i<<"] \""<<io.getMinString()<<"\""<<endl;
        cout<<"    LINES: ";
        list<int> outputList = io.deleteMin();
        for (std::list<int>::iterator it = outputList.begin(); it != outputList.end(); it++)
        {
            if (*it!= outputList.back())
                cout << *it << ",";
            else cout<<*it<<" ";
        }

        cout<< endl;
        cout<< endl;

    }
}



void removeString(IOHandler& io)
{
      cout<<"\nPART 5 TESTING FUNCTION: removeString(string word)//non-min-delete: "<<endl;

    string input;
    for(int i = 0; i<5; i++)
    {
        cout<<i+1<<"] Please enter a key for removal: ";
        cin>>input;
        if (io.removeKey(input) == 0)
        {
            cout<<"KEY : \""<<input<<"\" unfound"<<endl;
        }
        else
            cout<<"KEY : \""<<input<<"\": checked & successfully deleted"<<endl;
    }
}

void fastInsert(IOHandler& io)
{
    cout<<"\nPART 6 TESTING FUNCTION: fastInsert(string word)"<<endl;
    cout<<"Original Vector Indices:"<<endl;
    io.outputScannedIndices();
    cout<<endl;
    string ans;
    string word;
    do
    {
        cout<<"Please enter a string for fast insert:"<<endl;
        cin>>word;
        io.fastInsert(word);
//cout<<"New indices after fast insert: \n";
      //  io.outputScannedIndices();


        cout<<"To search again enter 'y' else hit any key: ";
        cin>>ans;
        cout<<endl<<endl;

    }while(ans=="y");
}
