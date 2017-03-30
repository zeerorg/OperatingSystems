#include <iostream>
#include "Process.h"

using namespace std;

struct ProcessHeap {
    Process q[MAX];
    int length;
    ProcessHeap() {
        length = 0;
    }
    /*
    1. Insert in heap
        ~ compare priority and move up
        ~ if comparing with topmost and switch occurs inside switch topmost : burst = burst - (time - start)
    */

    void insertHeap(Process p, int time) {
        q[length] = p;
        if(isEmpty()) {
            q[0].start = 0;
            cout << time << ":P[" << q[0].pid << "]\n";
        } else {
            int parent = (length-1)/2;
            int child = length;
            while(parent>0) {
                if(q[child].priority < q[parent].priority) {
                    Process temp = q[child];
                    q[child] = q[parent];
                    q[parent] = temp;
                    child = parent;
                    parent  = (child-1)/2;
                } else {
                    break;
                }
            }
            if(parent == 0) {
                if(q[child].priority < q[parent].priority) {
                    q[0].burst = q[0].burst - (time - q[0].start);
                    q[0].start = -1;
                    Process temp = q[child];
                    q[child] = q[0];
                    q[0] = temp;
                    q[0].start = time;
                    cout << time << ":P[" << q[0].pid << "]\n";
                }
            }
        }
        length++;
    }

    /*
    2. delete from heap
        ~ select the child with highest priority and start executing
        ~ set its start time
    */
    Process deleteHeap(int time) {
        Process p = q[0];
        q[0] = q[length-1];

        int parent = 0;
        int left, right;
        while(true) {
            left = parent*2 + 1;
            right = parent*2 + 2;
            if(left < length && q[left].priority < q[parent].priority)
                parent = left;
            if(right < length && q[right].priority < q[parent].priority)
                parent = right;
            if(parent == (right-1)/2)
                break;
            else {
                int t = (right-1)/2;
                Process temp = q[parent];
                q[parent] = q[t];
                q[t] = temp;
            }
        }
        q[0].start = time;
        length--;
        return p;
    }

    /*
    3. get top
    */
    Process* getTop() {
        return &q[0];
    }

    bool isEmpty() {
        return length <= 0;
    }
};

int main() {
    int slice;
    Process p;
    ProcessQueue processes;
    ProcessHeap ready;
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
        cout << "Enter Priority for P[" << temp.pid << "] : ";
        cin >> temp.priority;
        processes.insertQ(temp);
        cout << endl;
    }

    int time = 0;
    cout << endl;
    while(!(processes.isEmpty() && ready.isEmpty())) {

        if (!processes.isEmpty() && processes.first()->arrival == time) {
            Process ptemp = processes.delQ();
            if(ready.isEmpty() && time > 0) {
                cout << time << ":P[" << ptemp.pid << "]\n";
            }
            ready.insertHeap(ptemp, time);
            continue;
        }
        Process *top = ready.getTop();
        if(time == 0) {
            top->start = 0;

        }

        if(top->start + top->burst == time) {
            top = NULL;
            ready.deleteHeap(time);
            if (!ready.isEmpty()) {
                top = ready.getTop();
                cout << time << ":P[" << top->pid << "]\n";
            } else {
                cout << time << ":stopped\n";
            }
        }

        time ++;
    }

    return 0;
}

