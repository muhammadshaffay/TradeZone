# include <iostream>
# include <ctime>
# include <cstdlib>
# include <conio.h>
# include <fstream>
# include <string>

using namespace std;

void redrawMarket();

void comma_separator(string row, string **stocks_data, int index)
{
	string value = "";
	int column = 0;
	for (int i = 0; row[i] != '\0'; i++)
	{
		if (row[i] == ',')
		{
			stocks_data[column][index] = value;
			column += 1;
			value = "";			
		}
		else
			value += row[i];
	}
	stocks_data[column][index] = value;
	return;
}

int ReadData_Companies(string **stocks_data)
{
	ifstream file("companies.txt");
	string data = "";

	getline(file, data); // skipping first row
	int index = 0;
	while(getline(file, data))
	{
		comma_separator(data, stocks_data, index);
		index += 1;
	}
	file.close();
	return index;	
}

void displaymarket(string** stocks_data, int rows, float* prices, float* newprices)
{
	cout << "\n\n\t\t\t\t\t------------------------------" << endl;
	cout << "\t\t\t\t\t| Karachi Stock Market (Live)|" << endl;
	cout << "\t\t\t\t\t------------------------------\n\n" << endl;
	
	cout << "\t\t---------------------------------------------------------------------------------------------------" << endl; 
	cout << "\t\t|\tStocks\t" << "\tPrevious Price\t\t" << "Current Price\t" << "\tCompany Name\t\t  |\n";
	cout << "\t\t---------------------------------------------------------------------------------------------------\n\n" << endl; 
	
	for (int i = 0; i < rows; i++)
	cout << "\t\t|\t" << stocks_data[0][i] << " \t|\t" << prices[i] << " \t\t|\t" << newprices[i] << "\t\t|\t" << stocks_data[1][i] << " " << endl;
	
	
	return;
}

void WriteData_Companies(string **stocks_data, int rows, float* prices)
{
	ofstream file;
  	file.open ("saved.txt");
  	
  	for (int i = 0; i < rows; i++)
  	{
  		file << stocks_data[0][i] << "1" << stocks_data[1][i] << "," << prices[i] << "\n";
	}
  	file.close();
  	
  	return;
}

void displaymenu(char s)
{
		cout << "\n\t\t-------------------------------------------------------------------------------------------";
		cout << "\n\t\t| Show Portfolio: "<< s << " | Add Stock: A | Remove Stock: R | Add / Withdraw money : M | Exit: E |";
		cout << "\n\t\t-------------------------------------------------------------------------------------------";
		cout << "\n\t\t\tWhat Operation Do You Want To Perform (Quick Update : Enter): ";	
}

void updatemarket(float* prices, int rows)
{
	srand(time(0));
	for (int i = 0; i < rows; i++)
	{
		int choice = 1+ (rand() % 2);
		if (choice == 1)
			prices[i] = prices[i] + (rand() % int(prices[i] * 0.1));
		else
			prices[i] = prices[i] - (rand() % int(prices[i] * 0.1));
	}
}

int portfolio(string ** portfolio_data, float *p, float *c, string* n)
{
	ifstream file;
	file.open ("portfolio.txt");
							
	if(file)
	{
		string name = "", previous = "", current = "", data="";
		getline(file, name);
		getline(file, previous);
		getline(file, current);
		
		*n = name;
		*p = atof(previous.c_str());
		*c = atof(current.c_str());
		
		int index = 0;
		
		while(getline(file, data))
		{ 
			comma_separator(data, portfolio_data, index);
			index += 1;
		}
		file.close();
		return index;
	}
	else
		cout << "ERROR : Please Attach Your Portfolio File" << endl;
	return 0;
}

void displayportfolio(int num_stocks_portfolio, string** portfolio_data, string name, int* price, float current, float previous)
{
	cout << "\n\n\t\t\t\t\t------------------------------" << endl;
	cout << "\t\t\t\t\t| Karachi Stock Market (Live)|" << endl;
	cout << "\t\t\t\t\t------------------------------\n\n" << endl;
				
	cout << "\n\n\t\t\t---------------------" << endl;
	cout << "\t\t\t| Name : " << name << " |" << "\t Current Balance : " << current << "\t Previous Balance : " << previous << endl;
	cout << "\t\t\t---------------------" << endl;

	cout << "\n\n\t\t\tStock \t\tPrice \t\tShares \t\tCompany Name\n\n";
	for(int i = 0; i < num_stocks_portfolio; i++)
	{
		cout << "\t\t\t" << portfolio_data[0][i] << " \t\t" <<  price[i] << " \t\t" <<  portfolio_data[2][i] << " \t\t" <<  portfolio_data[1][i]<< endl;
	}
	cout << "\t\t\t---------------------------------------------------------------------" << endl;				
	cout << "\t\t\t| Press L To Go To Main Stock Market Window To Perform Operations : " << endl;
	cout << "\t\t\t---------------------------------------------------------------------" ;	
}

void changebalance()
{
	cout << "\n\n\t\t\t\t\t------------------------------" << endl;
	cout << "\t\t\t\t\t| Karachi Stock Market (Live)|" << endl;
	cout << "\t\t\t\t\t------------------------------\n\n" << endl;
	
	cout << "\t\t\t\t\t----------------------------" << endl;
	cout << "\t\t\t\t\t| Add  : A | Withdraw  : W |" << endl;
	cout << "\t\t\t\t\t----------------------------" << endl;
	
	cout << "\t\t\t\t\t  Select Operation : ";
}

void addmoney(float* current)
{
	float amount = 0;
	cout << "\n\n\t\t\t\t\t   Current Balance : " << *current << endl;
	cout << "\t\t\t\tEnter Amount You Want To Add To Your Account : ";
	cin >> amount;
	
	*current = *current + amount;
}

void withdrawmoney(float * current)
{
	float amount = 0;
	cout << "\n\n\t\t\t\t\t   Current Balance : " << *current << endl;
	cout << "\t\t\tEnter Amount You Want To Withdraw From Your Account : ";
	cin >> amount;
	
	while(amount >= *current)
	{
		cout << "\n\t\tERROR : Transaction Is InValid Because Your Withdrawal Amount Exceeds Current Balance\n\t\t\t\t\t Please Enter Valid Amount : " ;
		cin >> amount;
	}
	*current = *current - amount;		
}

void WriteData_Portfolio(string name, float previous, float current, string ** portfolio_data, int num_stocks_portfolio, int *prices, int *shares)
{
	ofstream file;
  	file.open ("portfolio.txt");
  	
  	file << name << "\n";
  	file << previous << "\n";
  	file << current << "\n";
  	
  	for (int i = 0; i < num_stocks_portfolio; i++)
  	{
  		file << portfolio_data[0][i] << "," << portfolio_data[1][i] << "," << shares[i] << "," << prices[i] << "\n";
	}
  	file.close();
  	
  	return;	
}

void copy(float* prices, float* newprices, int rows)
{
		for (int i = 0; i < rows; i++)
		{
			float value = newprices[i];
			prices[i] = newprices[i];
		}
}

char dropstock(int num_stocks_portfolio, string**portfolio_data, int*price_pstocks, int* shares, string name, float* current, float previous)
{
	char input;
	cout << "\n\n\t\t\t\t\t------------------------------" << endl;
	cout << "\t\t\t\t\t| Karachi Stock Market (Live)|" << endl;
	cout << "\t\t\t\t\t------------------------------\n\n" << endl;
				
	cout << "\n\n\t\t\t---------------------" << endl;
	cout << "\t\t\t| Name : " << name << " |" << "\t Current Balance : " << *current << "\tPrevious Balance : " << previous << endl;
	cout << "\t\t\t---------------------" << endl;

	cout << "\n\n\t\t\tHere Is The List Of Stocks You Currently Hold : " << endl;
	cout << "\t\t\tStock \t\tPrice \t\tShares \t\tCompany Name\n\n";
	for(int i = 0; i < num_stocks_portfolio; i++)
		cout << "\t\t\t" << portfolio_data[0][i] << " \t\t" <<  price_pstocks[i] << " \t\t" <<  shares[i] << " \t\t" <<  portfolio_data[1][i]<< endl;
	
	string dropname=  "";
	int dropshares = 0;
	bool present= false;
	int loc = 0;
	while(!present)
	{
		cout << "\n\n\t\t\tEnter Stock Name You Want To Drop : ";
		cin >> dropname;
	
		for(int i = 0; i < num_stocks_portfolio; i++)
		{
			if (dropname == portfolio_data[0][i])
			{
				present = true;
				loc = i;
			}
		}
		if(present)
		{
			cout << "\t\t\tEnter Amount of Shares Yo Want To Drop of " << dropname << " : ";
			cin >> dropshares;					
		}
		else
			cout << "\t\t\tERROR : Stock Not Found In Portfolio!";
	}
	if (shares[loc] <= dropshares)
	{
		while(input != 'E')
		{
			cout << "\t\t\tERROR : You don't hold this much shares! Press E To Move Back : ";
			input = getch();
			cout << endl;
		}	
	}
	else
	{
		shares[loc] -= dropshares;
		*current -= (price_pstocks[loc] * dropshares);
		
		cout << "\t\t\tShares Dropped, Press B : Return | Other Key : Updated Portfolio : ";
		input = getch();
	}
	return input;
}

int main()
{
	// delcaring 2-D array of size 3X37 (3 = features, 37 = companies)
	string** stocks_data = new string*[3];
	for (int i = 0; i < 3; i++) 
		stocks_data[i] = new string[100];
		
    // reading data from companies.txt
	int rows = ReadData_Companies(stocks_data);
	
	// string to float conversion of price
	float *prices = new float[rows]; 
	float *newprices = new float[rows];
    for (int i = 0; i < rows; i++)
    {
     	prices[i] = atof(stocks_data[2][i].c_str());	
     	newprices[i] = atof(stocks_data[2][i].c_str());    	
	}
 
 	// High-Low Indicator
 	int *direction = new int[rows]; 
    for (int i = 0; i < rows; i++)
     	direction[i] = 0; 	
 	
 	char input;
 	int best = 0, worst = 0;
 
 	// delcaring 2-D array for loading portfolio file
	string** portfolio_data = new string*[3];
	for (int i = 0; i < 4; i++) 
		portfolio_data[i] = new string[100];
	
	// loading portflio data	
	float previous = 0, current = 0;
	string name = "";
	int num_stocks_portfolio = portfolio(portfolio_data, &previous, &current, &name);
	
	int* price_pstocks = new int[num_stocks_portfolio];
	int *shares = new int[num_stocks_portfolio];
	for (int i = 0; i < num_stocks_portfolio; i++)
	{
		price_pstocks[i] = atoi(portfolio_data[3][i].c_str());
		shares[i] = atoi(portfolio_data[2][i].c_str());
	}
					
	while(input != 'E')
	{
		displaymarket(stocks_data, rows, prices, newprices);
		copy(prices, newprices, rows);
		displaymenu('P');
		input = getch();
		
		updatemarket(newprices, rows);
			
		if (input == 'P')
		{	
			while(input != 'L')
			{
				system("CLS");
				displayportfolio(num_stocks_portfolio, portfolio_data, name, price_pstocks, current, previous);
				input = getch();				
			}
		}
		else if (input == 'M')
		{
			while(input != 'W' and input != 'A')
			{
				system("CLS");
				changebalance();
				input = getch();	
			}
			if (input == 'A')
			{
				cout << input;
				previous = current;
				addmoney(&current);
			}
			else if (input == 'W')
			{
				cout << input;
				previous = current;
				withdrawmoney(&current);
			}			
		}
		else if(input == 'R')
		{
			
			while(input != 'B')
			{
				system("CLS");
				input = dropstock(num_stocks_portfolio, portfolio_data, price_pstocks, shares, name, &current, previous);	
			}
		} 
		system("CLS");
	}  

    // displaying stock market
    
    // updating portfolio
	WriteData_Portfolio(name, previous, current, portfolio_data, num_stocks_portfolio, price_pstocks, shares);
	
	// writing to companies.txt before closing
	WriteData_Companies(stocks_data, rows, prices);
	
	return 0;
}


/*
# Remaining
ADD Stock to Portfolio
*/
