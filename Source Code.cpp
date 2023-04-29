#include<bits/stdc++.h>
using namespace std;

struct Process
{
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    int priority;
};

double comp_avg, comp_tt;

bool compArr(Process p1,Process p2)
{
    return p1.arrival_time<p2.arrival_time;
}

bool compID(Process p1,Process p2)
{
    return p1.pid<p2.pid;
}




void fcfs(Process p[], int n, bool flag)
{
    int i;
    sort(p,p+n,compArr);

    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int current_time = 0;
    int idle_time = 0;
    if(flag == 0)
    cout <<"Gantt Chart"<<endl;
    for(i=0;i<n;i++)
    {
        if(i==0)
            p[i].start_time = p[i].arrival_time;
        else
            p[i].start_time = max(p[i].arrival_time , p[i-1].completion_time);

        if(p[i].start_time > current_time)
        {
            if(flag == 0)
            cout << current_time << " idle " ;
            idle_time += (p[i].start_time - current_time);
        }

        p[i].completion_time = p[i].start_time + p[i].burst_time;

        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;

        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;

        p[i].response_time = p[i].start_time - p[i].arrival_time;

        total_turnaround_time += p[i].turnaround_time;

        total_waiting_time += p[i].waiting_time;
        if(flag == 0)
        cout<<p[i].start_time<<" P"<<p[i].pid<<" ";
        current_time = p[i].completion_time;
    }
    if(flag == 0)
    cout << p[i-1].completion_time << endl;
    double avg_turnaround_time = (double)total_turnaround_time/n;
    double avg_waiting_time = (double)total_waiting_time/n;
    if(flag == 0)
    cout<<endl<<endl;
    if(flag == 0){
    for(i=0;i<n;i++)
    {
       cout<<"Process: P";
        cout<<p[i].pid<<"\t";

        cout<<"Finish time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].completion_time<<"\t";

        cout<<"Response time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].response_time<<"\t";

        cout<<"Waiting time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].waiting_time<<"\t";

        cout<<"Turnaround time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].turnaround_time<<endl;
    }

    cout<<"Average waiting time: ";
    cout<<avg_waiting_time<<endl;

    cout<<"Average turnaround time: ";
    cout<<avg_turnaround_time<<endl;

    cout <<"Idle time: " << idle_time << endl;
    cout << "Press any key for the home page" << endl;
    }
    comp_avg = avg_waiting_time;
    comp_tt = avg_turnaround_time;

}

void npsjf(Process p[], int n, bool flag)
{

    int current_time = 0;
    int completed = 0;
    int prev = 0;
    int chk = 0;
    int idle_time = 0;
    int is_completed[n+2];
    float avg_turnaround_time;
    float avg_waiting_time;
    int total_turnaround_time = 0;
    int total_idle_time = 0;
    int total_waiting_time = 0;
    memset(is_completed,0,sizeof(is_completed));
    if(flag == 0)
    cout << "Gantt Chart" << endl;
    while(completed != n) {
        int idx = -1;
        int past = current_time;
        int mn = 10000000;
        for(int i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                if(p[i].burst_time < mn) {
                    mn = p[i].burst_time;
                    idx = i;
                }
                if(p[i].burst_time == mn) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mn = p[i].burst_time;
                        idx = i;
                    }
                }
            }
        }
        if(idx != -1) {
            p[idx].start_time = current_time;
            p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_idle_time += p[idx].start_time - prev;

            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].completion_time;
            prev = current_time;
        }
        else {
            current_time++;
        }
        if(chk == -1 && idx == -1)continue;
        if(flag == 0)
        cout << past << " " << (idx == -1?"idle":"P"+to_string(p[idx].pid)) << " " ;//<< current_time <<" ";

        chk = idx;

    }
    if(flag == 0)
    cout << current_time << endl;

    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    for(int i = 0; i < n; i++) {
        min_arrival_time = min(min_arrival_time,p[i].arrival_time);
        max_completion_time = max(max_completion_time,p[i].completion_time);
    }

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    if(flag == 0){
    for(int i=0;i<n;i++)
    {
        cout<<"Process: P";
        cout<<p[i].pid<<"\t";

        cout<<"Finish time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].completion_time<<"\t";

        cout<<"Response time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].response_time<<"\t";

        cout<<"Waiting time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].waiting_time<<"\t";

        cout<<"Turnaround time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].turnaround_time<<endl;
    }

    cout<<"Average waiting time: ";
    cout<<avg_waiting_time<<endl;

    cout<<"Average turnaround time: ";
    cout<<avg_turnaround_time<<endl;

    cout <<"Idle time: " << total_idle_time << endl;
    cout << "Press any key for the home page" << endl;
    }
    comp_avg = avg_waiting_time;
    comp_tt = avg_turnaround_time;

}


void psjf(Process p[], int n, bool flag)
{

    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_idle_time = 0;
    int idle_time=0;
    int burst_remaining[n+5];
    int is_completed[n+5];
    memset(is_completed,0,sizeof(is_completed));

    int current_time = 0;
    int completed = 0;
    int prev = 0;
    int chk = -2;
    for(int i = 0; i < n; i++)
    {
        burst_remaining[i] = p[i].burst_time;
    }
    if(flag == 0)
    cout << "Gantt Chart" << endl;
    while(completed != n) {
        int past = current_time;
        int idx = -1;
        int mn = 10000000;
        for(int i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                if(burst_remaining[i] < mn) {
                    mn = burst_remaining[i];
                    idx = i;
                }
                if(burst_remaining[i] == mn) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mn = burst_remaining[i];
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1) {
            if(burst_remaining[idx] == p[idx].burst_time) {
                p[idx].start_time = current_time;
                total_idle_time += p[idx].start_time - prev;
            }
            burst_remaining[idx] -= 1;
            current_time++;
            prev = current_time;

            if(burst_remaining[idx] == 0) {
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else {
             current_time++;
        }
     //   if(chk == -1 && idx == -1)continue;
        if(chk == idx) continue;
        if(flag == 0)
        cout << past << " " << (idx == -1?"idle":"P"+to_string(p[idx].pid)) << " " ;//<< current_time <<" ";

        chk = idx;
    }
    if(flag == 0)
    cout << current_time << endl;
    if(flag == 0)
    cout << endl;
    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    for(int i = 0; i < n; i++) {
        min_arrival_time = min(min_arrival_time,p[i].arrival_time);
        max_completion_time = max(max_completion_time,p[i].completion_time);
    }

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;

    if(flag == 0){
    for(int i=0;i<n;i++)
    {
        cout<<"Process: P";
        cout<<p[i].pid<<"\t";

        cout<<"Finish time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].completion_time<<"\t";

        cout<<"Response time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].response_time<<"\t";

        cout<<"Waiting time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].waiting_time<<"\t";

        cout<<"Turnaround time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].turnaround_time<<endl;
    }

    cout<<"Average waiting time: ";
    cout<<avg_waiting_time<<endl;

    cout<<"Average turnaround time: ";
    cout<<avg_turnaround_time<<endl;

    cout <<"Idle time: " << total_idle_time << endl;
    cout << "Press any key for the home page" << endl;
    }
    comp_avg = avg_waiting_time;
    comp_tt = avg_turnaround_time;


}


void npp(Process p[],int n, bool flag)
{
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    float cpu_utilisation;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    int priority;
    int is_completed[n+5];
    memset(is_completed,0,sizeof(is_completed));

    int current_time = 0;
    int completed = 0;
    int prev = 0;
    int chk = -2;
    if(flag == 0)
    cout << "Gantt Chart" << endl;
    while(completed != n) {
         int past = current_time;
        int idx = -1;
        int mx = 100000000;
        for(int i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                if(p[i].priority < mx) {
                    mx = p[i].priority;
                    idx = i;
                }
                if(p[i].priority == mx) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mx = p[i].priority;
                        idx = i;
                    }
                }
            }
        }
        if(idx != -1) {
            p[idx].start_time = current_time;
            p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_response_time += p[idx].response_time;
            total_idle_time += p[idx].start_time - prev;

            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].completion_time;
            prev = current_time;
        }
        else {
            current_time++;
        }
        if(chk == idx) continue;
        if(flag == 0)
        cout << past << " " << (idx == -1?"idle":"P"+to_string(p[idx].pid)) << " " ;//<< current_time <<" ";

        chk = idx;
    }
    if(flag == 0)
    cout << current_time << endl;
    if(flag == 0)
    cout << endl;
    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    for(int i = 0; i < n; i++) {
        min_arrival_time = min(min_arrival_time,p[i].arrival_time);
        max_completion_time = max(max_completion_time,p[i].completion_time);
    }

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    if(flag == 0){
    for(int i=0;i<n;i++)
    {
        cout<<"Process: P";
        cout<<p[i].pid<<"\t";

        cout<<"Finish time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].completion_time<<"\t";

        cout<<"Response time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].response_time<<"\t";

        cout<<"Waiting time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].waiting_time<<"\t";

        cout<<"Turnaround time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].turnaround_time<<endl;
    }

    cout<<"Average waiting time: ";
    cout<<avg_waiting_time<<endl;

    cout<<"Average turnaround time: ";
    cout<<avg_turnaround_time<<endl;

    cout <<"Idle time: " << total_idle_time << endl;
    cout << "Press any key for the home page" << endl;
    }
    comp_avg = avg_waiting_time;
    comp_tt = avg_turnaround_time;
}

void pp(Process p[], int n, bool flag)
{
    float avg_turnaround_time;
    float avg_waiting_time;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_idle_time = 0;
    int burst_remaining[n];
    int is_completed[n];
    memset(is_completed,0,sizeof(is_completed));
    int current_time = 0;
    int completed = 0;
    int prev = 0;
    for(int i = 0; i < n; i++)
    {
        burst_remaining[i] = p[i].burst_time;
    }
     int chk = -2;
     if(flag == 0)
    cout << "Gantt Chart" << endl;
    while(completed != n) {
         int past = current_time;
        int idx = -1;
        int mx = 100000000;
        for(int i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                if(p[i].priority < mx) {
                    mx = p[i].priority;
                    idx = i;
                }
                if(p[i].priority == mx) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mx = p[i].priority;
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1) {
            if(burst_remaining[idx] == p[idx].burst_time) {
                p[idx].start_time = current_time;
                total_idle_time += p[idx].start_time - prev;
            }
            burst_remaining[idx] -= 1;
            current_time++;
            prev = current_time;

            if(burst_remaining[idx] == 0) {
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else {
             current_time++;
        }
        if(chk == idx) continue;
        if(flag == 0)
        cout << past << " " << (idx == -1?"idle":"P"+to_string(p[idx].pid)) << " " ;//<< current_time <<" ";

        chk = idx;
    }
    if(flag == 0)
    cout << current_time << endl;
    if(flag == 0)
    cout << endl;
    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    for(int i = 0; i < n; i++) {
        min_arrival_time = min(min_arrival_time,p[i].arrival_time);
        max_completion_time = max(max_completion_time,p[i].completion_time);
    }

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    if(flag == 0){
    for(int i=0;i<n;i++)
    {
        cout<<"Process: P";
        cout<<p[i].pid<<"\t";

        cout<<"Finish time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].completion_time<<"\t";

        cout<<"Response time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].response_time<<"\t";

        cout<<"Waiting time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].waiting_time<<"\t";

        cout<<"Turnaround time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].turnaround_time<<endl;
    }

    cout<<"Average waiting time: ";
    cout<<avg_waiting_time<<endl;

    cout<<"Average turnaround time: ";
    cout<<avg_turnaround_time<<endl;

    cout <<"Idle time: " << total_idle_time << endl;
    cout << "Press any key for the home page" << endl;
    }
    comp_avg = avg_waiting_time;
    comp_tt = avg_turnaround_time;
}

void rr(Process p[],int n,int t, bool flag)
{
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    float cpu_utilisation;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    float throughput;
    int burst_remaining[n];
    int idx;


    sort(p, p+n, compArr);
    for(int i = 0; i < n; i++)
    {
        p[i].start_time = -1;
        burst_remaining[i] = p[i].burst_time;
    }

    queue<int> q;
    int current_time = 0;
    int completed = 0;
    int mark[n];
    memset(mark,0,sizeof(mark));
    for(int i = 0; i < n; i++)
    {
        if(p[i].arrival_time <= current_time && mark[i] == 0)
        {
            q.push(i);
            mark[i] = 1;
        }
    }
    int chk = 0;
    if(flag == 0)
    cout << "Gantt Chart" << endl;
    while(completed != n)
    {
        int prev = current_time;
        idx = -1;
        if(!q.empty()){
            idx = q.front();
            q.pop();
            if(p[idx].start_time == -1)
                p[idx].start_time = current_time;
            if(burst_remaining[idx]-t>0)
            {
                burst_remaining[idx] -= t;
                current_time += t;
            }
            else
            {
                current_time += burst_remaining[idx];
                burst_remaining[idx] = 0;
                completed++;
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
            }
            for(int i = 0; i < n; i++)
            {
                if(p[i].arrival_time <= current_time && mark[i] == 0)
                {
                    q.push(i);
                    mark[i] = 1;
                }
            }
            if(burst_remaining[idx]>0)
            {
                q.push(idx);
            }

        }
        else
        {
            current_time++;
             for(int i = 0; i < n; i++) {
                if(p[i].arrival_time <= current_time && mark[i] == 0) {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }
        if(idx == -1)total_idle_time++;
        if(chk == -1 && idx == -1){continue;}
        if(flag == 0)
        cout << prev << " " << (idx == -1?"idle":"P"+to_string(p[idx].pid)) << " " ;//<< current_time <<" ";

        chk = idx;
    }
    if(flag == 0)
    cout << current_time << endl;

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;

    sort(p,p+n,compID);
    if(flag == 0){
    for(int i=0;i<n;i++)
    {
        cout<<"Process: P";
        cout<<p[i].pid<<"\t";

        cout<<"Finish time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].completion_time<<"\t";

        cout<<"Response time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].response_time<<"\t";

        cout<<"Waiting time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].waiting_time<<"\t";

        cout<<"Turnaround time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].turnaround_time<<endl;
    }

    cout<<"Average waiting time: ";
    cout<<avg_waiting_time<<endl;

    cout<<"Average turnaround time: ";
    cout<<avg_turnaround_time<<endl;

    cout <<"Idle time: " << total_idle_time << endl;
    cout << "Press any key for the home page" << endl;
    }
    comp_avg = avg_waiting_time;
    comp_tt = avg_turnaround_time;
}

int srch(Process p[], int n, queue<int> q, int rem[])
{
    int sum = 0, sz = q.size();
    queue<int>pq;
    while(!q.empty())
    {
        sum += rem[q.front()];
        pq.push(q.front());
        q.pop();
    }
    int m = sum / sz;
    int idx = -1, mn = 1000000;
    while(!pq.empty())
    {
        if(abs(m - rem[pq.front()]) <= mn)
        {
            idx = pq.front();
            mn = abs(m- rem[pq.front()]);
        }
        pq.pop();
    }
    return idx;
}

void opa(Process p[], int n, int t, bool flag)
{
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    float cpu_utilisation;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    float throughput;
    int burst_remaining[n];
    int idx;


    sort(p, p+n, compArr);
    for(int i = 0; i < n; i++)
    {
        p[i].start_time = -1;
        burst_remaining[i] = p[i].burst_time;
    }

    queue<int> q;
    int current_time = 0;
    int completed = 0;
    int mark[n];
    memset(mark,0,sizeof(mark));
    for(int i = 0; i < n; i++)
    {
        if(p[i].arrival_time <= current_time && mark[i] == 0)
        {
            q.push(i);
            mark[i] = 1;
        }
    }
    int chk = 0;
    if(flag == 0)
    cout << "Gantt Chart" << endl;
    while(completed != n)
    {
        int prev = current_time;
        idx = -1;
        if(!q.empty()){
            idx = srch(p,n,q,burst_remaining);
            queue<int> temp;
            while(!q.empty())
            {
                if(idx != q.front())temp.push(q.front());
                q.pop();
            }
            q = temp;
            if(p[idx].start_time == -1)
                p[idx].start_time = current_time;
            if(burst_remaining[idx]-t>0)
            {
                burst_remaining[idx] -= t;
                current_time += t;
            }
            else
            {
                current_time += burst_remaining[idx];
                burst_remaining[idx] = 0;
                completed++;
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
            }
            for(int i = 0; i < n; i++)
            {
                if(p[i].arrival_time <= current_time && mark[i] == 0)
                {
                    q.push(i);
                    mark[i] = 1;
                }
            }
            if(burst_remaining[idx]>0)
            {
                q.push(idx);
            }

        }
        else
        {
            current_time++;
             for(int i = 0; i < n; i++) {
                if(p[i].arrival_time <= current_time && mark[i] == 0) {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }
        if(idx == -1)total_idle_time++;
        if(chk == -1 && idx == -1){continue;}
        if(flag == 0)
        cout << prev << " " << (idx == -1?"idle":"P"+to_string(p[idx].pid)) << " " ;//<< current_time <<" ";

        chk = idx;
    }
    if(flag == 0)
    cout << current_time << endl;

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;

    sort(p,p+n,compID);
    if(flag == 0){
    for(int i=0;i<n;i++)
    {
        cout<<"Process: P";
        cout<<p[i].pid<<"\t";

        cout<<"Finish time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].completion_time<<"\t";

        cout<<"Response time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].response_time<<"\t";

        cout<<"Waiting time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].waiting_time<<"\t";

        cout<<"Turnaround time: ";
        cout << setw(2) << setfill('0');
        cout<<p[i].turnaround_time<<endl;
    }

    cout<<"Average waiting time: ";
    cout<<avg_waiting_time<<endl;

    cout<<"Average turnaround time: ";
    cout<<avg_turnaround_time<<endl;

    cout <<"Idle time: " << total_idle_time << endl;
    cout << "Press any key for the home page" << endl;
    }
    comp_avg = avg_waiting_time;
    comp_tt = avg_turnaround_time;
}

void cmp(Process p[], int n, int t)
{
    fcfs(p,n,1);
    cout << setw(5) << setfill(' ');
    cout << "Algorithm: 1 Average Waiting Time: "<< comp_avg <<" Average Turnaround Time: " << comp_tt << endl;
    npsjf(p,n,1);
    cout << setw(5) << setfill(' ');
    cout << "Algorithm: 2 Average Waiting Time: "<< comp_avg <<" Average Turnaround Time: " << comp_tt << endl;
    psjf(p,n,1);
    cout << setw(5) << setfill(' ');
    cout << "Algorithm: 3 Average Waiting Time: "<< comp_avg <<" Average Turnaround Time: " << comp_tt << endl;
    npp(p,n,1);
    cout << setw(5) << setfill(' ');
    cout << "Algorithm: 4 Average Waiting Time: "<< comp_avg <<" Average Turnaround Time: " << comp_tt << endl;
    pp(p,n,1);
    cout << setw(5) << setfill(' ');
    cout << "Algorithm: 5 Average Waiting Time: "<< comp_avg <<" Average Turnaround Time: " << comp_tt << endl;
    rr(p,n,t,1);
    cout << setw(5) << setfill(' ');
    cout << "Algorithm: 6 Average Waiting Time: "<< comp_avg <<" Average Turnaround Time: " << comp_tt << endl;
    opa(p,n,t,1);
    cout << setw(5) << setfill(' ');
    cout << "Algorithm: 7 Average Waiting Time: "<< comp_avg <<" Average Turnaround Time: " << comp_tt << endl;
    cout << "Press any key for the home page" << endl;
}

int main()
{
    int cs;
    while(1)
    {
        cout << "1:FCFS" << endl;
        cout << "2:Non-Preemptive-SJF" << endl;
        cout << "3:Preemptive-SJF" << endl;
        cout << "4:Non-Preemptive-Priority" << endl;
        cout << "5:Preemptive-Priority" << endl;
        cout << "6:Round-Robin" << endl;
        cout << "7:Our-Proposed-Algorithm" << endl;
        cout << "8:Compare-All" << endl;
        cout << "9:Exit" << endl;
        cout << "Input your choice: ";
        cin >> cs;
        if(cs == 9)
        {
            break;
        }
        cout << endl;

        int n, i ,j, t;
        cout<<"Number of process,n: ";
        cin>>n;
        cout<<endl;

        struct Process p[n];

        if(cs == 1 || cs == 2 || cs == 3 || cs == 6 || cs == 7)
        {
            if(cs == 6 || cs == 7)
            {
                cout<<"Enter time quantum: ";
                cin>>t;
            }
            for(i=0;i<n;i++)
            {
                cout<<"Enter the arrival time of P"<<i+1<<": ";
                cin>>p[i].arrival_time;

                cout<<"Enter the burst time of P"<<i+1<<": ";
                cin>>p[i].burst_time;
                cout<<endl;

                p[i].pid=i+1;
            }
        }
        else if(cs == 4 || cs == 5)
        {
            for(i=0;i<n;i++)
            {
                cout<<"Enter the arrival time of P"<<i+1<<": ";
                cin>>p[i].arrival_time;

                cout<<"Enter the burst time of P"<<i+1<<": ";
                cin>>p[i].burst_time;

                cout<<"Enter the priority of P"<<i+1<<": ";
                cin>>p[i].priority;
                cout<<endl;

                p[i].pid=i+1;
            }
        }
        else
        {

            cout<<"Enter time quantum: ";
            cin>>t;
            for(i=0;i<n;i++)
            {
                cout<<"Enter the arrival time of P"<<i+1<<": ";
                cin>>p[i].arrival_time;

                cout<<"Enter the burst time of P"<<i+1<<": ";
                cin>>p[i].burst_time;

                cout<<"Enter the priority of P"<<i+1<<": ";
                cin>>p[i].priority;
                cout<<endl;

                p[i].pid=i+1;
            }
        }


        if(cs == 1)
        {
            fcfs(p,n,0);
        }
        else if(cs == 2)
        {
            npsjf(p,n,0);
        }
        else if(cs == 3)
        {
            psjf(p,n,0);
        }
        else if(cs == 4)
        {
            npp(p,n,0);
        }
        else if(cs == 5)
        {
            pp(p,n,0);
        }
        else if(cs == 6)
        {
            rr(p,n,t,0);
        }
        else if(cs == 7)
        {
            opa(p,n,t,0);
        }
        else if(cs == 8)
        {
            cmp(p,n,t);
        }
        getchar();
        getchar();
    }
    return 0;
}
