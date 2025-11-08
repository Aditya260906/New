#include <iostream>
using namespace std;

int main() {
    int n, f;
    cout << "Enter number of pages: ";
    cin >> n;
    int pages[n];
    cout << "Enter pages: ";
    for(int i=0;i<n;i++) cin >> pages[i];
    cout << "Enter number of frames: ";
    cin >> f;

    int frame[f], faults=0;
    for(int i=0;i<f;i++) frame[i] = -1;

    for(int i=0;i<n;i++) {
        bool found=false;
        for(int j=0;j<f;j++)
            if(frame[j] == pages[i]) found = true;

        if(!found) {
            int pos=-1, farthest=-1;
            for(int j=0;j<f;j++) {
                int k;
                for(k=i+1;k<n;k++)
                    if(frame[j] == pages[k]) break;
                if(k > farthest) {
                    farthest = k;
                    pos = j;
                }
            }
            frame[pos] = pages[i];
            faults++;
        }
    }
    cout << "Page Faults (OPTIMAL) = " << faults << endl;
    cout << "Page Hits (OPTIMAL) = " << n - faults;
}
