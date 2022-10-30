#include <stdio.h>
#include <stdlib.h>

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
    printf("\nFor First Come First Serve\n");
    printf("Processes   Burst time   Waiting time  Response Time   Turn around time\n");

    // Calculate total waiting time and total turnaround time
    for (int  i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_bt = total_bt + bt[i];
        printf("   T%d ",(i+1));
        printf("       %d ", bt[i] );
        printf("     \t  %d",wt[i] );
        printf("        %d",wt[i]);
        printf("       %d\n",wt[i]+bt[i] );
    }
    float s=(float)total_wt / (float)n;
    float t=(float)(total_bt+total_wt) / (float)n;
    printf("Average waiting time = %0.2f",s);
    printf("\n");
    printf("Average turn around time = %0.2f ",t);
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
    printf("\nFor Shortest Job First\n");
    printf("Processes   Burst time   Waiting time  Response Time   Turn around time\n");


    // Calculate total waiting time and total turnaround time
    total_wt = total_bt = 0;
    for (int  i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_bt = total_bt + bt[i];
        printf("   T%d ",order[i]);
        printf("       %d ", bt[i] );
        printf("       %d",wt[i] );
        printf("        %d",wt[i]);
        printf("       %d\n",wt[i]+bt[i] );
    }
    int s=(float)total_wt / (float)n;
    int t=(float)(total_bt+total_wt) / (float)n;
    printf("Average waiting time = %d",s);
    printf("\n");
    printf("Average turn around time = %d ",t);

}

//Function to implement priority based CPU Scheduling
// The function takes in inputs as the number of tasks, burst time and priority for each task
void priority(int n, int bt[], int prior[])
{
    //declaring variables
    int order[n], wt[n], total_wt, total_bt, i, j, temp;
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
    printf("\nFor Priority Scheduling\n");
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
        printf("       %d",wt[i] );
        printf("        %d",wt[i]);
        printf("       %d\n",wt[i]+bt[i] );
    }
    int s=(float)total_wt / (float)n;
    int t=(float)(total_bt+total_wt) / (float)n;
    printf("Average waiting time = %d",s);
    printf("\n");
    printf("Average turn around time = %d ",t);
}

void round_robin(int n, int bt[], int quant)
{
    int wt[n], copy_bt[n];
    int tat[n];
    int rt[n];
    int sum =0, count =0;
    int i, y=n;
    int total_wt, total_tat, total_rt;

    rt[0] = 0;
    copy_bt[0]=bt[0];
    for(int j=1;j<n;j++)
    {
        rt[j] = rt[j-1] + min(quant, bt[j-1]);
        copy_bt[j]=bt[j];
    }
    for(sum=0, i = 0; y!=0; )
    {
        if(bt[i] <= quant && bt[i] > 0) // define the conditions
        {
            tat[i]=sum+bt[i];
            sum = sum + bt[i];
            wt[i]=sum-copy_bt[i];
            bt[i] = 0;
            count=1;
        }
        else if(bt[i] > 0)
        {
            bt[i] = bt[i] - quant;
            sum = sum + quant;
        }
        if(bt[i]==0 && count==1)
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

    printf("\nFor Round Robin\n");
    printf("Processes   Burst time   Waiting time  Response Time   Turn around time\n");

    // Calculate total waiting time and total turn
    // around time
    for (int  i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        total_rt = total_rt + rt[i];
        printf("   T%d ",(i+1));
        printf("       %d ", bt[i] );
        printf("       %d",wt[i] );
        printf("        %d",rt[i]);
        printf("       %d\n",tat[i] );
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

void priority_round_robin(int n, int bt[], int prior[], int quantum)
{

}

void main()
{
    printf("hi");
    int n = 5;
    int bt[5] = {20, 30, 10, 15, 90};
    int prior[5] = {8, 3, 1, 3, 2};
    int quantum = 20;
    fcfs (n, bt);
    sjf (n, bt);
    priority(n, bt, prior);
    round_robin(n, bt, quantum);

}
