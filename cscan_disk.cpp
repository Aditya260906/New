#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n, head, disk, req[100], total = 0;

    cout << "Enter disk size: ";
    cin >> disk;

    cout << "Enter number of requests: ";
    cin >> n;

    cout << "Enter request queue: ";
    for(int i=0;i<n;i++) cin >> req[i];

    cout << "Enter initial head: ";
    cin >> head;

    sort(req, req+n);

    int pos = 0;
    while(pos < n && req[pos] < head) pos++;

    cout << "CSCAN order: ";

    // Move right
    for(int i=pos;i<n;i++){
        cout << req[i] << " ";
        total += abs(req[i] - head);
        head = req[i];
    }

    // Go to end then jump to 0
    total += abs((disk-1) - head);
    total += (disk-1);
    head = 0;

    // Move again from 0
    for(int i=0;i<pos;i++){
        cout << req[i] << " ";
        total += abs(req[i] - head);
        head = req[i];
    }

    cout << "\nTotal Head Movement (CSCAN) = " << total;
}
