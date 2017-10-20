#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#define MAX 1000

int sort0[MAX];
int sort[MAX];

void print_star(int a[],int n)
{
	int x,y;
	for(x=0;x<n;x++) {
     for(y=0;y<a[x];y++)
        printf("*");
    printf("\n");
	}
}
void print_data(int a[],int n)
{
	int i;
	for(i=1;i<=n;i++)
		printf("%d  ",a[i]);
}

void Heapify(int first,int last)
{
    int r;
    r=first;
    while(r<=last/2)
    {
        if((r==last/2)&&(last%2==0))
        {
            if(sort0[r]<sort0[2*r])
            {
                int temp1=sort0[r];
                sort0[r]=sort0[2*r];
                sort0[2*r]=temp1;
            }
            r=last;
        }
        else if((sort0[r]<sort0[2*r])&&(sort0[2*r]>=sort0[2*r+1]))
        {
            int temp2=sort0[r];
            sort0[r]=sort0[2*r];
            sort0[2*r]=temp2;
            r=2*r;
        }
        else if((sort0[r]<sort0[2*r+1])&&(sort0[2*r+1]>sort0[2*r]))
        {
            int temp3=sort0[r];
            sort0[r]=sort0[2*r+1];
            sort0[2*r+1]=temp3;
            r=2*r+1;
        }
        else
        {
            r=last;
        }

    }
}
void BuildMaxHeap(int n)
{
    int i;
    for(int i=n/2; i>=1; i--)
    {
        Heapify(i,n);
        if(n<=20)
        	print_star(sort0,n);
        print_data(sort0,n);
        printf("\n");
    }
    printf("maxsort0 build!\n");
}

void HeapSort(int n)
{
	int i;
	BuildMaxHeap(n);
	for( i=n; i>=2; i--)
        {
            int temp=sort0[1];
            sort0[1]=sort0[i];
            sort0[i]=temp;
            Heapify(1,i-1);
            if(n<=20)
            	print_star(sort0,n);
            print_data(sort0,n);
            printf("\n");
        }
}

void CountingSort(int a[],int n)
{
	int x;
	int c[10];
	int b[n];
	for(x=1;x<=n;x++)
		b[x]=0;
	for(x=0;x<10;x++)
		c[x]=0;
	for(x=1;x<=n;x++)
		c[a[x]]=c[a[x]]+1;
	for(x=1;x<10;x++)
		c[x]=c[x]+c[x-1];
	for(x=n;x>=1;x--)
	{
        b[c[a[x]]]=sort[x];
        c[a[x]]=c[a[x]]-1;
	}
	for(x=1;x<=n;x++)
		sort[x]=b[x];
	print_data(sort,n);
	printf("\n");
}

void RadixSort(int n)
{
	int i;
	int digit[n];
	printf("round 1\n");
	for(i=1;i<=n;i++)
	{
		digit[i]=sort[i]%10;
	}
	print_data(digit,n);
	printf("\n");
	CountingSort(digit,n);
	printf("round 2\n");
	for(i=1;i<=n;i++)
	{
		digit[i]=(sort[i]%100)/10;
	}
    print_data(digit,n);
	printf("\n");
	CountingSort(digit,n);
	printf("round 3\n");
	for(i=1;i<=n;i++)
	{
		digit[i]=(sort[i]%1000)/100;
	}
    print_data(digit,n);
	printf("\n");
	CountingSort(digit,n);
}

int main(int argc, char const *argv[])
{
	int i,n,id;
	char ch='v';
	srand(time(NULL));
	while(1)
	{
			printf("\n======put in the sort methord you want to choose======\n\t1:Heap sort\n\t2:Radix sort\n");
			while(scanf("%d",&id)==1)// Error check
		{
			if(id==1||id==2)
				break;
			else
				printf("wrong input! input number should be 1 or 2\nreinput:\n");
		}
		printf("input how many numbers you want to sort\n");
		while(scanf("%d",&n)==1)// Error check
		{
			if(n<=0||n>MAX)
				printf("ERROR:input number illegal(0<n<1000)\nreinput:\n");
			else 
				break;
		}

		printf("%d number to be sorted,input data:\n",n);

	if(id==1)
	{
		printf("using HeapSort\n");
		if(n<=20)
		{
			for(i=1;i<=n;i++)	
				sort0[i]= rand()%15+1;//when n≤20,range between 1 and 15
			for(i=1;i<=n;i++)
				printf("%d  ",sort0[i]);
			//=============================================
			printf("\n=================\n");
		}
		else
		{
			for(i=1;i<=n;i++)
				sort0[i]= rand()%32767+1;//when n>20,range int(32767)
			for(i=1;i<=n;i++)
				printf("%d  ",sort0[i]);
		printf("\n=================\n");
		}
	}

	else if(id==2)
	{
		printf("using RadixSort\n");
		for(i=1;i<=n;i++)	
				sort[i]= rand()%1000;//rang between 0 and 999
			for(i=1;i<=n;i++)
				printf("%d  ",sort[i]);
			//=============================================
			printf("\n=================\n");
	}

			switch(id)
			{
					case 1:
					HeapSort(n); 
					printf("\n====result=====\n");
	     			print_data(sort0,n);
					break;
					case 2:
					RadixSort(n);
					printf("\n====result=====\n");
	     			print_data(sort,n);
					break;
			}

			printf("\npress'q' to Quit,press anything else to continue\n");
			getchar();
			scanf("%c",&ch);
			if(ch=='q')
				break;
	}
		return 0;
}