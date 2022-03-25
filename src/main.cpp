#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <map>

using namespace std;


enum Size_of_Container{oz8, oz16, oz32};
enum discount_promo{promo1, promo2, promo3};
const int number_of_container_sizes = 3;

map<int, double> discount_rate {
    {promo1, 0.02 },
    {promo2, 0.05 },
    {promo3, 0.1 }
};

struct Box{
    unsigned int no_of_orders = 0;
    long double price_per_box = 0;
    long double total_price_per_size = 0;
};


struct Sales{
    string name_of_salesperson;
    string name_of_customer;
    string date;
    Box container_size[number_of_container_sizes];
    long double price_total = 0;
    long double discount = 0;
    unsigned int total_orders = 0;
};

vector<Sales> company_sales;



void Inputs(Sales&);
void Processes(Sales&);
void Output(fstream&,string, Sales&);
void Order(int, Box[]);

int main(){
    fstream receipt; string receipt_template = "Receipt.txt";
    Sales order_sale;
    
    system("cls");
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
        sale.discount = sale.price_total * discount_rate[promo1];
    }else if (16 <= sale.total_orders && sale.total_orders <= 20){
        sale.discount = sale.price_total * discount_rate[promo2];
    }else if(20 < sale.total_orders){
        sale.discount = sale.price_total * discount_rate[promo3];
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
            if(lines == "Customer's Name:"){
                cout << ' ' << sale.name_of_customer;
            }
            if(lines == "Orders:"){
                for(int i = 0; i < number_of_container_sizes; i++){
                    cout << "\n\t";
                    if(sale.container_size[i].no_of_orders != 0){
                         switch (i)
                        {
                        case oz8:
                            cout << "8 oz:";
                            break;
                        
                        case oz16:
                            cout << "16 oz:";
                            break;

                        case oz32:
                            cout << "32 oz:";
                            break;
                        
                        default:
                            break;
                        }
                        cout <<"\t" << sale.container_size[i].no_of_orders << " x "
                        << sale.container_size[i].price_per_box << "\t.....\t" << sale.container_size[i].total_price_per_size;
                    }
                }
            }
            if(lines == "Total no. Of Items:"){
                cout << " " << sale.total_orders;
            }
            if(lines.find("Subtotal:") != string::npos){
                cout << "\t" << sale.price_total;
            }
            if(lines.find("Discount:") != string::npos){
                cout << "\n\t";
                if(sale.total_orders <= 15 && sale.total_orders >= 10){
                    cout << sale.price_total << "\tx\t" << discount_rate[promo1] << "\t.....\t" << sale.discount;
                }else if (16 <= sale.total_orders && sale.total_orders <= 20){
                    cout << sale.price_total << "\tx\t" << discount_rate[promo2] << "\t.....\t" << sale.discount;
                }else if(20 < sale.total_orders){
                    cout << sale.price_total << "\tx\t" << discount_rate[promo3] << "\t.....\t" << sale.discount;
                }
                
            }
            if(lines.find("Total:") != string::npos){
                cout << "\t" << sale.price_total - sale.discount;
            }
            if(lines == "Salesperson:"){
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

