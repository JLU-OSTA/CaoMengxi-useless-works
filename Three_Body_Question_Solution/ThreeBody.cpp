#include <iostream>
#include <cstdio>
#include <cmath>
#include <string.h>
using namespace std;

class point
{
public:
    double x,y,z,a;
    point(void)
    {
        a=x=y=z=0.0;
    };
};

double getm(char* s)
{
    double q;
    cout<<"Please insert the mass for the ";
    cout<<s;
    cout<<" :";
    scanf("%lf",&q);
    return q;
}

point sumforce(point x,point y,double fx,double fy)
{
    point q;
    q.x=fy*y.x+fx*x.x;
    q.y=fy*y.y+fx*x.y;
    q.z=fy*y.z+fx*x.z;
    return q;
}

point v2o(point p)
{
    point q;
    q.a=sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
    if(q.a!=0)
    {
        q.x=p.x/(q.a);
        q.y=p.y/(q.a);
        q.z=p.z/(q.a);
    }
    else
    {
        q.x=q.y=q.z=0;
    }
    return q;
}

point getvec(point x,point y)
{
    point q;
    q.x=y.x-x.x;
    q.y=y.y-x.y;
    q.z=y.z-x.z;
    q=v2o(q);
    return q;
}

point geta(point o,point x,point y,double fx,double fy)
{
    point q;
    q=sumforce(getvec(o,x),getvec(o,y),fx,fy);
    q=v2o(q);
    if(o.a!=0)
    {
        q.a=((q.a/o.a)/1000);
    }
    else
    {
        q.a=0;
    }
    return q;
}

void prt(point x)
{
    cout<<"(";
    cout<<scientific<<x.x;
    cout<<",";
    cout<<scientific<<x.y;
    cout<<",";
    cout<<scientific<<x.z;
    cout<<") ";
    cout<<scientific<<x.a;
    cout<<"."<<endl;
}

point getcheck(char* s)
{
    int check=2;
    point p;
    while(check)
    {
        if(check==1)
        {
            cout<<"\nOk... Let us reinsert the vector information...\n";
        }
        cout<<"Please insert the "<<s<<" vector of the body(etc,\"10.4 20.2 30.6\",measurement is km or km/s):";
        scanf("%lf %lf %lf",&p.x,&p.y,&p.z);
        cout<<"You have inserted the vector: ";
        prt(p);
        cout<<"You can insert \'0\' to be sure or \'1\' to reinsert information:";
        scanf("%d",&check);
    }
    cout<<endl;
    return p;
}

double cd(point x,point y)
{
    return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y)+(x.z-y.z)*(x.z-y.z));
}

double force(double m1,double m2,double d)
{
    if(d==0)
    {
        return (9999999*10^255);
    }
    else
    {
        return ((6.67408*(m1*m2)/(d*d))/100000000000000000);
    }
}

int main(void)
{
    char buf;
    cout<<"Loaded successfully!\nAnd press any key to continue...\n";
    buf=getchar();
    point p1=getcheck("1st location");
    point p2=getcheck("2nd location");
    point p3=getcheck("3rd location");
    point v1=getcheck("1st velocity");
    point v2=getcheck("2nd velocity");
    point v3=getcheck("3rd velocity");
    v1=v2o(v1);
    v2=v2o(v2);
    v3=v2o(v3);
    p1.a=getm("1st body");
    p2.a=getm("2nd body");
    p3.a=getm("3rd body");
    double d12,d13,d23;
    d12=cd(p1,p2);
    d13=cd(p1,p3);
    d23=cd(p2,p3);
    double t;
    cout<<"Please insert the time to calculate the three body question:";
    scanf("%lf",&t);
    double f12,f13,f23;
    f12=abs(force(p1.a,p2.a,d12));
    f13=abs(force(p1.a,p3.a,d13));
    f23=abs(force(p2.a,p3.a,d23));
    point a1=geta(p1,p2,p3,f12,f13);
    point a2=geta(p2,p1,p3,f12,f23);
    point a3=geta(p3,p1,p2,f13,f23);
    double i=0;
    double temp;
    for(;i<t;i+=0.001)
    {
        temp=p1.a;
        p1=sumforce(p1,v1,1.0,v1.a*0.001);
        p1.a=temp;
        temp=p2.a;
        p2=sumforce(p2,v2,1.0,v2.a*0.001);
        p2.a=temp;
        temp=p3.a;
        p3=sumforce(p3,v3,1.0,v3.a*0.001);
        p3.a=temp;
        v1=sumforce(v1,a1,v1.a,a1.a*0.001);
        v1=v2o(v1);
        v2=sumforce(v2,a2,v2.a,a2.a*0.001);
        v2=v2o(v2);
        v3=sumforce(v3,a3,v3.a,a3.a*0.001);
        v3=v2o(v3);
        d12=cd(p1,p2);
        d13=cd(p1,p3);
        d23=cd(p2,p3);
        f12=abs(force(p1.a,p2.a,d12));
        f13=abs(force(p1.a,p3.a,d13));
        f23=abs(force(p2.a,p3.a,d23));
        a1=geta(p1,p2,p3,f12,f13);
        a2=geta(p2,p1,p3,f12,f23);
        a3=geta(p3,p1,p2,f13,f23);

    }
    cout<<"\n\n########This is test module########\n";
    cout<<"Take time:";
    cout<<scientific<<t;
    cout<<" s."<<endl;
    cout<<"The 1st body: "<<endl;
    prt(p1);
    prt(v1);
    prt(a1);
    cout<<"The 2nd body: "<<endl;
    prt(p2);
    prt(v2);
    prt(a2);
    cout<<"The 3rd body: "<<endl;
    prt(p3);
    prt(v3);
    prt(a3);
    cout<<"\n########The test########\n\n\n";


    cout<<"\n####The result:####\n";
    cout<<"Take time:";
    cout<<scientific<<t;
    cout<<" s."<<endl;
    cout<<"The 1st body: "<<endl;
    cout<<"\tPosition:";
    prt(p1);
    cout<<"\tVelocity:";
    prt(v1);
    cout<<"The 2nd body: "<<endl;
    cout<<"\tPosition:";
    prt(p2);
    cout<<"\tVelocity:";
    prt(v2);
    cout<<"The 3rd body: "<<endl;
    cout<<"\tPosition:";
    prt(p3);
    cout<<"\tVelocity:";
    prt(v3);
    cout<<"Thanks for using."<<endl;
    cout<<"Press any key to exit..."<<endl;
    buf=getchar();
    return 0;
}
