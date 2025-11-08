#include <iostream>
using namespace std;

int main() {
    int n, bt[100], wt[100], tat[100];
    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter burst times: ";
    for(int i=0;i<n;i++) cin >> bt[i];

    wt[0] = 0;
    for(int i=1;i<n;i++)
        wt[i] = wt[i-1] + bt[i-1];

    for(int i=0;i<n;i++)
        tat[i] = wt[i] + bt[i];

    cout << "\nProcess\tBT\tWT\tTAT\n";
    for(int i=0;i<n;i++)
        cout << "P" << i+1 << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i] << endl;

    return 0;
}
