/*
CCC121 Laboratory Exercise No. 1
Due: November 20, 2022 (Sunday) at 11:55PM
*/

#include <iostream>
#include <assert.h>

using namespace std;

/*
The structure to be used for representing a doubly-linked link. This struct
declaration should not be modified in any way.
*/
template <class E>
struct DLink
{
    E theElement;
    DLink<E> *nextPtr;
    DLink<E> *prevPtr;
};

/*
Complete this implementation variant of the doubly-linked list. Use the same
convention as described in the slides. The DLink declaration to be used here is
just a struct and should not be modified in any way. All of the operations of
the original DLink class must be done in the methods of this class. Use
assertions to ensure the correct operation of this ADT. All memory allocations
should be checked with assertions and all discarded memory must be properly
deallocated.
*/
template <class E>
class DList
{
    //set head, tail, and curr to NULL for knowing whether or not they have been initialized in a constructor
    DLink<E> *head;
    DLink<E> *tail;
    DLink<E> *curr;
    int cnt;

public:
    // Return the size of the list
    int length() const
    {
        return cnt;// returns cnt, which is the number of the DList's DLinks aside from *head and *tail
    }

    // The constructor with initial list size
    DList(int size)
    {
        this();     
    }

    // The default constructor
    DList()
    {
        //allocates memory for head and tail
        curr = head = new DLink<E>;
        tail = new DLink<E>;

        //assert that head and tail weren't failed to be given allocated memory
        assert(head != NULL && tail !=NULL);

        //connects the two DLinks
        tail->prevPtr = head;
        tail->nextPtr = nullptr;
        head->nextPtr = tail;
        head->prevPtr = nullptr;

        //sets cnt to 0
        cnt = 0;
    }



    // The copy constructor
    //
    //
    // PACHECK
    //
    //
    //
    DList(const DList &source)
    {
        //allocates memory for head and tail
        curr = head = new DLink<E>;
        tail = new DLink<E>;

        //assert that head and tail weren't failed to be given allocated memory
        assert(head != NULL && tail !=NULL);

        //connects the two DLinks
        tail->prevPtr = head;
        tail->nextPtr = nullptr;
        head->nextPtr = tail;
        head->prevPtr = nullptr;

        //sets cnt to 0
        cnt = 0;

        //*looper's role is to "loop through" the DLinks in source, starting from the DLink next to *head's up until the
        //last appended DLink just before *tail. *looper will be updated and pointed to the same DLink
        //as it's *nextPtr, in other words moving through the DList source once for every iteration of the loop
        for(DLink<E> *looper = source.head->nextPtr; looper != source.tail; looper = looper->nextPtr){
            //append a new DLink to current object's DList by calling append() and passing the *looper DLink's theElement
            append(looper->theElement);

            //assigns the current object's *curr if looper happens to point at the same DLink as the source's *curr
            if(looper == source.curr) curr = tail->prevPtr;
        }
    }

    // The class destructor
    ~DList()
    {
        clear();//delete all the DLinks aside from *head and *tail's
        
        //delete manually *head and *tail, deallocating the memory
        delete head;
        delete tail;
    }

    // Empty the list
    void clear()
    {
        if(cnt > 0){//checks first if there are nodes in between *head and *tail
            curr = head->nextPtr;
            DLink<E> *temp;

            //deletes DLink one by one
            while(curr!=tail){
                temp = curr->nextPtr;
                delete curr;// deletes *curr, deallocating the memory
                curr = temp;
            }
            //connecting head and tail
            curr = head;
            head->nextPtr = tail;
            tail->prevPtr = head;
            cnt = 0;
        }
    }

    // Set current to first element
    void moveToStart()
    {
        //*curr points to the DLink of *head
        curr = head;
    }

    // Set current element to end of list
    void moveToEnd()
    {
        //*curr points to the previous DLink of *tail, thereby pointing to the last DLink
        curr = tail->prevPtr;

        //dili mainsertan si curr if == tail
    }

    // Advance current to the next element
    void next()
    {
        //checks first if there are DLinks between *head and *tail and *curr is not before *tail nor before the DLink behind of *tail's,
        //if so assigns *curr to the next DLink 
        if(cnt > 0 && (curr->nextPtr != tail->prevPtr || curr->nextPtr != tail)) curr = curr->nextPtr;
    }

    // Return the current element
    //Double Check
    E & getValue() const
    {
        //asserts first if *curr isn't NULL before
        //returning its theElement
        assert(curr != tail->prevPtr  && curr != tail);
        return curr->nextPtr->theElement;
    }

    // Insert value at current position
    // curr->next ang new DLink
    //
    void insert(const E &it)
    {
        //allocate memory first for temp and assert it was successful
        DLink<E> *temp = new DLink<E>;
        assert(temp != NULL);

        //inserting the DLink pointed by *temp after *curr's and before *curr->nextPtr's, the DLink after *curr's DLink originally
        temp->nextPtr = curr->nextPtr;
        temp->prevPtr = curr;
        curr->nextPtr = curr->nextPtr->prevPtr = temp;

        //setting the DLink's theElement value to it
        temp->theElement = it;
        //increment cnt
        cnt++;
    }

    // Append value at the end of the list
    void append(const E &it)
    {
        //allocate memory first for temp and assert it was successful
        DLink<E> *temp = new DLink<E>;
        assert(temp != NULL);

        //inserting the DLink pointed by *temp after *tail->prevPtr's and before *tail's
        temp->nextPtr = tail;
        temp->prevPtr = tail->prevPtr;
        tail->prevPtr = temp->prevPtr->nextPtr = temp;

        //setting the DLink's theElement value to it
        temp->theElement = it;
        //increment cnt
        cnt++;
    }

    // Remove and return the current element
    E remove()
    {   //assert(curr->nextPtr == tail);
        assert(cnt > 0);
        if(curr->nextPtr == tail) return '\0';//E(NULL)

        E it = curr->nextPtr->theElement;
        //We aim to delete *temp by the end, so we connect first the DLinks of *curr's
        //and after it then delete the DLink pointed by *temp
        DLink<E> *temp = curr->nextPtr;
        curr->nextPtr->nextPtr->prevPtr = curr;
        curr->nextPtr = curr->nextPtr->nextPtr;
        delete temp;
        //decrement cnt
        cnt--;

        if(curr->nextPtr == tail && curr != head) curr = curr->prevPtr;
        return it;
    }

    // Advance current to the previous element
    void prev()
    {
        //checks first if there are DLinks between *head's and *tail's DLinks and *curr is not equal to *head,
        //if so assigns *curr to the previous DLink 
        if(cnt > 0 && curr != head) curr = curr->prevPtr;
    }

    // Return position of the current element
    int currPos() const
    {
        int num;
        DLink<E> *temp = head;
        //checks first if *temp is equal to *curr before incrementing num
        for(num = 0; temp != curr; num++){
            temp = temp->nextPtr;
        }
        //return the integer position of *curr's DLink
        return num;
    }

    // Set current to the element at the given position
    void moveToPos(int pos)
    {
        assert(0 <= pos && pos < cnt);
        curr = head;
        //checks first if i is less than pos before moving *curr 1 DLink to the right
        for(int i = 0; i < pos; i++){
            curr = curr->nextPtr;
        }
    }
};

/*
This is the main function for testing the implementation of the DList class.
This function can be freely modified.
*/
int main(void)
{
    int i;
    DList<int> theList;
    //theList.prev();

    // populate the list
    for (i = 0; i < 10; ++i)
    {
        theList.append(i);
    }// i = 10
    while (i < 20)
    {
        theList.insert(i);
        ++i;
    }

    // display the contents of the list
    theList.moveToStart();
    for (i = 0; i < theList.length(); ++i)
    {
        cout << theList.getValue() << " ";

        theList.next();
    }
    cout << "\n";


    // display the contents of the list in reverse order
    theList.moveToEnd();
    for (i = 0; i < theList.length(); ++i)
    {
        theList.prev();
        cout << theList.getValue() << " ";
    }
    cout << "\n";

    // replace the contents of the list
    theList.clear();
    theList.clear();
    for (i = 0; i < 10; ++i)
    {
        //cout<<i;

        theList.append(i + 100);
        theList.moveToEnd();//ako nagedit
    }

    // display the contents of the list
    theList.moveToStart();
    for (i = 0; i < theList.length(); ++i)
    {
        cout << theList.getValue() << " ";

        theList.next();
    }
    cout << "\n";

    cout << endl << "kobe" << endl;

    // remove two elements at the specified position
    theList.moveToPos(9);
    cout << theList.currPos() << " " << theList.getValue() << "\n";

    theList.remove();
    theList.remove();

    // display the contents of the list
    theList.moveToStart();
    for (i = 0; i < theList.length(); ++i)
    {
        cout << theList.getValue() << " ";
 
        theList.next();
    }
    cout << "\n";

    theList.moveToPos(3);
    cout << "\n" << "theList's curr is " << theList.getValue() << endl;
    DList<int> anothaOne(theList);
    cout << "\n\n" << "anothaOne's curr is " << anothaOne.getValue() << endl << endl;

    cout<<"theList is copied to anothaOne"<<endl;
    cout<<"length of anothaOne is "<<anothaOne.length()<<"\n\n";
    
    //100 101 102 103 104 105 106 107
    anothaOne.moveToStart();
    anothaOne.append(69);
    anothaOne.insert(420);
    for (i = 0; i < anothaOne.length(); ++i)
    {
        cout << anothaOne.getValue() << " ";

        anothaOne.next();
    }
    
    //420 100 101 102 103 104 105 106 107 69
    //10
    
    anothaOne.moveToStart();//420
    anothaOne.insert(1000);
    cout<<"\n\n";
    anothaOne.moveToStart();

    for (i = 0; i < anothaOne.length(); ++i)
    {
        cout << anothaOne.getValue() << " ";

        anothaOne.next();
    }

    anothaOne.moveToStart();
    anothaOne.remove();    
    cout <<"\n\n";
    for (i = 0; i < anothaOne.length(); ++i)
    {
        cout << anothaOne.getValue() << " ";

        anothaOne.next();
    }

    anothaOne.moveToEnd();//getValue() = 69
    anothaOne.insert(9999);
    anothaOne.moveToStart();
    cout <<"\n\n";
    for (i = 0; i < anothaOne.length(); ++i)
    {
        cout << anothaOne.getValue() << " ";

        anothaOne.next();
    }

    //cout<< endl << anothaOne.length() << endl;
    
    cout << "\n\n";
    theList.moveToStart();
    for (i = 0; i < theList.length(); ++i)
    {
        cout << theList.getValue() << " ";

        theList.next();
    }

    // 1 2 3 4
    //moveToENd = tail->prev->prev
    //curr = 3
    //curr->next = 4
    //getValue = 4
    //remove() = 4
    //remove curr->next 
    //1 2 3

    return 0;
}
