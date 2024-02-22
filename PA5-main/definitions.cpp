/*
 Name: Noah Sabra
 Class: CPSC 122, Fall 2023
 Description: Taking data from a csv file and sorting it, 
 displaying calculated info in terminal and outputing new
 file
 Notes: No Notes
*/

#include "header.h"



/*****************************************************
 * Function: Open Input File
 * Date Created: 9/13/2023
 * Date Last Modified: 11/14/2023   
 * Description:
 * Open file and return boolean value if open or not
 * 
*/
bool openInputFile(ifstream &infile, string filename)
{
	infile.open(filename);
	return infile.is_open();
}

/*****************************************************
 * Function: Get Data
 * Date Created: 11/15/2023
 * Date Last Modified: 11/15/2023   
 * Description:
 * Gets data from a csv file
 * 
*/
void getData(ifstream &infile, PetStoreList& storeList, vector<string> headers)
{
    string line;
    string headerToken;
    getline(infile, line); // Read the header line
    stringstream headerStream(line); // Store the header line in a stringstream
    while (getline(headerStream, headerToken, ',')) // Tokenize the header line by comma
    {
        headers.push_back(headerToken); // Store each header token in the headers vector
    }
    cout << "Processed " << headers.size() << " header columns" << endl;
    for(int i = 0; i < headers.size(); i ++)
    {
        cout << headers[i];
        if(i < headers.size()-1)
        {
            cout << ", ";
        }
    }
    cout << endl << endl;
    while(getline(infile, line))
    {
        stringstream lineToParse(line); // Store the line in a stringstream
        string store, name, type;
        int numD;
        getline(lineToParse, store, ',');
        getline(lineToParse, name, ',');
        getline(lineToParse, type, ',');
        lineToParse >> numD;

        cout << "Processed a " << type << ", \"" << name <<"\" ... " << numD 
             << " day(s) on site at store " << store << endl;
        storeList.addPetData(store,name,type,numD);
    }
    cout << "All pet store data processed!" << endl << endl;
}







PetStoreList::PetStoreList()
{
    headPtr = nullptr;
}


PetStoreList::~PetStoreList()
{
    PetStoreData* trailingPtr = headPtr;
    PetStoreData* leadingPtr = nullptr;

    while(trailingPtr != nullptr)//Go through and delete everything
    {
        leadingPtr = trailingPtr->nextStore;
        delete trailingPtr;
        trailingPtr = leadingPtr;
    }
}

/*****************************************************
 * Function: Create Node
 * Date Created: 11/14/2023
 * Date Last Modified: 11/14/2023   
 * Description:
 * Creates a new PetStore Node for Pet Store List
*/
PetStoreList::PetStoreData* PetStoreList::createNode(string storeName)
{
    PetStoreData* newNode = new PetStoreData; // allocate memory
    newNode->petStoreName = storeName;
    newNode->nextStore = nullptr; // make next value nullptr
    return newNode;
}


/*****************************************************
 * Function: Insert at end
 * Date Created: 11/14/2023
 * Date Last Modified: 11/14/2023   
 * Description:
 * Inserts a node at the end of the list
*/
void PetStoreList::insertAtEnd(PetStoreData* newStoredata)
{
    PetStoreData* helpNodePtr = headPtr;
    if(headPtr == nullptr) //if list is empty
    {
        headPtr = newStoredata;
    } 
    else
    {
        while(helpNodePtr->nextStore != nullptr) // while the next pointer is not the nullptr
        {
            helpNodePtr = helpNodePtr->nextStore;
        }
        helpNodePtr->nextStore = newStoredata; //set the value of the final pointer to newStoreData
    }

}

/*****************************************************
 * Function: Add Pet Data
 * Date Created: 11/14/2023
 * Date Last Modified: 11/15/2023   
 * Description:
 * Adds Pet Data
*/
void PetStoreList::addPetData(string storeName, string pName, string pType, int numDays)
{
     PetStoreData* helpNodePtr = headPtr;

    if (helpNodePtr == nullptr) {
        // If the list is empty, create a new store and add pet data
        PetStoreData* newStore = createNode(storeName);
        insertAtEnd(newStore);
        PetData newPetData;
        newPetData.petName = pName;
        newPetData.petType = pType;
        newPetData.numDaysAtStore = numDays;
        newStore->petData.push_back(newPetData);
        return;
    }

    while (helpNodePtr != nullptr)
    {
        if (helpNodePtr->petStoreName == storeName)
        {
            // Once store is found, add data to perData vector
            PetData newPetData;
            newPetData.numDaysAtStore = numDays;
            newPetData.petName = pName;
            newPetData.petType = pType;
            helpNodePtr->petData.push_back(newPetData);
            return;
        }
        helpNodePtr = helpNodePtr->nextStore;
    }

    // If the store was not found, and the list was not empty, create a new store and add to list
    PetStoreData* newStore = createNode(storeName);
    insertAtEnd(newStore); 

    PetData newPetData;
    newPetData.petName = pName;
    newPetData.petType = pType;
    newPetData.numDaysAtStore = numDays;

    newStore->petData.push_back(newPetData); // Add pet data to the new store's petData vector
    
}
/*****************************************************
 * Function: Dsiplay Pet List
 * Date Created: 11/14/2023
 * Date Last Modified: 11/14/2023   
 * Description:
 * Displays the list of pets to the terminal
*/
void PetStoreList::displayPetList() const
{
    PetStoreData* helpNodePtr = headPtr;

    while(helpNodePtr != nullptr)
    {
        if(helpNodePtr->petStoreName == "")
        {
            return;
        }
        cout << "__________________________________" << endl;
        cout << "Pet Store Name: " << helpNodePtr->petStoreName << endl;
        cout << "**********************************" << endl;
        cout << "| Pet Information " << endl;
        for(int i = 0; i<helpNodePtr->petData.size(); i++)
        {
            cout << "> Pet " << i+1 << " Name: " << helpNodePtr->petData[i].petName 
                 << endl << "> Pet Type: " << helpNodePtr->petData[i].petType
                 << endl << "> Number of days at store: " << helpNodePtr->petData[i].numDaysAtStore 
                 << endl << "----------------------------" << endl;
        }
        helpNodePtr = helpNodePtr->nextStore;
    }


}
/*****************************************************
 * Function: Write Pet List
 * Date Created: 11/14/2023
 * Date Last Modified: 11/14/2023   
 * Description:
 * Writes the list of pets to the outfile
*/
void PetStoreList::writePetList(ofstream& outfile)
{
    PetStoreData* helpNodePtr = headPtr;


    while(helpNodePtr != nullptr)
    {
         if(helpNodePtr->petStoreName == "")
        {
            return;
        }
        outfile << "__________________________________" << endl;
        outfile << "Pet Store Name: " << helpNodePtr->petStoreName << endl;
        outfile << "**********************************" << endl;
        outfile << "| Pet Information " << endl;
        for(int i = 0; i<helpNodePtr->petData.size(); i++)
        {
            outfile << "> Pet " << i+1 << " Name: " << helpNodePtr->petData[i].petName 
                 << endl << "> Pet Type: " << helpNodePtr->petData[i].petType
                 << endl << "> Number of days at store: " << helpNodePtr->petData[i].numDaysAtStore 
                 << endl << "----------------------------" << endl;
        }
        helpNodePtr = helpNodePtr->nextStore;
    }

}
/*****************************************************
 * Function: Store In List
 * Date Created: 11/14/2023
 * Date Last Modified: 11/14/2023   
 * Description:
 * Checks if the store is found in the list
*/
bool PetStoreList::storeInList(string name)
{
    PetStoreData* helpStorePtr = headPtr;
    //head pointer is null?
    while(helpStorePtr != nullptr)
    {
        if(helpStorePtr->petStoreName == name)
        {
            return true;//If store is in list return true
        }
    }
    return false;

}
/*****************************************************
 * Function: Calculate Pet Summary
 * Date Created: 11/17/2023
 * Date Last Modified: 11/17/2023   
 * Description:
 * Calculates the pet store summary data
*/
void PetStoreList::calculatePetSummary()
{
    PetStoreData* helpStorePtr = headPtr;
    summaryData.minDaysAtStore = helpStorePtr->petData[0].numDaysAtStore;
    summaryData.maxDaysAtStore = helpStorePtr->petData[0].numDaysAtStore;
    summaryData.numPets = 0;
    int helpNum = 0;
    while(helpStorePtr->nextStore != nullptr)
    {
        for(int i = 0; i<helpStorePtr->petData.size(); i++)
        {
            //Find min and MAX
            if(helpStorePtr->petData[i].numDaysAtStore < summaryData.minDaysAtStore) //min
            {
                summaryData.minDaysAtStore = helpStorePtr->petData[i].numDaysAtStore;
            }
            if(helpStorePtr->petData[i].numDaysAtStore > summaryData.maxDaysAtStore) // max
            {
                summaryData.maxDaysAtStore = helpStorePtr->petData[i].numDaysAtStore;
            }
            helpNum = helpNum + helpStorePtr->petData[i].numDaysAtStore; //Add to the helper number so average can later be calculated
            summaryData.numPets = summaryData.numPets + 1;
        }
        helpStorePtr = helpStorePtr->nextStore;//incriment the node to the next store!!!
    }
    if(summaryData.numPets >= 1)
    {
        summaryData.averageDaysAtStore = helpNum/summaryData.numPets; // calculate the average days at store
    }
}
/*****************************************************
 * Function: Display Pet Summary
 * Date Created: 11/17/2023
 * Date Last Modified: 11/17/2023   
 * Description:
 * Displays a summary of pet information to the terminal
*/
void PetStoreList::displayPetSummary() const
{
    cout << "Pet Store CSV Summary Report" << endl << "__________________________________"
            << endl << "Total number of pets: " << summaryData.numPets
            << endl << "Average number of days at pet store: " << summaryData.averageDaysAtStore
            << endl << "Shortest stay at pet store: " << summaryData.minDaysAtStore
            << endl << "Longest stay at pet store: " << summaryData.maxDaysAtStore << endl;
}
/*****************************************************
 * Function: Write Pet Summary
 * Date Created: 11/17/2023
 * Date Last Modified: 11/17/2023   
 * Description:
 * Writes a summary of pet information to the output file
*/
void PetStoreList::writePetSummary(ofstream& outfile)
{
    outfile << "Pet Store CSV Summary Report" << endl << "__________________________________"
            << endl << "Total number of pets: " << summaryData.numPets
            << endl << "Average number of days at pet store: " << summaryData.averageDaysAtStore
            << endl << "Shortest stay at pet store: " << summaryData.minDaysAtStore
            << endl << "Longest stay at pet store: " << summaryData.maxDaysAtStore << endl;
}