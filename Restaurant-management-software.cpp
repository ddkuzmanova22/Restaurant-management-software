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
#include <string>

const char *MENUFILE = "menu.txt";
const char *ORDERFILE = "order.txt";
const char *WAREHOUSEFILE = "warehouse.txt";
const char* DAILYREPORTFILE = "dailyReport.txt";
const int MAX_MENU_ITEM = 100;
const int ITEM_NAME_LENGTH = 50;
const int MAX_ORDERS = 50;
const int DATE_LENGTH = 11;
const int PRODUCT_NAME_LENGTH = 50;
const int MAX_WAREHOUSE_ITEMS = 100;
const int MAX_ITEMS = 100;


struct MenuItem {
	char name[50];
	double price;
};

struct Order {
	char itemName[50];
	int quantity;
	double totalPrice; 
	char currentDate[DATE_LENGTH];
};

struct Products {
	char productName[50];
	int quantity;
};

void showRoleMenu()
{
	std::cout << "--- Select user ---\n";
	std::cout << "1. Waiter\n";
	std::cout << "2. Manager\n";
	std::cout << "0. Exit\n";
	std::cout << "-------------------\n";
	std::cout << "Enter role number:\n";
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

bool loadMenuFromFile(const char* menuFile, MenuItem* menu, int& itemCount)
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
//1-waiter

void displayMenuItems(const MenuItem menu[], int& itemCount) {
	std::cout << "--- Restaurant Menu ---\n";
	for (int i = 0; i < itemCount; i++) {
		std::cout << i + 1 << ". " << menu[i].name << " - "
			<< menu[i].price << " lv.\n";
	}
}

void printMenu(const char* menuFileName, MenuItem menu[], int& itemCount) {
	int returnToOptions;
	itemCount = 0;
	do {
		loadMenuFromFile(menuFileName, menu, itemCount);

		// Check and display the menu
		if (itemCount > 0) {
			displayMenuItems(menu, itemCount);
		}
		else {
			std::cout << "The menu is empty or could not be loaded correctly.\n";
		}

		// Return to functionalities
		std::cout << "\nPress 0 to return to the waiter options: ";
		std::cin >> returnToOptions;
	} while (returnToOptions != 0);
}

void myStrcpy(char* destination, const char* source) {
	int i = 0;
	while (source[i] != '\0') { // Докато не достигнем края на изходния низ
		destination[i] = source[i]; // Копиране на текущия символ
		i++;
	}
	destination[i] = '\0'; // Добавяне на терминиращ символ
}

bool loadCurrentDate(char* date) {
	std::ifstream file("current_date.txt");
	if (!file) {
		// If the file does not exist, set the initial date: 2025-01-01
		std::cerr << "Date file not found. Setting initial date: 2025-01-01\n";
		std::ofstream outFile("current_date.txt");
		if (!outFile) {
			std::cerr << "Error creating date file!\n";
			return false;
		}
		myStrcpy(date, "2025-01-01");
		outFile << date;
		outFile.close();
		return true;
	}
	file >> date;
	file.close();
	return true;
}

void incrementDate(char* date) {
	int year = 2025, month = 1, day = 0;

	// Разделя датата (YYYY-MM-DD)
	sscanf_s(date, "%d-%d-%d", &year, &month, &day);

	// Увеличава деня
	day++;

	// Проверка за преминаване към следващ месец
	if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) &&
		day > 31) {
		day = 1;
		month++;
	}
	else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
		day = 1;
		month++;
	}
	else if (month == 2) { // Февруари
		bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		int maxDays = isLeap ? 29 : 28;
		if (day > maxDays) {
			day = 1;
			month++;
		}
	}

	// Преминаване към следваща година
	if (month > 12) {
		month = 1;
		year++;
	}

	// Форматиране на новата дата
	sprintf_s(date, 110, "%04d-%02d-%02d", year, month, day);
}

void saveCurrentDate(const char date[]) {
	std::ofstream file("current_date.txt");
	if (!file) {
		std::cerr << "Error!!\n";
		return;
	}
	file << date; // Записва новата дата
	file.close();
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

void writeOrderToFile(const char* orderFile, const char* itemName, int quantity, double totalPrice, char* currentDate)
{
	std::ofstream file(orderFile, std::ios::app);
	if (!file.is_open())
	{
		return;
	}

	file << itemName<< " " << quantity<< " " << totalPrice << " " << currentDate << "\n";
	file.close();
}
//2-waiter
void addOrder(const char* menuFile, const char* orderFile, char* currentDate)
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
	displayMenuItems(menu, itemCount);
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
			writeOrderToFile(orderFile, itemName, quantity, totalPrice, currentDate);
			std::cout << "The order is added" << '\n';
			break;
		}
	}

	if (!isFound)
	{
		std::cout << "The order is canceled" << '\n';
	}
}

bool loadOrderFromFile(const char* orderFile, Order* order, int& orderCount)
{
	orderCount = 0;
	std::ifstream file(orderFile);

	if (!file){
		std::cerr << "Error!" << orderFile << '\n';
		return false;
	}
	while (file >> order[orderCount].itemName >> order[orderCount].quantity >> order[orderCount].totalPrice >> order[orderCount].currentDate){
		orderCount++;
		if (orderCount >= MAX_ORDERS) break; // Ограничение за броя поръчки
	}

	file.close();
	return true;
}

void printOrder(Order* order, int& orderCount)
{
	for (int i = 0; i < orderCount; i++){
		std::cout << i + 1 
			<< ". " << "Item name: " << order[i].itemName 
			<< " - " << "Quantity: " << order[i].quantity 
			<< " - " << "Total price: " << order[i].totalPrice 
			<< " - " << " Current date:  " << order[i].currentDate << '\n';
	}

}
//3-waiter
void cancelOrder(const char* orderFile, Order* order, int& orderCount)
{
	unsigned cancelindex;
	bool isvalid = loadOrderFromFile(orderFile, order, orderCount);

	if (!isvalid){
		std::cout << "There aren't any orders!" << '\n';
		return;
	}

	printOrder( order, orderCount);

	std::cout << "Input index of order which you want to cancel "<<'\n';
	std::cin >> cancelindex;

	if (cancelindex < 0 || cancelindex > orderCount){
		std::cout << " Order cancelletion is interrupted!" << '\n';
		return;
	}

	for (int i = cancelindex - 1; i < orderCount - 1; i++){
		order[i] = order[i + 1];
	}
	orderCount--;

	std::ofstream file(orderFile);
	for (int i = 0; i < orderCount; i++) {
		file << order[i].itemName<< " " << order[i].quantity<< " " << order[i].totalPrice << " " << order[i].currentDate << '\n';
	}
	std::cout << "the order has been successfully cancelled." << '\n';
}
//4-waiter
void viewPastOrder(const char* orderFile, Order* order, int& orderCount)
{
	bool isValid = loadOrderFromFile(orderFile, order, orderCount);

	if (!isValid){
		std::cout << "There aren't any orders!";
		return;
	}

	printOrder( order, orderCount );
}


void selectionSortOrders(Order* order, int orderCount) {
	for (int i = 0; i < orderCount - 1; i++) {
		int minIndex = i;
		for (int j = i + 1; j < orderCount; j++) {
			// Compare item names to find the smallest element
			if (myStrcmp(order[j].itemName, order[minIndex].itemName) < 0) {
				minIndex = j;
			}
		}
		// Swap the current element with the smallest element found
		if (minIndex != i) {
			Order temp = order[i];
			order[i] = order[minIndex];
			order[minIndex] = temp;
		}
	}
}
//5-waiter
void viewPastSortedOrder(const char* orderFile, Order order[], int& orderCount)
{
	bool isvalid = loadOrderFromFile(orderFile, order, orderCount);

	if (!isvalid){
		std::cout << "There aren't any orders!";
		return;
	}
	selectionSortOrders(order, orderCount);
	printOrder(order, orderCount);
	for (int i = 0; i < orderCount;){
		unsigned counter= 0;
		const char* currentName = order[i].itemName;
		while (i < orderCount && myStrcmp(order[i].itemName, currentName ) == 0 ){
			counter += order[i].quantity;
			i++;
		}
		std::cout << "Total orders count:";
		std::cout << "Item name: " << currentName << " - " << "Quantity: " << counter << '\n';
	}
}

bool compareStrings(const char* str1, const char* str2) {
	int i = 0;
	while (str1[i] != '\0' && str2[i] != '\0') {
		if (str1[i] != str2[i]) {
			return false;
		}
		i++;
	}
	return str1[i] == '\0' && str2[i] == '\0';
}

void takeCurrentDate(char* currentDate)
{
	bool isValid = loadCurrentDate(currentDate);
	if (!isValid)
	{
		std::cout << "Error loading the date!\n";
		return;
	}
	incrementDate(currentDate);
	saveCurrentDate(currentDate);
	std::cout << "Current date: " << currentDate << "\n";

}
//6-waiter
void checkturnover(const char* orderFile, Order* order, int& orderCount, const char* currentDate)
{
	bool isvalid = loadOrderFromFile(orderFile, order, orderCount);

	if (!isvalid){
		std::cout << "There aren't any orders!";
		return;
	}
	double turnover = 0;
	for (int i = 0; i < orderCount; i++){
		unsigned counter = 0;
		if(myStrcmp(order[i].currentDate, currentDate) == 0){
			turnover += order[i].totalPrice;
		}
	}
	std::cout << "Total turnover for: " << currentDate << ": " << turnover << " lv." << "\n";
}



//6-manager

bool loadWareHouseFromFile(const char* wareHouseFile, Products* products, int& productCount)
{
	productCount = 0;
	std::ifstream file(wareHouseFile);

	if (!file.is_open()){
		std::cout<< "Error!\n";
		return false;
	}
	while (file >> products[productCount].productName >> products[productCount].quantity){
		productCount++;
		if (productCount >= MAX_ITEMS) break; // Ограничение за броя поръчки
	}

	file.close();
	return true;
}
//6-manager
void displayWareHouseItems(const Products* products, int& productCount) {
	std::cout << "--- Restaurant Menu ---\n";
	for (int i = 0; i < productCount; i++) {
		std::cout << i + 1 << ". " << products[i].productName << " - "
			<< products[i].quantity << "\n";
	}
}

void printWareHouseItems(const char* wareHouseFile, Products* products, int& productCount) {
	int returnToOptions;
	do {
		loadWareHouseFromFile(wareHouseFile, products, productCount);

		// Check and display the menu
		if (productCount > 0) {
			displayWareHouseItems(products, productCount);
		}
		else {
			std::cout << "The menu is empty or could not be loaded correctly.\n";
		}

		// Return to functionalities
		std::cout << "\nPress 0 to return to the waiter options: ";
		std::cin >> returnToOptions;
	} while (returnToOptions != 0);
}

void writeProductToFile(const char* warehouseFile, const char* itemName, int quantity)
{
	std::ofstream file(warehouseFile, std::ios::app);
	if (!file.is_open()){
		return;
	}

	file << itemName << " " << quantity << " " << "\n";
	file.close();
}

void removeProduct(const char* wareHouseFile, Products* products, int& productCount)
{
	unsigned cancelindex;
	bool isvalid = loadWareHouseFromFile(wareHouseFile, products, productCount);

	if (!isvalid) {
		std::cout << "There aren't any orders!" << '\n';
		return;
	}

	displayWareHouseItems(products, productCount);

	std::cout << "Input index of product which you want to cancel " << '\n';
	std::cin >> cancelindex;

	if (cancelindex < 0 || cancelindex > productCount) {
		std::cout << " Order cancelletion is interrupted!" << '\n';
		return;
	}

	for (int i = cancelindex - 1; i < productCount - 1; i++) {
		products[i] = products[i + 1];
	}
	productCount--;

	std::ofstream file(wareHouseFile);
	for (int i = 0; i < productCount; i++) {
		file << products[i].productName << " " << products[i].quantity << '\n';
	}
	std::cout << "The product has been successfully cancelled." << '\n';
}
//8-manager
void addProduct(const char* wareHouseFilee)
{
	Products product[MAX_WAREHOUSE_ITEMS];
	int productCount = 0;
	char productName[PRODUCT_NAME_LENGTH];
	unsigned quantity;
	bool isLoaded = loadWareHouseFromFile(wareHouseFilee, product, productCount);

	if (!isLoaded)
	{
		std::cerr << "Error!";
		return;
	}
	displayWareHouseItems(product, productCount);
	std::cout << "Enter product name:" << '\n';
	std::cin >> productName;
	bool isFound = false;

	for (int i = 0; i < productCount; i++)
	{
		if (myStrcmp(productName, product[i].productName) != 0)
		{
			isFound = true;
			std::cout << "Enter quantity:" << '\n';
			std::cin >> quantity;
			writeProductToFile(wareHouseFilee, productName, quantity);
			std::cout << "The product is added" << '\n';
			break;
		}
	}

	if (!isFound)
	{
		std::cout << "The product is canceled" << '\n';
	}
}


void writeTurnOverToFile(const char* dailyReport, char* currentDate, double turnOver)
{
	std::ofstream report(dailyReport, std::ios::app);
	if (!report.is_open()){
		std::cout << "Error!";
		return;
	}
	report << currentDate << " " << turnOver << "\n";
	report.close();
}

//10

void generateDailyReport(const char* orderFile, const char* dailyReport, char* currentDate) {
	Order order[MAX_ORDERS];
	int orderCount = 0;
	bool isValid = loadOrderFromFile(orderFile, order, orderCount);

	if (!isValid) {
		std::cout << "Error!";
		return;
	}

	double dailyTurnover = 0;
	for (int i = 0; i < orderCount; i++){
		if (myStrcmp(currentDate, order[i].currentDate) == 0){
			dailyTurnover += order[i].totalPrice;
		}
	}

	writeTurnOverToFile(dailyReport, currentDate, dailyTurnover);
	std::cout << "Daily report generated for " << currentDate << " : " << dailyTurnover << "\n";
	incrementDate(currentDate);
	saveCurrentDate(currentDate);
	std::cout << "Current date is " << currentDate << '\n';
}


//11-manager
void displayTurnoverFromDateToCurrentDate(const char* dailyReport, char* startDate, char* currentDate) {

	std::ifstream file(dailyReport);
	if (!file.is_open())
	{
		std::cout << "Error!";
		return;
	}

	double turnover = 0;
	char date[DATE_LENGTH];
	bool dateFound = false;

	if (!file.is_open()) {
		std::cout << "Error!\n";
		return;
	}

	while (file >> date >> turnover) {
		// Check if the date is within the specified range
		if ((myStrcmp(date, startDate) >= 0) && (myStrcmp(date, currentDate) <= 0)) {
			std::cout << "Date: " << date << " - Turnover: "<< turnover << " lv.\n";
			dateFound = true;
		}
	}

	if (!dateFound) {
		std::cout << "No data found! " << "\n";
	}
	file.close();
	return;
}


//12 add item in menu
void writeProductToMenu(const char* menuFile, char* itemName, int price) {
	std::ofstream file(menuFile, std::ios::app);
	if (!file.is_open()){
		return;
	}

	file << itemName << " " << price << " " << "\n";
	file.close();
}

void addMenuItem(const char* menuFile)
{
	MenuItem menu[MAX_MENU_ITEM];
	int itemCount = 0;
	char itemName[ITEM_NAME_LENGTH];
	double price=0;
	bool isLoaded = loadMenuFromFile(menuFile, menu, itemCount);

	if (!isLoaded){
		std::cerr << "Error!";
		return;
	}
	displayMenuItems(menu, itemCount);
	std::cout << "Enter item in menu:" << '\n';
	std::cin >> itemName;
	bool isFound = false;

	for (int i = 0; i < itemCount; i++){
		if (myStrcmp(itemName, menu[i].name) != 0){
			isFound = true;
			std::cout << "Enter price:" << "\n";
			std::cin >> price;
			writeProductToMenu(menuFile, itemName, price);
			std::cout << "The item is added" << '\n';
			break;
		}
	}

	if (!isFound){
		std::cout << "The item is already added" << '\n';
	}
}

//13 remove item in menu

bool loadMenuItemFromFile(const char* menuFile, MenuItem* menu, int& itemCount)
{
	itemCount = 0;
	std::ifstream file(menuFile);

	if (!file.is_open()){
		std::cerr << "Error!" << menuFile << '\n';
		return false;
	}
	while (file >> menu[itemCount].name >> menu[itemCount].price ){
		itemCount++;
	}

	file.close();
	return true;
}

void writeItemToFile(const char* menuFile, const char* itemName, int price)
{
	std::ofstream file(menuFile, std::ios::app);
	if (!file.is_open()){
		return;
	}
	file << itemName << " " << price << "\n";
	file.close();
}

void removeMenuItem(const char* menuFile, MenuItem* menu, int& itemCount)
{
	unsigned cancelindex;
	bool isvalid = loadMenuItemFromFile(menuFile, menu, itemCount);

	if (!isvalid){
		std::cout << "There aren't any items!" << '\n';
		return;
	}

	displayMenuItems(menu, itemCount);
	std::cout << "Input index of item which you want to remove " << '\n';
	std::cin >> cancelindex;

	if (cancelindex < 0 || cancelindex > itemCount){
		std::cout << " Items cancelletion is interrupted!" << '\n';
		return;
	}

	for (int i = cancelindex - 1; i < itemCount - 1; i++){
		menu[i] = menu[i + 1];
	}
	itemCount--;

	std::ofstream file(menuFile);
	for (int i = 0; i < itemCount; i++) {
		file << menu[i].name<< " " << menu[i].price;
	}
	
	std::cout << "The item has been successfully removed." << '\n';
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
	char currentDate[DATE_LENGTH];
	Products products[MAX_WAREHOUSE_ITEMS];
	int productCount = 0;

	takeCurrentDate(currentDate);
	
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
					addOrder(MENUFILE, ORDERFILE,currentDate);
					break;
				case 3:
					cancelOrder(ORDERFILE, order, orderCount);
					break;
				case 4:			
					viewPastOrder(ORDERFILE, order, orderCount);
					break;
				case 5:
					viewPastSortedOrder(ORDERFILE, order, orderCount);
					break;
				case 6:
					checkturnover(ORDERFILE, order, orderCount, currentDate);
					break;
				case 7:
					showWaiterOptions();
					break;
				case 0:
					std::cout << "Return back!" << "\n";
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
				std::cout << "Enter manager choice:"<< "\n";
				std::cin >> managerChoice;
				switch (managerChoice)
				{
				case 1:
					printMenu(MENUFILE, menu, itemCount);
					break;
				case 2:
					addOrder(MENUFILE, ORDERFILE,currentDate);
					break;
				case 3:
					cancelOrder(ORDERFILE, order, orderCount);
					break;
				case 4:
					viewPastSortedOrder(ORDERFILE, order, orderCount);
					break;
				case 5:
					viewPastOrder(ORDERFILE, order, orderCount);
					break;
				case 6:
					printWareHouseItems(WAREHOUSEFILE, products, productCount);
					break;
				case 7:
					removeProduct(WAREHOUSEFILE, products, productCount);
					break;
				case 8:
					addProduct(WAREHOUSEFILE);
					break;
				case 9:
					checkturnover(ORDERFILE, order, orderCount, currentDate);
					break;
				case 10:
					generateDailyReport(ORDERFILE, DAILYREPORTFILE, currentDate);
					break;
				case 11:
					char startDate[DATE_LENGTH];
					//function
				    std::cin >> startDate;
					displayTurnoverFromDateToCurrentDate(DAILYREPORTFILE, startDate, currentDate);
					break;
				case 12:
					addMenuItem(MENUFILE);
					break;
				case 13:
					removeMenuItem(MENUFILE, menu, itemCount);
					break;
				case 14:
					showManagerOptions();
					break;
				case 0:
					std::cout << "Return back!" << "\n";
					break;
				default:
					std::cout << "Invalid choice!Please, try again!"<<'\n';
					break;
				}
			} while (managerChoice != 0);
			break;
		case 0: 
			std::cout << "Exit!";
			break;
		default: 
			std::cout<<"Invalid choice!Please, try again!"<<'\n';
			break;
		}
	}
	while (choice != 0);

	return 0;
}



