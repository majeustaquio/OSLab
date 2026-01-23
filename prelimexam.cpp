//https://github.com/benjajjajaa
//asdfghjkl1803/osLab
//FOR C++
//PREPARATORY COMMANDS
//mkdir -p FOLDER
//g++ -std=c++17 -O2 - Wall -Wextra FOLDER/FILENAME.LANGUAGE -o FILENAME

//EXECUTION COMMANDS
//./FILENAME

//FOR C#
//PREPARATORY COMMANDS
//dotnet new console -n HelloApp
//cd HelloApp

//EXECUTION COMMANDS
//dotnet run
//FOR C
//PREPARATORY COMMANDS
//gcc FILENAME.c -o FILENAME

//EXECUTION COMMANDS
//FILENAME OR ./FILENAME

//first task: gamit ang c++ code gumawa ng file na ang name prelim.cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <queue>
#include <climits>
using namespace std;

struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int tt;
    int wt;
};

int calculateTimeQuantum(vector<int>& bt) {
    sort(bt.begin(), bt.end());
    int n = bt.size();
    int median;
    if (n % 2 == 0) {
        median = (bt[n/2 - 1] + bt[n/2]) / 2;
    } else {
        median = bt[n/2];
    }
    return max(1, median);
}

void roundRobin(vector<Process>& processes, int tq) {
    vector<Process> pq = processes;
    vector<int> rt;
    for (auto& p : pq) rt.push_back(p.bt);
    
    int currentTime = 0;
    queue<int> q;
    vector<bool> added(pq.size(), false);
    vector<bool> completed(pq.size(), false);
    
    int completedCount = 0;
    while (completedCount < pq.size()) {
        // Add all processes that have arrived
        for (int i = 0; i < pq.size(); i++) {
            if (pq[i].at <= currentTime && !added[i]) {
                q.push(i);
                added[i] = true;
            }
        }
        
        if (q.empty()) {
            // Find next arrival time
            int nextArrival = INT_MAX;
            for (int i = 0; i < pq.size(); i++) {
                if (!completed[i]) {
                    nextArrival = min(nextArrival, pq[i].at);
                }
            }
            currentTime = nextArrival;
        } else {
            int idx = q.front();
            q.pop();
            
            if (rt[idx] <= tq) {
                currentTime += rt[idx];
                pq[idx].ct = currentTime;
                rt[idx] = 0;
                completed[idx] = true;
                completedCount++;
            } else {
                currentTime += tq;
                rt[idx] -= tq;
                q.push(idx);
            }
        }
    }
    
    for (auto& p : pq) {
        p.tt = p.ct - p.at;
        p.wt = p.tt - p.bt;
    }
    
    cout << "\n=== ROUND ROBIN (TQ=" << tq << ") ===\n";
    cout << left << setw(5) << "PID" << setw(5) << "AT" << setw(5) << "BT" << setw(5) << "CT" << setw(5) << "TT" << setw(5) << "WT" << "\n";
    for (auto& p : pq) {
        cout << left << setw(5) << p.pid << setw(5) << p.at << setw(5) << p.bt << setw(5) << p.ct << setw(5) << p.tt << setw(5) << p.wt << "\n";
    }
    double avgTT = 0, avgWT = 0;
    for (auto& p : pq) {
        avgTT += p.tt;
        avgWT += p.wt;
    }
    avgTT /= pq.size();
    avgWT /= pq.size();
    cout << "Average TT: " << fixed << setprecision(2) << avgTT << "\n";
    cout << "Average WT: " << fixed << setprecision(2) << avgWT << "\n";
}

void sjf(vector<Process> processes) {
    sort(processes.begin(), processes.end(), [](Process& a, Process& b) {
        return a.at < b.at || (a.at == b.at && a.bt < b.bt);
    });
    
    int currentTime = 0;
    for (auto& p : processes) {
        currentTime = max(currentTime, p.at);
        currentTime += p.bt;
        p.ct = currentTime;
        p.tt = p.ct - p.at;
        p.wt = p.tt - p.bt;
    }
    
    cout << "\n=== SHORTEST JOB FIRST ===\n";
    cout << left << setw(5) << "PID" << setw(5) << "AT" << setw(5) << "BT" << setw(5) << "CT" << setw(5) << "TT" << setw(5) << "WT" << "\n";
    for (auto& p : processes) {
        cout << left << setw(5) << p.pid << setw(5) << p.at << setw(5) << p.bt << setw(5) << p.ct << setw(5) << p.tt << setw(5) << p.wt << "\n";
    }
    double avgTT = 0, avgWT = 0;
    for (auto& p : processes) {
        avgTT += p.tt;
        avgWT += p.wt;
    }
    avgTT /= processes.size();
    avgWT /= processes.size();
    cout << "Average TT: " << fixed << setprecision(2) << avgTT << "\n";
    cout << "Average WT: " << fixed << setprecision(2) << avgWT << "\n";
}

void srtf(vector<Process> processes) {
    vector<int> rt;
    for (auto& p : processes) rt.push_back(p.bt);
    
    int currentTime = 0, completed = 0;
    while (completed < processes.size()) {
        int idx = -1;
        int minRT = INT_MAX;
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].at <= currentTime && rt[i] > 0 && rt[i] < minRT) {
                minRT = rt[i];
                idx = i;
            }
        }
        if (idx == -1) {
            currentTime++;
        } else {
            rt[idx]--;
            currentTime++;
            if (rt[idx] == 0) {
                processes[idx].ct = currentTime;
                processes[idx].tt = processes[idx].ct - processes[idx].at;
                processes[idx].wt = processes[idx].tt - processes[idx].bt;
                completed++;
            }
        }
    }
    
    cout << "\n=== SHORTEST REMAINING TIME FIRST ===\n";
    cout << left << setw(5) << "PID" << setw(5) << "AT" << setw(5) << "BT" << setw(5) << "CT" << setw(5) << "TT" << setw(5) << "WT" << "\n";
    for (auto& p : processes) {
        cout << left << setw(5) << p.pid << setw(5) << p.at << setw(5) << p.bt << setw(5) << p.ct << setw(5) << p.tt << setw(5) << p.wt << "\n";
    }
    double avgTT = 0, avgWT = 0;
    for (auto& p : processes) {
        avgTT += p.tt;
        avgWT += p.wt;
    }
    avgTT /= processes.size();
    avgWT /= processes.size();
    cout << "Average TT: " << fixed << setprecision(2) << avgTT << "\n";
    cout << "Average WT: " << fixed << setprecision(2) << avgWT << "\n";
}

int main() {
    vector<int> at = {4, 2, 3, 6, 1, 5, 8, 7};
    vector<int> bt = {53, 43, 18, 16, 44, 73, 99, 27};
    
    vector<Process> processes;
    for (int i = 0; i < at.size(); i++) {
        processes.push_back({i+1, at[i], bt[i], 0, 0, 0});
    }
    
    vector<int> btForTQ = bt;
    int tq = calculateTimeQuantum(btForTQ);
    
    roundRobin(processes, tq);
    sjf(processes);
    srtf(processes);
    
    return 0;
}