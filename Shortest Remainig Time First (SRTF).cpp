#include<stdio.h>
#include<conio.h>
struct Node
{
    int no;
    int arrivalTime;
    int execTime;
    int ReIns;
    int startTime;
    int waiting;
    int CmpTime;
};

int no,arr,n,Quantum;
float avgWait=0.0,avgUti=0.0,avgTT=0.0;
Node *process;
void Buildarray(int index,int Total)
{
    process[index].arrivalTime=++arr;
    process[index].no=++no;
    process[index].execTime=Total;
    process[index].ReIns=Total;
}
int Search(int arrival)
{
    for(int i=0;i<=n-1;i++)
    {
        if(process[i].arrivalTime==arrival)
         return i;
    }
    return -1;
}
int MinExecution(int index,int arrival)
{
    int minimum=index;
    for(int i=index;process[i+1].arrivalTime==arrival;i++)
    {
        if(process[i].ReIns>process[i+1].ReIns)
        {
            minimum=i+1;
        }
    }
    return minimum;
}
int Get_Shortest(int Range)
{    int shortest;
     int a=0;
        while(process[a].ReIns==0)
        {
            a=a+1;
        }
        shortest=a;
        for (int i=a+1;i<=Range;i++)
        {
           if(process[i].ReIns!=0)
           {
            { if((process[shortest].ReIns > process[i].ReIns))
                shortest=i;
            }
           }
        }
        return shortest;
}

void Display(int index)
{   int  Turnaround=process[index].CmpTime-process[index].arrivalTime;
    int waiting=Turnaround-process[index].execTime;
    float Utilization=((float)process[index].execTime/(float)Turnaround)*100.0;
    printf("\n\t\t   %d    \t      %d    \t     %d     \t     %d    \t       %d     \t  %d     \t   %.2f    ",process[index].no,process[index].arrivalTime,
    process[index].execTime,waiting,process[index].CmpTime,Turnaround,Utilization);
    avgWait=avgWait+waiting;
    avgUti=avgUti+Utilization;
    avgTT=avgTT+Turnaround;
}

void Processing(int Max_ArrivalTime,int count)
{
int Ins,mini,curr,prev;
prev=0;
while(count>=1)
{
    curr=Search(Quantum);
    if(curr!=-1 && Quantum <= Max_ArrivalTime)
    {   mini=MinExecution(curr,Quantum);
        if ((process[prev].ReIns <=process[mini].ReIns) && process[prev].ReIns!=0)
            curr=prev;
        else
            curr=mini;
        Ins=1;
    }
    else if(curr==-1 && Max_ArrivalTime<Quantum)
    {
        curr=Get_Shortest(n-1);
        Ins=process[curr].ReIns;
    }
    if(process[curr].ReIns==process[curr].execTime)
    {
        process[curr].startTime=Quantum;
    }
    if(process[curr].ReIns >0)
   {
    Quantum=Quantum+Ins;
    process[curr].ReIns=process[curr].ReIns-Ins;
    if(process[curr].ReIns==0)
    {  count--;
       process[curr].CmpTime=Quantum;
       Display(curr);
    }

    if(count!=0)
        prev=Get_Shortest(Quantum-1);
   }
   else
       Quantum++;
}
}
int main()
{
    int t,Max_ArrivalTime,count;
    no=0;
    arr=-1;
    printf("\n\tEnter No of Process: ");
    scanf("%d",&n);
    process=new Node [n];
    for (int i=0;i<=n-1;i++)
    {
        printf("\tEnter Total Instruction of Process %d:  ",i+1);
        scanf("%d",&t);
        Buildarray(i,t);
    }
    Max_ArrivalTime=process[n-1].arrivalTime;
    Quantum=process[0].arrivalTime;
    count= n;
    printf("\n\t\t__________________________________________________________________________________________________________________\n");
    printf("\n\t\tProcessNo\tArrivalTime\tExecutionTime\tWaitingTime\tCompletionTime\tT.T_Time\tUtilization");
    Processing(Max_ArrivalTime,count);
    printf("\n\t\t___________________________________________________________________________________________________________________\n");
    delete[] process;
    printf("\n\t\tThe Average Waiting Time is : %.2f\n",avgWait/n);
    printf("\n\t\tThe Average Utilization Time is : %.2f\n",avgUti/n);
    printf("\n\t\tThe Average Turnaround Time is : %.2f\n",avgTT/n);
}
