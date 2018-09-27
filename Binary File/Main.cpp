#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <filesystem>
#include <cstdio>
#include <sstream>
#include "InitFunctions.h"
#include "SavedData.h"
#include "Monsters.h"
using namespace std;

int main()
{
	while (true)
	{
		mainMenu();
		int input = checkValid(0);

		if (input == 1)
		{
			addMonster();
		}
		else if (input == 2)
		{
			removeMonster();
		}
		else if (input == 3)
		{
			viewByID();
		}
		else if (input == 4)
		{
			browseMonster();
		}
		else if (input == 5)
		{
			cout << "We thank you for using the Monster Bestiary. Come again!" << endl;
			cin.get();
			return 0;
		}
	}
}

void mainMenu()
{
	cout << "Welcome to the Monster Bestiary." << endl;
	cout << "What would you like to do?" << endl;
	cout << "1: Add a monster by ID." << endl;
	cout << "2: Remove monster by ID." << endl;
	cout << "3: View a monster by ID." << endl;
	cout << "4: Browse Monsters." << endl;
	cout << "5: Exit." << endl;
}

void addMonster()
{
	Monster newMonster;
	cout << "What's the monster's name?" << endl;
	cin >> newMonster.name;
	cout << "What's the monster's weapon class? (Swords, Staff, Shield, etc.)" << endl;
	cin >> newMonster.weaponClass;
	cout << "What's the monster's HP?" << endl;
	cin >> newMonster.HP;
	cout << "How would you describe this monster?" << endl;
	cin >> newMonster.description;
	cout << "What ID would you like to give this monster?" << endl;
	cin >> newMonster.ID;

	fstream file;
	file.open("Monsters/" + newMonster.ID + ".bin", ios::out | ios::binary);

	if (!file.is_open()) 
	{
		cout << "Failed." << endl;
	}

	file << newMonster.ID << endl;
	file << newMonster.name << endl;
	file << newMonster.weaponClass << endl;
	file << newMonster.HP << endl;
	file << newMonster.description;

	file.flush();
	file.close();

	fstream browsingFile;
	browsingFile.open("Monsters/BrowsingFile.bin", ios::app | ios::binary);
	if (!browsingFile.is_open())
	{
		cout << "Failed" << endl;
	}
	
	file.seekp(0, ios_base::end);
	browsingFile << "Monster with ID " << newMonster.ID << " named " << newMonster.name << " has been added." << endl;
	browsingFile.flush();
	browsingFile.close();
	

	int main();
}

void removeMonster()
{
	string getID;
	cout << "Please enter the ID of the monster." << endl;
	cin >> getID;
	if (remove(("Monsters/" + getID + ".bin").c_str()) != 0)
	{
		cout << "Failed" << endl;
	}
	else
	{
		fstream file;
		file.open("Monsters/BrowsingFile.bin", ios_base::app | ios::binary);
		file << "Monster with " << getID << " ID has been deleted." << endl;
		cout << "Monster successfully removed" << endl;
		file.flush();
		file.close();
	}
}

void browseMonster()
{
	fstream file;
	file.open("Monsters/BrowsingFile.bin", ios_base::in | ios::binary);
	if (!file.is_open()) {
		cout << "Failed." << endl;
	}
	string buffer;
	string result;
	while (getline(file, buffer))
	{
		cout << buffer << endl;
	}
	file.clear();
	file.close();

}

void viewByID()
{
	string getID;
	cout << "Please enter the ID of the monster." << endl;
	cin >> getID;
	fstream file;
	file.open("Monsters/" + getID + ".bin", ios_base::in | ios::binary);
	if (!file.is_open()) {
		cout << "Failed." << endl;
		system("exit");
	}
	string buffer;
	getline(file, buffer);
	cout << "ID: " << buffer << endl;
	getline(file, buffer);
	cout << "Name: " << buffer << endl;
	getline(file, buffer);
	cout << "Weopon Class: " << buffer << endl;
	getline(file, buffer);
	cout << "HP: " << buffer << endl;
	getline(file, buffer);
	cout << "Description: " << buffer << endl;
	file.flush();
	file.close();
	cin.get();
}

int checkValid(int input)
{
	bool validNum = false;
	while (!validNum)
	{
		bool validIn = false;
		while (!validIn)
		{
			std::cin >> input;
			if (!(validIn = std::cin.good()))
			{
				cout << "I'm sorry, that wasn't a valid response. Please try again" << endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
		if (input == 1 || 
			input == 2 ||
			input == 3 ||
			input == 4 ||
			input == 5)
		{
			validNum = true;
			return input;
		}
	}
}


/*int helloWorld()
{
	fstream file;
	file.open("HelloWorld.bin", ios::out | ios::binary);
	if (!file.is_open())
	{
		cout << "Failed." << endl;
		return -1;
	}
	file << "Hello World!" << endl;
	file.flush();
	file.close();
}

int save()
{
	saveData initialSave;
	initialSave.playerName = "Josh";
	initialSave.deathCount = 19;
	initialSave.deepestFloor = 8;
	initialSave.hasBeenBeatenGame = false;
	initialSave.timePlayed = 801120;

	fstream file;
	file.open("firstSave.bin", ios::out | ios::binary);
	if (!file.is_open()) {
		cout << "Failed" << endl;
		return -1;
	}
	file << initialSave.playerName << endl;
	file << initialSave.deathCount << endl;
	file << initialSave.deepestFloor << endl;
	file << initialSave.hasBeenBeatenGame << endl;
	file << initialSave.timePlayed << endl;

	file.flush();
	file.close();

	file.open("initialSave.bin", ios::in | ios::binary);
	string buffer;
	while (getline(file, buffer))
	{
		cout << buffer << endl;
	}
	system("pause");
}*/