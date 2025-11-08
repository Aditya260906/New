#include <iostream>
using namespace std;

int main() {
    int n, bt[100], rem[100], wt[100]={0}, tat[100]={0}, tq;
    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter burst times: ";
    for(int i=0;i<n;i++){
        cin >> bt[i];
        rem[i] = bt[i];
    }

    cout << "Enter time quantum: ";
    cin >> tq;

    int time = 0;
    bool done;

    do {
        done = true;
        for(int i=0;i<n;i++){
            if(rem[i] > 0){
                done = false;
                if(rem[i] > tq){
                    time += tq;
                    rem[i] -= tq;
                } else {
                    time += rem[i];
                    tat[i] = time;
                    rem[i] = 0;
                }
            }
        }
    } while(!done);

    for(int i=0;i<n;i++)
        wt[i] = tat[i] - bt[i];

    cout << "\nProcess\tBT\tWT\tTAT\n";
    for(int i=0;i<n;i++)
        cout << "P" << i+1 << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i] << endl;

    return 0;
}
