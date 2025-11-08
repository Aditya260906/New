#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of philosophers: ";
    cin >> n;

    int fork[20] = {0};   // 0 = free, 1 = in use

    for(int i = 0; i < n; i++) {
        if(fork[i] == 0 && fork[(i+1)%n] == 0) {
            cout << "Philosopher " << i << " is Eating\n";
            fork[i] = fork[(i+1)%n] = 1;
        } else {
            cout << "Philosopher " << i << " is Thinking\n";
        }
    }
    return 0;
}
