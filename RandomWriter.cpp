/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: Izzet Igal Benardete
 * Section: Raid Watson
 * This file is the starter project for the Random Writer problem.
 * This program takes two inputs from the user. First one is the file name from which the program reads the text.
 * The second input is the length of the seed or the order of the Markov Model [1-10]
 * With all the given inputs the program analyzes the text according to the order and creates random text
 * up to 2000 characters.
 */

#include <iostream>
#include "console.h"
#include <fstream>
#include "vector.h"
#include "map.h"
#include <stdlib.h>
#include <string>

using namespace std;

const int NUMBER_OF_CHARACTERS = 2000;

Map<string, Vector<string> > analyzeCharacters(ifstream &input, int seedLength); //Reads the characters from the file and creates a map
void createRandomText (Map<string, Vector<string> > *textAnalysis, string seed, int numberOfChar); //From the analyzed text creates a random text
string mostRepeatedSequence (Map<string, Vector<string> > *textAnalysis); //Finds the most repeated character group from the map.(among the keys of the map)

int main()
{
    // Initialization of the random seed
    srand (time(NULL));

    ifstream inputFile;
    string fileName;
    
    int seedLength; // The order of the Markov Model
    Map<string, Vector<string> > textAnalysis;
    
    
    //Inputs the name of the file from the user
    //Until a valid filename is written
    do
    {
        cout << "Please enter the name of the file: ";
        getline(cin, fileName);
        
        inputFile.open(fileName.c_str() );
        
    }while (!inputFile);
    
    //Inputs the order of the Markov Model from the user
    //Until a valid integer is written which is between 0 and 10 (inclusive)
    do
    {
        cout << "Please enter a number between 1 and 10 for the Order of Markov Model:";
        cin >> seedLength;
    } while (seedLength < 0 || seedLength > 10);
    

    textAnalysis = analyzeCharacters(inputFile, seedLength);
    
    cout << "Creating the random text...\n" << endl;
    createRandomText(&textAnalysis, mostRepeatedSequence(&textAnalysis), NUMBER_OF_CHARACTERS);
    
    return 0;
}

Map<string, Vector<string> > analyzeCharacters(ifstream &input, int seedLength)
{
    cout << "Processing..." << endl;
    Map<string, Vector<string> > textAnalysis;
    
    bool firstTime = true;
    string nChar;
    string key;
    string value;
    char currentChar = '\0';
    
    //Reads the file until the end
    while(!input.eof())
    {
        if(firstTime)
        {
            //At the beginning the input reads seedLength + 1 characters to create the first <Key>(first seedLength chars) <Value>(the last char) 
            for(int i = 0 ; i <= seedLength ; i++)
            {
                input.get(currentChar);
                nChar += currentChar;
            }            
            
            firstTime = false;
        }
        else
        {
            nChar.erase(0, 1);
            input.get(currentChar);
            nChar += currentChar;
        }
        
        //Seperates the <Key> and <Value> string since it reads them all at once.
        key = nChar.substr(0, seedLength);
        value = nChar.substr(seedLength, 1);
        
        //Checks the map and either puts the value in or creates a new key-value pair 
        if(textAnalysis.containsKey(key))
        {
            textAnalysis[key].add(value);
        }
        else
        {
            Vector<string> fallowingChars;
            fallowingChars.add(value);
            textAnalysis[key] = fallowingChars;
        }
    }
    
    cout << "The Text is analyzed !" << endl;
    
    return textAnalysis;
}

void createRandomText (Map<string, Vector<string> > *textAnalysis, string seed, int numberOfChar)
{    
    //Starts the text with the initial seed which is also the most repeated character group.
    if(numberOfChar == NUMBER_OF_CHARACTERS)
    {
        cout << seed;
    }
    
    if(numberOfChar == 0)
    {
        cout << "\n\n****** THE END ******" << endl;
        return;
    }
    else
    {
        //Chooses a random char according to the curent seed.
        //Prints the choosen char and creates the new seed.
        int randomNumber = rand() % (textAnalysis->get(seed).size());
        
        string nextChar = textAnalysis->get(seed).get(randomNumber);
        cout << nextChar;
        
        seed.erase(0,1);
        string nextSeed = seed + nextChar;
        
        if(textAnalysis->containsKey(nextSeed))
        {
            createRandomText(textAnalysis, nextSeed, numberOfChar-1);
        }
    }
}

string mostRepeatedSequence (Map<string, Vector<string> > *textAnalysis)
{
    Vector<string> firstVector;
    
    string theMost;
    
    //Loops through the map and selects the key that has the most number of elements in its value vector.
    foreach (string key in *textAnalysis)
    {
        firstVector = textAnalysis->get(key);
        
        if(firstVector.size() > textAnalysis->get(theMost).size())
        {
            theMost = key;
        }
    }
    
    return theMost;
}
















