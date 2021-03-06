// Heroes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Hero.h"
#include "Warrior.h"
#include "Thief.h"
#include "Necromancer.h"
using namespace std;


int main()
{
	int warriors = 0;
	int	thieves = 0;
	int	necromancers = 0;
	string name;
	cin >> warriors;
	cin >> thieves;
	cin >> necromancers;
	int numofplayers = warriors + thieves + necromancers;
	Hero *Heroes[9];
	for ( int i = 0; i < warriors; i++)
	{
		cout << "Please insert warrior number " << i+1 << " name:";
		cin >> name;
		Heroes[i] = new Warrior(name);
	}
	for (int i = warriors; i < thieves + warriors; i++)
	{
		cout << "Please insert thief number " << i + 1 - warriors << " name:";
		cin >> name;
		Heroes[i] = new Thief(name);
	}
	for (int i = warriors + thieves; i < thieves + warriors + necromancers; i++)
	{
		cout << "Please insert necromancer number " << i + 1 - warriors - thieves << " name:";
		cin >> name;
		Heroes[i] = new Necromancer(name);
	}
	bool play = true;
	bool Incometaken = false;
	bool found = false;
	int player = 0;
	int rounds = 1;
	int numofdeaths = 0;
	int move;
	int desicion;
	Hero *temp = Heroes[0];
	while (play)
	{
		if (temp->GetStatus())
		{
			cout << "Welcome " << temp->GetName() << "\n";
			cout << "What is your next step in the path to victory?\n";
			cout << "1. Attack\n";
			cout << "2. Get daily gold\n";
			cout << "3. Buy creatures\n";
			cout << "4. Show details\n";
			cout << "5. Special skill\n";
			cout << "6. End of my turn\n";
			cout << "7. Exit\n";
			cin >> move;
			switch (move)
			{
			case 1:
				cout << "1. Show me my opponents\n";
				cout << "2. Attack hero\n";
				cin >> desicion;
				switch (desicion)
				{
				case 1:
				{
					for (int i = 0; i < numofplayers; i++)
					{
						Hero *Target = Heroes[i];
						if (!(Target->GetName() == temp->GetName()))
						{
							cout << Target->GetName() << " " << Target->GetClass() << "\n";
						}
					}
					break;
				}
				case 2:
				{
					if (rounds > 3)
					{
						found = true;
						string opponent;
						cout << "Please insert your opponent name:\n";
						cin >> opponent;
						int i = 0;
						Hero *Target = Heroes[0];
						while (!(Target->GetName() == opponent))
						{
							if (i > numofplayers - 1)
							{
								found = false;
								cout << "Player doesn't exist\n";
								break;
							}
							Target = Heroes[i];
							i++;
						}
						if (found)
						{
							temp->Attack(Target);
						}
						numofdeaths++;
						if (numofdeaths == numofplayers - 1)
						{
							play = false;
							if (temp->GetArmySize() == 0)
								cout << temp->GetName() << " is the winner!";
							else
								cout << Target->GetName() << " is the winner!";
						}
					}
					else
					{
						cout << "You may only attack after 3 rounds!\n";
						break;
					}
				}
				}
				break;
			case 2:
				if (!Incometaken)
				{
					temp->GainGold(100);
					Incometaken = true;
				}
				break;
			case 3:
				temp->Enlist();
				break;
			case 4:
				cout << temp->GetName() << " " << temp->GetClass() << "\n";
				cout << temp->GetGold() << " gold \n";
				temp->GetArmy();
				break;
			case 5:
				if (temp->GetClass() == "Thief")
				{
					found = true;
					string victim;
					cout << "Please insert hero name:\n";
					cin >> victim;
					int i = 0;
					Hero *Target = Heroes[0];
					while (!(Target->GetName() == (victim)))
					{
						if (i > numofplayers - 1)
						{
							found = false;
							break;
						}
						Target = Heroes[i];
						i++;
					}
					if (found)
						temp->TAbility(Target);
				}
				else
					temp->Ability();
				break;
			case 6:
				if (player == numofplayers - 1)
				{
					rounds++;
					player = 0;
				}
				else
					player++;
				Incometaken = false;
				temp = Heroes[player];
				temp->newTurn();
				break;
			case 7:
				play = false;
				break;
			default:
				break;
			}
		}
	}
	for (int i = 0; i < numofplayers; i++)
	{
		delete(Heroes[i]);
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
