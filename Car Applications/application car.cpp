#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<limits>
using namespace std;

// Helper to safely read a full line after formatted (>>) extraction.
// Skips leading whitespace/newlines and returns the next non-empty line.
static string readNonEmptyLine(const string& prompt)
{
    string line;
    while (true)
    {
        cout << prompt;
        if (!std::getline(cin >> std::ws, line))
        {
            // Stream error/EOF; return empty and let caller decide.
            return {};
        }
        if (!line.empty())
            return line;

        cout << "Input cannot be empty. Please try again." << endl;
    }
}


class Car {
private:
    string brand;
    string model;
    int year;
    int price;

public:
    Car(const string& brand, const string& model, int year, int price) : brand(brand), model(model), year(year), price(price) {}

    string getbrand() const { return brand; }
    string getmodel() const { return model; }
    int getyear() const { return year; }
    int getprice() const { return price; }
};



void addCar(vector<Car>& cars) {
    string brand = readNonEmptyLine("Brand: ");
    if (brand.empty()) return;

    string model = readNonEmptyLine("Model: ");
    if (model.empty()) return;

    int year;
    cout << "Year: ";
    cin >> year;

    int price;
    cout << "Price: ";
    cin >> price;

    // Clear trailing newline so subsequent line-based reads behave correctly.
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cars.emplace_back(brand, model, year, price);
    cout << "Car added." << endl;
}

void listCars(const vector<Car>& cars) {
    for (const auto& car : cars) {
        cout << car.getbrand() << " " << car.getmodel() << " " << car.getyear() << " " << car.getprice() << "TL" << endl;
    }
}

void searchCars(const vector<Car>& cars) {
    string query = readNonEmptyLine("Search: ");
    if (query.empty()) return;

    for (const auto& car : cars) {
        if (car.getbrand().find(query) != string::npos || car.getmodel().find(query) != string::npos) {
            cout << car.getbrand() << " " << car.getmodel() << " " << car.getyear() << " " << car.getprice() << "TL" << endl;
        }
    }
}

void removeCar(vector<Car>& cars) {
    string brand = readNonEmptyLine("Brand: ");
    if (brand.empty()) return;

    string model = readNonEmptyLine("Model: ");
    if (model.empty()) return;

    cars.erase(remove_if(cars.begin(), cars.end(), [&](const Car& car) {
        return car.getbrand() == brand && car.getmodel() == model;
        }), cars.end());
    cout << "Car removed." << endl;
}



int main() {
    vector<Car> cars;
    while (true) {
        cout << "\n1.Add\n2.List\n3.Search\n4.Remove\n5.Exit\n";
        int choice;
        cin >> choice;

        // Clear trailing newline so later getline calls (inside handlers) behave correctly.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) addCar(cars);
        else if (choice == 2) listCars(cars);
        else if (choice == 3) searchCars(cars);
        else if (choice == 4) removeCar(cars);
        else if (choice == 5) break;
    }



    return 0;
}