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

    int frame[100], faults=0, recent[100];
    for(int i=0;i<f;i++){
        frame[i] = -1;
        recent[i] = -1;
    }

    for(int i =0;i<n;i++){
        bool found = false;
        for(int j = 0; j < f;j++){
            if(frame[j] == pages[i]){
                found = true;
                recent[j] = i;
            }
        }

        if(!found) {
            int pos=0;
            for(int j=1; j < f; j++){
                if(recent[j] < recent[pos]) pos = j;
            }   
            frame[pos] = pages[i];
            recent[pos] = i;
            faults++;
        }
    }
    cout << "Page Faults (LRU) = " << faults << endl;
    cout << "Page Hits (LRU) = " << n - faults;
}