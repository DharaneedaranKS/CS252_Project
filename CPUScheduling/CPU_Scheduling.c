

#include <stdio.h>
#include <stdlib.h>

//A function to compute the minimum of two integers
int min(int a, int b)
{
    return (a<b)?a:b;
}

// function to implement first come first serve
// The function takes in 2 inputs, number of tasks and burst time for each of these task
void fcfs(int n, int bt[])
{
    //intialising or declaring variables required for computation
    int wt[n]; // wait time for each task
    int total_wt=0; // total wait time
    int total_bt=0; // total burst time
    wt[0] = 0; //initalising the wait time of the first task as 0 as its universally true

    //for loop calculating the wait time for each task
    //As in FCFS, the wait time is equal to the sum of all task's burst time that has been executed before it, the same has been implemented here
    for (int i=1; i<n; i++)
    {
        wt[i] = wt[i-1] + bt[i-1];
    }

    //printing the outputs
    printf("\n\n\nFor First Come First Serve\n");
    printf("Processes   Burst time   Waiting time  Response Time   Turn around time\n");

    // Calculate total waiting time and total turnaround time
    for (int  i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_bt = total_bt + bt[i];
        printf("   T%d ",(i+1));
        printf("       %d ", bt[i] );
        printf("     \t  %d",wt[i] );
        printf("                %d",wt[i]);
        printf("                    %d\n",wt[i]+bt[i] );
    }
    float s=(float)total_wt / (float)n;
    float t=(float)(total_bt+total_wt) / (float)n;
    printf("Average waiting time = %0.2f",s);
    printf("\n");
    printf("Average turn around time = %0.2f ",t);
    printf("\n");
    printf("Average response time = %0.2f ",s);
}

// Function to implement Round Robin method of CPU Scheduling 
//The function takes in 4 inputs, number of tasks, burst time for each, the quantum and sum
void round_robin(int n, int bt[], int quant, int sum)
{
    //intitalising variables for necessary computation
    int wt[n], copy_bt[n]; //wt - waiting and a copy for the burst time
    int tat[n]; // turn around time variable
    int rt[n]; //respinse time
    int  count =0; // a count variable
    int i, y=n; 
    int total_wt=0, total_tat=0, total_rt=0; //intialising variables for total waiting time, turnaround time, response time

    rt[0] = 0; //As the first process response time will always be 0
    copy_bt[0]=bt[0]; //copying the first burst time into the copy variable
    //For loop to compute the response time of the each process and simulatenously copy the rest of the burst time into the copy variable
    for(int j=1;j<n;j++)
    {
        rt[j] = rt[j-1] + min(quant, bt[j-1]); //accounting for the case if the burst time is less than a quantum
        copy_bt[j]=bt[j];
    }
    //Calculating Wait and Turnaround time
    for(sum=0, i = 0; y!=0; )
    {
        if(copy_bt[i] <= quant && copy_bt[i] > 0) // define the conditions
        {
            tat[i]=sum+copy_bt[i];
            sum = sum + copy_bt[i];
            wt[i]=sum-bt[i];
            copy_bt[i] = 0;
            count=1;
        }
        else if(copy_bt[i] > quant)
        {
            copy_bt[i] = copy_bt[i] - quant;
            sum = sum + quant;
        }
        if(copy_bt[i]==0 && count==1)
        {
            y--; //decrement the process no.
            count =0;
        }
        if(i==n-1)
        {
            i=0;
        }
        else
        {
            i++;
        }
    }
    
    // Printing out all the values and final result
    printf("\n\n\nFor Round Robin\n");
    printf("Processes   Burst time   Waiting time  Response Time   Turn around time\n");
    
    for (int  i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        total_rt = total_rt + rt[i];
        printf("   T%d ",(i+1));
        printf("       %d ", bt[i] );
        printf("        %d",wt[i] );
        printf("            %d",rt[i]);
        printf("                %d\n",tat[i] );
    }
    int s=(float)total_wt / (float)n;
    int t=(float)(total_tat) / (float)n;
    int r=(float)(total_rt) / (float)n;
    printf("Average waiting time = %d",s);
    printf("\n");
    printf("Average turn around time = %d ",t);
    printf("\n");
    printf("Average response time = %d ",r);
}

// Function to implement Shortest Job First
// The function takes in 2 inputs, number of tasks and burst time for each of these task
void sjf(int n, int bt[])
{
    //declaring local variables used for computation throughout the function
    int order[n], wt[n], total_wt, total_bt, i, j, temp;
    /* order - to decide and track the order in which the tasks are implemented
    wt - wait time of each induvitual task
    total_wt - total waiting time, total_bt -  total burst time
    i, j - loop variables
    temp - for storing swapping elements*/

    // for loop intitalising the order
    for (i=1; i<=n;i++)
    {
        order[i-1] = i;
    }

    //for loop to decide the order of the task being executed as per the shortest execution time
    for(int i=0; i<n;i++)
    {
        for (int j=i+1; j<n;j++)
        {
            if (bt[j]<bt[i])
            {
                temp = bt[j];
                bt[j] = bt[i];
                bt[i] = temp;

                temp = order[j];
                order[j] = order[i];
                order[i] = temp;
            }
        }
    }

    wt[0] = 0; //initalising the wait time of the first task as 0 as its universally true
    // Calculation of waiting time
    for (int i=1; i<n; i++)
    {
        wt[i] = wt[i-1] + bt[i-1];
    }

    //Output
    printf("\n\n\nFor Shortest Job First\n");
    printf("Processes   Burst time   Waiting time  Response Time   Turn around time\n");


    // Calculate total waiting time and total turnaround time
    total_wt = total_bt = 0;
    for (int  i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_bt = total_bt + bt[i];
        printf("   T%d ",order[i]);
        printf("       %d ", bt[i] );
        printf("        %d",wt[i] );
        printf("            %d",wt[i]);
        printf("                %d\n",wt[i]+bt[i] );
    }
    int s=(float)total_wt / (float)n;
    int t=(float)(total_bt+total_wt) / (float)n;
    printf("Average waiting time = %d",s);
    printf("\n");
    printf("Average turn around time = %d ",t);
    printf("\n");
    printf("Average response time = %d ",s);

}

//Function to implement priority based CPU Scheduling
// The function takes in inputs as the number of tasks, burst time and priority for each task
void priority(int n, int bt[], int prior[])
{
    //declaring variables
    int order[n], wt[n], total_wt, total_bt,total_rt=0, i, j, temp;
        /* order - to decide and track the order in which the tasks are implemented
    wt - wait time of each induvitual task
    total_wt - total waiting time, total_bt -  total burst time
    i, j - loop variables
    temp - for storing swapping elements*/

    // For loop deciding the order of execution of the tasks based on priority of each
    for (i=1; i<=n;i++)
    {
        order[i-1] = i;
    }
    for(int i=0; i<n;i++)
    {
        for (int j=i+1; j<n;j++)
        {
            if (prior[j]<prior[i])
            {
                temp = prior[j];
                prior[j] = prior[i];
                prior[i] = temp;

                temp = bt[j];
                bt[j] = bt[i];
                bt[i] = temp;

                temp = order[j];
                order[j] = order[i];
                order[i] = temp;
            }
        }
    }
    // intial task waiting time intialised to 0 as univerally true
    wt[0] = 0;
    //Computation fo wait time for each tasl
    for (int i=1; i<n; i++)
    {
        wt[i] = wt[i-1] + bt[i-1];
    }
    //printing out the output
    printf("\n\n\nFor Priority Scheduling\n");
    printf("Processes   Burst time   Priorirty   Waiting time  Response Time   Turn around time\n");


    // Calculate total waiting time and total turnaround time
    total_wt = total_bt = 0;
    for (int  i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_bt = total_bt + bt[i];
        printf("   T%d ",order[i]);
        printf("       %d ", bt[i] );
        printf("      \t %d ", prior[i] );
        printf("            %d",wt[i] );
        printf("                %d",wt[i]);
        printf("                    %d\n",wt[i]+bt[i] );
    }
    int s=(float)total_wt / (float)n;
    int t=(float)(total_bt+total_wt) / (float)n;
    printf("Average waiting time = %d",s);
    printf("\n");
    printf("Average turn around time = %d ",t);
    printf("\n");
    printf("Average response time = %d ",s);
}

// Function to implement Priority Round Robin's round robin
/*This function takes in multiple inputs. 
  n -> number of tasks
  start -> The starting index of the process with the same priotiy
  bt -> burt time ; wt -> Wait Time ; rt -> Response time; tat -> Turnaround time
  quant -> Quantum in ms ; sum -> Response time sum as of now*/
void round_robin_for_priority(int n, int start, int bt[], int quant, int sum, int wt[],int rt[], int tat[])
{
    //initialising variables for computation through the function
    int copy_bt[n]; // a copy for the burst time
    int  count =0;
    int i, y=n;
    int total_wt=0, total_tat=0, total_rt=0; // intialising variables for total waiting time, turnaround time, response time

    rt[start] = 0 + sum; //Inititalising the very first response time as the sum off all time that has passed 
    copy_bt[0]=bt[start]; // copying Burst time into the secondary array
    // For loop calculation and assigning values of response time for each task
    for(int j=start+1;j<n+start;j++)
    {
        rt[j] = rt[j-1] + min(quant, bt[j-1]);
        copy_bt[j-start]=bt[j];
    }
    // Calculating turn around time and wait time
    for(i = 0; y!=0; )
    {
        if(copy_bt[i] <= quant && copy_bt[i] > 0) // define the conditions
        {
            tat[i+start]=sum+copy_bt[i];
            sum = sum + copy_bt[i];
            wt[i+start]=sum-bt[i+start];
            copy_bt[i] = 0;
            count=1;
        }
        else if(copy_bt[i] > quant)
        {
            copy_bt[i] = copy_bt[i] - quant;
            sum = sum + quant;
        }
        if(copy_bt[i]==0 && count==1)
        {
            y--; //decrement the process no.
            count =0;
        }
        if(i==n-1)
        {
            i=0;
        }
        else
        {
            i++;
        }
    }

}


// The main function to implement Priority Round Robin
//The function takes the number of tasks, burst time, priotrity and the quantum time as input
void priority_round_robin(int n, int bt[], int prior[], int quantum)
{
    //declaring variables
    int order[n], wt[n],rt[n],tat[n], total_wt, total_tat, total_rt =0, i, j, temp;
        /* order - to decide and track the order in which the tasks are implemented
    wt - wait time of each induvitual task
    total_wt - total waiting time, total_bt -  total burst time
    i, j - loop variables
    temp - for storing swapping elements*/

    // For loop deciding the order of execution of the tasks based on priority of each process
    for (i=1; i<=n;i++)
    {
        order[i-1] = i;
    }
    for(int i=0; i<n;i++)
    {
        for (int j=i+1; j<n;j++)
        {
            if (prior[j]<prior[i])
            {
                temp = prior[j];
                prior[j] = prior[i];
                prior[i] = temp;

                temp = bt[j];
                bt[j] = bt[i];
                bt[i] = temp;

                temp = order[j];
                order[j] = order[i];
                order[i] = temp;
            }
        }
    }
    // intial task waiting and response time intialised to 0 as univerally true
    wt[0] = 0;
    rt[0]=0;
    
    //Executing priotity and round robin scheduling
    for(int j=0;j<n;j++)
      {
        int start =j;
        int end =j;
        for(int k=j+1;k<n;k++)
          {
            if(prior[k]==prior[j])
              end =k;
            else
              break;
          }
        if(start==end)
        {
          if(j==0)
          {
            tat[0]=bt[0];
          }
          else
          {
            wt[j] = wt[j-1] + bt[j-1];
            rt[j]=wt[j];
            tat[j]=wt[j]+bt[j];
          }
        }

        else
        {
          round_robin_for_priority(end-start+1, start, bt, quantum, wt[start-1]+bt[start-1], wt, rt, tat);
          j=end;
        }
      }

    //printing out the output
    printf("\n\n\nFor Priority based round robin Scheduling\n");
    printf("Processes   Burst time   Priorirty   Waiting time  Response Time   Turn around time\n");


    // Calculate total waiting time and total turnaround time
    total_wt = total_tat = 0;
    for (int  i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        total_rt = total_rt+rt[i];
        printf("   T%d ",order[i]);
        printf("       %d ", bt[i] );
        printf("      \t %d ", prior[i] );
        printf("            %d",wt[i] );
        printf("                %d",rt[i]);
        printf("                    %d\n",tat[i] );
    }
    int s=(float)total_wt / (float)n;
    int t=(float)(total_tat) / (float)n;
    int r =(float)(total_rt) / (float)n;
    printf("Average waiting time = %d",s);
    printf("\n");
    printf("Average turn around time = %d ",t);
    printf("\n");
    printf("Average response time = %d ",r);
}

int main()
{
    //Declaring variables
    int n; //number of process
    int quantum = 10; //defining the quantum time in ms
    
    //Accepting input from user regarding the process priority and burst time
    printf("Please enter the no of processes: ");
    scanf("%d", &n);
    int bt[n], prior[n], copy_bt[n], bt_sjf[n], prior_copy[n];
    printf("\nEnter details of each task in the order of T1 to T%d as : <priority> <burst time>\n" ,n);
    for(int i =0; i<n;i++)
    {
        printf("T%d: ", i+1);
        scanf("%d %d",&prior[i], &bt[i]);
        //Making duplicates of burst time and priority for call by reference
        copy_bt[i]=bt[i];
        bt_sjf[i]=bt[i];
        prior_copy[i]=prior[i];

    }

    /* TEST CASE
    int n = 5;
    int bt[5]={20,30,10,15,90};
    int copy_bt[5]={20,30,10,15,90};
    int bt_sjf[5]={20,30,10,15,90};
    int prior[5] = {8, 3, 1, 3, 2};
    int prior_copy[5] ={8, 3, 1, 3, 2};*/
    
    //Calling all the different implementation of CPU Scheduling
    fcfs (n, bt);
    round_robin(n, copy_bt, quantum,0);
    sjf (n, bt_sjf);
    priority(n, copy_bt, prior);
    priority_round_robin(n, bt, prior_copy, quantum);


}

