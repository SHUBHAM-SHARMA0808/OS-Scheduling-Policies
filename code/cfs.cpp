#include<iostream>
#include<math.h>
#include<queue>
#include<map>

using namespace std;

int main(int argc, char** argv)
{
	int range1 = 9;
    int range2 = 9;
    int range3 = 40;
    int temp = 0;
    int *arrival_time;
    int *process_id;
    int *burst_time;
    int *d_burst_time;
    int *completion_time;
    int *turn_around_time;
    int *waiting_time;
    int *processed;
    int *nice_value;
    double *weight;
    int *responded;
    double *vrun_time;
    int *actual_run_time;
    int no_of_processes;
    double total_weight = 0;
    int choice;
    multimap<int, int, less<int> > m;
    
    srand(time(0));

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
    	processed = (int *)malloc(sizeof(int)*no_of_processes);
        nice_value = (int *)malloc(sizeof(int)*no_of_processes);
        weight = (double *)malloc(sizeof(double)*no_of_processes);
        responded = (int *)malloc(sizeof(int)*no_of_processes);
        vrun_time = (double *)malloc(sizeof(double)*no_of_processes);
        actual_run_time = (int *)malloc(sizeof(int)*no_of_processes);
    	cout<<"Enter arrival_time, burst_time and nice_value"<<endl;
    	for(int i = 0 ; i<no_of_processes ; i++)
    	{
     		process_id[i] = i+1;
            cin>>arrival_time[i];
            cin>>burst_time[i];
           
            cin>>nice_value[i];
            completion_time[i] = 0;
            turn_around_time[i] = 0;
            waiting_time[i] = 0;
            processed[i] = 0;
            responded[i] = 0;
            vrun_time[i] = 0;
            actual_run_time[i] = 0;
	    }

    }
    else
    {
        no_of_processes = rand()%range1+1;
	    cout<<"No. of processes = "<<no_of_processes<<endl;
	    arrival_time = (int *)malloc(sizeof(int)*no_of_processes);
	    burst_time = (int *)malloc(sizeof(int)*no_of_processes);
        d_burst_time = (int *)malloc(sizeof(int)*no_of_processes);
	    process_id = (int *)malloc(sizeof(int)*no_of_processes);
	    turn_around_time = (int *)malloc(sizeof(int)*no_of_processes);
	    completion_time = (int *)malloc(sizeof(int)*no_of_processes);
	    waiting_time = (int *)malloc(sizeof(int)*no_of_processes);
	    processed = (int *)malloc(sizeof(int)*no_of_processes);
        nice_value = (int *)malloc(sizeof(int)*no_of_processes);
        weight = (double *)malloc(sizeof(double)*no_of_processes);
        responded = (int *)malloc(sizeof(int)*no_of_processes);
        vrun_time = (double *)malloc(sizeof(double)*no_of_processes);
        actual_run_time = (int *)malloc(sizeof(int)*no_of_processes);
	    for(int i = 0 ; i<no_of_processes ; i++)
	    {
		    process_id[i] = i+1;
            arrival_time[i] = rand()%range2;
            burst_time[i] = rand()%range2+1;
            
            nice_value[i] = rand()%range3-20; 
            completion_time[i] = 0;
            turn_around_time[i] = 0;
            waiting_time[i] = 0;
            processed[i] = 0;
            responded[i] = 0;
            vrun_time[i] = 0;
            actual_run_time[i] = 0;
	    }
	} 

    int weight_for_pri[40] = {
      88761,     71755,     56483,     46273,     36291,
      29154,     23254,     18705,     14949,     11916,
       9548,      7620,      6100,      4904,      3906,
       3121,      2501,      1991,      1586,      1277,
       1024,       820,       655,       526,       423,
        335,       272,       215,       172,       137,
        110,        87,        70,        56,        45,
         36,        29,        23,        18,        15,};

    for(int i = 0 ; i<no_of_processes ; i++)
    {
        weight[i] = weight_for_pri[nice_value[i]+20];
        d_burst_time[i] = burst_time[i];
    }

	cout<<"\nProcess id    Arrival time    Burst time    Nice_vlaue      Weight\n";
	for(int i = 0 ; i<no_of_processes ; i++)
	{
		cout<<"    "<<process_id[i]<<"             "<<arrival_time[i]<<"              "<<burst_time[i]<<"              "<<nice_value[i]<<"            "<<weight[i]<<endl;
	}
	
	cout<<"\nGantt chart : \n";
	int count = 0, min_gran = 4, targeted_latency = 20, cs = 0, flag = 0;
    double time_slice = 0, min_vrun = 0, run_time = 0;
    pair<int, int> run_process;
    multimap<int, int> :: iterator itr;
	for(int current_time = 0 ;  ; )
	{
        targeted_latency = 20;
        flag = 0;
        cout<<"\n current_time is "<<current_time<<" , ";
        for(int i = 0 ; i<no_of_processes ; i++)
        {
            if(arrival_time[i]<=current_time && !responded[i])
            {
                vrun_time[i] = min_vrun;
                m.insert(make_pair(vrun_time[i], i));
                cout<<"  process "<<process_id[i]<<" inserted into rb tree with vrun_time = "<<vrun_time[i]<<endl;
                responded[i] = 1;
                min_vrun = vrun_time[i];
                total_weight += weight[i];
                flag = 1;
            }
        }
        
        if(cs == 1 && flag == 1)
        {
            vrun_time[run_process.second] += run_time*(1024/weight[run_process.second]);
            m.insert(make_pair(vrun_time[run_process.second], run_process.second));
            cout<<"  process "<<process_id[run_process.second]<<" is preempted & pushed back in rb tree with updated vrun_time = "<<vrun_time[run_process.second]<<endl;
            cs = 0;
        }
        if(cs == 0 && !m.empty())
        {
            cs = 1;
            run_time = 0;
            //itr = m.fin(min_vrun);
            itr = m.begin();
            cout<<"  size of m is "<<m.size()<<endl;
            run_process.first = itr->first;
            run_process.second = itr->second;
            m.erase(itr);
            cout<<"  process "<<process_id[run_process.second]<<" is extracted from rb tree"<<endl;
            
            if((min_gran * (m.size()+1)) > targeted_latency)
                targeted_latency = (m.size()+1)*min_gran;

            time_slice = targeted_latency*(weight[run_process.second]/total_weight);
            d_burst_time[run_process.second]--;
            cout<<"  process "<<process_id[run_process.second]<<" exected for 1 unit rem burst time is "<<d_burst_time[run_process.second]<<endl;
            time_slice--;
            actual_run_time[run_process.second]++;
            run_time++;
            current_time++;
            if(d_burst_time[run_process.second] <= 0)
            {
                cout<<"  process "<<process_id[run_process.second]<<" completed at "<<current_time<<endl;
                processed[run_process.second] = 1;
                completion_time[run_process.second] = current_time;
                turn_around_time[run_process.second] = completion_time[run_process.second]-arrival_time[run_process.second];
                waiting_time[run_process.second] = turn_around_time[run_process.second]-burst_time[run_process.second];
                count++;
                total_weight -= weight[run_process.second];
                if(!m.empty())
                    min_vrun = (m.begin()->first);
                cs = 0;
            }
            else if(time_slice <= 0)
            {
                vrun_time[run_process.second] += run_time*(1024/weight[run_process.second]);
                m.insert(make_pair(vrun_time[run_process.second], run_process.second));
                cout<<"  process "<<process_id[run_process.second]<<" completed its time slice & pushed back in rb tree with updated vrun_time = "<<vrun_time[run_process.second]<<endl;
                min_vrun = (m.begin()->first);
                cs = 0;
            }
        }
        else if(cs == 1 && flag == 0)
        {
            d_burst_time[run_process.second]--;
            run_time++;
            cout<<"  process "<<process_id[run_process.second]<<" exected for 1 unit rem burst time is "<<d_burst_time[run_process.second]<<endl;
            time_slice--;
            actual_run_time[run_process.second]++;
            current_time++;
            if(d_burst_time[run_process.second] == 0)
            {
                cout<<"  process "<<process_id[run_process.second]<<" completed at "<<current_time<<endl;
                processed[run_process.second] = 1;
                completion_time[run_process.second] = current_time;
                turn_around_time[run_process.second] = completion_time[run_process.second]-arrival_time[run_process.second];
                waiting_time[run_process.second] = turn_around_time[run_process.second]-burst_time[run_process.second];
                count++;
                total_weight -= weight[run_process.second];
                if(!m.empty())
                    min_vrun = (m.begin()->first);
                cs = 0;
            }
            else if(time_slice <= 0)
            {
                vrun_time[run_process.second] += run_time*(1024/weight[run_process.second]);
                m.insert(make_pair(vrun_time[run_process.second], run_process.second));
                cout<<"  process "<<process_id[run_process.second]<<" completed its time slice & pushed back in rb tree with updated vrun_time = "<<vrun_time[run_process.second]<<endl;
                min_vrun = (m.begin()->first);
                cs = 0;
            }   
        }
        else
            current_time++;
        if(count == no_of_processes)
        	break;
	}

	double wait_sum = 0, mean_wait = 0, dif_sum = 0;
    double turn_around_sum = 0, mean_turn_around = 0, dif_sum2 = 0;
	cout<<"\nProcess id    Arrival time    Burst time    Nice_vlaue      Weight      completion_time     turn_around_time     waiting_time\n";
	for(int i = 0 ; i<no_of_processes ; i++)
	{ 
		cout<<"    "<<process_id[i]<<"             "<<arrival_time[i]<<"              "<<burst_time[i]<<"              "<<nice_value[i]<<"            "<<weight[i]<<"                 "<<completion_time[i]<<"                  "<<turn_around_time[i]<<"                 "<<waiting_time[i]<<endl;
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