#include <iostream>
using namespace std;

int main() {
    int start, length, files[100], allocated = 0;

    // initialize all blocks as free
    for(int i = 0; i < 100; i++)
        files[i] = 0;

    cout << "Enter starting block: ";
    cin >> start;

    cout << "Enter length of file: ";
    cin >> length;

    // check if blocks are free
    for(int i = start; i < start + length; i++) {
        if(files[i] == 1) {
            cout << "Block " << i << " already allocated!\n";
            allocated = 1;
            break;
        }
    }

    if(allocated == 0) {
        for(int i = start; i < start + length; i++)
            files[i] = 1;

        cout << "File allocated successfully.\nBlocks allocated: ";
        for(int i = start; i < start + length; i++)
            cout << i << " ";
    }

    return 0;
}
