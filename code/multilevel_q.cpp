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
    int *q_no;
    int time_quantum = 2;
    int choice;
    priority_queue<op, vector<op>, greater<op> > pq1, pq2;
    queue<int> rq1;
    cout<<"want to enter input? ";
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
    	q_no = (int *)malloc(sizeof(int)*no_of_processes);
    	processed = (int *)malloc(sizeof(int)*no_of_processes);
    	responsed = (int *)malloc(sizeof(int)*no_of_processes);
    	cout<<"Enter arrival_time, burst_time, queue no. "<<endl;
    	for(int i = 0 ; i<no_of_processes ; i++)
    	{
     		process_id[i] = i+1;
            cin>>arrival_time[i];
            cin>>burst_time[i];
            cin>>q_no[i];
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
	    q_no = (int *)malloc(sizeof(int)*no_of_processes);
    	processed = (int *)malloc(sizeof(int)*no_of_processes);
    	responsed = (int *)malloc(sizeof(int)*no_of_processes);
    	for(int i = 0 ; i<no_of_processes ; i++)
    	{
    		process_id[i] = i+1;
            arrival_time[i] = rand()%range2;
            burst_time[i] = rand()%range2+1;
            q_no[i] = rand()%2+1;
            d_burst_time[i] = burst_time[i];
            completion_time[i] = 0;
            turn_around_time[i] = 0;
            waiting_time[i] = 0;
            processed[i] = 0;
            responsed[i] = 0;
            d_wait_time[i] = 0;
	    }
	}    
	
	cout<<"\nProcess_id    Arrival_time    Burst_time      queue_no.\n";
	for(int i = 0 ; i<no_of_processes ; i++)
	{
		cout<<"    "<<process_id[i]<<"             "<<arrival_time[i]<<"              "<<burst_time[i]<<"                "<<q_no[i]<<endl;
	}

    cout<<"\nGantt chart : \n";
	int count = 0, cs = 0;
	int run_time = 0, run_process;
	pair<int, int> run_process_q2, ins;
	for(int current_time = 0 ; ;)
	{
        cout<<" current_time = "<<current_time<<" ";
		for(int i = 0 ; i<no_of_processes ; i++)
		{
			if(arrival_time[i]<=current_time && !responsed[i])
			{
				if(q_no[i] == 1)
					pq1.push(make_pair(arrival_time[i], i));
				else
					pq2.push(make_pair(arrival_time[i], i));
				responsed[i] = 1;
			}
		}
        
        while(!pq1.empty())
        {
            ins = pq1.top();
            rq1.push(ins.second);
            pq1.pop();
        }
        if(cs == 1)
        {
            rq1.push(run_process);
        }
        if(!rq1.empty())
        {
            cs = 1;
        	run_process = rq1.front();
            rq1.pop();

            if(d_burst_time[run_process]<time_quantum)
        	    run_time = d_burst_time[run_process];
            else
        	    run_time = time_quantum;

        	d_burst_time[run_process] -= run_time;
            current_time += run_time;
            cout<<"excuted process = "<<process_id[run_process]<<" for "<<run_time<<" units"<<endl;
            if(d_burst_time[run_process]<=0)
            {
        	    count++;
        	    completion_time[run_process] = current_time;
        	    turn_around_time[run_process] = completion_time[run_process]-arrival_time[run_process];
		        waiting_time[run_process] = turn_around_time[run_process]-burst_time[run_process];
		        processed[run_process] = 1;
                cs = 0;
            }
        }
        else if(!pq2.empty())
        {
            run_process_q2 = pq2.top();
            current_time++;
            d_burst_time[run_process_q2.second]--;
            cout<<"excuted process = "<<process_id[run_process]<<" for 1 unit"<<endl;
            if(d_burst_time[run_process_q2.second]==0)
            {
        	    count++;
        	    completion_time[run_process_q2.second] = current_time;
        	    turn_around_time[run_process_q2.second] = completion_time[run_process_q2.second]-arrival_time[run_process_q2.second];
		        waiting_time[run_process_q2.second] = turn_around_time[run_process_q2.second]-burst_time[run_process_q2.second];
		        processed[run_process_q2.second] = 1;
		        pq2.pop();
            }
        } 
        else
        	current_time++;
       
        if(count == no_of_processes)
        	break;
     
	}

    double wait_sum = 0, mean_wait = 0, dif_sum = 0;
    double turn_around_sum = 0, mean_turn_around = 0, dif_sum2 = 0;
    cout<<"\n\nProcess id    Arrival time    Burst time    queue_no.   completion_time     turn_around_time      waiting_time\n";
    for(int i = 0 ; i<no_of_processes ; i++)
    { 
        cout<<"    "<<process_id[i]<<"             "<<arrival_time[i]<<"              "<<burst_time[i]<<"                "<<q_no[i]<<"            "<<completion_time[i]<<"                   "<<turn_around_time[i]<<"               "<<waiting_time[i]<<endl;
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

             
