#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

class Item {
public:
    string name;
    double price;
    int quantity;

    Item(string n, double p, int q) : name(n), price(p), quantity(q) {}
};

class SupermarketBilling {
private:
    vector<Item> items;

    void saveToFile() {
        ofstream file("items.txt");
        for (const auto& item : items) {
            file << item.name << " " << item.price << " " << item.quantity << endl;
        }
        file.close();
    }

    void loadFromFile() {
        ifstream file("items.txt");
        if (file.is_open()) {
            string name;
            double price;
            int quantity;
            while (file >> name >> price >> quantity) {
                items.push_back(Item(name, price, quantity));
            }
            file.close();
        }
    }

public:
    SupermarketBilling() {
        loadFromFile();
    }

    ~SupermarketBilling() {
        saveToFile();
    }

    void addItem(string name, double price, int quantity) {
        items.push_back(Item(name, price, quantity));
    }

    void displayItems() {
        cout <<setw(20)<<"Item"
             <<setw(10)<<"Price"
             <<setw(10)<<"Quantity"
             <<setw(10)<<"Total"<<endl;
        double grandTotal = 0;
        for (const auto& item : items) {
            double total = item.price * item.quantity;
            grandTotal += total;
            cout <<setw(20)<<item.name
                 <<setw(10)<<item.price
                 <<setw(10)<<item.quantity
                 <<setw(10)<<total<<endl;
        }
        cout<<setw(50)<<"Grand Total: "<<grandTotal<<endl;
    }
};

int main() {
    SupermarketBilling billingSystem;
    int choice;
    do {
        cout<<"1. Add Item\n2. Display Items\n3. Exit\nEnter your choice: ";
        cin>>choice;

        switch (choice) {
            case 1: {
                string name;
                double price;
                int quantity;
                cout<<"Enter item name: ";
                cin>>name;
                cout<<"Enter item price: ";
                cin>>price;
                cout<<"Enter item quantity: ";
                cin>>quantity;
                billingSystem.addItem(name, price, quantity);
                break;
            }
            case 2:
                billingSystem.displayItems();
                break;
            case 3:
                cout << "Exiting..."<< endl;
                break;
            default:
                cout <<"Invalid choice. Try again."<< endl;
        }
    } while (choice!=3);

    return 0;
}
