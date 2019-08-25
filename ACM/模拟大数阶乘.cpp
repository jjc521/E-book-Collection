#include "bits/stdc++.h"
using namespace std;
int NUM=-1;
typedef struct BinPoint
{
    char data;
    BinPoint *ls;
    BinPoint *rs;
}*node,BinTree;

int PreCre(node &p,char array[])
{
    NUM++;
    if(array[NUM]=='#')
        p=NULL;
    else
    {
        p=(node)malloc(sizeof(BinTree));
        p->data=array[NUM];
        PreCre(p->ls,array);
        PreCre(p->rs,array);
    }
}
int PreVisit(node &p)
{
    if(p)
    {
        cout<<p->data;
        PreVisit(p->ls);
        PreVisit(p->rs);
    }

}
int MidVisit(node &p)
{
    if(p)
    {
        MidVisit(p->ls);
        cout<<p->data;
        MidVisit(p->rs);
    }

}
int LastVisit(node &p)
{
    if(p)
    {
        LastVisit(p->ls);
        LastVisit(p->rs);
        cout<<p->data;
    }

}
int main()
{
    char array1[]="41#32###65##7##";
    int ceng=0;
    node BinT1;
    if(PreCre(BinT1,array1))
    {
        //cout<<"OK"<<endl;
        PreVisit(BinT1);
        cout<<endl;
        MidVisit(BinT1);
        cout<<endl;
        LastVisit(BinT1);
    }
    cout<<endl;
    return 0;
}
