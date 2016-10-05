#include <stdio.h>
#include <malloc.h>
#include <math.h>
#define N 10
typedef struct Lnode
{
float coef;
int expn;
struct Lnode *next;
}Lnode,*LinkList;
LinkList L[N]={NULL};
void CreatePolyn(LinkList *head){
    int i,n;
    float x;
    int y;
    LinkList p;
    scanf("%d",&n);
    (*head)=(LinkList)malloc(sizeof(struct Lnode));
    (*head)->next=NULL;
    for(i=0;i<n;i++){
        p=(LinkList)malloc(sizeof(struct Lnode));
        scanf("%f %d",&x,&y);
        p->coef=x;
        p->expn=y;
        p->next=(*head)->next;
        (*head)->next=p;
    }
}
void PrintPolyn(LinkList L){
    LinkList p,q;
    int flag=0;
    int k=0;
    q=L->next;
    while(q!=NULL){
        if(q->coef!=0)
            k++;
        q=q->next;
    }
    printf("%d,",k);
    p=L->next;
    if(p->coef!=0){
        printf("%f,%d,",p->coef,p->expn);
        flag++;
    }
    for(p=p->next;p!=NULL;p=p->next){
        if(p->coef!=0){
            printf("%f,%d,",p->coef,p->expn);
            flag++;
        }
    }
    if(flag==0)//
        printf("%d\n",flag);
    else
        printf("\n");
}
void InsertPolyn(LinkList phead,LinkList head){
    if(phead->coef==0)
        free(phead);
    else{
        LinkList p,q;
        p=head;
        q=head->next;
        while(q){
            if(phead->expn>=q->expn)
                break;
            p=q;
            q=q->next;
        }
        if(q&&phead->expn==q->expn){
            q->coef+=phead->coef;
            free(phead);
            if(!q->coef){
                p->next=q->next;
                free(q);
            }
        }
        else{
            phead->next=q;
            p->next=phead;
        }
    }
}
LinkList makenode(float coef, int expn){
        LinkList p;
        p=(LinkList)malloc(sizeof(struct Lnode));
        p->coef=coef;
        p->expn=expn;
        p->next=NULL;
        return p;
}
void Linklistcopy(LinkList a,LinkList *b){
    LinkList qa;
    qa=a->next;
    (*b)=(LinkList)malloc(sizeof(struct Lnode));
    (*b)->next=NULL;
    while(qa){
        InsertPolyn(makenode(qa->coef,qa->expn),(*b));
        qa=qa->next;
    }
}
void LinkListdestroy(LinkList *head){
    (*head)->coef=0;
    (*head)->expn=0;
    (*head)->next=NULL;
}
void LinkListadd(LinkList ahead,LinkList bhead,LinkList *chead){
    LinkList qa,qb,qc;
    qa=ahead->next;
    qb=bhead->next;
    (*chead)=(LinkList)malloc(sizeof(struct Lnode));
    (*chead)->next=NULL;
    while(qa||qb){
        qc=(LinkList)malloc(sizeof(struct Lnode));
        if(qb==NULL){
        qc->coef=qa->coef;
        qc->expn=qa->expn;
        qa=qa->next;
        }
        else if(qa==NULL){
            qc->coef=qb->coef;
            qc->expn=qb->expn;
            qb=qb->next;
        }
        else if(qa->expn>qb->expn){
            qc->coef=qa->coef;
            qc->expn=qa->expn;
            qa=qa->next;
        }
        else if(qa->expn==qb->expn){
            qc->coef=(qa->coef+qb->coef);
            qc->expn=qa->expn;
            qa=qa->next;
            qb=qb->next;
        }
        else {
            qc->coef=qb->coef;
            qc->expn=qb->expn;
            qb=qb->next;
        }
        if(fabs(qc->coef)>1E-8){
            qc->next=(*chead)->next;
            (*chead)->next=qc;
        }
        else
            free(qc);
    }
}
void LinkListsub(LinkList ahead,LinkList bhead,LinkList *chead){
    LinkList qa,qb,qc;
    qa=ahead->next;
    qb=bhead->next;
    (*chead)=(LinkList)malloc(sizeof(struct Lnode));
    (*chead)->next=NULL;
    while(qa||qb){
        qc=(LinkList)malloc(sizeof(struct Lnode));
        if(qb==NULL){
        qc->coef=qa->coef;
        qc->expn=qa->expn;
        qa=qa->next;
        }
        else if(qa==NULL){
            qc->coef=-qb->coef;
            qc->expn=qb->expn;
            qb=qb->next;
        }
        else if(qa->expn>qb->expn){
            qc->coef=qa->coef;
            qc->expn=qa->expn;
            qa=qa->next;
        }
        else if(qa->expn==qb->expn){
            qc->coef=(qa->coef-qb->coef);
            qc->expn=qa->expn;
            qa=qa->next;
            qb=qb->next;
        }
        else {
            qc->coef=-qb->coef;
            qc->expn=qb->expn;
            qb=qb->next;
        }
        if(fabs(qc->coef)>1E-8){
            qc->next=(*chead)->next;
            (*chead)->next=qc;
        }
        else
            free(qc);
    }
}
void LinkListmulti(LinkList ahead,LinkList bhead,LinkList *chead){
    LinkList pa=ahead->next,pb=bhead->next,q;
    (*chead)=(LinkList)malloc(sizeof(struct Lnode));
    (*chead)->next=NULL;
    for(pa=ahead->next;pa;pa=pa->next){
        for(pb=bhead->next;pb;pb=pb->next){
            q=(LinkList)malloc(sizeof(struct Lnode));
            q->coef=pa->coef*pb->coef;
            q->expn=pa->expn+pb->expn;
            InsertPolyn(q,*chead);
        }
    }
}
void LinkListderivative(LinkList ahead,int n){
    int i;
    LinkList p=ahead->next,pa;
    for(i=1;i<=n;i++){
        p->coef=(p->coef)*(p->expn);
        p->expn--;
        pa=p;
        p=p->next;
        while(p){
            p->coef=(p->coef)*(p->expn);
            p->expn--;
            p=p->next;
        }
        p=pa;
    }
}
float LinkListvalue(LinkList head,float x){
    float sum=0,t;
    int i;
    LinkList p;
    for(p=head->next;p;p=p->next){
        t=1;
        for(i=p->expn;i!=0;){
            if(i<0){
                t=t/x;
                i++;
            }
            else{
                t=t*x;
                i--;
            }
        }
        sum+=p->coef*t;
    }
    return sum;
}
void iteintegral(LinkList head){
    LinkList p=head->next;
    while(p!=NULL){
        p->expn+=1;
        p->coef=p->coef/p->expn;
        p=p->next;
    }
}
void LinkListpower(LinkList head,int n){
    int i;
    LinkList b[10]={NULL};
    Linklistcopy(head,&b[1]);
    for(i=1;i<n;i++){
        LinkListmulti(head,b[i],&b[i+1]);
    }
    PrintPolyn(b[i]);
}
void main(){
    int menu,i,i1,i2,i3;
    float x,x1,x2;
    while(1){
        printf("0...exit\n");
        printf("1...create a polynominal\n");
        printf("2...show a polynominal\n");
        printf("3...copy a polynominal\n");
        printf("4...delete a polynominal\n");
        printf("5...add two polynominals\n");
        printf("6...difference of two polynominals\n");
        printf("7...product of two polynominals\n");
        printf("8...derivative of a polynominal\n");
        printf("9...value of a polynominal\n");
        printf("10...integral of a polynominal\n");
        printf("11...power of a polynominal\n");
        printf("please select a menu:");
        scanf("%d",&menu);
        switch(menu){
            case 0:return;
            case 1:
                printf("please imput the label of new polynominal:");
                scanf("%d",&i);
                CreatePolyn(&L[i]);
                break;
            case 2:
                printf("please imput the label of polynominal you want to show:");
                scanf("%d",&i);
                PrintPolyn(L[i]);
                break;
            case 3:
                printf("please imput the label of polynominal you want to copy:");
                scanf("%d",&i1);
                printf("please imput the label of polynominal you want to paste:");
                scanf("%d",&i2);
                Linklistcopy(L[i1],&L[i2]);
                break;
            case 4:
                printf("please imput the label of polynominal you want to destroy:");
                scanf("%d",&i);
                PrintPolyn(&L[i]);
                break;
            case 5:
                printf("please imput the labels of two polynominals you want to add:");
                scanf("%d %d",&i1,&i2);
                printf("please imput the label you want to store:");
                scanf("%d",&i);
                LinkListadd(L[i1],L[i2],&L[i]);
                break;
            case 6:
                printf("please imput the labels of two polynominals you want to minus:");
                scanf("%d %d",&i1,&i2);
                printf("please imput the label you want to store:");
                scanf("%d",&i);
                LinkListsub(L[i1],L[i2],&L[i]);
                break;
            case 7:
                printf("please imput the labels of two polynominals you want to multiply:");
                scanf("%d %d",&i1,&i2);
                printf("please imput the label you want to store:");
                scanf("%d",&i);
                LinkListmulti(L[i1],L[i2],&L[i]);
                break;
            case 8:
                printf("please imput the label of polynominal you want to derive:");
                scanf("%d",&i1);
                printf("please imput the number of derivatives:");
                scanf("%d",&i2);
                LinkListqiudao(L[i1],i2);
                break;
            case 9:
                printf("please imput the label of polynominal you want to value:");
                scanf("%d",&i);
                printf("please imput the value of X:");
                scanf("%f",&x);
                printf("the value of polynominal is %f\n",LinkListvalue(L[i],x));
                break;
            case 10:
                printf("please imput the label of polynominal you want to integral:");
                scanf("%d",&i);
                printf("please imput the upper bound:");
                scanf("%f",&x1);
                printf("please imput the lower bound:");
                scanf("%f",&x2);
                iteintegral(L[i]);
                printf("the integral of the polynominal is %f\n",LinkListvalue(L[i],x1)-LinkListvalue(L[i],x2));
                LinkListqiudao(L[i],1);
                break;
            case 11:
                printf("please imput the label of polynominal you want to power:");
                scanf("%d",&i1);
                printf("please imput the power:");
                scanf("%d",&i2);
                LinkListpower(L[i1],i2);
                break;
            default:;
        }
    }
}
