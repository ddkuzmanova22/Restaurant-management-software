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

const char MENUFILE[] = "menu.txt";
const int MAX_MENU_ITEM = 100;
struct MenuItem {
	char name[50];
	double price;
};

struct Order {
	char itemName[50];
	int quantity;
	double totalPrice; 
};

void showRoleMenu()
{
	std::cout << "--- Select user ---" << '\n';
	std::cout << "1. Waiter" << '\n';
	std::cout << "2. Manager" << '\n';
	std::cout << "3. Exit" << '\n';
	std::cout << "-------------------\n";
	std::cout << "Enter role number:"<<'\n';
}

void showWaiterOptions() {
	std::cout << "--- All Available Options ---\n";
	std::cout << "1. Show the menu\n";
	std::cout << "2. Add an order\n";
	std::cout << "3. Cancel an order\n";
	std::cout << "4. View past orders\n";
	std::cout << "5. Sort and count orders\n";
	std::cout << "6. Calculate turnover\n";
	std::cout << "7. Show all available options\n";
	std::cout << "0. Return to role selection\n";
	std::cout << "-----------------------------\n";
}

bool loadMenuFromFile(const char menuFile[], MenuItem menu[], int& itemCount)
{
	
	if (!menuFile)
	{
		return false;
	}
	std::ifstream file(menuFile);
	if (!file.is_open())
	{
		return false;
	}

	while (file >> menu[itemCount].name >> menu[itemCount].price)
	{
		itemCount++;
		if (itemCount >= MAX_MENU_ITEM) break;
		
	}
	file.close();
	return true;
}

void printMenu(const char menuFile[], MenuItem menu[], int& itemCount)
{
	bool isLoaded = loadMenuFromFile(menuFile, menu, itemCount);
	if (!isLoaded)
	{
		std::cerr << "Error!";
	}
	for (int i = 0; i < itemCount; i++)
	{
		std::cout << i+1 << " " << menu[i].name << '-' << menu[i].price << '\n';
	}
    
}

int main()
{
	
	unsigned choice;
	unsigned waiterChoice;
	unsigned managerChoice;
	MenuItem menu[MAX_MENU_ITEM];
	int itemCount = 0;

	do {
		showRoleMenu();
		std::cin >> choice;
		switch (choice)
		{

		case 1:
			do
			{
				showWaiterOptions();
				std::cout << "Enter waiter choice:";
				std::cin >> waiterChoice;
				switch (waiterChoice)
				{
				case 1:
					printMenu("menu.txt", menu, itemCount);
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
		case 2:
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



