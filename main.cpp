//Maximillian Senisch
//COSC 1437-58000
//Instructor: Dr.Tyson Mcmillan
//School: Tarrant County College
//IDE: repl.it
//Language: C++ 11
//forked off of: A  Restaurant Project Struct style Dr_T Dr. Tyson McMillan 10-2-2019
//Description: The goal was to take Dr.T's program with a struct and turn the struct into a class and add to the program to create...
/*
Name of restaurant: Max's E-bistro because its an electronic bistro-
Print a menu to for the customer to order from
The ability for the customer to order/leave a tip/and pay for their food
Print a reciept for the customer
Print the reciept an html file
Loop entire program to accept multiple customers with an exit labeled as store closed 
*/

#include <iostream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std; 

class MenuItem
{
  private:
    string name;
    double itemCost; 
    string desc; 
    char addLetter; 
    char removeLetter;
    int count;
  public: 
    MenuItem() //default constructor
    {
      name = "No name";
      itemCost = 0.00;
      desc = "yum";
      addLetter = ' ';
      removeLetter = ' ';
      count = 0;
    }
    void setName(string n) { name = n; }
    void setItemCost(double cost) { itemCost = cost; }
    void setDesc(string d) { desc = d; }
    void setAddLetter(char add) { addLetter = add; }
    void setRemoveLetter(char remove) { removeLetter = remove; }
    void setCount(int c) { count = c; }

    string getName() { return name; }
    double getItemCost() { return itemCost; }
    string getDesc() { return desc; }
    char getAddLetter() { return addLetter; }
    char getRemoveLetter() { return removeLetter; }
    int getCount() { return count; }
};

//function definitions
void populateMenu(vector<MenuItem> &entireMenu)
{
  //put some default values in our Menu
  const int numItems = 7; 
  MenuItem Item1; 
  MenuItem Item2;
  MenuItem Item3; 
  MenuItem Item4;
  MenuItem Item5;
  MenuItem Item6;
  MenuItem Item7;    

  entireMenu.push_back(Item1); //add to the end of list the Item1
  entireMenu.push_back(Item2); //add to the end of list the Item2
  entireMenu.push_back(Item3); //add to the end of list the Item3
  entireMenu.push_back(Item4); //add to the end of list the Item4
  entireMenu.push_back(Item5); //add to the end of list the Item5
  entireMenu.push_back(Item6); //add to the end of list the Item6
  entireMenu.push_back(Item7); //add to the end of list the Item7

  vector<string> defaultMenuItemNames = {"Water     ", "Green Tea ", "Tacos     ", "Burrito   ", "Enchillada", "Hotdogs   ", "Hamburger "}; 
  vector<char> defaultAddLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G'}; 
  vector<char> defaultRemoveLetters = {'a', 'b', 'c', 'd', 'e', 'f', 'g'}; 

  for(int i = 0; i < numItems; i++)
  {
    //add each item to the default list efficiently 
    entireMenu[i].setName(defaultMenuItemNames[i]); 
    entireMenu[i].setAddLetter(defaultAddLetters[i]); 
    entireMenu[i].setRemoveLetter(defaultRemoveLetters[i]); 
    entireMenu[i].setItemCost(1.00 + i); //set a random starter cost for each item
    entireMenu[i].setCount(0); //initialze all counts to 0
    if(i > 1 && i < 5)
    {
      entireMenu[i].setDesc("delicioso"); 
    }
    else
    {
      entireMenu[i].setDesc("delicious");
    }
  }


}

void showMenu(vector<MenuItem> &m)
{
  cout << fixed << setprecision(2);//set doubles to 2 decimal places
  cout << "DrT's Effcient Menu" << endl; 
  cout << "ADD  \tNAME \t COST \tREMOVE\tCOUNT\tDESC"<<endl; 
  for(int i = 0; i < m.size(); i++)
  {
    cout << m[i].getAddLetter() << ")" << setw(10) << m[i].getName() 
    << setw(5) << "$" << m[i].getItemCost() << setw(5) << "(" << m[i].getRemoveLetter()
    << ")" << setw(7) << m[i].getCount() << setw(13) << m[i].getDesc()<<endl; 
  }

}

void acceptOrder(vector<MenuItem> &m)
{
  char moreCustomers = 'Y';
  do
  {
    for(int i = 0; i < 7; i++)
    {
      m[i].setCount(0);
    }
    cout << "\033[2J\033[1;1H\n\n";
    showMenu(m);  
    //declare and initialize necessary variables
      char option = '\0';// the user-selected menu item
      char choice = '\0';// tip choice
      double subtotal = 0.00; 
      double tip = 0.00;
      double tax = 0.00;
      double total = 0.00;
      double tender = 0.00;
      double change = 0.00;
      string paymentMethod;
      string str;
    
    //accept the order
      do
      {
        cout << "\nPlease choose an item (x to Exit): ";
        cin >> option; 

        for(int i=0; i < m.size(); i++)
        {
          if(option == m[i].getAddLetter())
          {
            cout << "\nMenu Item " << m[i].getAddLetter() << " selected."; 
            m[i].setCount(m[i].getCount() + 1); //increment the count by 1
            cout << "\033[2J\033[1;1H"; //clear screen 
            cout << "\n1 UP on " << m[i].getName() << endl;
            subtotal += m[i].getItemCost(); //increment the subtotal by the cost of the item 
            showMenu(m); //show the updated menu
            cout << "\nSubtotal: $" << subtotal << endl;  
          }
          else if(option == m[i].getRemoveLetter())
          {
            cout << "\nRemove Item " << m[i].getRemoveLetter() << " selected."; 
            if(m[i].getCount() > 0) //subtract if and only if the count is > 0
            {
              m[i].setCount(m[i].getCount() - 1); //decrement the count by 1
              cout << "\033[2J\033[1;1H"; //clear screen 
              cout << "\n1 DOWN on " << m[i].getName() << endl;
              subtotal -= m[i].getItemCost(); //decrement the subtotal by the cost of the item
              showMenu(m); //show the updated menu
              cout << "\nSubtotal: $" << subtotal << endl;  
            }
            else //the the user why you blocked item removal 
            {
                
                cout << "\nYou have no " << m[i].getName() << " to remove from your cart" << endl;
            }
          }
          else if(
                    option != m[i].getAddLetter() && 
                    option != m[i].getRemoveLetter() &&
                    option != 'x' &&
                    option != 'X' 
                ) //test for all of my valid inputs
                {
                  if(i == 0)
                  {
                    cout << "\nInvalid input (" << option << "). Please try again." << endl; 
                  }  
                }
        }
      }while(option != 'x' && option != 'X'); 
      cout << "\nThank you for placing your order.\n" << endl; 

    //handle the tip process here
      cout << "Your order total is: $" << subtotal << "\n\n";
      //tip menu
        cout << "Please choose an amount to tip\n";
        cout << "A) 20% ($" << subtotal * .2 << ")\n";
        cout << "B) 25% ($" << subtotal * .25 << ")\n";
        cout << "C) 30% ($" << subtotal * .3 << ")\n";
        cout << "D) Manually enter an amount\n";

      do
      {
        cout << "Please choose a tip amount: ";
        cin >> choice;
      }
      while(choice != 'A' && choice != 'B' && choice != 'C' && choice != 'D' && choice != 'a' && choice != 'b' && choice != 'c' && choice != 'd');

      if(choice == 'a' || choice == 'A')
      {
        tip = subtotal * .20;
      }
      else if(choice == 'b' || choice == 'B')
      {
        tip = subtotal * .25;
      }
      else if(choice == 'c' || choice == 'C')
      {
        tip = subtotal * .30;
      }
      else
      {
        cout << "Manually enter tip\n";
        cout << "1) Percentage (%)\n";
        cout << "2) Dollar amount ($)\n";
        do
        {
          cout << "Please choose an option: ";
          cin >> choice;
          getline(cin, str); //checks to see if more than a single character was entered
        }
        while(choice < '1' || choice > '2' || str != ""); //if more than a single character was entered then loop

        if(choice == '1')
        {
          cout << "Please enter the percentage you would like to tip: ";
          cin >> tip;
          if(tip < 0.00)
          {
            tip = tip * (-1.00);
            cout << "\nYou must think you're slick.\n";
          }
          tip = subtotal * tip/100.00;
        }
        else
        {
          cout << "Please enter the tip amount in dollars: ";
          if(tip < 0.00)
          {
            tip = tip * (-1.00);
            cout << "\nYou must think you're slick.\n";
          }
          cin >> tip;
        }
        cout << "TIP: " << tip;
      }
    
    //calculate tax
      tax = subtotal * .0825;
    //calculate total
      total = subtotal + tip + tax;
    //accept payment
      cout << "\n\nHow would you like to pay?\n";
      cout << "1) Cash\n2) Debit/Credit Card\n";
      do
      {
        cout << "Please choose an option: ";
        cin >> choice;
        getline(cin, str); //checks to see if more than a single character was entered
      }
      while(choice < '1' || choice > '2' || str != ""); //if more than a single character was entered then loop 
      if(choice == '1')
      {
        paymentMethod = "Cash       ";
        cout << "Total is: $" << total;
        cout << "\nPlease enter the cash amount: $";
        cin >> tender;
        if(tender < total)
        {
          paymentMethod = "Cash & Card";
          cout << "Remaining balance: $" << total - tender << endl;
          cout << "Please pay the remaining balance with a Debit/Credit Card.\n(Customer hands server card)\n";
        }
        else if(tender == total)
        {
          cout << "We appreciate the exact change!\n";
        }
        else
        {
          change = tender - total;
          cout << "Your change is: $" << change << endl;
        }
      }
      else
      {
        paymentMethod = "Card       ";
      }

      cout << "Thank you for eating at Max's food place!\n";

    //handle reciept generation here
      cout << "\033[2J\033[1;1H";
      cout << "\x1B[47m\x1B[30m                                 \n             RECIEPT             \n";
      cout << "---------------------------------\n";
      cout << "    Server name: Maximillian     \n                                 \n";
      cout << "    Items            Price       \n";
      //cout << "\t\t";
      for(int i = 0; i < m.size(); i++)
      {
        if(m[i].getCount() > 0)
        {
          cout <<"    X" << m[i].getCount() << "    " << m[i].getName() << "    $" << m[i].getItemCost() * m[i].getCount() << "    \n";
        }
      }
      cout << "                                 \n            Subtotal: $" << subtotal << "      \n";
      cout << "                 Tax: $" << tax << "      \n";
      cout << "                 Tip: $" << tip << "      \n                                 \n";
      cout << "               Total: $" << total << "     \n";
      cout << "      Payment Method: " << paymentMethod << "\n";
      cout << "              Change: $" << change << "      \n";
      cout << "             Balance: $0.00      \n";
      cout << "---------------------------------\n                                 \033[0m\n";

    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nNext Customer Please!\n";
    cout << "Is there another customer?\n";
    cout << "N or n) for No\n";
    cout << "Y or y) for Yes\n";
    cout << "Choice: ";
    cin >> moreCustomers;
  }
  while(moreCustomers != 'N' && moreCustomers != 'n');
}

int main() 
{
  vector<MenuItem> wholeMenu; 
  populateMenu(wholeMenu);
  acceptOrder(wholeMenu);  
  return 0; 
}