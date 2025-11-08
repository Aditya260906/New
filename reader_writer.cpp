#include <iostream>
using namespace std;

int main() {
    int readers = 0;
    int writing = 0;
    int choice;

    do {
        cout << "\n1. Reader enters\n2. Reader leaves\n3. Writer tries to write\n4. Writer leaves\n5. Exit\nChoice: ";
        cin >> choice;

        if(choice == 1) {
            if(writing == 0) {
                readers++;
                cout << "Reader entered. Readers inside = " << readers << endl;
            } else {
                cout << "Writer is writing! Reader must wait.\n";
            }
        }
        else if(choice == 2) {
            if(readers > 0) {
                readers--;
                cout << "Reader left. Readers inside = " << readers << endl;
            }
        }
        else if(choice == 3) {
            if(readers == 0 && writing == 0) {
                writing = 1;
                cout << "Writer started writing.\n";
            } else {
                cout << "Writer must wait! Readers inside or another writer.\n";
            }
        }
        else if(choice == 4) {
            if(writing == 1) {
                writing = 0;
                cout << "Writer finished writing.\n";
            }
        }
    } while(choice != 5);

    return 0;
}
