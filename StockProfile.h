#ifndef STOCK_H_INCLUDED
#define STOCK_H_INCLUDED

#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <unistd.h>
#include <cmath>
#include <ctime>

using namespace std;

class StockProfile {
	struct Person {
		string name;
		int pan;
		float balance = 100000.0;
		float profit_loss = 0.0;
	};
	Person curr;
	int max_value[5] = {0};
	int min_value[5] = {0};
	string stock_name[5] = {"ABC", "XYZ", "PQR", "EFG", "MNO"};
	int curr_value[5];
	public:
		StockProfile(string name);
		StockProfile(string name, int pan);
		void displayAllStocks();
	        void buySellStock();
		void buyStock();
		void sellStock();
		void updateProfile();
		void portfolioStocks();
		void viewTransactionHistory();
		void addTransaction(string name, int quantity, float curr_price);
		void removeTransaction(int pos);
		int getIndex(string name);
		string getName();
		void minMaxStockValues();
		void showProfits();
		void netProfitLoss();
		void displayProfile();
		void logout();
		int getPAN();
};
#endif
