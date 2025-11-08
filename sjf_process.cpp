#include <iostream>
#include <algorithm>
using namespace std;

struct Process {
    int bt, id;
};

int main() {
    int n;
    Process p[100];

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter burst times: ";
    for(int i=0;i<n;i++){
        cin >> p[i].bt;
        p[i].id = i+1;
    }

    sort(p, p+n, [](Process a, Process b){ return a.bt < b.bt; }); //vvimp

    int wt[100], tat[100];
    wt[0] = 0;
    for(int i=1;i<n;i++)
        wt[i] = wt[i-1] + p[i-1].bt;

    for(int i=0;i<n;i++)
        tat[i] = wt[i] + p[i].bt;

    cout << "\nProcess\tBT\tWT\tTAT\n";
    for(int i=0;i<n;i++)
        cout << "P" << p[i].id << "\t" << p[i].bt << "\t" << wt[i] << "\t" << tat[i] << endl;

    return 0;
}
