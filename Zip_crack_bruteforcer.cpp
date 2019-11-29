#include <bits/stdc++.h>
using namespace std;
#define array_size 300000
#include "word_gen_main.h"

struct Node
{
    string arr[array_size];
    Node* next;
    int No;
};

int max_l;
string file;
string password="";
string listL="";
Node* node_create_fill()
{
    Node* A = new Node();
    Node* B = new Node();
    Node* C = new Node();
    Node* head=A;
    Node* ptr=A;
    A->next = B;
    A->No=1;
    B->next = C;
    B->No=2;
    C->next = A;
    C->No=3;
    return head;
}
string wordgen()
{
  int max_limit, min_limit;
  string list, resume;
    max_limit=max_l;
    min_limit=3;
    list=listL;
  if(max_limit > 0 && min_limit > 0 && min_limit <= max_limit && list.size() != 0)
    {
    Word_Gen_main  static gen(max_limit, min_limit, list);
    return(gen.next());
  }
}

void creation(Node* head)
{
    Node* node=head;
    int i=0;
    while(i<array_size)
    {
        node->arr[i]=wordgen();

        i++;
    }
    return;
}

void checking(Node * head,string pass)
{
    Node* node=head;
    int i=0;
    while(i<array_size)
    {
        if(node->arr[i]=="\0"){
            cout<<"Not Found";
            exit(0);
            }
        string entered=node->arr[i];
        string cmd=("7z e "+ file + " -p"+entered + " -y");
        system("clear");
        if( system(cmd.c_str())==0)

        {
//            system("clear");
            password=entered;
            return;
        }
        i++;
    }
}

void print_list(Node * head)
{
    Node* node=head;
    int k,l,m=0;
    for(k=0,l=0;k<array_size*3;k++)
    {
        if(m==0)
            cout<<"node "<<++m<<"  ->";
        if (l==array_size)
        {
            l=l%array_size;
            node=node->next;
            cout<<"\n\nnode "<<++m<<"  ->";
        }
        cout<<" | "<<node->arr[l];
        l++;
    }
    cout<<"\n\n";
}

void traversal(Node * head, string pass,int flag=0)
{
    mutex m;
    Node* node=head;
    if(flag==0)
    {
        creation(head);
        flag=1;
        node=node->next;
    }
    while(password=="")
    {
        if(node->No==1)
        {
            m.lock();
            thread t1 (creation,head);
            thread t2 (checking,head->next->next,pass);
            t1.join();
            t2.join();
            m.unlock();
        }
        else if(node->No==2)
        {
            m.lock();
            thread t1 (creation,head->next);
            thread t2 (checking,head,pass);
            t1.join();
            t2.join();
            m.unlock();
        }
        else
        {
            m.lock();
            thread t1 (creation,head->next->next);
            thread t2 (checking,head->next,pass);
            t1.join();
            t2.join();
            m.unlock();
        }

        node=node->next;
    }
}

int main()
{
    string charset="";
    string l;
    string passphrase="aaaa";
    system("clear");
    string lower = "abcdefghijklmnopqrstuvwxyz", upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ", numbers = "1234567890", special = "_-+=!$%?*()^@#?/\\{}[]~";
    cout<<"Enter \"l\" for Lowercase, \"u\" for Uppercase, \"n\" for numbers, \"s\" for symbols, \"x\" for customized characterset  \"lu\" for lower and upercase"<<endl;
    cout<<"\nEnter character set :";
    cin>>l;
    string pch;
    for(int i = 0; i < l.size(); i++)
    {
        pch = l[i];
        if(pch == "u") charset += upper;
        else if(pch == "l") charset += lower;
        else if(pch == "n") charset += numbers;
        else if(pch == "s") charset += special;
        else if(pch == "x")
        {
            cout<<"Enter customized characterset: ";
            cin>>charset;
        }
    }
    listL=charset;
    cout<<"\nEnter max password size: ";
    cin>>max_l;
    cout<<"Enter file name with path: ";
    cin>>file;
    Node* head=node_create_fill();
    traversal(head,passphrase);
//    system("clear");
    cout<<"\n\n";
    cout<<"\n****Found***** "<<password;
    cout<<"\n\n";
	return 1;
}
