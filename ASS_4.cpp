#include <iostream>
#include <string>
using namespace std;

const int SIZE = 10;
const int DELETED = -1;

class DataItem {
public:
    string key;
    int data;

    DataItem(string k = "", int d = -1) : key(k), data(d) {}
};

DataItem* hashArray[SIZE];
DataItem* dummyItem = new DataItem("dummy", -1);

int hashCode( string &key){
	if(key.empty()) return 0;
	cout<<"ASCII: "<<static_cast<int> (key[0])<<endl;
	return static_cast<int> (key[0])%SIZE;

}

void insertWithReplacement(string key, int data) {
    DataItem* item = new DataItem(key, data);
    int hashIndex = hashCode(key);

    cout << "Key: " << key << " Value: " << data << endl;
    cout << "HashCode: " << hashIndex << endl;

    if (hashArray[hashIndex] != nullptr && hashCode(hashArray[hashIndex]->key) != hashIndex) {
        DataItem* temp = hashArray[hashIndex];
        hashArray[hashIndex] = item;
        item = temp;
        cout << "Replaced" << endl;
    }

    while (hashArray[hashIndex] != nullptr) {
        ++hashIndex;
        hashIndex %= SIZE;
    }

    hashArray[hashIndex] = item;
    cout << "Inserted at index " << hashIndex << endl;
}



void insertWithReplacementt(string key,int data)
{
	DataItem* item= new DataItem(key,data);
	int hashIndex=hashCode(key);

    cout << "Key: " << key << " Value: " << data << endl;
    cout << "HashCode: " << hashIndex << endl;
	int count=0;
	if(hashArray[hashIndex]!=nullptr && hashCode(hashArray[hashIndex]->key) != hashIndex){
		DataItem* temp= hashArray[hashIndex];
		hashArray[hashIndex]=item;
		item=temp;
        cout << "Replaced" << endl;
	}

	while(hashArray[hashIndex]!=nullptr || hashArray[hashIndex]!=dummyItem){
		++hashIndex;
		hashIndex%=SIZE;
        
	}
	hashArray[hashIndex]=item;
    cout << "Inserted at index " << hashIndex << endl;

}

void insertWithoutReplacementt(string key,int data){
	DataItem *item=new DataItem(key,data);
	int hashIndex=hashCode(key);

    cout << "Key: " << key << " Value: " << data << endl;
    cout << "HashCode: " << hashIndex << endl;
	int count=0;
	while(count<SIZE && hashArray[hashIndex]!=nullptr && hashArray[hashIndex]->key!="dummy"){
		++hashIndex;
		count++;
		hashIndex%=SIZE;

	}

	hashArray[hashIndex]=item;
	cout<<"Insted at index "<<hashIndex<<endl;

}
void insertWithoutReplacement(string key, int data) {
    DataItem* item = new DataItem(key, data);
    int hashIndex = hashCode(key);

    cout << "Key: " << key << " Value: " << data << endl;
    cout << "HashCode: " << hashIndex << endl;
    int count=0;
    while (count<SIZE && hashArray[hashIndex] != nullptr && hashArray[hashIndex]->key != "dummy") {
        ++hashIndex;
        count++;
        hashIndex %= SIZE;
    }

    hashArray[hashIndex] = item;
    cout << "Inserted at index " << hashIndex << endl;
}

int search(string key, bool withReplacement) {
    int hashIndex = hashCode(key);
    int comparisons = 0;

    while (hashArray[hashIndex] != nullptr) {
        comparisons++;
        if (hashArray[hashIndex]->key == key) {
            cout << "Found item with key " << key << " at index " << hashIndex << endl;
            cout << "Comparisons made: " << comparisons << endl;
            return comparisons;
        }
        ++hashIndex;
        hashIndex %= SIZE;
    }
    cout << "Item with key " << key << " not found!" << endl;
    return comparisons;
}



DataItem* deleteItem(string key) {
    int hashIndex = hashCode(key);

    while (hashArray[hashIndex] != nullptr) {
        if (hashArray[hashIndex]->key == key) {
            DataItem* temp = hashArray[hashIndex];
            hashArray[hashIndex] = dummyItem;
            cout << "Item with key " << key << " deleted from index " << hashIndex << endl;
            return temp;
        }
        ++hashIndex;
        hashIndex %= SIZE;
    }

    cout << "Item with key " << key << " not found!" << endl;
    return nullptr;
}

void display() {
    for (int i = 0; i < SIZE; i++) {
        if (hashArray[i] != nullptr || hashArray[i]->key == "dummy") {
            cout << "Index " << i << ": Key = " << hashArray[i]->key << ", Data = " << hashArray[i]->data << endl;
        } else {
            cout << "Index " << i << ": [empty]" << endl;
        }
    }
}

int main() {
    for (int i = 0; i < SIZE; i++) {
        hashArray[i] = nullptr;
    }

    int choice;
    string key;
    int data;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert with replacement\n";
        cout << "2. Insert without replacement\n";
        cout << "3. Search\n";
        cout << "4. Delete\n";
        cout << "5. Display\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key (string): ";
                cin >> key;
                cout << "Enter data (int): ";
                cin >> data;
                insertWithReplacement(key, data);
                break;
            case 2:
                cout << "Enter key (string): ";
                cin >> key;
                cout << "Enter data (int): ";
                cin >> data;
                insertWithoutReplacement(key, data);
                break;
            case 3:
                cout << "Enter key (string) to search: ";
                cin >> key;
                search(key, true);
                break;
            case 4:
                cout << "Enter ke   y (string) to delete: ";
                cin >> key;
                deleteItem(key);
                break;
            case 5:
                display();
                break;
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice, try again." << endl;
                break;
        }
    } while (choice != 6);

    return 0;
}
