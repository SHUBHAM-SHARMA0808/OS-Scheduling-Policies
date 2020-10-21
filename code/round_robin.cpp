#include<iostream>
#include<math.h>
#include<queue>

using namespace std;

typedef pair<int, int> op;

int main(int argc, char** argv)
{
	int range1 = 9;
    int range2 = 9;
    int temp = 0;
    int *arrival_time;
    int *process_id;
    int *burst_time;
    int *d_burst_time;
    int *completion_time;
    int *turn_around_time;
    int *waiting_time;
    int *response;
    int no_of_processes;
    int time_quantum = 3;
    int choice;
    srand(time(0));
    priority_queue<op, vector<op>, greater<op> > pq;
    queue<int> rq;

    cout<<"Want to enter manually ? ";
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
    	response = (int *)malloc(sizeof(int)*no_of_processes);
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
            response[i] = 0;
	    }

    }
    else
    { 	
	    no_of_processes = rand()%range1+1;
	    arrival_time = (int *)malloc(sizeof(int)*no_of_processes);
	    burst_time = (int *)malloc(sizeof(int)*no_of_processes);
	    d_burst_time = (int *)malloc(sizeof(int)*no_of_processes);
	    process_id = (int *)malloc(sizeof(int)*no_of_processes);
	    turn_around_time = (int *)malloc(sizeof(int)*no_of_processes);
	    completion_time = (int *)malloc(sizeof(int)*no_of_processes);
	    waiting_time = (int *)malloc(sizeof(int)*no_of_processes);
	    response = (int *)malloc(sizeof(int)*no_of_processes);

	    for(int i = 0 ; i<no_of_processes ; i++)
	    {
		    process_id[i] = i+1;
            arrival_time[i] = rand()%range2;
            burst_time[i] = rand()%range2+1; 
            d_burst_time[i] = burst_time[i];
            completion_time[i] = 0;
            turn_around_time[i] = 0;
            waiting_time[i] = 0;
            response[i] = 0;
	    }
	}    
	cout<<"\nProcess id    Arrival time    Burst time\n";
	for(int i = 0 ; i<no_of_processes ; i++)
	{
		cout<<"    "<<process_id[i]<<"             "<<arrival_time[i]<<"              "<<burst_time[i]<<endl;
	}
	
    cout<<"\n Gantt chart : \n";
	int run_time = 0;
	int run_process = 0;
	pair<int, int> ins;
	int count = 0, cs  = 0;
	for(int current_time = 0 ; ; )
	{
        cout<<" current_time = "<<current_time<<" ";
		for(int i = 0 ; i<no_of_processes ; i++)
		{	
			if(arrival_time[i]<=current_time && !response[i])
			{
                
				pq.push(make_pair(arrival_time[i], i));
				response[i] = 1;
			}
		}	
		while(!pq.empty())
		{
			ins = pq.top();
			rq.push(ins.second);
			pq.pop();
		}
        if(cs == 1)
        {
            rq.push(run_process);
        }
		if(!rq.empty())
		{	
            cs = 1;
            run_process = rq.front();
            rq.pop();
            if(d_burst_time[run_process]<time_quantum)
            {
        	    run_time = d_burst_time[run_process];
        	    d_burst_time[run_process] -= run_time;
            }
            else
            {
        	    run_time = time_quantum;
        	    d_burst_time[run_process] -= time_quantum;
            }
            current_time += run_time;
            cout<<"excuted process = "<<process_id[run_process]<<" for "<<run_time<<" units"<<endl;
            if(d_burst_time[run_process]<=0)
            {
                cs = 0;
        	    count++;
        	    completion_time[run_process] = current_time;
        	    turn_around_time[run_process] = completion_time[run_process]-arrival_time[run_process];
		        waiting_time[run_process] = turn_around_time[run_process]-burst_time[run_process];
            }
        }
        else
        	current_time++;
        if(count == no_of_processes)
        	break;
	}
	double wait_sum = 0, mean_wait = 0, dif_sum = 0;
    double turn_around_sum = 0, mean_turn_around = 0, dif_sum2 = 0;
    cout<<"\n\nProcess id    Arrival time     Burst time    completion_time    turn_around_time    waiting_time\n";
    for(int i = 0 ; i<no_of_processes ; i++)
    { 
        cout<<"    "<<process_id[i]<<"             "<<arrival_time[i]<<"              "<<burst_time[i]<<"                 "<<completion_time[i]<<"                  "<<turn_around_time[i]<<"                 "<<waiting_time[i]<<endl;
        wait_sum += waiting_time[i];
        turn_around_sum += turn_around_time[i];
    }
    mean_wait = wait_sum/no_of_processes;
    mean_turn_around = turn_around_sum/no_of_processes;
    for(int i = 0 ; i<no_of_processes ; i++)
    {
        dif_sum += ((waiting_time[i]-mean_wait)*(waiting_time[i]-mean_wait));   
        dif_sum2 += ((turn_around_time[i]-mean_turn_around)*(turn_around_time[i]-mean_turn_around));
    }
    cout<<endl<<"Average waiting time = "<<mean_wait<<" , "<<"standard deviation = "<<sqrt(dif_sum/no_of_processes)<<endl;
    cout<<"Average turn around time = "<<mean_turn_around<<" , "<<"standard deviation = "<<sqrt(dif_sum2/no_of_processes)<<endl<<endl;
    return 0;
}