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

    cout << "SCAN order: ";

    // Move right first
    for(int i=pos; i<n; i++){
        cout << req[i] << " ";
        total += abs(req[i] - head);
        head = req[i];
    }

    // Go to end of disk
    total += abs((disk-1) - head);
    head = disk-1;

    // Move left
    for(int i=pos-1; i>=0; i--){
        cout << req[i] << " ";
        total += abs(req[i] - head);
        head = req[i];
    }

    cout << "\nTotal Head Movement (SCAN) = " << total;
}
