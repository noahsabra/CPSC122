
/*
	CPSC 122
	PA6 - Players Starter Code
	You should NOT be submitting a file named "pa6Starter.cpp"
	Please use this as a starting point.
	Cite all sources used.
*/


#ifndef HEADER_H 
#define HEADER_H

#include <iostream> //need for IO
#include <string> //need for string data type and member functions
#include <cstdlib> //need for random
#include <ctime> //need for random
#include <vector> //need for vector data type
#include <iomanip> //need to format output

using namespace std;


//Global constant to set upper limit on number of playerIds generated
const int MAX_ID_VALUE = 1000;
const int INV_SIZE = 10;

//This struct is used to populate possibleItems. This is it's 
//only purpose. You are not expected to use it as a member 
//variable in your classes
struct InventoryItem
{
	string weaponName;
	int damage;

	int type;	


};

//Global CONSTANT variable. You should modify and fill this
//vector with predefined possible weapons for your player
//objects.
const vector<InventoryItem> possibleItems{
	{"Great Sword", 20,1}, //heavy damage
	{"Cross Bow", 30,  2}, //heavy damage 
	{"Dagger", 2,0}, //smalldamage
	{"Metal Gauntlet", 15, 1}, //moderate damage,l
    {"Bow", 30, 2}, //heavy damage moderate 
	{"BIG Fish", 20, 0}, //fish :)
    {"Long Sword", 10, 1}, //moderate damage, 
    {"Long Bow", 40, 2} //Heavy Damage, 
    };

//Class for your inventory
//This should be implemented as one of the following:
//1. A doubly linked list
//2. A stack (linked list)
//3. A queue (linked list)
class PlayerInventory
{
private:	
    int inventorySize;
    struct queueNode
    {
        InventoryItem item;
        queueNode* nextItem;
    };
    queueNode* front;
    queueNode* rear;

public:
	queueNode* getFront() {
		return front;
	}
	PlayerInventory();
	~PlayerInventory();
    void enqueue(InventoryItem item);
    void dequeue();
    bool isEmpty();
    void displayAllItems(queueNode* current);
    void clear();
    int size();
    bool inList(InventoryItem item);
    int getInvSize();
	InventoryItem getRandItem();

};

//Abstract Base Class
class Player
{
private:

	//static member variable keeping track of the number of players generated
	static int numPlayers;
	//static list of playerIds generated.
	//used to make sure no players have the same id
	static vector<int> playerIds;

protected:
	string subclass;
	string name;
	int playerId;
	int health;
	int experience;

    string currentWeapon;
	int currentWeaponDamage;
    double rangeSense;
	double swordSense;
	int burn;
	int hit;

	double accuracy;

	//Inventory is the name of your doubly linked list, stack linked list, or queue linked list class
	PlayerInventory playerInventory;

	//mutator/setter for player id
	void setPlayerId(int id) { playerId = id; }

	//used to generate a random stat value between min and max, e.g., 50 and 150
	//used when initializing player stats
	int generateRandomStat(int min, int max) const;

	//checks if an id is already in the playerIds vector.
	static bool playerIdIsInList(int id);

	//generates a UNIQUE player id. player id can be between 1 and MAX_ID_VALUE
	//if number generated is in playerIds, generate again otherwise, add to 
	//playerIds vector (to keep track of id generated) and return value to be 
	//used in initialization
	int generatePlayerId(void) const;


public:
	//Default constructor
	Player() {
		subclass = "Player";
		name = "";
		playerId = -1;
		health = -1;
		experience = 0;
		swordSense = 1.0;
        rangeSense = 1.0;
        currentWeapon = "";
		currentWeaponDamage = 0;
		numPlayers++;
		burn = 0;
		hit = 0;
		accuracy = 0;


		//TODO: initialize PlayerInventory member (fill it with "weapons" from global constant vector)
	}

	//Destructor
	~Player()
	{
		numPlayers--;
		playerIds.clear();
	};

	//accessors/getters and mutators/setters
	void setName(string newName) { name = newName; }
	string getName(void) const { return name; };
    void setCurrentWeapon(string weapon) { currentWeapon = weapon; }
    string getCurrentWeapon(void) const { return currentWeapon; };
	void setCurrentWeaponDamage (int damage) { currentWeaponDamage = damage; }
	int getCurrentWeaponDamage(void) const { return currentWeaponDamage; };
	void setHealth(int h) { health = h; }
	int getHealth(void) const { return health; }
	void setBurn(int b) { burn = b; }
	int getBurn(void) const { return burn; }
	void setHit(int h) { hit = h; }
	int getHit(void) const { return hit; }
	int getPlayerId(void) const { return playerId; }
	void setExperience(int exp) { experience = exp; }
	int getExperience(void) const { return experience; }
	void setAccuracy(double a) { accuracy = a; }
	double getAccuracy(void) const { return accuracy; }



	//Pure Virtual Functions
	//initializes a player of given name with randomly allocated stats
	virtual void initializePlayer(string newName) = 0;
	virtual void printPlayerClassInfo(void) const = 0;

	//Virtual Functions
    virtual double getRangeSense(void) const { return rangeSense; } 
	virtual double getSwordSense(void) const { return swordSense; } 


	/*****************************************************
	 * Function: Print Player Info
	 * Date Created: 12/6/23
	 * Date Last Modified: 12/6/23
	 * Description:
	 * Prints the Players info, displays tombstone if dead
	 * 
	*/
	virtual void printPlayerInfo(void) final
	{
		string skull = "\n    _____\n   /     \\\n  | () () |\n   \\  ^  /\n    |||||\n";
		string tombstone = "\n       ,-=-.\n      /  +  \\\n      | ~~~ |\n      |R.I.P|\n      |_____| \n";

		string healthValue = this->health > 0 ? to_string(this->health) : tombstone; //"~RIP~"
		cout << ">>>>>>>>>>>>>>>>>>>>>>>>>|PID:" << this->playerId << "|" << endl;
		cout << ">>" << this->name << "'s info" << endl;
		cout << "Health: " << healthValue << endl;
		cout << "Experience: " << this->experience << endl;
		cout << "---------------------------------" << endl;
		cout << "Class: " << this->subclass << endl;
		printPlayerClassInfo();
		cout << "_________________________________" << endl;
		cout << endl;
	}

	/*****************************************************
	 * Function: Play Again
	 * Date Created: 12/6/23
	 * Date Last Modified: 12/6/23
	 * Description:
	 * Loops through game till player is dead
	 * 
	*/
	template <class T1, class T2>
	static void playAgain( T1& p1,  T2& p2, int turn) 
	{
		while (p1.getHealth() > 0 && p2.getHealth() > 0)
		{

			p1.playGame(p1,turn);
			p2.playGame(p2,turn);
			printBattleCard(p1,p2,turn);

			//if player hits subtract damage and set experience
			if (p2.getHit() == 1)
			{
				p1.setHealth(p1.getHealth()- p2.getCurrentWeaponDamage());
				p2.setExperience(p2.getExperience()+10);
			}
			if (p1.getHit() == 1)
			{
				p2.setHealth(p2.getHealth()- p1.getCurrentWeaponDamage());
				p1.setExperience(p1.getExperience()+10);

			}
			turn++;

		} 
		//check who is dead!
		if(p2.getHealth() <= 0 && p1.getHealth() <=0)
		{
			cout << "Draw... No one really wins this" << endl;
			
		} else if(p2.getHealth() <= 0)
		{
			cout << endl << p1.getName() << " Wins!" << endl;
		} else if (p1.getHealth() <= 0)
		{
			cout << endl << p2.getName() << " Wins!" << endl;
		}
		//reprint the player info
		p1.printPlayerInfo();
		p2.printPlayerInfo();
	}


	/*****************************************************
	 * Function: Print Battle Card
	 * Date Created: 12/6/23
	 * Date Last Modified: 12/6/23
	 * Description:
	 * Prints card demonstrating the turn
	 * 
	*/
	template <class T1, class T2>
	static void printBattleCard(const T1& p1, const T2& p2, int turn) 
	{
        cout << "|------- Turn " << turn << " -------|" << endl;
        cout << p1.getName() << "'s Health: " << p1.getHealth() << " - "
             << p2.getName() << "'s Health: " << p2.getHealth() << endl;

        cout << p1.getName() << " Attacks " << p2.getName() << " with a(n) " << p1.getCurrentWeapon();
		if(p1.getHit() == 1) //if the player is hit show weapon damage
		{
			cout << " Hits for... " << p1.getCurrentWeaponDamage() << endl;
		} else //else do not show damage
		{
			cout << " Missed..." << endl;
		}
		//same thing for other player
		cout << p2.getName() << " Attacks " << p1.getName() << " with a(n) " << p2.getCurrentWeapon();
		if(p2.getHit() == 1)
		{
			cout << " Hits for... " << p2.getCurrentWeaponDamage() << endl;
		} else
		{
			cout << " Missed..." << endl;
		}
		cout << endl;
		return; //graceful exit :)
	}

	/*****************************************************
	 * Function: Play Game
	 * Date Created: 12/6/23
	 * Date Last Modified: 12/6/23
	 * Description:
	 * sets weapon and damage for player
	 * 
	*/
	template <class T1>
	static void playGame( T1& p1, int turn) 
	{
		InventoryItem item = p1.playerInventory.getRandItem();
		p1.setCurrentWeapon(item.weaponName);

		if(p1.attackPlayerSuccess(p1)) //if the player succesfully hits
		{
			if(item.type == 1) //if the item type is a sword
			{
				p1.setCurrentWeaponDamage(item.damage * p1.getSwordSense() + p1.getBurn()); //multiple item damage by sword multiplier and add burn
			} else if(item.type == 2)
			{
				p1.setCurrentWeaponDamage(item.damage * p1.getRangeSense() + p1.getBurn()); //multiple item damage by range multiplier and add burn
			} else
				p1.setCurrentWeaponDamage(item.damage+p1.getBurn()); // this is just for the fish and dagger
			p1.setHit(1);
		} else
		{ //if player doesnt hit, weapon does no damage and hit is 0
			p1.setCurrentWeaponDamage(0);
			p1.setHit(0);
		}

		

	}

	/*****************************************************
	 * Function: Attack Player Success
	 * Date Created: 12/6/23
	 * Date Last Modified: 12/6/23
	 * Description:
	 * Sees if the attack hits, checks accuracy vs random hit chance
	 * 
	*/
	template <class T1>
	bool attackPlayerSuccess(T1& p1)
	{
		int chanceHit = generateRandomStat(0,10);
    	if(p1.getAccuracy() >= chanceHit)
    	{
        	return true;
    	}
    	return false;
	}
};

class Knight : public Player
{
protected:
public:
    void initializePlayer(string newName);
	void printPlayerClassInfo(void) const;
	void deleteItem();
	void displayInventory();
	~Knight(){};
};

class MagicSwordsman : public Knight
{
protected:
public:
	void initializePlayer(string newName);
	void printPlayerClassInfo(void) const;
	void deleteItem();
	void displayInventory();
	~MagicSwordsman(){};
};

class Archer : public Player
{
protected:
public:
    void initializePlayer(string newName);
	void printPlayerClassInfo(void) const;
	void deleteItem();
	void displayInventory();
	~Archer(){};
};




//normal function :O
void chooseClass(char& chosenClass);


#endif