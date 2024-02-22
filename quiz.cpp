/*
*	CPSC 122
*	Practice Lab Final Exam
*	Fall 2023
*
*   Deque or Double Ended Queue is a generalized version of Queue data structure
*   that allows insert and delete at both ends.
*   (pronounced �deck� or �deek�) is a double-ended queue. It is similar to a vector,
*	but allows efficient access to values at both the front and the rear.
*/

#include <iostream>

using namespace std;

//header area
class DynamicDeque
{
private:
	// Structure for the deque nodes
	struct DequeNode
	{
		int value;       // Value in a node
		DequeNode* nextPtr; // Pointer to the next node
		DequeNode* prevPtr; // Pointer to the prev node
	};

	DequeNode* frontPtr;  // The front of the deque
	DequeNode* rearPtr;   // The rear of the deque
	int numItems;      // Number of items in the deque
public:
	// Constructor
	DynamicDeque(){
        numItems = 0;
        frontPtr = nullptr;
        rearPtr = nullptr;
    }

	~DynamicDeque(){
        clear();
        numItems = 0;
    }

	// Deque operations
	void enqueue(int);
	void dequeue(int&);
	bool isEmpty(void) const;
	void clear(void);

	//TODO: implement Additional Deque member functions
	void enqueueFront(int);

	void displayReverse(void) const; //TODO: must be recursive
	void traverseInReverse(DequeNode*) const;

	int getNumItems(void) const {return numItems;};
};

class Generic {
    public:
    
    void nonOveride(void) const { cout << "I Cannot be Overidden!" << endl;}
    DynamicDeque deque;

};

class Derived : public Generic {
};

//TODO: create two additional class definitions
// Class1
//1. create an abstract base class called Generic (details are up to you)
//2. create a public member function which cannot be overriden in a derived class
	// a. this member function outputs "I cannot be overriden!" when called
//3. Make your DynamicDeque class a public composite member (named deque) of the Generic class

// Class2
//4. create a public class named "Derived" derived from the abstract base class from #1
//5. declare an instance of your derived class variable in your main.
//6. call the non-overridable public member function from main (from 2.a).
//7. using your instance of the Derived class object, complete the remaining missing steps in main


//main area
int main(void)
{
	//DynamicDeque myDeque; <- you should NOT be using this to demonstrate anything below.
	int value = 0;
	int numItems = 0;

	//Declare instance of Derived class object
    Derived classVariable;
	//demonstrate Derived class functions
    classVariable.nonOveride();

	cout << endl;

	//demonstrating deque functions

	//add 6 items to the list via Derived class object.
    classVariable.deque.enqueue(2);
    classVariable.deque.enqueue(10);
    classVariable.deque.enqueue(20);
    classVariable.deque.enqueue(30);
    classVariable.deque.enqueue(40);
    classVariable.deque.enqueue(50);
    
    numItems = classVariable.deque.getNumItems();


	cout << "Added " << numItems << " items to the deque." << endl;
	classVariable.deque.displayReverse();
    cout << endl;
    classVariable.deque.dequeue(value);
    numItems = classVariable.deque.getNumItems();

	cout << "Removed a " << value << " from the front of the deque" << endl;
	cout << "The deque now contains " << numItems << " items." << endl;
	classVariable.deque.displayReverse();
    cout << endl;
    classVariable.deque.enqueueFront(42);
    numItems = classVariable.deque.getNumItems();

	cout << "Now adding a 42 to the front of the deque " << endl;
	cout << "The deque now contains " << numItems << " items." << endl;
	classVariable.deque.displayReverse();
    cout << endl;
    classVariable.deque.enqueueFront(9001);
    numItems = classVariable.deque.getNumItems();

	cout << "Now adding a 9001 to the front of the deque " << endl;
	cout << "The deque now contains " << numItems << " items." << endl;
	classVariable.deque.displayReverse();
    cout << endl;
	return 0;
}

//definitions area

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the deque.                 *
//********************************************

void DynamicDeque::enqueue(int num)
{
	DequeNode* newNode = nullptr;

	// Create a new node and store num there.
	newNode = new DequeNode;
	newNode->value = num;
	newNode->nextPtr = nullptr;
	newNode->prevPtr = nullptr;

	// Adjust front and rear as necessary.
	if (isEmpty())
	{
		frontPtr = newNode;
		rearPtr = newNode;
	}
	else
	{
		newNode->prevPtr = rearPtr;
		rearPtr->nextPtr = newNode;
		rearPtr = newNode;
	}

	// Update numItems.
	numItems++;
}


//********************************************
// Function enqueueFront inserts the value in *
// num at the front of the deque.             *
//********************************************
void DynamicDeque::enqueueFront(int num)
{
    DequeNode* tempNode = new DequeNode;
    tempNode->value = num;
    tempNode->nextPtr = nullptr;
	tempNode->prevPtr = nullptr;

    if (isEmpty())
	{
		frontPtr = tempNode;
		rearPtr = tempNode;
	} else {
	    tempNode->nextPtr = frontPtr;
        frontPtr->prevPtr = tempNode;
	    frontPtr = tempNode;
    }

	numItems++;
}

void DynamicDeque::traverseInReverse(DequeNode* tempNode) const {
        if (tempNode == nullptr) { 
        return;
    }
    cout<<tempNode->value<<" ";
    traverseInReverse(tempNode->prevPtr);
}

void DynamicDeque::displayReverse(void) const {
    traverseInReverse(rearPtr);
}
//**********************************************
// Function dequeue removes the value at the   *
// front of the deque, and copies it into num. *
//**********************************************

void DynamicDeque::dequeue(int& num)
{
	DequeNode* temp = nullptr;

	if (isEmpty())
	{
		cout << "The deque is empty.\n";
	}
	else
	{
		// Save the front node value in num.
		num = frontPtr->value;

		// Remove the front node and delete it.
		temp = frontPtr;
		frontPtr = frontPtr->nextPtr;

		if (!frontPtr) //One element deque
		{
			rearPtr = nullptr;
		}
		else
		{
			frontPtr->prevPtr = nullptr;
		}

		delete temp;

		// Update numItems.
		numItems--;
	}
}

//*********************************************
// Function isEmpty returns true if the deque *
// is empty, and false otherwise.             *
//*********************************************

bool DynamicDeque::isEmpty() const
{
	bool status;

	if (numItems > 0)
		status = false;
	else
		status = true;
	return status;
}

//********************************************
// Function clear dequeues all the elements  *
// in the deque.                             *
//********************************************

void DynamicDeque::clear()
{
	int value;   // Dummy variable for dequeue

	while (!isEmpty())
		dequeue(value);
}