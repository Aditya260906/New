#include <iostream>
using namespace std;

int main() {
    int n, head, req[100], total = 0;

    cout << "Enter number of requests: ";
    cin >> n;

    cout << "Enter request queue: ";
    for(int i=0;i<n;i++) cin >> req[i];

    cout << "Enter initial head position: ";
    cin >> head;

    for(int i=0;i<n;i++){
        total += abs(req[i] - head);
        head = req[i];
    }

    cout << "Total Head Movement (FCFS) = " << total;
    return 0;
}
