/*
 Name: Noah Sabra
 Class: CPSC 122, Fall 2023
 Description: Taking data from a csv file and sorting it, 
 displaying calculated info in terminal and outputing new
 file
 Notes: No Notes
*/


#include "header.h"

int main(void)
{
   
    ofstream outfile;
    string inputFileName = "petstoredata.csv";
    string outputFileName = "petreport.txt";
    vector<string> header; //vectors to store header row data
    bool firstRow = true;
    PetStoreList storeList; //The linked list object
    ifstream infile;
    if(openInputFile(infile, inputFileName))
    {
        outfile.open(outputFileName);
        getData(infile, storeList, header);
        storeList.calculatePetSummary();
        
        storeList.displayPetSummary();
        storeList.displayPetList();

        storeList.writePetSummary(outfile);
        storeList.writePetList(outfile);
    }
    return 0;
}