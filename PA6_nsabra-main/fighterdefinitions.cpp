
#include "header.h"

//static functions
int Player::numPlayers;
vector<int> Player::playerIds;




//Main Functions
/*****************************************************
 * Function: Choose Class
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * Allow Player to choose class
 * 
*/
void chooseClass(char& chosenClass)
{

    cout << "Please Choose Your Class Below: " << endl
         << "(Type m)               (Type k)" << endl
         << "|MAGIC SWORDSMAN|------|KNIGHT|" << endl;
    cin >> chosenClass;
    if(chosenClass == 'k' || chosenClass == 'K' || chosenClass == 'm' || chosenClass == 'M' ) // check caps too because im nice
    {
        return;
    } else
    {
        cout << "Invalid Choice- please try again" << endl;
        chooseClass(chosenClass); // recursive :O
    }
}





//PlayerInventory Functions

/*****************************************************
 * Function: Is Empty
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * Checks if empty
 * 
*/
bool PlayerInventory::isEmpty()
{
    return front == nullptr; //is empty if the front is the nullptr
}
/*****************************************************
 * Function: Default Constructor
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * Default Constructor
 * 
*/
PlayerInventory::PlayerInventory()
{
    inventorySize = 0; //set inventory size to 0
    front = nullptr; //front and rear are nullptr
    rear = nullptr;
}
/*****************************************************
 * Function: Destructor
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * Allow Player to choose class
 * 
*/
PlayerInventory::~PlayerInventory()
{
    while(!isEmpty())
    {
        dequeue(); //deconstruct in the same way you clear
    }
}
/*****************************************************
 * Function: EnQueue
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * Adds to queue
 * 
*/
void PlayerInventory::enqueue(InventoryItem item)
{
    queueNode* newNode = new queueNode; //allocate memory for newNode
    newNode->item = item; //set initial values
    newNode->nextItem = nullptr;
    if(isEmpty())
    {
        front = rear = newNode; //if empty, set the front and rear to newNode
    }
    else
    {
        rear->nextItem = newNode; //set the item following the rear to newNode
        rear = newNode; //set the rear newNode
    }
    inventorySize++; //incriment inventory size
}

/*****************************************************
 * Function: Display All Items
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * Displays the Inventory
 * 
*/
void PlayerInventory::displayAllItems(queueNode* current) {
    if (isEmpty() || current == nullptr) {
        cout << endl; // base case
        return;
    }

    cout << current->item.weaponName << endl; 
    displayAllItems(current->nextItem); //recurse
}


/*****************************************************
 * Function: DeQueue
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * Allow Player to choose class
 * 
*/
void PlayerInventory::dequeue()
{
    if(isEmpty())
    {
        return; //if empty do not remove anything
    }
    queueNode* headPtr = front;

    front = front->nextItem;//set front equal to next item
    if (front == nullptr) //if the front is now the null ptr
    {
        rear = nullptr; //set the rear to the null ptr
    }
    delete headPtr; //delete first node
}

/*****************************************************
 * Function: Clear
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * clears the inventory
 * 
*/
void PlayerInventory::clear()
{
    while(!isEmpty())
    {
        dequeue(); //go through everything and delete until empty
    }
}

/*****************************************************
 * Function: Size
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * Outputs the Size
 * 
*/
int PlayerInventory::size()
{
    int size = 0;
    queueNode* headPtr = front;
    while(headPtr != nullptr) //run through  list from front to rear, adding to size each iteration
    {
        headPtr = headPtr->nextItem;
        size++;
    }
    return size; //return calculated size
}

/*****************************************************
 * Function: In List
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * Checks if item is in list
 * 
*/
bool PlayerInventory::inList(InventoryItem item)
{
    queueNode* headPtr = front;
    while(headPtr != nullptr) //while the headptr is not the nullptr
    {
        if(headPtr->item.weaponName == item.weaponName) //check if the item is in the list
        {
            return true;
        }
        headPtr = headPtr->nextItem; //incriment
    }
    return false;
}

/*****************************************************
 * Function: Get Inv Size
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * getter function to get inventory size
 * 
*/
int PlayerInventory::getInvSize()
{
    return inventorySize; //get function
}

/*****************************************************
 * Function: Get Random Item
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * Gets a random item
 * 
*/
InventoryItem PlayerInventory::getRandItem()
{
    queueNode* itemNode = front;
    if(isEmpty()) //if empty return an empty item
    {
        return {"empty", 0, 0};
    }
    else
    {
        for(int i = 0; i<(rand()%INV_SIZE); i++) //for a random num of times
        {
            itemNode = itemNode->nextItem; //go forward in list
        }
    }
    return itemNode->item; //display item
}
//Player Functions

/*****************************************************
 * Function: Generate Player ID
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 *  generates a random player ID
 * 
*/
int Player::generatePlayerId(void) const
{
    return (generateRandomStat(0, MAX_ID_VALUE)); //rand player id between 0 and 999
}

/*****************************************************
 * Function: Generate Random Stat
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * generates a random stat between two nums
 * 
*/
int Player::generateRandomStat(int min, int max) const
{
    return (rand()%(max-min+1)+min); //rand INT num between min and max
}




// void PlayerInventory::push(InventoryItem tempItem){
// 	PlayerInventoryNode* tempNode = new PlayerInventoryNode; //create node

// 	tempNode->item = tempItem; // add item to node
// 	tempNode->nextPtr = head; // make tempNode the new head
// 	head = tempNode;
// 	inventorySize++; // increase inventory size
// }


// void PlayerInventory::pop() {
//     if (isEmpty()) {
//         return;
//     }

//     PlayerInventoryNode* helperNode = head->nextPtr;
//     delete head;
//     head = helperNode;

//     if (head == nullptr) {
//         inventorySize = 0; // control inventory size monitoring
//     } else {
//         inventorySize--; // control inventory size monitoring
//     }
// }






// Knight Functions

/*****************************************************
 * Function: Initialize Player
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * Initializes Knight Player
 * 
*/
void Knight::initializePlayer(string newName)
{
    playerId = generatePlayerId();
    setName(newName);
    subclass = "Knight";
    name = newName;
    health = generateRandomStat(120,250);
    rangeSense = generateRandomStat(5,10)/10.0;
    swordSense = generateRandomStat(15,25)/10.0;
    accuracy = generateRandomStat(3,5)*swordSense;
    burn = 0;



    while (playerInventory.getInvSize() < INV_SIZE) //fill inv
    {
        playerInventory.enqueue(possibleItems[generateRandomStat(0,7)]);
    }
}
/*****************************************************
 * Function: Print Player Class Info
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * Prints Info for Knight Player
 * 
*/
void Knight::printPlayerClassInfo(void) const
{
    cout << "Range Mastery: " << this->rangeSense << endl
         << "Sword Mastery: " << this->swordSense << endl
         << "Accuracy: " << this->accuracy << endl;
}

/*****************************************************
 * Function: Display Inventory
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * Runs through the inventory by calling the recursive function
 * 
*/
void Knight::displayInventory()
{
    playerInventory.displayAllItems(playerInventory.getFront());
}

// Archer Functions

/*****************************************************
 * Function: Initialize Player
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * Initializes Archer Player
 * 
*/
void Archer::initializePlayer(string newName)
{
    playerId = generatePlayerId();
    setName(newName);
    subclass = "Archer";
    health = generateRandomStat(85,175);
    rangeSense = generateRandomStat(20,30)/10.0;
    swordSense = generateRandomStat(5,10)/10.0;
    accuracy = generateRandomStat(1,4)*rangeSense;
    burn = 0;
    while (playerInventory.getInvSize() < INV_SIZE) //fill inv
    {
        playerInventory.enqueue(possibleItems[generateRandomStat(0,7)]);
    }
}
/*****************************************************
 * Function: Print Player Class Info
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * Prints Info for Archer Player
 * 
*/
void Archer::printPlayerClassInfo(void) const
{
    cout << "Health: " << this->health << endl
         << "Range Mastery: " << this->rangeSense << endl
         << "Sword Mastery: " << this->swordSense << endl
         << "Accuracy: " << this->accuracy << endl;
}

/*****************************************************
 * Function: Display Inventory
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * Runs through the inventory by calling the recursive function
 * 
*/
void Archer::displayInventory()
{
    playerInventory.displayAllItems(playerInventory.getFront());
}
// Magic Swordsman Functions

/*****************************************************
 * Function: Initialize Player
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * Initializes Magic Swordsman Player
 * 
*/
void MagicSwordsman::initializePlayer(string newName)
{
    playerId = generatePlayerId();
    setName(newName);
    subclass = "Magic Swordsman";
    name = newName;
    health = generateRandomStat(120,150);
    rangeSense = generateRandomStat(10,15)/10.0;
    swordSense = generateRandomStat(12,17)/10.0;
    accuracy = 9;
    burn = 10;

    while (playerInventory.getInvSize() < INV_SIZE) //fill inv
    {
        playerInventory.enqueue(possibleItems[generateRandomStat(0,7)]);
    }
}
/*****************************************************
 * Function: Print Player Class Info
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * Prints Info for Magic Swordsman Player
 * 
*/
void MagicSwordsman::printPlayerClassInfo(void) const
{
    cout << "Health: " << this->health << endl
         << "Range Mastery: " << this->rangeSense << endl
         << "Sword Mastery: " << this->swordSense << endl
         << "Accuracy: " << this->accuracy << endl;
}

/*****************************************************
 * Function: Delete Item
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * Deletes 1 item from inventory, only used for assignment 
 * demonstration
*/
void MagicSwordsman::deleteItem()
{
    playerInventory.dequeue();
}

/*****************************************************
 * Function: Display Inventory
 * Date Created: 12/6/23
 * Date Last Modified: 12/6/23
 * Description:
 * Runs through the inventory by calling the recursive function
 * 
*/
void MagicSwordsman::displayInventory()
{
    playerInventory.displayAllItems(playerInventory.getFront());
}
