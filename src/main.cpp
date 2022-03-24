#include <iostream>
#include <vector>

using namespace std;

struct Box{
    int no_of_orders = 0;
    double price_per_box = 0;
    double total_price_per_size = 0;
};

enum Size_of_Container{oz8, oz16, oz32};

// struct Sales{
//     string name_of_salesperson;
//     Box container_size[3];
//     double price_total;
// }sales;
//vector<Sales> company_sales;


int number_of_container_sizes = 3;

void Inputs(string&,string&,string&,Box[]);
void Processes(Box[], double, int);
void Output();
void Order(int, Box[]);

int main(){
    string name_of_customer, name_of_salesperson, date;
    Box container_size[number_of_container_sizes];
    double price_total = 0;
    int total_orders = 0;

    Inputs(name_of_customer, name_of_salesperson, date, container_size);
    Processes(container_size, price_total, total_orders);
    Output();
    return 0;
}

void Inputs(string &name_of_customer, string &name_of_salesperson, string &date, Box container[]){
    char addOrder;
    do{
        int container_size; 
        cout << "Size of Containers (Press 1 for 8oz or 1 cup; 2 for 16oz or 2 cups; 3 for 32oz or 4 cups): ";
        cin >> container_size;
        container_size--;
        switch (container_size)
        {
            case oz8:
                Order(oz8,container);
                break;
            case oz16:
                Order(oz16,container);
                break;
            case oz32:
                Order(oz32,container);
                break;
            default:
                break;
        }
        cout << "Press + to add another order or enter to proceed.";
        cin.clear();
        cin.ignore(1000,'\n');
        cin.get(addOrder);
    }while(addOrder == '+');
}

void Processes(Box container[], double price_total, int total_orders){};
void Output(){};

void Order(int i, Box container[]){
    int no_of_orders; double price_per_box;
    cout << "No. of orders: ";
    cin >> no_of_orders; 
    container[i].no_of_orders += no_of_orders;
    cout << "Price per Box: ";
    cin >> price_per_box;
    container[i].price_per_box += price_per_box; 
}
            