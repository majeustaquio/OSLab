#include <iostream>
#include <iomanip>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    // Number of processes
    int n = 10;
    // Burst time (CPU execution time) for each process
    int burstTime[] = {3, 5, 4, 3, 2, 1, 0, 7, 8, 1};
    // Array to store waiting time for each process
    int waitingTime[n];
    // Array to store turnaround time for each process
    int turnaroundTime[n];
    
    // First process has no waiting time
    waitingTime[0] = 0;
    // Calculate waiting time for remaining processes (cumulative burst times)
    for (int i = 1; i < n; i++) {
        waitingTime[i] = waitingTime[i-1] + burstTime[i-1];
    }
    
    // Calculate turnaround time (waiting time + burst time) for each process
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = waitingTime[i] + burstTime[i];
    }
    
    // Print table header
    cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time" << endl;
    // Print separator line
    cout << "-------\t----------\t------------\t---------------" << endl;
    
    // Print each process's details
    for (int i = 0; i < n; i++) {
        cout << "P" << i+1 << "\t" << burstTime[i] << "\t\t" 
             << waitingTime[i] << "\t\t" << turnaroundTime[i] << endl;
    }
    
    // Initialize total waiting time
    int totalWaiting = 0;
    // Initialize total turnaround time
    int totalTurnaround = 0;
    
    // Sum all waiting times
    for (int i = 0; i < n; i++) {
        totalWaiting += waitingTime[i];
        totalTurnaround += turnaroundTime[i];
    }
    
    // Print separator for results
    cout << "\n====================" << endl;
    // Calculate and print average waiting time
    cout << "Average Waiting Time: " << fixed << setprecision(2) 
         << (float)totalWaiting / n << endl;
    // Calculate and print average turnaround time
    cout << "Average Turnaround Time: " << fixed << setprecision(2) 
         << (float)totalTurnaround / n << endl;
    
    // Exit program
    return 0;
}