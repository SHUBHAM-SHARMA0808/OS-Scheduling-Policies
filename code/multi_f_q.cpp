#include<iostream>
#include<queue>

using namespace std;

typedef pair<int, int> op;

int main(int argc, char** argv)
{   
	int range1 = 9;
    int range2 = 9;
    int temp = 0;
    int no_of_processes;
    int *arrival_time;
    int *process_id;
    int *burst_time;
    int *d_burst_time;
    int *completion_time;
    int *turn_around_time;
    int *waiting_time;
    int *d_wait_time;
    int *processed;
    int *responsed;
    int time_quantum1 = 2;
    int time_quantum2 = 4;
    int choice;
    priority_queue<op, vector<op>, greater<op> > pq;
    queue<int> rq1, rq2, rq3;
    cout<<"want to enter input?";
    cin>>choice;
    if(choice == 1)
    {
    	cout<<"Enter No. of processes ";
	    cin>>no_of_processes; 
    	arrival_time = (int *)malloc(sizeof(int)*no_of_processes);
    	burst_time = (int *)malloc(sizeof(int)*no_of_processes);
    	d_burst_time = (int *)malloc(sizeof(int)*no_of_processes);
    	process_id = (int *)malloc(sizeof(int)*no_of_processes);
    	turn_around_time = (int *)malloc(sizeof(int)*no_of_processes);
    	completion_time = (int *)malloc(sizeof(int)*no_of_processes);
    	waiting_time = (int *)malloc(sizeof(int)*no_of_processes);
    	d_wait_time = (int *)malloc(sizeof(int)*no_of_processes);
    	processed = (int *)malloc(sizeof(int)*no_of_processes);
    	responsed = (int *)malloc(sizeof(int)*no_of_processes);
    	cout<<"Enter arrival_time, burst_time"<<endl;
    	for(int i = 0 ; i<no_of_processes ; i++)
    	{
     		process_id[i] = i+1;
            cin>>arrival_time[i];
            cin>>burst_time[i];
            d_burst_time[i] = burst_time[i];
            completion_time[i] = 0;
            turn_around_time[i] = 0;
            waiting_time[i] = 0;
            processed[i] = 0;
            responsed[i] = 0;
            d_wait_time[i] = 0;
	    }

    }
    else
    {
    	srand(time(0));
	    no_of_processes = rand()%range1+1; 
    	cout<<"No. of processes = "<<no_of_processes<<endl; 
	    arrival_time = (int *)malloc(sizeof(int)*no_of_processes);
    	burst_time = (int *)malloc(sizeof(int)*no_of_processes);
    	d_burst_time = (int *)malloc(sizeof(int)*no_of_processes); 
    	process_id = (int *)malloc(sizeof(int)*no_of_processes);
     	turn_around_time = (int *)malloc(sizeof(int)*no_of_processes);
    	completion_time = (int *)malloc(sizeof(int)*no_of_processes); 
    	waiting_time = (int *)malloc(sizeof(int)*no_of_processes);
     	d_wait_time = (int *)malloc(sizeof(int)*no_of_processes); 
    	processed = (int *)malloc(sizeof(int)*no_of_processes);
    	responsed = (int *)malloc(sizeof(int)*no_of_processes);
    	for(int i = 0 ; i<no_of_processes ; i++)
    	{
    		process_id[i] = i+1;
            arrival_time[i] = rand()%range2;
            burst_time[i] = rand()%range2+1;
            d_burst_time[i] = burst_time[i];
            completion_time[i] = 0;
            turn_around_time[i] = 0;
            waiting_time[i] = 0;
            processed[i] = 0;
            responsed[i] = 0;
            d_wait_time[i] = 0;
	    }
	}    
	
	cout<<"\nProcess_id    Arrival_time    Burst_time\n";
	for(int i = 0 ; i<no_of_processes ; i++)
	{
		cout<<"    "<<process_id[i]<<"             "<<arrival_time[i]<<"              "<<burst_time[i]<<"                "<<endl;
	}

	int count = 0;
    int run_time = 0, run_process = 0;
	pair<int, int> ins;
	int flag = 0;
	for(int current_time = 0 ; ;)
	{
		//cout<<current_time<<" ";
		for(int i = 0 ; i<no_of_processes ; i++)
		{
			if(arrival_time[i]<=current_time && !responsed[i])
			{
				pq.push(make_pair(arrival_time[i], i));
			    responsed[i] = 1;
			}
		}
        while(!pq.empty())
        {
            ins = pq.top();
            rq1.push(ins.second);
            pq.pop();
        }
        if(!rq1.empty())
        {
        	run_process = rq1.front();
            rq1.pop();
            if(d_burst_time[run_process]<time_quantum1)
            {
        	   run_time = d_burst_time[run_process];
        	   d_burst_time[run_process] -= run_time;
            }
            else
            {
        	    run_time = time_quantum1;
        	    d_burst_time[run_process] -= run_time;
            }
            current_time += run_time;
            //cout<<d_burst_time[run_process]<<" ";
            if(d_burst_time[run_process]<=0)
            {
        	    count++;
        	    completion_time[run_process] = current_time;
        	    turn_around_time[run_process] = completion_time[run_process]-arrival_time[run_process];
		        waiting_time[run_process] = turn_around_time[run_process]-burst_time[run_process];
		        processed[run_process] = 1;
            }
            else
        	    rq2.push(run_process);
        }
        else if(!rq2.empty())
        {
            run_process = rq2.front();
            rq2.pop();
            if(d_burst_time[run_process]<time_quantum2)
            {
               run_time = d_burst_time[run_process];
               d_burst_time[run_process] -= run_time;
            }
            else
            {
                run_time = time_quantum2;
                d_burst_time[run_process] -= run_time;
            }
            current_time += run_time;
            //cout<<d_burst_time[run_process]<<" ";
            if(d_burst_time[run_process]<=0)
            {
                count++;
                completion_time[run_process] = current_time;
                turn_around_time[run_process] = completion_time[run_process]-arrival_time[run_process];
                waiting_time[run_process] = turn_around_time[run_process]-burst_time[run_process];
                processed[run_process] = 1;
            }
            else
                rq3.push(run_process);

        }

        else if(!rq3.empty())
        {
            run_process = rq3.front();
            current_time++;
            d_burst_time[run_process]--;
            if(d_burst_time[run_process]==0)
            {
        	    count++;
        	    completion_time[run_process] = current_time;
        	    turn_around_time[run_process] = completion_time[run_process]-arrival_time[run_process];
		        waiting_time[run_process] = turn_around_time[run_process]-burst_time[run_process];
		        processed[run_process] = 1;
		        rq3.pop();
            }
        } 
        else
        	current_time++;
        //cout<<process_id[run_process]<<endl;
        //cout<<"process completed "<<count<<endl;
        if(count == no_of_processes)
        	break;
     
	}

    float sum_wait = 0;
	cout<<"\nProcess id    Arrival time    Burst time       completion_time     turn_around_time      waiting_time\n";
	for(int i = 0 ; i<no_of_processes ; i++)
	{ 
		cout<<"    "<<process_id[i]<<"             "<<arrival_time[i]<<"              "<<burst_time[i]<<"                "<<completion_time[i]<<"                    "<<turn_around_time[i]<<"                 "<<waiting_time[i]<<endl;
		sum_wait += waiting_time[i];
	}

	cout<<endl<<"Average waiting time is : "<<sum_wait/no_of_processes<<" units"<<endl;
	return 0;
}

             
