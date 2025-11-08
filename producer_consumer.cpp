#include <iostream>
using namespace std;

int main() {
    int buffer = 0, maxSize;
    cout << "Enter buffer size: ";
    cin >> maxSize;

    int choice;
    do {
        cout << "\n1. Produce\n2. Consume\n3. Exit\nEnter choice: ";
        cin >> choice;

        if(choice == 1) {
            if(buffer < maxSize) {
                buffer++;
                cout << "Produced. Buffer = " << buffer << endl;
            } else {
                cout << "Buffer is Full!\n";
            }
        }
        else if(choice == 2) {
            if(buffer > 0) {
                buffer--;
                cout << "Consumed. Buffer = " << buffer << endl;
            } else {
                cout << "Buffer is Empty!\n";
            }
        }
    } while(choice != 3);

    return 0;
}
