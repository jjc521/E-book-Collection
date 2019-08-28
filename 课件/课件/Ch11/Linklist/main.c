#include <stdio.h>
#include <stdlib.h>

#define LEN sizeof(struct student)

typedef struct student{
  int num;
  float score;
  struct student *next;
} Student;

Student * create(){
  Student *head, *rear, *tmp;
  head = rear = (Student*) malloc(LEN);
  head->next=NULL;

  int num;
  float score;

  do{
    scanf("%d%f",&num, &score);
    if(num<0) break;

    tmp=(Student*) malloc(LEN);
    tmp->num=num;
    tmp->score=score;

    rear->next=tmp;
    rear=tmp;
  }while (1);
  rear->next=NULL;

  return head;
}

void print(Student * h){
  Student *p;

  p=h->next;
  while(p){
    printf("%d %f\n", p->num, p->score);
    p=p->next;
  }
}

void insert(Student * h, int num, int score){
  Student *p1, *p2, *tmp;

  p1=h;
  p2=h->next;

  while(p2){
    if(p2->num>num) break;
    p1=p2;
    p2=p2->next;
  }
  tmp=(Student*)malloc(LEN);
  tmp->num=num;
  tmp->score=score;
  tmp->next=p2;
  p1->next=tmp;
}

void delete(Student *h, int num){
  Student *p1, *p2;

  p1=h;
  p2=h->next;
  while(p2){
    if(p2->num==num)break;
    p1=p2;
    p2=p2->next;
  }
  if(!p2) return;
  p1->next=p2->next;
  free(p2);
}


int main()
{
    Student *head;

    head=create();

    printf("\n\n");
    print(head);

    printf("\n\n");
    insert(head, 10, 98);
    print(head);

    printf("\n\n");
    delete(head, 10);
    print(head);

    return 0;
}
