#include<iostream>
#include<math.h>

using namespace std;

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
    int *priority;
    int max_arrival = -1;
    int max_pri = -1;
    int no_of_processes;
    int choice;
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
    	priority = (int *)malloc(sizeof(int)*no_of_processes);
    	cout<<"Enter arrival_time, burst_time"<<endl;
    	for(int i = 0 ; i<no_of_processes ; i++)
    	{
     		process_id[i] = i+1;
            cin>>arrival_time[i];
            if(arrival_time[i]>max_arrival)
	        	max_arrival = arrival_time[i];
            cin>>burst_time[i];
	        cin>>priority[i];
	        if(priority[i]>max_pri)
	        	max_pri = priority[i];
            completion_time[i] = 0;
            turn_around_time[i] = 0;
            waiting_time[i] = 0;
            processed[i] = 0;
	    }

    }
    else
    {	
	    srand(time(0));
		no_of_processes = rand()%range1+1;
		arrival_time = (int *)malloc(sizeof(int)*no_of_processes);
		burst_time = (int *)malloc(sizeof(int)*no_of_processes);
		process_id = (int *)malloc(sizeof(int)*no_of_processes);
		turn_around_time = (int *)malloc(sizeof(int)*no_of_processes);
		completion_time = (int *)malloc(sizeof(int)*no_of_processes);
		waiting_time = (int *)malloc(sizeof(int)*no_of_processes);
		processed = (int *)malloc(sizeof(int)*no_of_processes);
		priority = (int *)malloc(sizeof(int)*no_of_processes);
		for(int i = 0 ; i<no_of_processes ; i++)
		{
			process_id[i] = i+1;
	        arrival_time[i] = rand()%range2;
	        if(arrival_time[i]>max_arrival)
	        	max_arrival = arrival_time[i];
	        burst_time[i] = rand()%range2+1; 
	        priority[i] = rand()%range2+5;
	        if(priority[i]>max_pri)
	        	max_pri = priority[i];
	        completion_time[i] = 0;
	        turn_around_time[i] = 0;
	        waiting_time[i] = 0;
	        processed[i] = 0;
		}
    }
	cout<<"\nProcess_id    Arrival_time    Burst_time    priority\n";
	for(int i = 0 ; i<no_of_processes ; i++)
	{
		cout<<"    "<<process_id[i]<<"             "<<arrival_time[i]<<"              "<<burst_time[i]<<"              "<<priority[i]<<endl;
	}
	
	cout<<"\nGantt chart : \n";
    
    int count = 0;
    int run_process = 0;
    int min_pri;
    int flag = 0;
    int min_arrival;
    
	for(int current_time = 0 ; ; )
	{
		cout<<" current_time = "<<current_time<<" ";
		min_pri = max_pri+1;
		min_arrival = max_arrival+1;
		flag = 0;
		for(int i = 0 ; i<no_of_processes ; i++)
		{
			if(arrival_time[i]<=current_time && arrival_time[i]<=min_arrival && !processed[i])
				{
					if(arrival_time[i]<min_arrival)
					{
					    min_pri = priority[i];
					    min_arrival = arrival_time[i];
					    run_process = i;
					    flag = 1;
					}
					else if(arrival_time[i]==min_arrival && priority[i]<min_pri)
					{
	                    min_pri = priority[i];
						run_process = i;
					    flag = 1;
					}    
				}
		}
		if(flag == 1)
		{	
		    completion_time[run_process] = current_time+burst_time[run_process];
		    current_time += burst_time[run_process];
		    cout<<"excuted process = "<<process_id[run_process]<<" for "<<burst_time[run_process]<<" units"<<endl;
		    turn_around_time[run_process] = completion_time[run_process]-arrival_time[run_process];
		    waiting_time[run_process] = turn_around_time[run_process]-burst_time[run_process];
		    processed[run_process] = 1;
		    count++;
		}
		else
			current_time++;
		if(count == no_of_processes)
			break;
	}
	double wait_sum = 0, mean_wait = 0, dif_sum = 0;
    double turn_around_sum = 0, mean_turn_around = 0, dif_sum2 = 0;
	cout<<"\n\nProcess id    Arrival time     Burst time     Priority     completion_time    turn_around_time    waiting_time\n";
	for(int i = 0 ; i<no_of_processes ; i++)
	{ 
		cout<<"    "<<process_id[i]<<"             "<<arrival_time[i]<<"              "<<burst_time[i]<<"                 "<<priority[i]<<"              "<<completion_time[i]<<"                  "<<turn_around_time[i]<<"                 "<<waiting_time[i]<<endl;
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
