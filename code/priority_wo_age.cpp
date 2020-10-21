#include<iostream>
#include<math.h>

using namespace std;

void generate_priority(int* p, int n);

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
    int *priority;
    int *processed;
    srand(time(0));
	int no_of_processes = rand()%range1+1;
	arrival_time = (int *)malloc(sizeof(int)*no_of_processes);
	burst_time = (int *)malloc(sizeof(int)*no_of_processes);
	d_burst_time = (int *)malloc(sizeof(int)*no_of_processes);
	process_id = (int *)malloc(sizeof(int)*no_of_processes);
	turn_around_time = (int *)malloc(sizeof(int)*no_of_processes);
	completion_time = (int *)malloc(sizeof(int)*no_of_processes);
	waiting_time = (int *)malloc(sizeof(int)*no_of_processes);
	priority = (int *)malloc(sizeof(int)*no_of_processes);
	processed = (int *)malloc(sizeof(int)*no_of_processes);
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
	}
	
	generate_priority(priority, no_of_processes);
	cout<<"\nProcess_id    Arrival_time    Burst_time      priority\n";
	for(int i = 0 ; i<no_of_processes ; i++)
	{
		cout<<"    "<<process_id[i]<<"             "<<arrival_time[i]<<"              "<<burst_time[i]<<"                "<<priority[i]<<endl;
	}

	int min_pri = no_of_processes+1;
	int count = 0;
	int run_process = 0;
	int flag = 0;
	for(int current_time = 0 ; ;)
	{
		flag = 0;
		min_pri = no_of_processes+1;
		for(int i = 0 ; i<no_of_processes ; i++)
		{
			if(arrival_time[i]<=current_time && priority[i]<min_pri && !processed[i])
				{
					min_pri = priority[i];
					run_process = i;
					flag = 1;
			    }    		
		}
		current_time++;
		if(flag == 1)
		{
		    d_burst_time[run_process]--;
		    if(d_burst_time[run_process]==0)
			{
				processed[run_process] = 1;
				count++;
				completion_time[run_process] = current_time;
        	    turn_around_time[run_process] = completion_time[run_process]-arrival_time[run_process];
		        waiting_time[run_process] = turn_around_time[run_process]-burst_time[run_process];
		    }    
		}    
		if(count == no_of_processes)
			break;
		
	}

    double wait_sum = 0, mean_wait = 0, dif_sum = 0;
    double turn_around_sum = 0, mean_turn_around = 0, dif_sum2 = 0;
	cout<<"\nProcess id    Arrival time     Burst time    completion_time    turn_around_time    waiting_time\n";
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

void generate_priority(int* p, int n)
{
	int temp = 0, temp1 = 0;
	for(int i = 0 ; i<n ; i++)
		p[i] = i+1;

	for(int len = n ; len>0 ; len--)
	{
		temp = rand()%len;
		temp1 = p[len-1];
		p[len-1] = p[temp];
		p[temp] = temp1;
	}
}