#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


enum Size_of_Container{oz8, oz16, oz32};

struct Box{
    int no_of_orders = 0;
    double price_per_box = 0;
    double total_price_per_size = 0;
};


struct Sales{
    string name_of_salesperson;
    string name_of_customer;
    string date;
    Box container_size[3];
    double price_total;
    double discount;
    int total_orders;
};

vector<Sales> company_sales;

const int number_of_container_sizes = 3;

void Inputs(Sales&);
void Processes(Sales&);
void Output(fstream&,string, Sales&);
void Order(int, Box[]);

int main(){
    fstream receipt; string receipt_template = "Receipt.txt";
    Sales order_sale;
    
    Box container_size[number_of_container_sizes];

    Inputs(order_sale);
    Processes(order_sale);
    Output(receipt,receipt_template,order_sale);
    return 0;
}

void Inputs(Sales &sale){
    bool isFail = false;

    char addOrder;
    do{
        int container_size; 

        do{
            isFail = false;
            cout << "Size of Containers (Press 1 for 8oz or 1 cup; 2 for 16oz or 2 cups; 3 for 32oz or 4 cups): ";
            if(!(cin >> container_size) || container_size < 1 || container_size >3){
                cout << "Unknown Value Input. Please Try Again." << endl;
                cin.clear();
                cin.ignore(1000,'\n');
                isFail = true;
            }
        }while(isFail);

        container_size--;
        switch (container_size)
        {
            case oz8:
                Order(oz8,sale.container_size);
                break;
            case oz16:
                Order(oz16,sale.container_size);
                break;
            case oz32:
                Order(oz32,sale.container_size);
                break;
            default:
                break;
        }
        
        
        do{
            cout << "Press + to add another order or enter to proceed: ";
            cin.clear();
            cin.ignore(1000,'\n');
            cin.get(addOrder);
        }while(!(addOrder == 10 || addOrder == '+')); 
    
    }while(addOrder == '+');

    cout << "Customer's Name: ";
    getline(cin, sale.name_of_customer);
    cout << "Date: ";
    cin >> sale.date;
    cin.ignore();
    cout << "Salesperson: ";
    getline(cin, sale.name_of_salesperson);
}

void Processes(Sales &sale){

    for(int i = 0; i < number_of_container_sizes; i++){
        sale.container_size[i].total_price_per_size = sale.container_size[i].no_of_orders * sale.container_size[i].price_per_box;
    }

    for(int i = 0; i < number_of_container_sizes; i++){
        sale.price_total += sale.container_size[i].total_price_per_size;
        sale.total_orders += sale.container_size[i].no_of_orders;
    }

    if(sale.total_orders <= 15 && sale.total_orders >= 10){
        sale.discount = sale.price_total * 0.02;
    }else if (16 <= sale.total_orders && sale.total_orders <= 20){
        sale.discount = sale.price_total * 0.05;
    }else if(20 < sale.total_orders){
        sale.discount = sale.price_total * 0.1;
    }
}

void Output(fstream &receipt, string receipt_template, Sales& sale){
    string lines;
    receipt.open(receipt_template,ios::in);
    if(!receipt){
        cout << "Receipt Template could not be found. Please contact the system administrator.";
    }
    else{
        while(getline(receipt,lines)){
            cout << lines;
            if(lines == "Date:"){
                cout << ' ' <<sale.date; 
            }
            else if(lines == "Customer's Name:"){
                cout << ' ' << sale.name_of_customer;
            }
            else if(lines == "Orders:"){
                for(int i = 0; i < number_of_container_sizes; i++){
                    cout <<"\n\t" << sale.container_size[i].no_of_orders << "\tx\t"
                    << sale.container_size[i].price_per_box << "\t....." << sale.container_size[i].total_price_per_size;
                }
            }
            else if(lines == "Salesperson:"){
                cout << ' ' << sale.name_of_salesperson;
            }
            cout << endl;
        }
    }
};

void Order(int i, Box container[]){
    int no_of_orders; double price_per_box; bool isFail;
    
    do{
        cout << "No. of orders: ";
        isFail = false;
        if(!(cin >> no_of_orders || no_of_orders < 0)){
            cout << "Unknown Value Input. Please Try Again." << endl;
                    cin.clear();
                    cin.ignore(1000,'\n');
                    isFail = true;
        } 
    }while(isFail);

    container[i].no_of_orders = no_of_orders;
    
    do{
        isFail = false;
        cout << "Price per Box: ";
        if(!(cin >> price_per_box || price_per_box < 0)){
            cout << "Unknown Value Input. Please Try Again." << endl;
                    cin.clear();
                    cin.ignore(1000,'\n');
                    isFail = true;
        } 
    }while(isFail);
    
    container[i].price_per_box = price_per_box; 
}

