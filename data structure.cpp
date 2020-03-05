#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include<ctime>
#include<conio.h>

using namespace std;

struct user_node;
struct user;

struct date
{
        int h;
        int m;
        int s;
 };

struct main_node
{
    int n;
    char question[75];
    struct ans_node* ans_link;
    struct main_node* next;
    struct main_node* uqnext;
    struct date pub_date;
    struct user* u;
};

struct ans_node
{
    int n;
    char answer[75];
    struct ans_node* next;
    struct ans_node* uanext;
    struct date pub_date;
    struct user* u;
};

struct user
{
    struct user* next;
    string name;
    int userid;
    struct user_node* in;
};

struct user_node
{
        struct ans_node *ans;
        struct main_node *ques;
};

////////////////////////////////////////////////////////////////////

typedef struct main_node* MAINPTR;
MAINPTR list = NULL;

typedef struct ans_node* ANSPTR;

typedef struct user* USERPTR;
USERPTR ulist = NULL;

typedef struct user_node* UNODEPTR;

int no_of_users = 0;
////////////////////////////////////////////////////////////////////

MAINPTR getquesnode()
{
    MAINPTR p;
    p = (MAINPTR)malloc(sizeof(struct main_node));
    p->u = (USERPTR)malloc(sizeof(struct user));
    return p;
}

ANSPTR getansnode()
{
        ANSPTR p;
        p = (ANSPTR)malloc(sizeof(struct ans_node));
        p->u = (USERPTR)malloc(sizeof(struct user));
        return p;
}

USERPTR getusernode()
{
        USERPTR p;
        p=(USERPTR)malloc(sizeof(struct user));
        return p;
}

////////////////////////////////////////////////////////////////////

void get_time (struct date &t)
{
        time_t now = time(0);
        string t1;
        tm* ltm = localtime(&now);
        t.h = ltm->tm_hour;
        t.m = ltm->tm_min;
        t.s = ltm->tm_sec;
}

void insertques(int i)
{
    MAINPTR p = getquesnode(),q = list;
    p->next = NULL;
    get_time(p->pub_date);
    cout<<"Enter the question : ";
    scanf("%*c%[^\n]s",p->question);
    p->ans_link = NULL;
    p->uqnext  =NULL;
    if(list == NULL)
    {
        list = p;
        p->n = 1;
    }
    else
    {
        while(q->next != NULL)
        {
            q = q->next;
        }
        p->n = (q->n) +1;
        q->next = p;
    }
//user entry part
    int ii;
    USERPTR up = ulist;
    for(ii=1; ii<i; ii++)
    {
        up=up->next;
    }
    p->u = up;
    MAINPTR qp = up->in->ques;
    if(qp != NULL)
    {
        while(qp->uqnext != NULL)
        {
                cout << qp->question <<endl;
                qp = qp->uqnext;
        }
        qp->uqnext = p;
    }
    else
    {
            up->in->ques = p;
    }
}

void insertans(int i)
{
        ANSPTR q = getansnode();
        q->next = NULL;
        q->uanext = NULL;
        if(list != NULL)
        {
                printf("The questions are \n");
                MAINPTR p = list;
                while(p != NULL)
                {
                        cout<<p->n<<") "<<p->question<<endl;
                        p = p->next;
                }
                while(1)
                {
                        printf("Enter the question number in which you want to answer : ");
                        int num;
                        scanf("%d",&num);
                        p = list;
                        int i;
                        for(i=1; i<num; i++)
                        {
                                p = p->next;
                                if(p == NULL)
                                        num = -5;

                        }
                        if(num < 0)
                        {
                                printf("Entered value is wrong Enter again \n");
                        }
                        else
                                break;
                }
                ANSPTR r;
                printf("Enter the answer : ");
                scanf("%*c%[^\n]s",q->answer);
                r = p->ans_link;
                if(r == NULL)
                {
                        p->ans_link = q;
                        q->n = 1;
                }
                else
                {
                        while(r->next != NULL)
                        {
                                r = r->next;
                        }
                        r->next = q;
                        q->n = r->n+1;
                }
       }
        else
        {
                printf("There is no question to answer");
        }
//this is user entry part
        USERPTR u1=ulist;
        int ii;
        for(ii=1; ii<i; ii++)
        {
                u1 = u1->next;
        }
        q->u = u1;
        if(u1->in->ans == NULL)
        {
                u1->in->ans = q;
        }
        else
        {
                ANSPTR up;
                up = u1->in->ans;
                while(up->uanext != NULL)
                {
                        up = up->uanext;
                }
                up->uanext = q;
        }
}

////////////////////////////////////////////////////////////////////
void display()
{
    ANSPTR p;
    MAINPTR q = list;
    if(q!=NULL)
        q->n = 1;
    while(q!=NULL)
    {
        if(q->next!=NULL)
                q->next->n = q->n + 1;
        p = q->ans_link;
        printf("%d) %s\n",q->n,q->question);
        if(p!=NULL)
                p->n = 1;
        while(p != NULL)
        {
            if(p->next!=NULL)
                p->next->n = p->n+1;
            printf("\t%d) %s\n",p->n,p->answer);
            p=p->next;
        }
        q = q->next;
    }
    getch();
}
////////////////////////////////////////////////////////////////////
void deleteans()
{
    int qu,a,i;
    ANSPTR q,ua,ua1;
    MAINPTR p = list;
    printf("Questions and answers are \n");
    display();
    while(1)
    {
        printf("Enter the question number to delete : ");
        scanf("%d",&qu);
cout<<"0"<<endl;
        for(i=1; i<qu; i++)
        {
            p = p->next;
            if(p == NULL)
            {
                qu = -5;
                break;
            }
        }
cout<<"0";
        if(qu <= 0)
        {
            printf("Enter the value again\n");
            continue;
        }
        q = p->ans_link;
        while(1)
        {
            printf("Enter the answer number to be deleted : ");
            scanf("%d",&a);
                for(i=2; i<a; i++)
                {
                    q = q->next;
                    if(q->next == NULL)
                        a = -5;
                }
                if(a < 0)
                    printf("Enter again");
                else
                    break;
        }
        break;
    }
cout<<"55555"<<endl;
    ua = q->next;
    ua1 = ua->u->in->ans;
    if(ua1 == ua)
    {
            ua->u->in->ans = ua1->uanext;
    }
    else
    {
            while(ua1->next != ua)
            {
                    ua1 = ua1->uanext;
            }
            ua1->uanext = ua->uanext;
    }

//deletion
    if(a!=1)
    {
        q->next = q->next->next;
        free(q->next);
    }
    else
    {
        q = p->ans_link;
        p->ans_link = q->next;
        free(q);
    }
}
////////////////////////////////////////////////////////////////////
void deleteques()
{

//quetion deletion
    ANSPTR q,q1;
    int i = 0,n;
    MAINPTR p = list,p1;
    while(p!= NULL)
    {
            cout<<++i<<") "<<p->question<<endl;
            p=p->next;
    }
    p=list;
    while(1)
    {
        printf("Enter the question to be deleted : ");
        scanf("%d",&n);
        if(n==1)
        {
                list = list->next;
        }
        for(i=1; i<n-1; i++)
        {
            p = p->next;
            if(p->next == NULL)
            {
                n = -5;
            }
        }
        if(n <= 0)
            printf("Enter again");
        else
            break;
    }
cout<<"00000"<<endl;
    p1 = p->next;
    if(p1!=NULL)
    {
        q = p1->ans_link;
    }
    else
    {
        p1= p;
        q = p->ans_link;
    }
    q1 = q;
cout<<"00000"<<endl;
    while(q1 != NULL)
    {
        q1 = q->next;
        free(q);
        q = q1;
    }
    p->next = p1->next;
//user part
cout<<"11111"<<endl;
        MAINPTR uq = p1->u->in->ques;
        if(uq != p1)
        {
                while(uq->next != p1)
                {
                        uq = uq->uqnext;
                }
                uq->uqnext = p->uqnext;
        }
        else
        {
                p1->u->in->ques = uq->uqnext;
        }
//deletion
    free(p1);

}
////////////////////////////////////////////////////////////////////
void adduser()
{
        string s;
        USERPTR p = getusernode(),q = ulist;
        cout<<"Enter the user name : ";
        getchar();
        getline(cin,s);
        p->name = s;
        cout<<"Enter the user id : ";
        cin>>p->userid;
        p->next = NULL;
        p->in = (struct user_node*)malloc(sizeof(struct user_node));
        p->in->ans = NULL;
        p->in->ques = NULL;
        while(q->next != NULL)
        {
                q = q->next;
        }
        q->next = p;
        no_of_users++;
}


/////////////////////////////////////////////////////////////////////////
void search(string fstr)
{
        int i,j,c[100] = {0},n1=0,n;
        char s[50];
        memset(s,0,sizeof(s));
        MAINPTR p = list;
        ANSPTR p1;
        while(p != NULL)
        {
                p=p->next;
                n1++;
        }
cout<<"0";
        string str[n1];
        MAINPTR q[n1];
        for(i=0; i<n1; i++)
        {
                str[i] = p->question;
                q[i] = p;
                p = p->next;
cout<<"str [i]"<<str[i]<<endl;
        }
cout<<"0";
        for(j=0;j<n1;j++)
        {
                for(i=0; fstr[i]; i++)
                {
                        if(fstr[i] != ' '&& fstr[i] != ',' && fstr[i] != '.' && fstr[i] != '?')
                        {
                                s[n*(i/(2*n)) + i%n] = fstr[i];
                        }
                        else
                        {
                                n=i+1;
                                if(str[j].find(s) != string::npos)
                                {
                                        c[j]++;
                                }
                                memset(s, 0, sizeof(s));
                        }
                }
        }
        n=0;
        for(i=0;i<n1;i++)
        {
               if(n<c[i])
                        n=c[i];
        }
        for(i=n; i>=0; i--)
        {
                for(j=0; j<n1; j++)
                {
                        if(i == c[j])
                        {
                                cout<<str[j]<<endl;
                                p1=q[i]->ans_link;
                                int i1=0;
 //                               cout<<"time : "<<p1.pub_date.h<<":"p1.pub_date.m<<":"<<p1.pub_date.s<<endl;
                                while(p1!=NULL)
                                {
                                        cout<<"Answer "<<++i1<<p1->answer;
                                }
                        }
                }
        }
        while(getchar()!='\n');
}
//////////////////////////////////////////////////////////////////


void adminside()
{
        int n;
        while(1)
        {
                system("cls");
                cout<<"\t\t\t\t\t\tADMIN"<<endl<<endl<<endl;

                cout<<"\nEnter the process to be done : "<<endl;
                cout<<"1) Enter the question"<<endl<<"2) Enter the answer"<<endl<<"3) delete answer"<<endl<<"4) delete question"<<endl<<"5) display"<<endl<<"6) add user"<<endl<<"7) Back to user"<<endl<<":::::::::::::::";
                cin>>n;
                if(n == 7)
                break;
                switch(n)
                {
                case 1: insertques(1);
                        break;
                case 2: insertans(1);
                        break;
                case 3: deleteans();
                        break;
                case 4:deleteques();
                        break;
                case 5:display();
                        break;
                case 6:adduser();
                        break;
                };
        }
}

void userside ()
{
        string s;
        int i,n;
        cout<<"Enter the USER number :"<<endl;
        for(i=0; i<no_of_users-1; i++)
        {
                cout<<"\t"<<i+1<<") User"<<i+1<<endl;
        }
        cin>>i;
        i++;
////user id and pass word checking
        string s1;
        int a;
        cout<<"Enter name : ";
        getchar();
        getline(cin,s1);
        cout<<"Enter user id : ";
        cin>>a;
        int ii;
        USERPTR p = ulist;
        for(ii=1;ii<i;ii++)
        {
                p=p->next;
        }
        if(s1!=p->name||a!=p->userid)
                return;

        while(1)
        {
                system("cls");
                cout<<"\t\t\t\t\t\tUSER"<<endl<<endl<<endl;
               cout<<"Enter the process to be done "<<endl;
                cout<<"1) Add Question"<<endl<<"2) Add Answer"<<endl<<"3) Go to Main Menu"<<endl;
                cin>>n;
                switch(n)
                {
                        case 1:
                                insertques(i);
                                break;
                        case 2:
                                insertans(i);
                                break;
                        case 4:
                                cout<<"Enter the question to be search : ";
                                cin>>s;
                                search(s);
                                break;
                        case 3:
                                return;
                }
        }
}

void admininsert()
{
        USERPTR p=getusernode();
        p->name = "admin";
        p->userid = 141414;
        p->next = NULL;
        p->in = (struct user_node*)malloc(sizeof(struct user_node));
        p->in->ans = NULL;
        p->in->ques = NULL;
        ulist = p;
        no_of_users = 1;
}

int main()
{
cout<<"0";
        admininsert();
        int n;
        while(1){
                system("cls");
                cout<<"\t\t\t\t\t\tQUEST HUB"<<endl<<endl<<endl;
                cout<<"Switch between the persons : "<<endl;
                cout<<"\t1) ADMIN "<<endl<<"\t2) USERS"<<endl<<"\t3) EXIT";
                cin>>n;
                if(n == 3)
                {
                        return 0;
                }
                switch(n)
                {
                        case 1:
                                adminside();
                                break;
                        case 2:
                                userside();
                                break;
                }
        }
        return 0;
}










