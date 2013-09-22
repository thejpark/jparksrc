#include <stdio.h>
#include <stdlib.h>

struct node {
   int val;
   struct node *next;
};


struct node *
create_node(int val)
{
   struct node * ret;
   ret = malloc(sizeof(struct node));
   if (ret == NULL)
       return ret;
   ret->val = val;
   ret->next = NULL;
   return ret;
}

struct list {
   struct node *first;
};


struct list *
create_list()
{
   struct list *ret = malloc(sizeof(struct list));
   if (ret == NULL)
       return ret;
   ret->first = NULL;
   return ret;
}

int
is_element_at(struct list *l, int loc)
{
   struct node *t = l->first;
   int i = 0;
   for (;(i < loc) && (t != NULL); i++, t = t->next) ;

   if (t == NULL)
       return 0;
   return 1;
}

int
element_at(struct list *l, int loc)
{
   struct node *t = l->first;
   int i = 0;
   for (;(i < loc) && (t != NULL); i++, t = t->next) ;

   return t->val;
}

void
append(struct list *a, int val)
{
   struct node *tmp = create_node(val);
   if(a->first == NULL) {
       a->first = tmp;
   } else {
       struct node *t = a->first;
       while (t->next) {
           t = t->next;
       }
       t->next = tmp;
   }
}

void
print_list(struct list *l)
{
   struct node *t = l->first;
   while(t) {
       printf(" [%d] ", t->val);
       t = t->next;
   }
   printf("\n");
}


void main()
{
   int i;

   struct list *l = create_list();
   for (i = 0; i < 10; i++) {
       append(l, i);
   }

  print_list(l);
  if (is_element_at(l, 10)) {
      printf("element at 7 is %d\n", element_at(l, 7));
  }
}

