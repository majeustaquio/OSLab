#include <iostream>
#include <iomanip> //2dec places
using namespace std;

int main()
{
    int p[5], i, j;
    float bt[5] = {50.54, 10.11, 33.34, 2.50, 101.10}; //variable is set
    float wt[5], tat[5];
    float wtavg = 0, tatavg = 0, temp;

    int n = 5;

    // Initialize process numbers
    for (i = 0; i < n; i++)
        p[i] = i;

    // SJF sorting based on burst time
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (bt[i] > bt[j])
            {
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Waiting time and turnaround time calculation
    wt[0] = 0;
    tat[0] = bt[0];

    for (i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = wt[i] + bt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }

    // Display result
    cout << "\nPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n";
    cout << fixed << setprecision(2);

    for (i = 0; i < n; i++)
        cout << "P" << p[i] << "\t"
             << bt[i] << "\t\t"
             << wt[i] << "\t\t"
             << tat[i] << endl;

    cout << "\nAverage Waiting Time = " << wtavg / n;
    cout << "\nAverage Turnaround Time = " << tatavg / n << endl;

    return 0;
}