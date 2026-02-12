#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

#define MAX 1000
#define QUANTA 4

int at[MAX], bt[MAX], pt[MAX], rt[MAX];
int ft[MAX], fe[MAX], flag[MAX], qt[MAX];
int tms;

// Queues for MLFQ
queue<int> rrQueue;       // Top queue: Round Robin
vector<int> sjfQueue;     // Middle queue: SJF
queue<int> fcfsQueue;     // Bottom queue: FCFS

/* Round Robin execution for 1 time unit */
void RR() {
    if (!rrQueue.empty()) {
        int idx = rrQueue.front();
        rrQueue.pop();

        if (fe[idx] == -1)
            fe[idx] = tms;   // First execution time

        qt[idx]++;
        rt[idx]--;           // Execute 1 time unit

        if (rt[idx] == 0) {
            ft[idx] = tms + 1;
            flag[idx] = 1;
        }
        else if (qt[idx] == QUANTA) {
            qt[idx] = 0;
            sjfQueue.push_back(idx);   // Move to SJF
        }
        else {
            rrQueue.push(idx);         // Stay in RR
        }
    }
}

int main() {
    int n, i, sum = 0, large = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        printf("Enter AT: ");
        scanf("%d", &at[i]);
        printf("Enter BT: ");
        scanf("%d", &bt[i]);
        printf("Enter Priority: ");
        scanf("%d", &pt[i]);

        rt[i] = bt[i];
        qt[i] = 0;
        ft[i] = 0;
        fe[i] = -1;
        flag[i] = 0;

        sum += bt[i];
        if (at[i] > large)
            large = at[i];
    }

    // Main scheduling loop
    for (tms = 0; tms <= sum + large; tms++) {

        // Add newly arrived processes to RR queue
        for (i = 0; i < n; i++) {
            if (at[i] == tms && !flag[i] && rt[i] > 0) {
                rrQueue.push(i);
            }
        }

        // 1️⃣ Top Queue – Round Robin
        if (!rrQueue.empty()) {
            RR();
        }
        // 2️⃣ Middle Queue – SJF
        else if (!sjfQueue.empty()) {

            sort(sjfQueue.begin(), sjfQueue.end(),
                 [&](int a, int b) {
                     return rt[a] < rt[b];
                 });

            int idx = sjfQueue.front();
            sjfQueue.erase(sjfQueue.begin());

            if (fe[idx] == -1)
                fe[idx] = tms;

            rt[idx]--;   // Execute 1 time unit
            tms++;

            if (rt[idx] == 0) {
                ft[idx] = tms;
                flag[idx] = 1;
            }
            else {
                fcfsQueue.push(idx);   // Move to FCFS
            }
            tms--;
        }
        // 3️⃣ Bottom Queue – FCFS
        else if (!fcfsQueue.empty()) {

            int idx = fcfsQueue.front();
            fcfsQueue.pop();

            if (fe[idx] == -1)
                fe[idx] = tms;

            rt[idx]--;   // Execute 1 time unit
            tms++;

            if (rt[idx] == 0) {
                ft[idx] = tms;
                flag[idx] = 1;
            }
            else {
                fcfsQueue.push(idx);
            }
            tms--;
        }
        // CPU idle
        else {
            continue;
        }
    }

    // Output Table
    cout << "\nPROCESS SCHEDULING TABLE\n";
    cout << "-------------------------------------------------------------\n";
    cout << left
         << setw(8) << "PID"
         << setw(8) << "AT"
         << setw(8) << "BT"
         << setw(8) << "P"
         << setw(8) << "FE"
         << setw(8) << "FT"
         << setw(8) << "WT" << endl;
    cout << "-------------------------------------------------------------\n";

    for (i = 0; i < n; i++) {
        int WT = ft[i] - at[i] - bt[i];

        cout << left
             << setw(8) << (i + 1)   // Auto PID
             << setw(8) << at[i]
             << setw(8) << bt[i]
             << setw(8) << pt[i]
             << setw(8) << fe[i]
             << setw(8) << ft[i]
             << setw(8) << WT << endl;
    }

    return 0;
}

/*
3
1 2 5 2
2 0 3 1
3 2 1 4

1 1 9 2
2 0 3 0
3 5 8 5
*/