#include <bits/stdc++.h>
#include <fstream>
using namespace std;

using namespace std;

class student{
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


    void getdata(){
            string temp;
            cout<<"ENter Name\n";
            getline(cin,name);
            cout<<"Enter Roll number\n";
            getline(cin,temp);
            rollno=stoi(temp);
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
    void addrecord(){
        file.open("data.txt",ios::app |ios::binary);
        if(!file){
            cerr << "Error opening file for append\n";
            return;
        }

        s.getdata();
        file.write((char* ) (&s),sizeof(s));
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

        while(file.read((char*) &s,sizeof(s))){
            s.show();

        }
        file.close();

    }

    void remove1()
    {
        // int roll;
        // cout<<"Ente roll"<<endl;
        // cin>>roll;
        // cin.ignore(numeric_limits<streamsize>:: max(),'\n');
            int roll;
            string r;
            cout<<"Enter roll number\n";
            getline(cin,r);
            roll=stoi(r);
            file.open("data.txt", ios::in | ios::binary);

            fstream temp("temp.txt",ios::out|ios::binary);
            if (!file || !temp)
            {
                cerr << "File error\n";
                return;
            }
    
            bool found = false;

            while(file.read((char *)(&s), sizeof(s))){

                if(s.rollno!=roll){
                    temp.write((char*) (& s), sizeof(s));
                }else{
                    found = true;
                    cout << "RECORD DELETED:\n";
                    s.show();
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

int main(){



    return 0;

}