#include <iostream>
using namespace std;

const int MAX = 50;
const int QMAX = 10000; // for RR circular queue

// ---------- Utility I/O ----------
void inputCommon(int &n, int process[], int at[], int bt[]) {
    cout << "Enter number of processes (<=50): ";
    cin >> n;
    if (n > MAX) { cout << "Capped to 50.\n"; n = MAX; }

    cout << "Enter process IDs: ";
    for (int i = 0; i < n; i++) cin >> process[i];

    cout << "Enter arrival times: ";
    for (int i = 0; i < n; i++) cin >> at[i];

    cout << "Enter burst times: ";
    for (int i = 0; i < n; i++) cin >> bt[i];
}

void printResults(int n, int process[], int at[], int bt[], int ct[], int tat[], int wt[]) {
    double totalTAT = 0, totalWT = 0;

    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << process[i] << "\t" << at[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
        totalTAT += tat[i];
        totalWT  += wt[i];
    }

    cout << "\nAverage TAT: " << (totalTAT / n);
    cout << "\nAverage WT : " << (totalWT  / n) << "\n\n";
}

// ---------- FCFS ----------
void fcfs(int n, int process[], int at[], int bt[]) {
    int idx[MAX];
    for (int i = 0; i < n; i++) idx[i] = i;

    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (at[idx[j]] > at[idx[j+1]] ||
               (at[idx[j]] == at[idx[j+1]] && idx[j] > idx[j+1])) {
                int t = idx[j]; idx[j] = idx[j+1]; idx[j+1] = t;
            }
        }
    }

    int ct[MAX], tat[MAX], wt[MAX];
    int current_time = 0;

    for (int k = 0; k < n; k++) {
        int i = idx[k];
        if (current_time < at[i]) current_time = at[i];
        current_time += bt[i];
        ct[i]  = current_time;
        tat[i] = ct[i] - at[i];
        wt[i]  = tat[i] - bt[i];
    }

    printResults(n, process, at, bt, ct, tat, wt);
}

// ---------- SJF (Non-Preemptive) ----------
void sjf_non_preemptive(int n, int process[], int at[], int bt[]) {
    bool done[MAX] = {false};
    int ct[MAX], tat[MAX], wt[MAX];
    int completed = 0, time = 0;

    int earliest = at[0];
    for (int i = 1; i < n; i++) if (at[i] < earliest) earliest = at[i];
    time = earliest;

    while (completed < n) {
        int pick = -1;
        int best_bt = 1e9;

        for (int i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time) {
                if (bt[i] < best_bt) {
                    best_bt = bt[i];
                    pick = i;
                }
            }
        }

        if (pick == -1) {
            int next_at = 1e9;
            for (int i = 0; i < n; i++)
                if (!done[i] && at[i] < next_at) next_at = at[i];
            time = next_at;
            continue;
        }

        time += bt[pick];
        ct[pick]  = time;
        tat[pick] = ct[pick] - at[pick];
        wt[pick]  = tat[pick] - bt[pick];
        done[pick] = true;
        completed++;
    }

    printResults(n, process, at, bt, ct, tat, wt);
}

// ---------- SRTF (Preemptive SJF) ----------
void srtf(int n, int process[], int at[], int bt[]) {
    int rem[MAX], ct[MAX], tat[MAX], wt[MAX];
    bool done[MAX] = {false};
    for (int i = 0; i < n; i++) rem[i] = bt[i];

    int completed = 0, time = 0;

    int earliest = at[0];
    for (int i = 1; i < n; i++) if (at[i] < earliest) earliest = at[i];
    time = earliest;

    while (completed < n) {
        int pick = -1;
        int best_rem = 1e9;

        for (int i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time && rem[i] > 0) {
                if (rem[i] < best_rem) {
                    best_rem = rem[i];
                    pick = i;
                }
            }
        }

        if (pick == -1) {
            int next_at = 1e9;
            for (int i = 0; i < n; i++)
                if (!done[i] && at[i] < next_at) next_at = at[i];
            time = next_at;
            continue;
        }

        rem[pick]--;
        time++;

        if (rem[pick] == 0) {
            done[pick] = true;
            ct[pick] = time;
            tat[pick] = ct[pick] - at[pick];
            wt[pick]  = tat[pick] - bt[pick];
            completed++;
        }
    }

    printResults(n, process, at, bt, ct, tat, wt);
}

// ---------- Round Robin ----------
void round_robin(int n, int process[], int at[], int bt[]) {
    int tq;
    cout << "Enter the time quantum: ";
    cin >> tq;

    int rem[MAX], ct[MAX], tat[MAX], wt[MAX];
    bool in_queue[MAX] = {false};
    for (int i = 0; i < n; i++) rem[i] = bt[i];

    int q[QMAX];
    int front = 0, rear = 0;

    int time = 0, completed = 0;

    int earliest = at[0];
    for (int i = 1; i < n; i++) if (at[i] < earliest) earliest = at[i];
    time = earliest;

    for (int i = 0; i < n; i++) {
        if (at[i] <= time && rem[i] > 0 && !in_queue[i]) {
            q[rear] = i; rear = (rear + 1) % QMAX;
            in_queue[i] = true;
        }
    }

    while (completed < n) {
        if (front == rear) {
            int next_at = 1e9;
            for (int i = 0; i < n; i++)
                if (rem[i] > 0 && at[i] < next_at) next_at = at[i];
            time = next_at;

            for (int i = 0; i < n; i++) {
                if (at[i] <= time && rem[i] > 0 && !in_queue[i]) {
                    q[rear] = i; rear = (rear + 1) % QMAX;
                    in_queue[i] = true;
                }
            }
            continue;
        }

        int idx = q[front]; front = (front + 1) % QMAX;

        int slice = (rem[idx] > tq) ? tq : rem[idx];
        rem[idx] -= slice;
        time += slice;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rem[i] > 0 && !in_queue[i]) {
                q[rear] = i; rear = (rear + 1) % QMAX;
                in_queue[i] = true;
            }
        }

        if (rem[idx] == 0) {
            ct[idx]  = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx]  = tat[idx] - bt[idx];
            completed++;
            in_queue[idx] = false;
        } else {
            q[rear] = idx; rear = (rear + 1) % QMAX;
        }
    }

    printResults(n, process, at, bt, ct, tat, wt);
}

// ---------- Priority (Preemptive) ----------
void priority_preemptive(int n, int process[], int at[], int bt[]) {
    int pr[MAX];
    cout << "Enter priority for each process (lower = higher priority): ";
    for (int i = 0; i < n; i++) cin >> pr[i];

    int rem[MAX], ct[MAX], tat[MAX], wt[MAX];
    bool done[MAX] = {false};
    for (int i = 0; i < n; i++) rem[i] = bt[i];

    
    int completed = 0;
    int time = 0;

    int earliest = at[0];
    for (int i = 1; i < n; i++) if (at[i] < earliest) earliest = at[i];
    time = earliest;

    while (completed < n) {
        int pick = -1;
        int best_pr = 1e9;

        for (int i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time && rem[i] > 0) {
                if (pr[i] < best_pr) {
                    best_pr = pr[i];
                    pick = i;
                }
            }
        }

        if (pick == -1) {
            int next_at = 1e9;
            for (int i = 0; i < n; i++)
                if (!done[i] && at[i] < next_at) next_at = at[i];
            time = next_at;
            continue;
        }

        rem[pick]--;
        time++;

        if (rem[pick] == 0) {
            done[pick] = true;
            ct[pick]  = time;
            tat[pick] = ct[pick] - at[pick];
            wt[pick]  = tat[pick] - bt[pick];
            completed++;
        }
    }

    printResults(n, process, at, bt, ct, tat, wt);
}

// ---------- main ----------
int main() {
    while (true) {
        cout << "================ Scheduling Menu ================\n";
        cout << "1. FCFS\n";
        cout << "2. SJF (Non-Preemptive)\n";
        cout << "3. SRTF (Preemptive)\n";
        cout << "4. Round Robin\n";
        cout << "5. Priority (Preemptive)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        int ch; cin >> ch;

        switch (ch) {
            case 1: {
                int n, process[MAX], at[MAX], bt[MAX];
                inputCommon(n, process, at, bt);
                fcfs(n, process, at, bt);
                break;
            }
            case 2: {
                int n, process[MAX], at[MAX], bt[MAX];
                inputCommon(n, process, at, bt);
                sjf_non_preemptive(n, process, at, bt);
                break;
            }
            case 3: {
                int n, process[MAX], at[MAX], bt[MAX];
                inputCommon(n, process, at, bt);
                srtf(n, process, at, bt);
                break;
            }
            case 4: {
                int n, process[MAX], at[MAX], bt[MAX];
                inputCommon(n, process, at, bt);
                round_robin(n, process, at, bt);
                break;
            }
            case 5: {
                int n, process[MAX], at[MAX], bt[MAX];
                inputCommon(n, process, at, bt);
                priority_preemptive(n, process, at, bt);
                break;
            }
            case 6:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}
