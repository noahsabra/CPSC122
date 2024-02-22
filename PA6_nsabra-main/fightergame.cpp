
#include "header.h"

int main()
{
    char classChoice;
    srand(time(NULL));
    PlayerInventory myInventory;
    MagicSwordsman p1;
    Knight p2;
    chooseClass(classChoice);
    //Initialize the Players
    p1.initializePlayer("Gerald");
    p2.initializePlayer("Noah");

    //Demonstration for assignment
    cout << "Filled the list ... " << endl;
	cout << "Demonstrating printing the list ... " << endl;
    p1.displayInventory();
    cout << "Demonstrating removing an item from the list ... " << endl;
    p1.deleteItem();
    p1.displayInventory();

    //Begin Game
    cout << endl << endl << endl << "Welcome to the battle arena!" << endl << "Today we will be seeing a battle between two worth opponents!" 
    << endl <<"Our first participant is:" << endl;
        p1.printPlayerInfo();
    cout << "And our second participant is: " << endl;
        p2.printPlayerInfo();
    //Play game loop
    Player::playAgain(p1,p2,1);
    return 0;
}