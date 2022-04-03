# StockMarket101

**_StockMarket101_**

_Virtual Stock Simulation Game_

**_Introduction:_**

Investing in stocks is a very important financial strategy in today’s world, as it enables one to grow with the economy, also to make money in two ways. Starting early is the key to becoming a successful investor. For example, educating students about investment is very important, and presently, in schools, the only focus is to teach formulas of compounding, hence they end up in between some numeric values, the significance of which they may not understand.

Through virtual world simulation, we want to give our players the experience required, also help them understand what compounding and investing actually means. Our game can be a wonderful platform for potential investors to build their own portfolio and gain the experience and feel of placing trade and orders.

<!-- -->

*   Description of our game and introduce the game rules
    *   The investor will be asked to:
          *   create his/her account with “name”, then an account will be created by assigning a "Personal account number” 
                                                           
                                                           (or)
                                                           
             *   The "Personal account number" is set to 1000 at first. So whenever a new user creates an account, 
                 the "Personal account number" is incremented by 1(i.e., 1001, 1002..etc)

          *   login into an existing account with “name” and “Personal account number” as input \
   
  

    *   After creating/logging into his/her account, the user will be redirected to the main menu consisting of 9 different options. 

        _(New player starts with virtual cash of 100,000 HKD in his/her \
          portfolio account, while an already registered user can \
          view all his previous activity.)_

    *   **The main menu** – it consists of 9 different options and gives the user at most flexibility to navigate through various features of the game. Here are                               the 9 options explained briefly:
        *   "1. Display all stocks." - Used for refreshing all stock values and display it to the user. All stocks are displayed with their current par value

            _(Player gets to experiment with these stocks by investing in virtual stocks_)

        *   "2. Do you want to buy/sell stocks." – Used for buying or selling a specific stock

             If, yes

           *   Player would choose to buy or sell
              *   Player would input the name and number of stocks he wants to buy 
                                               (or)
              *   Player would input the name and number of stocks he wants to sell
                                             
              
        *   "3. Display your stocks." – to display all stocks in the user’s portfolio with quantity
        *   "4. View Transaction history." - Display all the transactions made by the user, including the date and time of the transaction
        *   “5. Display minimum and maximum value of all stocks till date.” - Display the minimum and maximum value for each of stock
        *   "6. current day profit/loss for each stock." - Used for displaying profits for each transaction made so far
        *   "7. Net profit/loss." - Used for displaying profits for each transaction made so far along with Net profit/loss
        *   "8. Display your profile." - Display the user profile details including the available balance
        *   "9. logout." - Update the stock values and exit the game "PRESS ANY KEY AND HIT ENTER TO RETURN TO MAIN MENU..."

        *   "PRESS ANY KEY AND HIT ENTER TO RETURN TO MAIN MENU..." 
        After the user selects one of the above options, the above message saying would be displayed.


    Then, the investor will be redirected to the home page and the process continues. If the user does not want to invest further he/she can select logout option       from the drop down menu and successfully logout of his/her portfolio.

<!-- -->

**Features incorporating coding requirements:**



1. _Generation of random game sets or events:_

    The current market value of stocks would be made dynamic.


    - **stock value **is generated randomly using the **rand() funtion**


    - stock value will always lies in the range of **1000 - 1499**



2. _Data structures for storing game status:_

     We used arrays, structures and classes for storing our game data.


    - used **structure** to hold the user account details such as name, personal   account number, balance and profit/loss

  	- **arrays **are used for holding the current values of the stocks


    - **classes** are used for combining the user details and stock market general  operations



3. _Dynamic memory management:_

    Used for storing details of past transactions, including profit/loss made, historical prices of stocks.

    - all **the transaction history** is displayed along with overall profit/loss amount



4. _File input/output_ (e.g., for loading/saving game status):

    - **minimum and maximum values** of all stocks for each user are stored in file

 	- **user login details** are stored in a file

  	- **all transaction history** is stored in a file

 	- **all stocks for a specific user** are stored in a file



5. _Program codes in multiple files_:

  - program is divided into multiple files i.e., **Main.cpp** which is a main program to display menu and invoke appropriate functions, **StockProfile.h** is an header file, **StockProfile.cpp **is an implementation of StockProfile.h

<!-- -->

**Compilation and execution instructions**

On Academy Linux Server:

1. make StockProfile
2. ./StockProfile
