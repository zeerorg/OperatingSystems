#include <iostream>
#include "Process.h"

using namespace std;

int main() {
    Process p;
    ProcessQueue processes;
    int n;
    cout << "Enter Number of Processes: ";
    cin >> n;
    for(int i=1; i<=n; i++) {
        Process temp;
        temp.pid = 1000 + i;
        cout << "Enter burst time for P[" << temp.pid << "] : ";
        cin >> temp.burst;
        processes.insertQ(temp);
    }
    //processes.displayQ();

    int time = 0;
    processes.first()->start = 0;
    cout << "0:P[1001]\t\t";
    while(!processes.isEmpty()) {
        Process *top = processes.first();
        if(top->start + top->burst == time) {
            processes.delQ();
            if (!processes.isEmpty()) {
                top = processes.first();
                cout << time << ":P[" << top->pid << "]\t\t";
                top->start = time;
            } else {
                cout << time << ":finish";
            }
        }

        time ++;
    }

    return 0;
}
