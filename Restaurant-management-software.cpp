/**
* 
* Solution to course project #1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
* 
* @author Daniela Kuzmanova
* @idnumber 7MI0600539
* @compiler VS
* 
* <file with helper funcions> 
* 
*/

#include <iostream>
#include <fstream>

void showRoleMenu()
{
	std::cout << "Select user:" << '\n';
	std::cout << "1) Waiter" << '\n';
	std::cout << "2) Manager" << '\n';
	std::cout << "3) Exit" << '\n';
	std::cout << "Enter role number:"<<'\n';
}

int main()
{
	unsigned choice;
	unsigned waiterChoice;
	unsigned managerChoice;
	
	do {
		showRoleMenu();
		std::cin >> choice;
		switch (choice)
		{

		case 1:
			std::cout << "Waiter"<<'\n';
			std::cout << "WaiterChoice"<<'\n';
			do
			{
				std::cin >> waiterChoice;
				switch (waiterChoice)
				{
				case 1:
					//showMenu();
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 0:
					break;
				default:
					std::cout << "Invalid choice!Please, try again!"<<'\n';
					break;
				}
			} while (waiterChoice != 0);
			break;
		case 2:std::cout << "Manager";
			std::cout << "ManagerChoice";
			
			do
			{
				std::cin >> managerChoice;
				switch (managerChoice)
				{
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 8:
					break;
				case 9:
					break;
				case 10:
					break;
				case 11:
					break;
				case 12:
					break;
				case 13:
					break;
				case 14:
					break;
				case 0:
					break;
				default:
					std::cout << "Invalid choice!Please, try again!"<<'\n';
					break;
				}
			} while (managerChoice != 0);
			break;
		case 3: 
			break;
		default: 
			std::cout<<"Invalis choice!Please, try again!"<<'\n';
			break;
		}
	}
	while (choice != 3);




	return 0;
}



