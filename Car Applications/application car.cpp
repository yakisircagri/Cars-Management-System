#include <iostream>
#include<string>
#include<iomanip>
#include<vector>
#include<cstdlib>
#include<limits>

using namespace std;

static int readInt(const std::string& prompt)
{
	while (true)
	{
		cout << prompt;
		int value;
		if (cin >> value)
		{
			return value;
		}

		// Handle non-numeric input: clear fail state and discard the line.
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Please enter a number." << endl;
	}
}

// CLASSES

class Car {
public:
	string carName;
	int carModel;
	int carPrice;
};

class Member {
public:
	string MemberName;
	string MemberSurname;
	string MemberAdress;
	int MemberID;
};

//Vector

vector<Car> cars;
vector<Member> members;

//ADDING

void CarAdd() {
	Car car;
	cout << "Enter car name: ";
	cin>> car.carName;
	cout << "Enter car model: ";
	cin >> car.carModel;
	cout << "Enter car price: ";
	cin >> car.carPrice;
	cout << "Car added succesfully." << endl;

	cars.push_back(car);
}

void MemberAdd() {
	Member member;
	cout << "Enter member name: ";
	cin >> member.MemberName;
	cout << "Enter member surname: ";
	cin >> member.MemberSurname;
	cout << "Enter member adress: ";
	cin>> member.MemberAdress;
	cout << "Enter member ID: ";
	cin>> member.MemberID;
	cout << "Member added succesfully."<<endl;
	members.push_back(member);
}

//LISTING

void CarsList() {
	cout << "Cars" << endl;
	cout << left << setw(20) << "Name" << setw(10) << "Model" << setw(10) << "Price" << endl;
	cout << setfill('-') << setw(40) << "" << setfill(' ') << endl;

	for (const auto& car : cars) {
		cout << left << setw(20) << car.carName << setw(10) << car.carModel << setw(10) << car.carPrice << endl;
	}
}

void MemberList() {
	cout << "Members" << endl;
	cout << left << setw(20) << "Name" << setw(10) << "Surname" << setw(20) << "Adress" << setw(10) << "ID" << endl;
	cout << setfill('-') << setw(60) << "" << setfill(' ') << endl;

	for (const auto& member : members) {
		cout << left << setw(20) << member.MemberName << setw(10) << member.MemberSurname << setw(20) << member.MemberAdress << setw(10) << member.MemberID << endl;
	}
}


//SEARCH


void SearchCar() {
	string searchName;
	cout << "Enter car name to search: ";
	cin >> searchName;

	for (const auto& car : cars) {
		if (car.carName == searchName) {
			cout << "Car found." << endl;
			cout << left << setw(20) << "Name" << setw(10) << "Model" << setw(10) << "Price" << endl;
			cout << setfill('-') << setw(40) << "" << setfill(' ') << endl;
			cout << left << setw(20) << car.carName << setw(10) << car.carModel << setw(10) << car.carPrice << endl;
			return;
		}
	}

	cout << "Car not found." << endl;
}

void SearchMember() {
	int searchID;
	cout << "Enter member ID to search: ";
	cin >> searchID;

	for (const auto& member : members) {
		if (member.MemberID == searchID) {
			cout << "Member found." << endl;
			cout << left << setw(20) << "Name" << setw(10) << "Surname" << setw(20) << "Adress" << setw(10) << "ID" << endl;
			cout << setfill('-') << setw(60) << "" << setfill(' ') << endl;
			cout << left << setw(20) << member.MemberName << setw(10) << member.MemberSurname << setw(20) << member.MemberAdress << setw(10) << member.MemberID << endl;
			return;
		}
	}

	cout << "Member not found." << endl;
}

//DELETE
void DeleteCar() {
	string deleteName;
	cout << "Enter car name to delete: ";
	cin >> deleteName;

	for (auto it = cars.begin(); it != cars.end(); ++it) {
		if (it->carName == deleteName) {
			cars.erase(it);
			cout << "Car deleted successfully." << endl;
			return;
		}
	}

	cout << "Car not found." << endl;
}

void DeleteMember() {
	int deleteID;
	cout << "Enter member ID to delete: ";
	cin >> deleteID;

	for (auto it = members.begin(); it != members.end(); ++it) {
		if (it->MemberID == deleteID) {
			members.erase(it);
			cout << "Member deleted successfully." << endl;
			return;
		}
	}

	cout << "Member not found." << endl;
}


int main() {
	int choice;

	while (true) {
		cout << "\nCar Management System" << endl;
		cout << "1. Add Car" << endl;
		cout << "2. Add Member" << endl;
		cout << "3. List Cars" << endl;
		cout << "4. List Members" << endl;
		cout << "5. Search Car" << endl;
		cout << "6. Search Member" << endl;
		cout << "7. Delete Car" << endl;
		cout << "8. Delete Member" << endl;
		cout << "9. Exit" << endl;

		choice = readInt("Enter your choice: ");

		switch (choice) {
		case 1:
			CarAdd();
			break;
		case 2:
			MemberAdd();
			break;
		case 3:
			CarsList();
			break;
		case 4:
			MemberList();
			break;
		case 5:
			SearchCar();
			break;
		case 6:
			SearchMember();
			break;
		case 7:
			DeleteCar();
			break;
		case 8:
			DeleteMember();
			break;
		case 9:
			cout << "Exiting program." << endl;
			return 0;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	}

	return 0;
}
