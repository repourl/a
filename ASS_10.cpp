#include <iostream>
using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if (left <= n && arr[left] > arr[largest])
        largest = left;
    if (right <= n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void buildMaxHeap(int arr[], int n) {
    for (int i = n / 2; i >= 1; i--)
        heapify(arr, n, i);
}

void heapSort(int arr[], int n) {
    buildMaxHeap(arr, n);
    for (int i = n; i >= 2; i--) {
        swap(arr[1], arr[i]);  // Swap root with last element
        heapify(arr, i - 1, 1); // Heapify the reduced heap
    }
}

void display(int arr[], int n) {
    cout << "Array: ";
    for (int i = 1; i <= n; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

int main() {
    int arr[101]; // One extra space as arr[0] is unused
    int n = 0, choice;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Enter Elements\n";
        cout << "2. Display Elements\n";
        cout << "3. Heap Sort\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
                    // sort();
        if (choice == 1) {
            cout << "Enter number of elements: ";
            cin >> n;
            cout << "Enter " << n << " elements:\n";
            for (int i = 1; i <= n; i++)
                cin >> arr[i];
        }
        else if (choice == 2) {
            if (n == 0)
                cout << "Array is empty.\n";
            else
                display(arr, n);
        }
        else if (choice == 3) {
            if (n == 0)
                cout << "No elements to sort.\n";
            else {
                heapSort(arr, n);
                cout << "Array sorted using Heap Sort.\n";
                display(arr, n);
            }
        }
    } while (choice != 4);

    return 0;
}
