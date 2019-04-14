#include<stdio.h>

struct process
{
      char process_name;
      int arrival_time, burst_time, ct, waiting_time, turnaround_time, priority;
      int status;
      int enter;
}process_queue[100],roundRobin[100];

int limit;
int quant_time;
void Arrival_Time_Sorting()
{
      struct process temp;
      int i, j;
      for(i = 0; i < limit - 1; i++)
      {
            for(j = i + 1; j < limit; j++)
            {
                  if(process_queue[i].arrival_time > process_queue[j].arrival_time)
                  {
                        temp = process_queue[i];
                        process_queue[i] = process_queue[j];
                        process_queue[j] = temp;
                  }
            }
      }
}
void round_robin(int time,int size){
  int i, limit, total = 0, x, counter = 0, time_quantum; 
  int wait_time = 0, turnaround_time = 0; 
  limit = size;
  x = limit;
  time_quantum = time;
  printf("\nProcess ID\t\tBurst Time\t Turnaround Time\t Waiting Time\n");
  for(total = 0, i = 0; x != 0;) 
      { 
            if(roundRobin[i].burst_time <= time_quantum && roundRobin[i].burst_time > 0) 
            { 
                  total = total + roundRobin[i].burst_time; 
                  roundRobin[i].burst_time = 0; 
                  counter = 1; 
            } 
            else if(roundRobin[i].burst_time > 0) 
            { 
                  roundRobin[i].burst_time = roundRobin[i].burst_time - time_quantum; 
                  total = total + time_quantum; 
            } 
            if(roundRobin[i].burst_time == 0 && counter == 1) 
            { 
                  x--; 
                  printf("\nProcess[%d]\t\t%d\t\t %d\t\t\t %d", i + 1, roundRobin[i].ct, total - roundRobin[i].arrival_time, total - roundRobin[i].arrival_time - roundRobin[i].ct);
                  wait_time = wait_time + total - roundRobin[i].arrival_time - roundRobin[i].ct; 
                  turnaround_time = turnaround_time + total - roundRobin[i].arrival_time; 
                  counter = 0; 
            } 
            if(i == limit - 1) 
            {
                  i = 0; 
            }
            else if(roundRobin[i+1].arrival_time <= total) 
            {
                  i++;
            }
            else 
            {
                  i = 0;
            }
      } 
}
void main()
{
      int i;
	  int time = 0;
	  int burst_time = 0; 
	  int largest = 0;
      char c;
      int k = 0;
      int r = -1;
      int sub_time = 1;
      float wait_time = 0; 
      int end_time;
      int prC = 0;
	  float turnaround_time = 0; 
	  float average_waiting_time; 
	  float average_turnaround_time;
	  printf("///////////////MULTILEVEL QUEUE SCHEDULING ALGORITHM/////////////////\n");
      printf("\nEnter Total Number of Processes:\t");
      scanf("%d", &limit);
      for(i = 0, c = 'A'; i < limit; i++, c++)
      {
            process_queue[i].process_name = c;
            printf("\nEnter Details For Process[%C]:\n", process_queue[i].process_name);
            printf("Enter Arrival Time:\t");
            scanf("%d", &process_queue[i].arrival_time );
            printf("Enter Burst Time:\t");
            scanf("%d", &process_queue[i].burst_time);
            printf("Enter Priority:\t");
            scanf("%d", &process_queue[i].priority);
            process_queue[i].status = 0;
            process_queue[i].enter = 0;
            process_queue[i].ct = process_queue[i].burst_time;
            burst_time = burst_time + process_queue[i].burst_time;
      }
      Arrival_Time_Sorting();
      
      for(time = process_queue[0].arrival_time; time < burst_time;time++)
      {
            
            if(process_queue[largest].burst_time<=0){
            	int end_time = time;
            	process_queue[largest].turnaround_time = end_time - process_queue[largest].arrival_time;
            	process_queue[largest].status = 1;
		    }
            for(i = 0; i < limit; i++)
            {
            	  if(process_queue[largest].status==1 && process_queue[i].arrival_time<=time){
            	  	largest = i;
				  }else if(process_queue[i].arrival_time <= time && process_queue[i].status != 1 && process_queue[i].priority > process_queue[largest].priority)
                  {
                  	    
                  	    int end_time = time;
                  	    process_queue[largest].turnaround_time = end_time - process_queue[largest].arrival_time;
                  	    
						r++;
						roundRobin[r] = process_queue[largest];
						roundRobin[r].arrival_time = time;
						roundRobin[r].ct = roundRobin[r].burst_time;
						process_queue[largest].enter = 1;
                  	    process_queue[largest].status = 1;
                  	    burst_time = burst_time - process_queue[largest].burst_time;
                        largest = i;
                  }
            }
            process_queue[largest].burst_time = process_queue[largest].burst_time - sub_time;
            
	  }
	  ///////////////////////////////////////////////////////////////////////////////
	  end_time = time;
      process_queue[largest].turnaround_time = end_time - process_queue[largest].arrival_time;
      //////////////////////////////////////////////////////////////////////////////
      
	  for(prC;prC<limit;prC++){
        process_queue[prC].waiting_time =  process_queue[prC].turnaround_time - process_queue[prC].ct;
	  }
	  prC = 0;
	  for(prC;prC<=r;prC++){
	  	roundRobin[prC].waiting_time = roundRobin[prC].turnaround_time - roundRobin[prC].ct;
	  }
	  prC = 0;
	  int l = 0;
	  printf("Waiting time of Interactive processes\n");
	  printf("ProcessName   Arrival Time   BurstTime   Priority   WaitingTime\n");
	  for(prC;prC<limit;prC++){
        if(process_queue[prC].enter!=1){
        	printf("%c   %d   %d   %d   %d\n",process_queue[prC].process_name,process_queue[prC].arrival_time,process_queue[prC].ct,process_queue[prC].priority,process_queue[prC].waiting_time);
		}
	  }
	  printf("////////////////////ENABLING ROUND ROBIN SCHEDULING///////////////////\n");
      printf("\n");
	  printf("Enter the quantum time for roundRobin algorithm\n");
	  scanf("%d",&quant_time);
	  round_robin(quant_time,r+1);
      printf("////////////////////EXIT///////////////////////////////////////////////\n");
}

