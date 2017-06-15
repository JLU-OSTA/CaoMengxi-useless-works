#include <stdio.h>

int id[18]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const int mul[17]={7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
const char ck[11]={'1','0','X','9','8','7','6','5','4','3','2'};

int sum_unit(void);
char check_sum(void);

int main()
{
    int i,j;
    char check=0;
    int sex=0;
    do
    {
        printf("Insert the id num of first 14:\n");
        for(i=0;i<14;i++)
        {
            id[i]=getch()-0x30;
            if(id[i]>10 || id[i]<0)
            {
                printf("Something wrong!\n");
                getch();
                return 1;
            }
        }
        printf("You have insert the id number:");
        for(i=0;i<14;i++)
            printf("%d",id[i]);
        printf("xxxx.\nIf you think it is OK, press \"p\" to continue...\n");
        check=getch();
    }while(check!='p');
    printf("Insert the sex you are:\n1.male;\t2.female\n");
    sex=getch()-0x30;
    if(sex!=1 && sex!=2)
    {
        printf("Sex wrong!\n");
        getch();
        return 1;
    }
    printf("The following is the number might be:\n");
    check=0;
    for(i=0;i<1000;i++)
    {
        if(sex==1 && (i%2)!=1)
            continue;
        if(sex==2 && (i%2)!=0)
            continue;
        id[14]=i/100;
        id[15]=(i/10)%10;
        id[16]=i%10;
        id[17]=check_sum();
        for(j=0;j<17;j++)
        {
            printf("%d",id[j]);
        }
        printf("%c\n",id[17]);
    }
    printf("Press Enter to exit...\n");
    scanf("1",&j);
    return 0;
}

int sum_unit(void)
{
    int sum,i;
    sum=0;
    for(i=0;i<17;i++)
        sum+=id[i]*mul[i];
    return sum;
}

char check_sum(void)
{
    return ck[sum_unit()%11];
}
