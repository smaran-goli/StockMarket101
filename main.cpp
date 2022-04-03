#include <iostream>
#include <unistd.h>
#include "StockProfile.h"
using namespace std;

int main() {
	int choice, pan;
	string name;
	StockProfile* sp;
	cout << "***************** Stock Market 101 ***************** " << endl;
	
	cout << "Create your new account(0) / login into your account(1): ";
	cin >> choice;
	// create or login account to the user
	if (choice == 1) { // login
		cout << "Enter your name: ";
		cin >> name;
		cout << "Enter your Personal account number: ";
		cin >> pan;
		sp = new StockProfile(name, pan);
	}
	else if (choice == 0) { // create a new account
		cout << "Enter your name: ";
		cin >> name;
		sp = new StockProfile(name);
	}
	else {
		cout << "Invalid choice! Please try later with correct option...";
		exit(1);
	}
	
	// Regular Menu
	while (true) {
		system("clear");
		cout << "**************************************************************" << endl;
		cout << "Hello Mr|Mrs. " << sp->getName() << ", Personal Account Number: " << sp->getPAN() << endl;
		cout << "**************************************************************" << endl;
		cout << "1. Display all stocks." << endl;
		cout << "2. Do you want to buy/sell stocks." << endl;
		cout << "3. Display your stocks." << endl;
		cout << "4. View Transaction history." << endl;
		cout << "5. Display minimum and maximum value of all stocks till date." << endl;
		cout << "6. current day profit/loss for each stock." << endl;
		cout << "7. Net profit/loss." << endl;
		cout << "8. Display your profile." << endl;
		cout << "9. logout." << endl;
		cout << "**************************************************************" << endl;
		cout << "Enter your choice from the above menu (1-9): ";
		cin >> choice;
		switch(choice) { // based on appropriate choice, invoke corresponding function
			case 1: sp->displayAllStocks();
					break;
			case 2: sp->buySellStock();
					break;
			case 3: sp->portfolioStocks();
					break;
			case 4: sp->viewTransactionHistory();
					break;
			case 5: sp->minMaxStockValues();
					break;
			case 6: sp->showProfits();
					break;
			case 7: sp->netProfitLoss();
					break;
			case 8: sp->displayProfile();
					break;
			case 9: sp->logout();
					break;
			default: cout << "Please choose correct option...";
					 cout << "PRESS ANY KEY AND HIT ENTER TO RETURN TO MAIN MENU...";
					 cin.get();
					 cin.get();
		}
	}
	return 0;
}

