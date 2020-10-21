#include<iostream>
#include<queue>
#include<math.h>

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
    int *completion_time;
    int *turn_around_time;
    int *waiting_time;
    int *processed;
    int no_of_processes;
    int choice;
    priority_queue<op, vector<op>, greater<op> > rq;
    srand(time(0));

    cout<<"Want to enter manually ? ";
    cin>>choice;
    if(choice == 1)
    {
    	cout<<"Enter No. of processes ";
	    cin>>no_of_processes; 
    	arrival_time = (int *)malloc(sizeof(int)*no_of_processes);
    	burst_time = (int *)malloc(sizeof(int)*no_of_processes);
    	process_id = (int *)malloc(sizeof(int)*no_of_processes);
    	turn_around_time = (int *)malloc(sizeof(int)*no_of_processes);
    	completion_time = (int *)malloc(sizeof(int)*no_of_processes);
    	waiting_time = (int *)malloc(sizeof(int)*no_of_processes);
    	processed = (int *)malloc(sizeof(int)*no_of_processes);
    	cout<<"Enter arrival_time, burst_time"<<endl;
    	for(int i = 0 ; i<no_of_processes ; i++)
    	{
     		process_id[i] = i+1;
            cin>>arrival_time[i];
            cin>>burst_time[i];
            completion_time[i] = 0;
            turn_around_time[i] = 0;
            waiting_time[i] = 0;
            processed[i] = 0;
	    }

    }
    else
    {
        no_of_processes = rand()%range1+1;
	    cout<<"No. of processes = "<<no_of_processes<<endl;
	    arrival_time = (int *)malloc(sizeof(int)*no_of_processes);
	    burst_time = (int *)malloc(sizeof(int)*no_of_processes);
	    process_id = (int *)malloc(sizeof(int)*no_of_processes);
	    turn_around_time = (int *)malloc(sizeof(int)*no_of_processes);
	    completion_time = (int *)malloc(sizeof(int)*no_of_processes);
	    waiting_time = (int *)malloc(sizeof(int)*no_of_processes);
	    processed = (int *)malloc(sizeof(int)*no_of_processes);
	    for(int i = 0 ; i<no_of_processes ; i++)
	    {
		    process_id[i] = i+1;
            arrival_time[i] = rand()%range2;
            burst_time[i] = rand()%range2+1; 
            completion_time[i] = 0;
            turn_around_time[i] = 0;
            waiting_time[i] = 0;
            processed[i] = 0;
	    }
	}    
	cout<<"\nProcess id    Arrival time    Burst time\n";
	for(int i = 0 ; i<no_of_processes ; i++)
	{
		cout<<"    "<<process_id[i]<<"             "<<arrival_time[i]<<"              "<<burst_time[i]<<endl;
	}
	
    cout<<"\nGantt chart : \n";
	pair<int, int> run_process;
	int count = 0;
	for(int current_time = 0 ;  ; )
	{
        cout<<" current_time = "<<current_time<<" ";
        for(int i = 0 ; i<no_of_processes ; i++)
        {
        	if(arrival_time[i]<=current_time && !processed[i])
        	{
        		rq.push(make_pair(arrival_time[i], i));
        		processed[i] = 1;
        	}
        }	
        if(!rq.empty())
        {
            run_process = rq.top();
            rq.pop();
            cout<<"excuted process = "<<process_id[run_process.second]<<" for "<<burst_time[run_process.second]<<" units"<<endl;
            current_time += burst_time[run_process.second];
            completion_time[run_process.second] = current_time;
            turn_around_time[run_process.second] = completion_time[run_process.second]-arrival_time[run_process.second];
            waiting_time[run_process.second] = turn_around_time[run_process.second]-burst_time[run_process.second];
            count++;
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