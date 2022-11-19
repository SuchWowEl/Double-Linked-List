#include <iostream>
//#include <assert.h>

using namespace std;

struct linkNode{
    int number;
    linkNode *nextLink;
};

void deleteNode(linkNode *temp){
    /*linkNode *baseLink;
    for(int x = 0; x < 20; x++){
        baseLink = temp;
        temp = baseLink->nextLink;
        cout << "Deleting: " << baseLink->number << endl;
        delete baseLink;
        cout << baseLink->number << " " << baseLink->nextLink << endl;
    }*/

    if(temp->number != 20)
        deleteNode(temp->nextLink);
    //cout << "Deleting: " << temp->number<< endl;
    delete temp;
    //return;
    //cout << temp->number << " " << temp->nextLink << endl;
}

int main()
{
    linkNode *tempLink = new linkNode, *baseLink = tempLink;
    //assert(tempLink != NULL);

    for(int x = 1; x <= 19; x++){
        tempLink->number = x;
        tempLink->nextLink = new linkNode;
        //assert(tempLink->nextLink != NULL);
        tempLink = tempLink->nextLink;
    }

    tempLink->number = 20;
    tempLink->nextLink = baseLink;
    tempLink = baseLink;

    for(int x = 0; x < 20; x++){
        cout << tempLink->number << "          " << tempLink << endl;
        tempLink = tempLink->nextLink;
    }

    deleteNode(tempLink);

    return 0;
}
