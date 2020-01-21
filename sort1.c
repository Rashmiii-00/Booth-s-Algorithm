#include<math.h>
#include<stdio.h>
#include<conio.h>
#define MAX 4
int a[MAX]={0},q[MAX],q0=0,m[MAX],qc[MAX],mc[MAX];
void binary(int no,int q[])
{
    int i = 0,j;
    int bin[MAX];
    int n=no;
    while (n>0) {
        // storing remainder in binary array
        bin[i] = n % 2;
        n = n / 2;
        i++;
    }
    if(i<=MAX-1)
        for(j=i;j<MAX;j++)
            bin[j]=0;
    for(i=0;i<MAX;i++)
        q[i] = bin[MAX-1-i];
}
int lsb(int a[]){
    return a[MAX-1];
}
int msb(int a[]){
    return a[0];
}
void rt(int a[],int msb)
{

    int i;
    for(i=MAX-1;i>0;i--)
    {
        a[i]=a[i-1];
    }
    a[0]=msb;
}
int right_shift(int acc[],int q[])
{
    int lsb_q=lsb(q);  // getting q0
    int lsb_acc=lsb(acc);  //bit that shifts from a to q
    int mb=msb(acc); // leading zero or one
    rt(acc,mb);
    rt(q,lsb_acc);
    return lsb_q;
}
int add_bits(int a1[],int a2[],int n3,int i){
    int n1,n2,res;
    n1=a1[i];
    n2=a2[i];
    res=n1+n2+n3;
    switch(res){
        case 0:
            a[i]=0;
            return 0;
            break;
        case 1:
            a[i]=1;
            return 0;
            break;
        case 2:
            a[i]=0;
            return 1;
            break;
        case 3:
            a1[i]=1;
            return 1;
            break;
    }
}
int add(int add1[],int add2[]){
    int p_carry = 0,carry;
    int i;
    for(i=MAX-1;i>=0;i--)
    {
        carry = add_bits(add1,add2,p_carry,i);
        p_carry = carry;
    }
    return p_carry;
}
void comp(int n[],int nc[]){
    int i=0;
    int last=0;
    int one[] = {0,0,0,1};


    for(i=MAX-1;i>=0;i--){
        if(last==0)
            if(n[i]==1)
            {
                last=1;
                nc[i]=n[i];
            }
            else
                nc[i]=n[i];
        else
        switch(n[i]){
        case 1:
            nc[i]=0;
            break;
        case 0:
            nc[i]=1;
            break;
        }
    }

        //if(n[i] == 0)
          //  nc[i] = 1;
        //else
        //    nc[i] = 0;
    //add(nc,one);

}
int main()
{
    int  n1,n2,n1C,n2C,n,i;
    printf("Enter two numbers between 7 and 0:");
    scanf("%d%d",&n1,&n2);
    if(n1>0)
    {
        binary(n1,q);
        comp(q,qc);
    }
    else{
        n1C=n1*n1;
        n1C=sqrt(n1C);
        binary(n1C,qc);
        comp(qc,q);
    }
    if(n2>0)
    {
        binary(n2,m);
        comp(m,mc);
    }
    else{
        n2C=n2*n2;
        n2C=sqrt(n2C);
        binary(n2C,mc);
        comp(mc,m);
    }
    /*
    printf("\nbinary  n1\n");
    for(i=0;i<MAX;i++)
        printf("%d\t",qc[i]);

    printf("\nbinary n2\n");
    for(i=0;i<MAX;i++)
        printf("%d",mc[i]);
        */

    n=0;//counts number of steps
    while(n < MAX){
        if(q0 == lsb(q))//0 to 0 transition
            {
             q0 = right_shift(a,q);
            //printf("\nq0 after 0->0 %d",q0);
            }
        else
            {
            switch(q0){
            case 0:
                //0 to 1 transition
                add(a,mc);
                //printf("\nAdd 0-> 1 : %d",add(a,mc));
                q0 = right_shift(a,q);
                //printf("\nq0 after 0->1 %d",q0);
                break;
            case 1:
                //1 to 0 transition
                 add(a,m);
                 //printf("\nAdd 1-> 0 : %d",add(a,m));
                q0 = right_shift(a,q);
                //printf("\nq0 after 1->0 %d",q0);
                break;
            }
        }
        n++;
    }
    printf("\nAns : ");
    for(i=0;i<MAX;i++)
        printf("%d",a[i]);
    printf(" ");
    for(i=0;i<MAX;i++)
        printf("%d",q[i]);
}

