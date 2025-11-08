#include <iostream>
using namespace std;

int main() {
    int n, head, req[100], visited[100] = {0}, total = 0;

    cout << "Enter number of requests: ";
    cin >> n;

    cout << "Enter request queue: ";
    for(int i=0;i<n;i++) cin >> req[i];

    cout << "Enter initial head: ";
    cin >> head;

    for(int c=0;c<n;c++){
        int pos = -1, diff = 99999;

        for(int i=0;i<n;i++){
            if(!visited[i] && abs(req[i] - head) < diff){
                diff = abs(req[i] - head);
                pos = i;
            }
        }
        visited[pos] = 1;
        total += abs(req[pos] - head);
        head = req[pos];
    }

    cout << "Total Head Movement (SSTF) = " << total;
}
