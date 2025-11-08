#include <iostream>
using namespace std;

int main() {
    int blocks, start, next[100], visited[100] = {0};;

    cout << "Enter total number of blocks: ";
    cin >> blocks;

    cout << "Enter next block for each block (-1 for end):\n";
    for(int i = 0; i < blocks; i++)
        cin >> next[i];

    cout << "Enter starting block: ";
    cin >> start;

    cout << "File allocated blocks (Linked): ";
    int current = start;

    while(current != -1 && current < blocks && visited[current] == 0) {
        cout << current << " ";
        visited[current] = 1;
        current = next[current];
    }

    return 0;
}

