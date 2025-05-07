#include <bits/stdc++.h>
#include <fstream>
using namespace std;

class student
{
public:
    int rollno;
    string name;
    string division;
    string address;

    void show()
    {
        cout << "--------------------------\n";
        cout << "NAME     : " << name << '\n';
        cout << "ROLL     : " << rollno << '\n';
        cout << "DIVISION : " << division << '\n';
        cout << "ADDRESS  : " << address << '\n';
    }

    void getdata()
    {
        string tmp;

        cout << "ENTER NAME\n> ";
        getline(cin, name);

        cout << "ENTER ROLL NO\n> ";
        getline(cin, tmp);
        rollno = stoi(tmp);

        cout << "ENTER DIVISION\n> ";
        getline(cin, division);

        cout << "ENTER ADDRESS\n> ";
        getline(cin, address);
    }
};

class Myfile
{
    fstream file;
    student s;

public:
    void addrecord()
    {
        file.open("data.txt", ios::app | ios::binary);
        if (!file)
        {
            cerr << "Error opening file for append\n";
            return;
        }
        s.getdata();
        file.write((char *)(&s), sizeof(s));
        cout << "ADDED:\n";
        s.show();
        file.close();
    }

    void showfile()
    {
        file.open("data.txt", ios::in | ios::binary);
        if (!file)
        {
            cerr << "Error opening file for read\n";
            return;
        }



        cout << "\n=== ALL RECORDS ===\n";
        while (file.read((char *)(&s), sizeof(s)))
        {
            s.show();
        }
        file.close();
    }

    void remove1()
    {
        int roll;
        cout << "ENTER ROLL NO TO DELETE:\n> ";
        cin >> roll;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush before next getline

        file.open("data.txt", ios::in | ios::binary);
        fstream temp("temp.txt", ios::out | ios::binary);
        if (!file || !temp)
        {
            cerr << "File error\n";
            return;
        }

        bool found = false;
        while (file.read((char *)(&s), sizeof(s)))
        {

            if (s.rollno == roll)
            {
                found = true;
                cout << "RECORD DELETED:\n";
                s.show();
            }
            
            else
            {
                temp.write((char *)(&s), sizeof(s));
            }
        }

        file.close();
        temp.close();
        remove("data.txt");
        rename("temp.txt", "data.txt");

        if (!found)
            cout << "RECORD NOT FOUND\n";
    }

    void displayOne()
    {
        int roll;
        cout << "ENTER ROLL NO TO DISPLAY:\n> ";
        cin >> roll;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush

        file.open("data.txt", ios::in | ios::binary);
        if (!file)
        {
            cerr << "Error opening file for read\n";
            return;
        }

        bool found = false;
        while (file.read((char *)(&s), sizeof(s)))
        {
            if (s.rollno == roll)
            {
                cout << "\n-- RECORD FOUND --\n";
                s.show();
                found = true;
                break;
            }
        }

        if (!found)
            cout << "RECORD NOT FOUND\n";

        file.close();
    }
};

int main()
{
    Myfile m;
    int choice;
    do
    {
        cout << "\n1. Add Record\n"
             << "2. Show All Records\n"
             << "3. Delete Record\n"
             << "4. Display One Record\n"
             << "5. Exit\n"
             << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            m.addrecord();
            break;
        case 2:
            m.showfile();
            break;
        case 3:
            m.remove1();
            break;
        case 4:
            m.displayOne();
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice\n";
        }
    } while (choice != 5);

    return 0;
}
