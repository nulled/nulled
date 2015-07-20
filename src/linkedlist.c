#include <stdio.h>
#include <stdlib.h>

typedef struct linkedlist {
  char *name;
  int age;
  struct linkedlist *next;
} List;

void Add_Element(List ** list, char * name, int age)
{
  List *tmp = malloc(sizeof(List));
  
  tmp->name = name;
  tmp->age  = age;
  tmp->next = *list;
 
  *list = tmp;
}

List* Add_Elem(List * list, char * name, int age)
{
  List* tmp = malloc(sizeof(List));

  tmp->name = name;
  tmp->age  = age;
  tmp->next = list;

  return tmp;
}

void point_char(char *ptr)
{
  *(ptr + 1) = '2';
}

void point_int(int *i)
{
  *i = 10;
}

int main()
{
  List *head = malloc(sizeof(List));

  head = NULL;
  
  /* We pass &head because we want to pass the address of head NOT the value of head. 
   * 
   * Pass by value (without &) would result in passing in NULL, which is not good.
   * use &head to pass the address of head so it can be worked on.
   */
  /*
  Add_Element(&head, "Matt", 36);
  Add_Element(&head, "Matt2", 3);
  Add_Element(&head, "Matt3", 6);
  */
  head = Add_Elem(head, "Matt", 36);
  head = Add_Elem(head, "Matt2", 3);
  head = Add_Elem(head, "Matt3", 6);
  
  List *iter = head;
  while (iter)
  {
    printf("%s %d\n", iter->name, iter->age);
    iter = (*iter).next;
  }
  
 /* 
  char *str = malloc(sizeof(char*)*5);
  strcpy(str, "Matt");
  *(str + 1) = '.';
  printf("%s\n", str);
  point_char(str);
  printf("%s\n", str);
  */
  /*
   * We do not need to &p to the function because p already contains the address of a.
   * Since we are dereferencing the address contained in point_int(int *i) we are
   * dereferencing the address and getting the contents and changing it.
   */
  /*
  int a = 5;
  int * p;
  p = &a;
  printf("%d\n", *p);
  point_int(p);
  printf("%d\n", *p);
  (*p)++;
  printf("%d\n", *p);
  */
  return 0;
}
