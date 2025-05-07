#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int MAX_NAME = 30;
const int MAX_ADDR = 50;
const int TABLE_SIZE = 100;

class Employee {
public:
    int empID;
    bool active;
    char name[MAX_NAME];
    char address[MAX_ADDR];

    Employee() {
        empID = 0;
        active = false;
        memset(name, 0, MAX_NAME);
        memset(address, 0, MAX_ADDR);
    }
};

int hashFn(int id) {
    return id % TABLE_SIZE;
}

fstream openFile(const char* filename) {
    fstream file(filename, ios::in | ios::out | ios::binary);
    if (!file) {
        file.open(filename, ios::out | ios::binary);
        Employee blank;
        for (int i = 0; i < TABLE_SIZE; ++i)
            file.write((char*)(&blank), sizeof(blank));
        file.close();
        file.open(filename, ios::in | ios::out | ios::binary);
    }
    return file;
}

int findSlot(fstream& file, int empID) {
    int hash = hashFn(empID);
    for (int i = 0; i < TABLE_SIZE; ++i) {
        int slot = (hash + i) % TABLE_SIZE;
        file.seekg(slot * sizeof(Employee));
        Employee temp;
        file.read((char*)(&temp), sizeof(temp));
        if (!temp.active || temp.empID == empID)
            return slot;
    }
    return -1;
}

void insertRecord(const char* filename) {
    fstream file = openFile(filename);
    Employee emp;

    cout << "ID: "; cin >> emp.empID;
    cin.ignore();
    cout << "Name: "; cin.getline(emp.name, MAX_NAME);
    cout << "Address: "; cin.getline(emp.address, MAX_ADDR);
    emp.active = true;

    int slot = findSlot(file, emp.empID);
    if (slot >= 0) {
        file.seekp(slot * sizeof(Employee));
        file.write((char*)(&emp), sizeof(emp));
        cout << "Inserted at slot " << slot << "\n";
    } else {
        cout << "Hash table full!\n";
    }

    file.close();
}

void deleteRecord(const char* filename) {
    fstream file = openFile(filename);
    int id;
    cout << "Delete ID: "; cin >> id;

    int slot = findSlot(file, id);
    if (slot >= 0) {
        file.seekg(slot * sizeof(Employee));
        Employee emp;
        file.read((char*)(&emp), sizeof(emp));
        if (emp.active && emp.empID == id) {
            emp.active = false;
            file.seekp(slot * sizeof(Employee));
            file.write((char*)(&emp), sizeof(emp));
            cout << "Deleted slot " << slot << "\n";
        } else {
            cout << "Record not found.\n";
        }
    } else {
        cout << "Record not found.\n";
    }

    file.close();
}

void displayRecord(const char* filename) {
    fstream file = openFile(filename);
    int id;
    cout << "Find ID: "; cin >> id;

    int slot = findSlot(file, id);
    if (slot >= 0) {
        file.seekg(slot * sizeof(Employee));
        Employee emp;
        file.read((char*)(&emp), sizeof(emp));
        if (emp.active && emp.empID == id) {
            cout << "ID: " << emp.empID << ", Name: " << emp.name << ", Address: " << emp.address << "\n";
        } else {
            cout << "Record not found.\n";
        }
    } else {
        cout << "Record not found.\n";
    }

    file.close();
}

int main() {
    const char* filename = "employee.dat";
    int choice;
    do {
        cout << "\n1) Insert  2) Delete  3) Display  4) Exit\n> ";
        cin >> choice;
        switch (choice) {
            case 1: insertRecord(filename); break;
            case 2: deleteRecord(filename); break;
            case 3: displayRecord(filename); break;
        }
    } while (choice != 4);
    return 0;
}
