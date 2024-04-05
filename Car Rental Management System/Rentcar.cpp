#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <forward_list>

using namespace std;

class Customer{
	public:
	string name;
	string info;
	
	forward_list<string> rentedCars;
	
	Customer(string n, string i){
	name = n;
	info = i;
	
}
	
	string getName() const { return name; }
    string getInfo() const { return info; }
    

    void addRentedCar(const string& carInfo) {
        rentedCars.push_front(carInfo);
    }


    void displayRentedCars() const {
        cout << "Rented vehicles:" << endl;
        for (const auto& car : rentedCars) {
            cout << car << endl << endl;
        }
    }
	
};

class Car{
	public:
	string type;
	string brand;
    string model;
    string category;
    int year;
    bool available;

    Car(const string type, const string brand, const string model, int year,bool available)
        : type(type), brand(brand), model(model), category(category), year(year), available(available) {}
        	
};


class CarList {
private:
    forward_list<Car> cars;
    forward_list<Customer> customers;
    

public:
	    
   void loadCarsFromFile(const string& filename, const string& filterType) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "File could not be opened: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string type, brand, model;
        int year;
        getline(ss, type, ',');
        getline(ss, brand, ',');
        getline(ss, model, ',');
        ss >> year;

        if (type == filterType || filterType.empty()) {
            cars.emplace_front(type, brand, model, year, true);
        }
    }

    file.close();
}


  void addCustomer(const string& name, const string& info) {
        customers.emplace_front(name, info);
        cout << "New customer added successfully." << endl;
    }
 
void displayAll(){
	
	    cout << "Available Car List:" << endl;
        for (const auto& car : cars) {
            cout << car.type << " - " << car.brand << " " << car.model << " (" << car.year << ")";
            cout << (car.available ? " - Available" : " - For Rent") << endl;
        }
        cout << endl;
    }

  
void displayCarList(const string& filterType) const {
       cout << "Available Car List:" << endl;
    for (const auto& car : cars) {
        if (filterType.empty() || car.type == filterType) {
            cout << car.type << " - " << car.brand << " " << car.model << " (" << car.year << ")";
            cout << (car.available ? " - Available" : " - For Rent") << endl;
        }
    }
    cout << endl;
}


    void rentCar(const string &brand, const string &model, Customer &customer) {
        for (auto &car : cars) {
            if (car.brand == brand && car.model == model && car.available) {
                car.available = false;
                customer.addRentedCar(car.brand + " " + car.model);
                cout << "Car rental process successful." << endl;
                return;
            }
        }
        cout << "This car is not available or has already been rented." << endl;
    }
    
    void returnCar(const string &brand, const string &model){
    	for (auto &car : cars) {
            if (car.brand == brand && car.model == model && !car.available) {
                car.available = true;
                cout << "Car return process successful." << endl;
                return;
            }
        }
        cout << "This car is available or has already been rented." << endl;
    }
	



};

int main(){
	int choice=0;
	string brand,model;
	string filterType;
	string name,info;
	
	cout <<"---EliteDrive---"<<endl;
	cout<<"Enter Name and Adress"<<endl;
	getline(cin, name);
	getline(cin, info);
	Customer customer(name,info);
	
	CarList carList;
    carList.loadCarsFromFile("cars.txt","");
	
    
    do {
    	
    	
		cout <<"1.Show car list"<<endl;
    	cout <<"2.Rent a car"<<endl;
    	cout <<"3.Return car"<<endl;
    	cout <<"4.Show car history"<<endl;
    	cout <<"5.Add new customer"<<endl;
    	cout <<"6.Exit"<<endl<<endl;
    	
    	cin>>choice;
    	
        switch(choice){
        	case 1: 
        
        carList.displayAll();
        	break;
        	
        	case 2: 
        cout<<"Enter car type"<<endl;
        cin>>filterType;;
        
        carList.displayCarList(filterType);
        cout<<"Enter car brand"<<endl;
		cin>>brand;
		cout<<"Enter model"<<endl;
		cin>>model;
		carList.rentCar(brand,model,customer);
			
        		break;
        		
        	case 3:
        	
		cout<<"Enter car brand"<<endl;
		cin>>brand;
		cout<<"Enter model"<<endl;
		cin>>model;
		carList.returnCar(brand,model);	
		
		    break;
		        
			case 4:
		
		 customer.displayRentedCars();		
	
			break;
			
			
			case 5:
	    cout<<"Enter Name and Adress"<<endl;
	    cin>>name;
	    cin>>info;	
		    
			break;
		
				
		}
           
	}
    while(choice!=6);
	
	cout<<"Exiting..."<<endl;
    

return 0;

}