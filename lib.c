#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list {
  struct list *next;
  int data;
};

struct list *list_init()
{
  struct list *first = malloc(sizeof(struct list));

  first->next = NULL;
  return (first);
}

int list_push(struct list **list, const char *value)
{
  if (value == NULL || value[0] == 0) {
    puts("\nErreur: impossible de push NULL.");
    return (-1);
  }
  
  if (strlen(value) > 10) {
    puts("\nErreur: nombre trop grand.\n");
    return (-1);
  }

  char *ptr = NULL;
  int i = strtol(value, &ptr, 10);
  int bool = 0;
  struct list *tmp = NULL;
  struct list *new = NULL;
  
  new = list_init();
  
  if (ptr[0] != 0) {
    printf("\nErreur: '%s' caractère(s) invalide(s).\n", ptr);
    free(new);
    return (-1);
  }

  if (i >= '0' && i <= '9')
    bool = 0;
  else
    bool = 1;

  if (i > 2147483647 || i < -2147483647) {
    puts("\nErreur: nombre trop grand.\n");
    free(new);
    return (-1);
  }
  
  new->data = i;
  new->next = NULL;

  if ((*list) != NULL) {
    tmp = (*list);
    while (tmp->next != NULL)
      tmp = tmp->next;
    tmp->next = new;
  } else {
    (*list) = new;
  }
  
  if (bool == 0)
    return (0);
  else
    return (-1);
}

int list_len(struct list *list)
{
  int nb = 0;

  while (list != NULL) {
    nb++;
    list = list->next;
  }
  return (nb);
}

void list_print(struct list *list)
{
  puts("\n");
  while (list != NULL) {
    printf("%d -> ", list->data);
    list = list->next;
  }
  printf("NULL\n");
}

int list_del(struct list **list, struct list *chunk)
{
  struct list *tmp = NULL;
  struct list *tmp2 = NULL;
  int bool = 0;

  tmp = (*list);
  tmp2 = (*list);

  if (chunk == NULL) {
    puts("\nErreur: impossible de supprimer NULL.\n");
    return (-1);
  }

  if (tmp == chunk)
    (*list) = (*list)->next;

  while (tmp != NULL) {
    if (tmp == chunk) {
      tmp2->next = tmp->next;
      bool = 0;
      break;
    }
    bool = 1;
    tmp2 = tmp;
    tmp = tmp->next;
  }

  if (bool == 0) {
    return (0);
  } else
    return (-1);
}

int list_del_by_data(struct list **list, const char *data)
{
  char *ptr;
  int i = strtol(data, &ptr, 10); 
  int nb = 0;
  int bool = 0;
  struct list *tmp = NULL;
  struct list *tmp2 = NULL;

  tmp = (*list);
  tmp2 = (*list);

  nb = tmp->data;

  if (nb == i)
    (*list) = (*list)->next;

  while (tmp != NULL) {
    nb = tmp->data;
    if (nb == i) {
      tmp2->next = tmp->next;
      free(tmp);
      bool = 0;
      break;
    }
    bool = 1;
    tmp2 = tmp;
    tmp = tmp->next;
  }
  
  if (bool == 0)
    return (0);
  else
    return (-1);
}

void list_free(struct list *list)
{
  struct list *tmp = NULL;

  while (list != NULL) {
    tmp = list;
    list = list->next;
    free(tmp);
  }
  puts("\nListe free.\n");
}

int main(void)
{
  int i;
  int size;
  const char *tab_add[] = {"0","0","1","11","3","5","55","8"};
  const char *tab_del[] = {"0","11","5","8"};
  const char *tab_bad[] = {"12a", "aaa", "", NULL};
  struct list *list = NULL;

  size = sizeof(tab_add)/sizeof(char*);
  for (i = 0; i < size; i++) {
    if ((list_push(&list, tab_add[i])) == 0)
      printf("\n'%s' ajouté à la liste.\n", tab_add[i]);
  }
  
  list_print(list);
  printf("\nLa liste contient %d chunk(s).\n", list_len(list));
  
  size = sizeof(tab_bad)/sizeof(char*);
  for (i = 0; i < size; i++)
    list_push(&list, tab_bad[i]);

  list_print(list);
  printf("\nLa liste contient %d chunk(s).\n", list_len(list));
  
  size = sizeof(tab_bad)/sizeof(char*);
  for (i = 0; i < size; i++)
    list_del_by_data(&list, tab_bad[1]);

  list_print(list);
  printf("\nLa liste contient %d chunk(s).\n", list_len(list));

  size = sizeof(tab_del)/sizeof(char*);
  for (i = 0; i < size; i++)
    list_del_by_data(&list, tab_del[i]);

  list_print(list);
  printf("\nLa liste contient %d chunk(s).\n", list_len(list));
  list_free(list);
  list = NULL;
  printf("\nLa liste contient %d chunk(s).\n", list_len(list));
  return 0;
}
