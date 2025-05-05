
// 5 . Implement all the functions of a dictionary (ADT) using open hashing
//technique: separate chaining using linked list Data: Set of (key, value)
//pairs, Keys are mapped to values, Keys must be comparable, and Keys
//must be unique. Standard Operations: Insert(key, value), Find(key), Delete(key)

#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    string key, value;
    Node* next;

    Node(string key, string value) {
        this->key = key;
        this->value = value;
        this->next = nullptr;
    }
};

class Hash {
    Node** arr;
    int size;

public:
    Hash(int size) {
        this->size = size;
        arr = new Node*[size];
        for (int i = 0; i < size; i++) {
            arr[i] = nullptr;
        }
    }

    int hashFunction(string key) {
        int ascii = 0;
        for (char ch : key) {
            ascii += ch;
        }
        return ascii % size;
    }

    void insert(string key, string value) {
        int idx = hashFunction(key);
        Node* newNode = new Node(key, value);

        if (!arr[idx]) {
            arr[idx] = newNode;
        } else {
            Node* curr = arr[idx];
            while (curr->next) {
                curr = curr->next;
            }
            curr->next = newNode;
        }
    }

    bool search(string key) {
        int idx = hashFunction(key);
        Node* curr = arr[idx];

        while (curr) {
            if (curr->key == key) {
                cout << "Found: " << curr->value << endl;
                return true;
            }
            curr = curr->next;
        }
        cout << "Not Found" << endl;
        return false;
    }

    void delete_key(string key) {
        int idx = hashFunction(key);
        Node* curr = arr[idx];
        Node* prev = nullptr;

        while (curr) {
            if (curr->key == key) {
                if (prev) {
                    prev->next = curr->next;
                } else {
                    arr[idx] = curr->next;
                }
                delete curr;
                cout << "Deleted Successfully" << endl;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        cout << "Key not found" << endl;
    }
    void display(){
        // cout<<arr[0]<<"Displaying value"<<endl;
        vector<int> vec(10);
        
        for(int i=0;i<size;i++){
                if(arr[i]==nullptr){
                    cout<<i<<"->"<<"null"<<endl;
                }else{
                   cout<<i;
                   Node* temp=arr[i];
                   while(temp){
                    cout<<"->"<<"["<<temp->key<<":"<<temp->value<<"]";
                    temp=temp->next;
                   }
                   cout<<endl;

                }
        }


    }
};

int main() {
    int size;
    cout << "Enter the size of the dictionary: ";
    cin >> size;
    Hash dictionary(size);

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert\n2. Search\n3. Delete\n4. display\n5. Exit\nChoose an option: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string key, value;
            cout << "Enter the word and its meaning: ";
            cin >> key >> value;
            dictionary.insert(key, value);
        } else if (choice == 2) {
            string key;
            cout << "Enter the word to search: ";
            cin >> key;
            dictionary.search(key);
        } else if (choice == 3) {
            string key;
            cout << "Enter the word to delete: ";
            cin >> key;
            dictionary.delete_key(key);
        } else if(choice==4){
            dictionary.display();
        }else if (choice == 5) {
            cout << "Exiting..." << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
         }
    }
    return 0;
}