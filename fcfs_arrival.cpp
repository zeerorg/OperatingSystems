#include <iostream>
#include "Process.h"

using namespace std;

int main() {
    Process p;
    ProcessQueue processes;
    ProcessQueue readyQ;
    int n;
    cout << "Enter Number of Processes: ";
    cin >> n;
    cout << endl;
    for(int i=1; i<=n; i++) {
        Process temp;
        temp.pid = 1000 + i;
        cout << "Enter burst time for P[" << temp.pid << "] : ";
        cin >> temp.burst;
        cout << "Enter Arrival time for P[" << temp.pid << "] : ";
        cin >> temp.arrival;
        processes.insertQ(temp);
        cout << endl;
    }

    int time = 0;
    readyQ.insertQ(processes.delQ());
    readyQ.first()->start = 0;
    cout << "0:P[1001]\n";
    while(!(processes.isEmpty() && readyQ.isEmpty())) {
        if (!processes.isEmpty() && processes.first()->arrival == time) {
            Process ptemp = processes.delQ();
            ptemp.start = time;
            if(readyQ.isEmpty()) {
                cout << time << ":P[" << ptemp.pid << "]\n";
            }
            readyQ.insertQ(ptemp);
            continue;
        }


        Process *top = readyQ.first();
        if(top->start + top->burst == time) {
            top = NULL;
            readyQ.delQ();
            if (!readyQ.isEmpty()) {
                top = readyQ.first();
                cout << time << ":P[" << top->pid << "]\n";
                top->start = time;
            } else {
                cout << time << ":stopped\n";
            }
        }

        time ++;
    }

    return 0;
}

