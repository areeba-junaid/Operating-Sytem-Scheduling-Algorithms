#include<stdio.h>
#include<conio.h>
struct node
{
    int no;
    int art;
    int et;
    int st;
    float uti;
    int endt;
    int tt;
    int wt;
};
int no=0,art=-1;
node* arr;
void buildarray(int t,int a)
{
    arr[a].art=++art;
    arr[a].no=++no;
    arr[a].et=t;
    return;

}
void swap (node *a,node *b)
{
    node t=*a;
    *a=*b;
    *b=t;

}
int setstart(int st,int a)
{

        arr[a].st=st;
        st=arr[a].et+st;
        return st;
}
int setend(int endt,int a)
{

        endt=arr[a].et+endt;
        arr[a].endt=endt;
        return endt;
}
main()
{
    int n,t;
    float avgw=0.0,avgtt=0.0,avgut=0.0;
    printf("\tENTER NUMBER OF PROCESSES:\t");
    scanf("%d",&n);
    arr=new node[n];
    int p=1;
    for(int a=0;a<n;a++)
    {
        printf("\tENTER NUMBER OF INSTRUCTIONS FOR %d\t",p);
        scanf("%d",&t);
        buildarray(t,a);
        p++;
    }

    int a=0,q=0,st=0,endt=0;
    while(a<n)
    {
        st=setstart(st,a);
        endt=setend(endt,a);
        q=endt;
        a++;
       for(int i=a;i<q;i++)
        {
            for(int j=i+1;j<=q;j++)
            {
               if(j>n)
                {
                    break;
                }
                if(arr[i].et>arr[j].et)
                {
                    swap(&arr[i],&arr[j]);
                }
            }

        }
    }

    for(int a=0;a<n;a++)
    {
        arr[a].tt=arr[a].endt-arr[a].art;
        arr[a].wt=arr[a].st-arr[a].art;
        arr[a].uti=((float)arr[a].et/(float)arr[a].tt)*100;
        avgw=avgw+arr[a].wt;
        avgtt=avgtt+arr[a].tt;
        avgut=avgut+arr[a].uti;
    }
    avgw=avgw/n;
    avgtt=avgtt/n;
    avgut=avgut/n;
    printf("\n\t\t============================================================================================================");
    printf("\n\t\t ProcessNo\tArrivalTime\tExecutionTime\tWaitingTime\tCompletionTime\tT.T_Time\tUtilization");
     for(int a=0;a<n;a++)
    {
        printf("\n\t\t%d\t\t%d\t\t %d\t\t %d\t\t %d\t\t %d\t\t %f",arr[a].no,arr[a].art,arr[a].et,arr[a].wt,arr[a].endt,arr[a].tt,arr[a].uti);

    }
    printf("\n\t\t============================================================================================================");
    printf("\n\n\t\tAverage Waiting Time:  %f\n\t\tAverage Turnaround Time: %f\n\t\tAverage Utilization: %f\n",avgw,avgtt,avgut);

}

