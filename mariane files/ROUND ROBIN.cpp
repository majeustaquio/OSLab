#include <iostream>
#include <queue>

using namespace std;

int main() {
    int n = 5;                 // Number of processes
    double timeQuantum = 20;   // Time quantum

    // Burst times of processes
    double burstTime[5] = {50.54, 10.11, 33.34, 2.5, 101.1};

    double remainingTime[5];  // Remaining burst time
    double waitingTime[5] = {0};
    double turnaroundTime[5] = {0};

    queue<int> q;             // Queue for Round Robin
    double currentTime = 0;

    // Initialize remaining time and queue
    for (int i = 0; i < n; i++) {
        remainingTime[i] = burstTime[i];
        q.push(i);            // Add process index to queue
    }

    // Round Robin Scheduling logic
    while (!q.empty()) {
        int p = q.front();    // Get next process
        q.pop();

        if (remainingTime[p] > timeQuantum) {
            currentTime += timeQuantum;
            remainingTime[p] -= timeQuantum;
            q.push(p);        // Put process back in queue
        } else {
            currentTime += remainingTime[p];
            turnaroundTime[p] = currentTime;
            waitingTime[p] = turnaroundTime[p] - burstTime[p];
            remainingTime[p] = 0; // Process completed
        }
    }

    // Display results
    cout << "\nRound Robin Scheduling\n";
    cout << "Time Quantum: " << timeQuantum << "\n\n";
    cout << "Process\tBurst\tTurnaround\tWaiting\n";

    double totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t"
             << burstTime[i] << "\t"
             << turnaroundTime[i] << "\t\t"
             << waitingTime[i] << endl;

        totalWT += waitingTime[i];
        totalTAT += turnaroundTime[i];
    }

    cout << "\nAverage Waiting Time: " << totalWT / n << endl;
    cout << "Average Turnaround Time: " << totalTAT / n << endl;

    return 0;
}
