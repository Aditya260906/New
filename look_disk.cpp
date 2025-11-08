#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n, head, req[100], total = 0;

    cout << "Enter number of requests: ";
    cin >> n;

    cout << "Enter request queue: ";
    for(int i=0;i<n;i++) cin >> req[i];

    cout << "Enter initial head: ";
    cin >> head;

    sort(req, req+n);

    int pos = 0;
    while(pos<n && req[pos] < head) pos++;

    cout << "LOOK order: ";

    // Move right only to the highest request
    for(int i=pos;i<n;i++){
        cout << req[i] << " ";
        total += abs(req[i] - head);
        head = req[i];
    }

    // Move left only to the lowest request
    for(int i=pos-1;i>=0;i--){
        cout << req[i] << " ";
        total += abs(req[i] - head);
        head = req[i];
    }

    cout << "\nTotal Head Movement (LOOK) = " << total;
}
