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
const char ORDERFILE[] = "order.txt";
const int MAX_MENU_ITEM = 100;
const int ITEM_NAME_LENGTH = 50;
const int MAX_ORDERS = 50;

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
	std::cout << "0. Exit" << '\n';
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

void showManagerOptions() {
	std::cout << "--- Manager Options ---\n";
	std::cout << "1. View the menu\n";
	std::cout << "2. Place an order (item from the menu)\n";
	std::cout << "3. Cancel an order\n";
	std::cout << "4. View past orders sorted alphabetically with counts\n";
	std::cout << "5. View past orders\n";
	std::cout << "6. Check inventory levels\n";
	std::cout << "7. Remove an item from inventory\n";
	std::cout << "8. Add an item to inventory\n";
	std::cout << "9. View daily turnover\n";
	std::cout << "10. Reset daily turnover (end-of-day report)\n";
	std::cout << "11. View all turnovers from a given date to the present\n";
	std::cout << "12. Add a new product to the menu\n";
	std::cout << "13. Remove a product from the menu\n";
	std::cout << "14. Show all available options\n";
	std::cout << "0. Return to role selection\n";
	std::cout << "-----------------------\n";
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
		return;
	}
	for (int i = 0; i < itemCount; i++)
	{
		std::cout << i+1 << " " << menu[i].name << '-' << menu[i].price << '\n';
	}
    
}

int myStrcmp(const char* firstString, const char* secondString)
{
	if (!firstString || !secondString)
		return 0; 

	while ((*firstString) && ((*firstString) == (*secondString)))
	{
		firstString++;
		secondString++;
	}

	return (*firstString - *secondString);

}

void writeOrderToFile(const char orderFile[], const char itemName[], int quantity, double totalPrice)
{

	std::ofstream file(orderFile, std::ios::app);
	if (!file.is_open())
	{
		return;
	}
	file << itemName << " " << quantity<< " " << totalPrice << '\n';
	file.close();
}

void addOrder(const char menuFile[], const char orderFile[])
{
	MenuItem menu[MAX_MENU_ITEM];
	int itemCount = 0;
	unsigned quantity;
	char itemName[ITEM_NAME_LENGTH];
	double totalPrice = 0;
	bool isLoaded = loadMenuFromFile(menuFile, menu, itemCount);

	if (!isLoaded)
	{
		std::cerr << "Error!";
		return;
	}

	std::cout << "Enter item name:" << '\n';
	std::cin >> itemName;
	bool isFound = false;

	for (int i = 0; i < itemCount; i++)
	{
		if (myStrcmp(itemName, menu[i].name)==0)
		{
			isFound = true;
			std::cout << "Enter quantity:" << '\n';
			std::cin >> quantity;
			totalPrice = quantity * menu[i].price;	
			writeOrderToFile(orderFile, itemName, quantity, totalPrice);
			std::cout << "The order is added" << '\n';
			break;
		}
	}

	if (!isFound)
	{
		std::cout << "The order is canceled" << '\n';
	}
}

bool loadOrderFromFile(const char* orderFile, Order order[], int& orderCount)
{
	orderCount = 0;
	std::ifstream file(orderFile);

	if (!file)
	{
		std::cerr << "Error!" << orderFile << '\n';
		return false;
	}

	while (file >> order[orderCount].itemName >> order[orderCount].quantity
		>> order[orderCount].totalPrice) {
		orderCount++;
		if (orderCount >= MAX_ORDERS) break; // Ограничение за броя поръчки
	}

	file.close();
	return true;
}

void printOrder(const char orderFile[], Order order[], int& orderCount)
{
	bool isLoaded = loadOrderFromFile(orderFile, order, orderCount);

	if (!isLoaded)
	{
		std::cerr << "Error!";
		return;
	}

	std::cout << "Available orders:" << '\n';

	for (int i = 0; i < orderCount; i++)
	{
		std::cout << i + 1 << " " << order[i].itemName << '-' << order[i].quantity << '*' << order[i].totalPrice << '\n';
	}

}

void cancelorder(const char orderFile[], Order order[], int& orderCount)
{
	unsigned cancelindex;
	unsigned returntooptions;
	bool isvalid = loadOrderFromFile(orderFile, order, orderCount);

	if (!isvalid)
	{
		std::cout << "There aren't any orders!" << '\n';
		return;
	}

	printOrder(orderFile, order, orderCount);

	std::cout << "Input index of order which you want to cancel "<<'\n';
	std::cin >> cancelindex;

	if (cancelindex < 0 || cancelindex > orderCount)
	{
		std::cout << " Order cancelletion is interrupted!" << '\n';
		return;
	}

	for (int i = cancelindex - 1; i < orderCount - 1; i++)
	{
		order[i] = order[i + 1];
	}
	orderCount--;
	//imame f
	std::ofstream file(orderFile);
	for (int i = 0; i < orderCount; i++) {
		file << order[i].itemName
			<< " " << order[i].quantity
			<< " " << order[i].totalPrice;
		
	}
	std::cout << "the order has been successfully cancelled." << '\n';
}

void viewPastOrder(const char orderFile[], Order order[], int& orderCount)
{
	bool isValid = loadOrderFromFile(orderFile, order, orderCount);

	if (!isValid)
	{
		std::cout << "There aren't any orders!";
		return;
	}

	printOrder(orderFile, order, orderCount);
}

//proba 5

void viewPastSortedOrder()
{

}


void checkTurnover()
{

}

int main()
{
	unsigned choice;
	unsigned waiterChoice;
	unsigned managerChoice;
	MenuItem menu[MAX_MENU_ITEM];
	int itemCount = 0;
	Order order[MAX_ORDERS];
	int orderCount = 0;

	do {
		showRoleMenu();
		std::cin >> choice;
		switch (choice)
		{

		case 1:
			do
			{
				showWaiterOptions();
				std::cout << "Enter waiter choice:"<<'\n';
				std::cin >> waiterChoice;
				switch (waiterChoice)
				{
				case 1:
					printMenu(MENUFILE, menu, itemCount);
					break;
				case 2:
					addOrder(MENUFILE, ORDERFILE);
					break;
				case 3:
					cancelorder(ORDERFILE, order, orderCount);
					break;
				case 4:			
					viewPastOrder(ORDERFILE, order, orderCount);
					break;
				case 5:
					
					break;
				case 6:
					printOrder(ORDERFILE, order, orderCount);
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
				showManagerOptions();
				std::cout << "Enter manager choice:";
				std::cin >> managerChoice;
				switch (managerChoice)
				{
				case 1:
					printMenu(MENUFILE, menu, itemCount);
					break;
				case 2:
					addOrder(MENUFILE, ORDERFILE);
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
		case 0: 
			break;
		default: 
			std::cout<<"Invalid choice!Please, try again!"<<'\n';
			break;
		}
	}
	while (choice != 0);




	return 0;
}



