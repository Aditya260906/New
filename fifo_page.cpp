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

    int frame[f], idx=0, faults=0;
    for(int i=0;i<f;i++) frame[i] = -1; // Initially all frames are empty
    // idx keeps track of which frame will be replaced next

    for(int i=0;i<n;i++) {
        bool found=false;
        for(int j=0;j<f;j++)
            if(frame[j]==pages[i]) found=true;

        if(!found) {
            frame[idx] = pages[i];
            idx = (idx+1)%f; // for shifting idx use idx = (idx + 1) % f;
            faults++;
        }
    }
    cout << "Page Faults (FIFO) = " << faults << endl;
    cout << "Page Hits (FIFO) = " << n - faults;
    // hits will be number of pages - faults
}
