#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

enum CategoryOfItem {
	Medicine, Food, Book, Others
};

class Item {
	private:
		int quantity;
		CategoryOfItem itemCategory;
		double price;
		bool imported;

	public:

		Item(int, CategoryOfItem, double, bool);
		bool getImported() { return imported; }
		int getQuantity()  { return quantity; }
		double getPrice()   { return (quantity * price); }
		CategoryOfItem getItemCategoryy() { return itemCategory; }
};

Item::Item( int quantity, CategoryOfItem category, double price, bool imported ){
	
	this->quantity = quantity;
	this->itemCategory = category;
	this->price = price;
	this->imported = imported;
} 

class Tax {
	private:
		const double BASIC_RATE  = 0.1;
		const double IMPORT_RATE = 0.05;

		double roundOff(double price);

	public:
		double getTaxOnItem(Item item);
};

double Tax::roundOff(double price)  {

	return ceil(price * 20)/20;
}

double Tax::getTaxOnItem(Item item) {

	double tax = 0.0;

	if ( item.getImported() ) {
		tax += roundOff(item.getPrice() * IMPORT_RATE) ;
	}

	if ( item.getItemCategoryy() == CategoryOfItem::Others ){
		tax += roundOff(item.getPrice() * BASIC_RATE) ;
	}

	return tax;
}

void generateBill(vector<Item> &order, vector<string> &totalOrder ) {

	cout << "\n-----------------------------------------------------------------------";
	double totalTax = 0.0;
	double totalSales = 0.0;

	for (int i=0; i<totalOrder.size(); i++) {
		Tax t;
		cout << "\n" << totalOrder[i] << ": " << t.getTaxOnItem(order[i]) + order[i].getPrice() ;
		totalTax += t.getTaxOnItem(order[i]) ;
		totalSales += order[i].getPrice() ;
	}
	totalSales += totalTax;
	cout << "\nSales Taxes: " << totalTax;
	cout << "\nGrand Total: " << totalSales ;
	cout << "\n-----------------------------------------------------------------------\n";
}

int main() {

	cout << "\nType Done to stop adding items.\n\n";
	string s;

	vector<Item> order;
	vector<string> totalOrder;

	while(getline(cin, s)) {
		
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		if ( s == "done")
			break;

		stringstream ss(s);
		
		int i=0;
		while ( i<s.size() && s[i] != ' ')
			i++;

		int quantity = stoi(s.substr(0, i));
		string temp;
		bool imported = false;
		CategoryOfItem category = CategoryOfItem::Others;

		while( ss >> temp ) {

			if ( temp == "imported" )
				imported = true;

			if ( temp == "chocolate" || temp == "chocolates" ) 
				category = CategoryOfItem::Food;

			else if ( temp == "pills" )
				category = CategoryOfItem::Medicine;

			else if ( temp == "book" )
				category = CategoryOfItem::Book;
		}

		double price = stod(temp);

		int len = s.size() - temp.size() - 4;
		totalOrder.push_back(s.substr(0,len));
		order.push_back(Item(quantity,category,price, imported));
	}

	generateBill(order, totalOrder);

	return 0; 
}
