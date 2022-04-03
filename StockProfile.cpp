#include <iostream>
#include "StockProfile.h"

using namespace std;

// Return the name of the User
string StockProfile::getName() {
	return curr.name;	
}

// Input: get the name of the stock
// Return the index of the stock, if exists else -1
int StockProfile::getIndex(string name){
	int index;
	for (index = 0; index < 5; index++) { 
		if (name == stock_name[index]) {
			return index;
		}
	}
	return -1;
}

// Input: get the name of the User
// Constructor for 'StockProfile' class
// Used for creating a account for the User
StockProfile::StockProfile(string name){
	ofstream update;
	ifstream read;
	
	read.open("base.txt"); // Get the last used Personal account number, and increment it assign it to the new user
	int base;
	read >> base;
	base += 1;
	read.close();
	
	update.open("base.txt"); // update the new last used Personal account number
	update << base;
	update.close();
	
	// Append the user details in 'details.txt'
	update.open("details.txt", ios::out | ios::app);
	update << name << " " << base << " " << fixed << setprecision(1) 
					<< 100000.0 << " " << fixed << setprecision(1) << 0.0 << endl;
	curr.name = name;
	curr.pan = base;
	curr.balance = 100000.0;
	curr.profit_loss = 0.0;
	update.close();
	
	// Create his own stock profile with all stocks as '0'
        update.open("./RecordDetails/Record_" + to_string(base) + "_" + name + ".txt", ios::out|ios::app);
	for (int i = 0; i < 5; i++) {
		update << stock_name[i] << " " << 0 << endl;
	}
	update.close();
	
	// Create an empty transaction file for the user
	update.open("./RecordDetails/Tran_" + to_string(base) + "_" + name + ".txt", ios::out|ios::app);
	update.close();
	
	string line;
	string final;
	string n;
	int v, i = 0;
	read.open("stockData.txt");
	// Set initial minimum and maximum values as the current stock values
	update.open("./RecordDetails/Min_Max_" + to_string(base) + "_" + name + ".txt");
	while (getline(read, line)) {
		istringstream word(line);
		word >> n >> v;
		curr_value[i] = v;
		min_value[i] = max_value[i] = v;
		final += (to_string(v) + " ");
		i++;
	}
	read.close();
	update << final << endl;
	update << final << endl;
	update.close();
}

// Input: get the name of the User, and Personal account number
// Constructor for 'StockProfile' class with two parameters
// Used for login in his account
StockProfile::StockProfile(string name, int pan){
	ifstream read;
	string line;
	bool flag = false;
	string a_name;
	int a_pan;
	float a_balance, a_profit_loss;
	
	// match the name and personal account number with 'details.txt', if found update all the parameter values
	read.open("details.txt", ios::in);
	while (getline(read, line)) {
		istringstream word(line);
		word >> a_name >> a_pan >> a_balance >> a_profit_loss;
		if (a_name == name && a_pan == pan) {
			curr.name = a_name;
			curr.pan = a_pan;
			curr.balance = a_balance;
			curr.profit_loss = a_profit_loss;
			flag = true;
			read.close();
			read.open("./RecordDetails/Min_Max_" + to_string(curr.pan) + "_" + curr.name + ".txt");
			int i = 0;
			// store last known min and max values of stock in two different arrays
			while (getline(read, line)) {
				istringstream word(line);
				if (i%2 == 0) {
					word >> min_value[0] >> min_value[1] >> min_value[2] >> min_value[3] >> min_value[4];
				}
				else {
					word >> max_value[0] >> max_value[1] >> max_value[2] >> max_value[3] >> max_value[4];
				}
				i++;
			}
			read.close();
			read.open("stockData.txt");
			i = 0;
			while(getline(read, line)){
				istringstream word(line);
				string n;
				int v;
				word >> n >> v;
				curr_value[i] = v;
				i++;
			}
			read.close();
			break;
		}
	}
	
	// if user not found
	if (!flag) {
		cout << "****************************************" << endl;
		cout << "Invalid credentails..." << endl;
		cout << "Run again, and give valid credentails!" << endl;
		cout << "****************************************" << endl;
		exit(1);
	}
}

// Used for refreshing all stock values and display it to the user
void StockProfile::displayAllStocks(){
	ofstream update;
	update.open("stockData.txt");
	
	cout << "************************" << endl;
	cout << "Name    Current_Price" << endl;
	cout << "************************" << endl;
	for (int i = 0; i < 5; i++) {
		int temp = 1000 + (rand() % 500); // stock value will always lie in the range of 1000 - 1499
		if (temp > max_value[i]) { // check and update if current value for stock is minimum
			max_value[i] = temp;
		}
		if (temp < min_value[i]) { // check and update if current value for stock is minimum
			min_value[i] = temp;
		}
		curr_value[i] = temp;
		update << stock_name[i] << " " << temp << endl; // update the new stock values in 'stockData.txt'
		cout << stock_name[i] << "        " << temp << endl;
	}
	update.close();
	cout << "************************" << endl;
	
	// update the min and max stock values in user min_max file
	string data;
	for (int i=0; i<5; i++){
		data += (to_string(min_value[i]) + " ");
	}		
	data +=  "\n";
	for (int i=0; i<5; i++){
		data += (to_string(max_value[i]) + " ");
	}
	data += "\n";
	update.open("./RecordDetails/Min_Max_" + to_string(curr.pan) + "_" + curr.name + ".txt", ios::out);
	update << data << endl;	
	update.close();
	
	cout << "PRESS ANY KEY AND HIT ENTER TO RETURN TO MAIN MENU...";
	cin.get();
	cin.get();
}

// Used for updating the user profile whenever user buys/sells stocks
void StockProfile::updateProfile(){
	ifstream read;
	ofstream update;
	
	// Update the user 'balance' and 'profit_loss' values
	string data, line, name;
	read.open("details.txt");
	while (getline(read, line)) {
		istringstream word(line);
		word >> name;
		if (name == curr.name) {
			data += curr.name + " " + to_string(curr.pan) + " " + to_string((int)curr.balance) 
						+ ".0 " + to_string((int)curr.profit_loss) + ".0\n";
		}
		else {
			data += (line + "\n");
		}
	}
	read.close();
	
	update.open("details.txt");
	update << data;
	update.close();
}

// Used for buying a specific stock
void StockProfile::buyStock(){
	string name, data, line;
	int qty;
	ifstream read;
	ofstream update;

	cout << "Which stock you want buy: ";  // get the name of the stock
	cin >> name;
	
	int index = getIndex(name); // find certain stock name exists or not
	if (index == -1) {
		cout << name << " such stock does not exist." << endl;
		return;
	}
	cout << "How many stocks do you want to buy: "; // get how many quantity does the user wants to buy
	cin >> qty;
	if (qty * curr_value[index] > curr.balance) { // verify whether the user has sufficient balance or not
		cout << "Required amount is not available, Try with other quantity." << endl;
		return;
	}
	addTransaction(name, qty, curr_value[index]); // add the transaction details into a file
	curr.balance = (curr.balance - qty * curr_value[index]); // deduct the balance
	updateProfile(); // update the user profile details in the 'details.txt'
	data.clear();
	int q;
	
	// Increase the stock quantity by that quantity which the user has bought
	read.open("./RecordDetails/Record_" + to_string(curr.pan) + "_" + curr.name + ".txt");
	while (getline(read, line)) {
		istringstream word(line);
		word >> name >> q;
		if (name == stock_name[index]) {
			data += (stock_name[index] + " " + to_string(qty + q) + "\n");
		}
		else {
			data += (line + "\n");
		}
	}
	read.close();
	
	update.open("./RecordDetails/Record_" + to_string(curr.pan) + "_" + curr.name + ".txt", ios::out);
	update << data;
	update.close();
	
	cout << "****************************************************************************" << endl;
	cout << "'"<< stock_name[index] << "' stock bought " << qty << " quantity at a price of " << curr_value[index] << endl;
	cout << "****************************************************************************" << endl;
}

// Used for selling a specific stock
void StockProfile::sellStock(){
	string name, data, line;
	int qty, index = 1;
	ifstream read;
	ofstream update;
	
	// Display all the transaction made by the user, so far
	read.open("./RecordDetails/Tran_" + to_string(curr.pan) + "_" + curr.name + ".txt");
	cout << "*************************************************" << endl;
	cout << "Index  Date        Time    Name   Quantity   Buy_Price  " << endl;
	cout << "*************************************************" << endl;
	while (getline(read, line)) {
		string name, date, time, qty, buy_price;
		istringstream word(line);
		word >> date >> time >> name >> qty >> buy_price;
		cout << "  " << index << ".   " << date << "  " << time << "   " << name << "       " 
														<< qty << "        " << buy_price << endl;
		index += 1;
	}
	read.close();
	cout << "*************************************************" << endl;

	cout << "Which stock transaction you want sell (Choose Index : 1-" << index-1 << "): ";
	int max = index - 1;
	cin >> index; // get the transaction index which the user wants to sell
	if (index >= 0 && index <= max) { // verify whether certain transaction index exists or not
		removeTransaction(index);	// if exists remove the transaction details
	}
	else {
		cout << "No such transaction number exists..." << endl;
	}
}

// Used for instantiating buy/sell stock 
void StockProfile::buySellStock(){
	char temp;
	int c, index = 0, value;
	ifstream read;
	string line, name;
	// Display all the stock names and current value of the stock
	read.open("stockData.txt");
	cout << "************************" << endl;
	cout << "Name    Current_Price" << endl;
	cout << "************************" << endl;
	while (getline(read, line)) {
		istringstream word(line);
		word >> name >> value;
		cout << name << "        " << value << endl;
		index += 1;
	}
	cout << "************************" << endl;
	read.close();
	
	// verify whether the user wants to buy or sell stocks and call appropriately
	cout << "Do you want buy(1) or sell(0) stock: ";
	cin >> c;
	if (c == 1) {
		buyStock();
	}
	else if (c == 0) {
		sellStock();
	}
	else {
		cout << "Please choose a valid option..." << endl;
	}
	cout << "PRESS ANY KEY AND HIT ENTER TO RETURN TO MAIN MENU...";
	cin.get();
	cin.get();
}

// Return Personal Account Number
int StockProfile::getPAN(){
	return curr.pan;
}
// Display all the stocks in the user portfolio with quantity
void StockProfile::portfolioStocks(){
	ifstream read;
	string line;
	read.open("./RecordDetails/Record_" + to_string(curr.pan) + "_" + curr.name + ".txt");
	cout << "************************" << endl;
	cout << "Name    Quantity" << endl;
	cout << "************************" << endl;
	while (getline(read, line)) {
		string name, qty;
		istringstream word(line);
		word >> name >> qty;
		cout << name << "        " << qty << endl;
	}
	read.close();
	cout << "************************" << endl;
	cout << "PRESS ANY KEY AND HIT ENTER TO RETURN TO MAIN MENU...";
	cin.get();
	cin.get();
}

// Input: get the name of stock, quantity and current price of stock
// Used for adding a new stock transaction in user account
void StockProfile::addTransaction(string name, int quantity, float curr_price){
	ofstream update;
	time_t curr_time = time(0);
	
	// Append date, time, stock name, quantity, current price in user transaction file
	tm *ltm = localtime(&curr_time);
	update.open("./RecordDetails/Tran_" + to_string(curr.pan) + "_" + curr.name + ".txt", ios::out | ios::app);
	update << ltm->tm_mday << "/" << (ltm->tm_mon) + 1 << "/" << (ltm->tm_year) + 1900 << " " 
			<< ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << " "
			<< name << " " << quantity << " " << curr_price << endl;
	update.close();
}

// Input: get the transaction index
// Used for removing any specified transaction index from file
void StockProfile::removeTransaction(int pos){
	ifstream read;
	ofstream update;
	string data, line, name;
	int loc = 1, qty, pro_loss;
	
	// goto the user transaction file and search for specified index i.e., 'pos'
	read.open("./RecordDetails/Tran_" + to_string(curr.pan) + "_" + curr.name + ".txt");
	while (getline(read, line)) {
		if (loc == pos) {
			string date, time;
			float buy_price;
			istringstream word(line);
			word >> date >> time >> name >> qty >> buy_price;
			int s_index = getIndex(name);
			pro_loss = (curr_value[s_index] - buy_price) * qty;
			curr.profit_loss += pro_loss; // update the profit_loss of the user in his profile
			curr.balance += (qty * curr_value[s_index]); // add the new amount in user balance
			updateProfile(); // update the user profile file i.e., 'details.txt'
			loc += 1;
			continue;
		}
		data += (line + "\n");
		loc += 1;
	}
	read.close();
	
	update.open("./RecordDetails/Tran_" + to_string(curr.pan) + "_" + curr.name + ".txt");
	update << data;
	update.close();
	
	data.clear();
	string n;
	int q;
	// Remove those stock quantities from the user stock portfolio
	read.open("./RecordDetails/Record_" + to_string(curr.pan) + "_" + curr.name + ".txt");
	while (getline(read, line)) {
		istringstream word(line);
		word >> n >> q;
		if (n == name) {
			data += (name + " " + to_string(q-qty) + "\n");
		}
		else {
			data += (line+"\n");
		}
	}
	read.close();
	
	update.open("./RecordDetails/Record_" + to_string(curr.pan) + "_" + curr.name + ".txt");
	update << data;
	update.close();
	cout << "****************************************************************************" << endl;
	cout << "'"<< name << "' stock sold from your portfolio and made a profit/loss of " << pro_loss << endl;
	cout << "****************************************************************************" << endl;
}

// Display all the transaction made by the user
void StockProfile::viewTransactionHistory(){
	ifstream read;
	string line;
	read.open("./RecordDetails/Tran_" + to_string(curr.pan) + "_" + curr.name + ".txt");
	cout << "*************************************************" << endl;
	cout << "Date        Time    Name   Quantity   Buy_Price  " << endl;
	cout << "*************************************************" << endl;
	while (getline(read, line)) {
		string name, date, time, qty, buy_price;
		istringstream word(line);
		word >> date >> time >> name >> qty >> buy_price;
		cout << date << "  " << time << "   " << name << "       " << qty << "        " << buy_price << endl;	
	}
	cout << "*************************************************" << endl;
	read.close();
	
	cout << "PRESS ANY KEY AND HIT ENTER TO RETURN TO MAIN MENU...";
	cin.get();
	cin.get();
}

// Display all the minimum and maximum value for each of the stock
void StockProfile::minMaxStockValues(){
	for (int i = 0; i<5; i++) {
		cout << "**************************" << endl;
		cout << stock_name[i] << endl;
		cout << "**************************" << endl;
		cout << "Minimum value : " << min_value[i] << endl;
		cout << "Maximum value : " << max_value[i] << endl;
	}
	cout << "**************************" << endl;
	cout << "PRESS ANY KEY AND HIT ENTER TO RETURN TO MAIN MENU...";
	cin.get();
	cin.get();
}

// Used for displaying profits for each transaction made so far
void StockProfile::showProfits(){
	ifstream read;
	
	string line, name, date, time;
	int i, qty, buy_price;;
	
	// Display all transactions along with profit/loss for each one for them
	read.open("./RecordDetails/Tran_" + to_string(curr.pan) + "_" + curr.name + ".txt");
	cout << "****************************************************************************" << endl;
	cout << "Date        Time    Name   Quantity   Buy_Price   Current_Price   Profit/Loss" << endl;
	cout << "****************************************************************************" << endl;
	while (getline(read, line)) {
		istringstream word(line);
		word >> date >> time >> name >> qty >> buy_price;
		int s_index = getIndex(name);
		int total_profit = (curr_value[s_index] - buy_price) * qty;
		cout << date << "  " << time << "   " << name << "       " << qty << "        " << 
				buy_price << "           " << curr_value[s_index] << "            " << total_profit << endl;
	}
	cout << "****************************************************************************" << endl;
	read.close();
	
	cout << "PRESS ANY KEY AND HIT ENTER TO RETURN TO MAIN MENU...";
	cin.get();
	cin.get();
}

// Used for displaying profits for each transaction made so far along with Net profit/loss
void StockProfile::netProfitLoss(){
	ifstream read;
	
	string line, name, date, time;
	int i, qty, buy_price;
	int total_profit = 0, sum_total = 0;
	
	read.open("./RecordDetails/Tran_" + to_string(curr.pan) + "_" + curr.name + ".txt");
	cout << "****************************************************************************" << endl;
	cout << "Date        Time    Name   Quantity   Buy_Price   Current_Price   Profit/Loss" << endl;
	cout << "****************************************************************************" << endl;
	while (getline(read, line)) {
		istringstream word(line);
		word >> date >> time >> name >> qty >> buy_price;
		int s_index = getIndex(name);
		total_profit = ((curr_value[s_index] - buy_price) * qty);
		sum_total += total_profit;
		cout << date << "  " << time << "   " << name << "       " << qty << "        " << 
					buy_price << "           " << curr_value[s_index] << "            " << total_profit << endl;
	}	
	cout << "****************************************************************************" << endl;
	cout << "Net Profit/Loss for available stocks : " << sum_total << endl;
	cout << "****************************************************************************" << endl;
	read.close();
	
	cout << "PRESS ANY KEY AND HIT ENTER TO RETURN TO MAIN MENU...";
	cin.get();
	cin.get();
}

// Display the user profile details
void StockProfile::displayProfile(){
	cout << "**************************************" << endl;
	cout << "Name : " << curr.name << endl;
	cout << "Personal Account Number : " << curr.pan << endl;
	cout << "Available Balance (in HKD): " << curr.balance << endl;
	cout << "Overall Profit/Loss made so far : " << curr.profit_loss << endl;
	cout << "**************************************" << endl;
	cout << "PRESS ANY KEY AND HIT ENTER TO RETURN TO MAIN MENU...";
	cin.get();
	cin.get();
}

// Update the stock values and exit the game
void StockProfile::logout(){
	ofstream update;
	update.open("stockData.txt");
	
	for (int i = 0; i < 5; i++) {
		int temp = (1000 + (rand() % 500));
		if (temp > max_value[i]) {
			max_value[i] = temp;
		}
		if (temp < min_value[i]) {
			min_value[i] = temp;
		}
		update << stock_name[i] << " " << temp << endl;
	}
	update.close();
		
	string data;
	for (int i = 0; i < 5; i++){
		data += (to_string(min_value[i]) + " ");
	}
	data +=  "\n";
	for (int i=0; i<5; i++){
		data += (to_string(max_value[i]) + " ");
	}
	data += "\n";
	
	update.open("./RecordDetails/Min_Max_" + to_string(curr.pan) + "_" + curr.name + ".txt", ios::out);
	update << data << endl;	
	update.close();
	
	cout << "**********************************************" << endl;
	cout << "Bye " << curr.name << "! Hope to see you soon!" << endl;
	cout << "**********************************************" << endl;
	exit(1);
}
