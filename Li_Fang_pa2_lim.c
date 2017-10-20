#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int * prod(int n,int *u,int *v)
{
	int *x,*y,*w,*z;
	int *r1,*r2,*r3,*r4;
	int *result;
	int temp;
	int i;
	x = (int *)malloc(sizeof(int)*(n/2+1));
	y = (int *)malloc(sizeof(int)*(n/2+1));
	w = (int *)malloc(sizeof(int)*(n/2+1));
	z = (int *)malloc(sizeof(int)*(n/2+1));

	r1 = (int *)malloc(sizeof(int)*(n+1));
	r2 = (int *)malloc(sizeof(int)*(n+1));
	r3 = (int *)malloc(sizeof(int)*(n+1));
	r4 = (int *)malloc(sizeof(int)*(n+1));

	result = (int *)malloc(sizeof(int)*(2*n+2));

	int n1,m;
	if(n==0)
		return 0;
	if(n==1)
	{
		temp = u[0]*v[0];
		result[0] = temp / 10;
		result[1] = temp % 10;
		//return result;
	}

	if(n>=2)
	{
		m=n/2;//n1:digit number；
		if(n%2==0)
			n1=m;
		else
			n1=m+1;
//==========================
		if(n%2==0)
		{
			for(i=0;i<n1;i++)
			{
				x[i]=u[i];
				y[i]=u[i+n1];

				w[i]=v[i];
				z[i]=v[i+n1];
			}
		}
		if(n%2!=0)
		{
			x[0]=0;
			w[0]=0;
			for(i=0;i<n1-1;i++)
			{
				x[i+1]=u[i];
				w[i+1]=v[i];
			}
			for(i=0;i<n1;i++)
			{
				y[i]=u[i+n1-1];
				z[i]=v[i+n1-1];
			}
		}
//==========================

		r1=prod(n1,x,w);
		r2=prod(n1,x,z);
		r3=prod(n1,w,y);
		r4=prod(n1,y,z);

		for(i=0;i<2*n1;i++)
		{
			result[i]=r1[i];
		}
		for(i=2*n1;i<4*n1;i++)
		{
			result[i]=r4[i-2*n1];
		}
		for(i=n1;i<3*n1;i++)
		{
			result[i]=result[i]+r2[i-n1]+r3[i-n1];
		}
		for(i=4*n1-1;i>0;i--)
		{
			if(result[i]>=10)
			{
				result[i-1]=result[i-1]+result[i]/10;
				result[i]=result[i]%10;
			}
		}
		if(n1!=m)
		{
			for(i=0;i<4*n1-2;i++)
				result[i]=result[i+2];
		}
	}

	free(x);
	free(y);
	free(w);
	free(z);

	free(r1);
	free(r2);
	free(r3);
	free(r4);

	return result;
}



int * prod_3(int n,int *u,int *v)
{
	int *x,*y,*z,*i,*j,*l;
	int *r1,*r2,*r3,*r4,*r5,*r6,*r7,*r8,*r9;
	int *result;
	int m,a;


	result = (int *)malloc(sizeof(int)*(2*n+2));

	x = (int *)malloc(sizeof(int)*(n/3+1));
	y = (int *)malloc(sizeof(int)*(n/3+1));
	z = (int *)malloc(sizeof(int)*(n/3+1));
	i = (int *)malloc(sizeof(int)*(n/3+1));
	j = (int *)malloc(sizeof(int)*(n/3+1));
	l = (int *)malloc(sizeof(int)*(n/3+1));

	r1 = (int *)malloc(sizeof(int)*(n+1));
	r2 = (int *)malloc(sizeof(int)*(n+1));
	r3 = (int *)malloc(sizeof(int)*(n+1));
	r4 = (int *)malloc(sizeof(int)*(n+1));
	r5 = (int *)malloc(sizeof(int)*(n+1));
	r6 = (int *)malloc(sizeof(int)*(n+1));
	r7 = (int *)malloc(sizeof(int)*(n+1));
	r8 = (int *)malloc(sizeof(int)*(n+1));
	r9 = (int *)malloc(sizeof(int)*(n+1));



if(n<3)
{
	result=prod(n,u,v);
}

if(n>=3)
{
	m = n/3;

	for(a=0;a<m;a++)
		x[a]=u[a];
	for(a=0;a<m;a++)
		y[a]=u[a+m];
	for(a=0;a<m;a++)
		z[a]=u[a+2*m];

	for(a=0;a<m;a++)
		i[a]=v[a];
	for(a=0;a<m;a++)
		j[a]=v[a+m];
	for(a=0;a<m;a++)
		l[a]=v[a+2*m];

	r1 = prod(m,z,l);//size 2m
	r2 = prod(m,y,l);
	r3 = prod(m,x,l);

	r4 = prod(m,z,j);
	r5 = prod(m,y,j);
	r6 = prod(m,x,j);

	r7 = prod(m,z,i);
	r8 = prod(m,y,i);
	r9 = prod(m,x,i);
//  r9*10^4m*2 + (r6+r8)*10^3m*2 + (r3+r5+r7)*10^2m*2 + (r2+r4)*10^m*2 + r1
	for(a=0;a<6*m;a++)
		result[a]=0;

	for(a=0;a<2*m;a++)
	{
		result[a]=r9[a];
	}
	for(a=m;a<3*m;a++)
	{
		result[a]=result[a]+r6[a-m]+r8[a-m];
	}
	for(a=2*m;a<4*m;a++)
	{
		result[a]=result[a]+r3[a-2*m]+r5[a-2*m]+r7[a-2*m];
	}
	for(a=3*m;a<5*m;a++)
	{
		result[a]=result[a]+r2[a-3*m]+r4[a-3*m];
	}
	for(a=4*m;a<6*m;a++)
	{
		result[a]=result[a]+r1[a-4*m];
	}

	for(a=6*m-1;a>0;a--)
		{
			if(result[a]>=10)
			{
				result[a-1]=result[a-1]+result[a]/10;
				result[a]=result[a]%10;
			}
		}

}

	free(x);
	free(y);
	free(z);

	free(i);
	free(j);
	free(l);

	free(r1);
	free(r2);
	free(r3);
	free(r4);
	free(r5);
	free(r6);
	free(r7);
	free(r8);
	free(r9);

	return result;
}



int main(int argc, char const *argv[])
{
	int *a;
	int *b;
	int *c;
	int *d;
	int i,n;
	n= atoi(argv[1]);
	srand(time(NULL));
	a = (int *)malloc(sizeof(int)*n);
	b = (int *)malloc(sizeof(int)*n);
	for (i=0;i<n;i++)
	{
		a[i]=rand()%9+1;
		b[i]=rand()%9+1; 
	}
	for(i=0;i<n;i++)
	{
		printf("%d",a[i]);
	}
	printf("\n\n");
		for(i=0;i<n;i++)
	{
		printf("%d",b[i]);
	}
	printf("\n");
	c=prod(n,a,b);
	d=prod_3(n,a,b);

	free(a);
	free(b);
	printf("====================222222=================\n");
	for(i=0;i<2*n;i++)
	{
		printf("%d",c[i]);
	}
	printf("\n======================333333=================\n");
	for(i=0;i<2*n;i++)
	{
		printf("%d",d[i]);
	}
	printf("\n");
	free(c);
	free(d);
	return 0;
}