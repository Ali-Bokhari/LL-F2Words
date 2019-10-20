/*
abokhari
0970498
abokhari@uoguelph.ca
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "text.h"

void listAppend(struct node_struct **list, void *word){
  struct node_struct *new_node = malloc (sizeof(struct node_struct));
  struct node_struct *tail;
  new_node->data = word;
  new_node->next = NULL;

  if ( *list == NULL){
    *list = new_node;
    return;
  }

  tail = *list;

  while (tail->next) {
    tail = tail->next;
  }

  tail->next = new_node;
}

void printList(struct node_struct *list){
  while (list) {
    printf("%s\n", (char *)list->data);
    list = list->next;
  }
}

void searchPrintList(struct node_struct *list){
  struct node_struct *temp;
  while (list) {
    temp = list->data;
    printf("%s\n", (char *)temp->data);
    list = list->next;
  }
}

struct node_struct *txt2words( FILE *fp ) {
  struct node_struct *head, **current;
  char *str = malloc (256);
  char *sptr;
  char *token;
  current = &head;
  sptr = str;

  while ( fgets (str, 256, fp) ) {
    if (*str == '\n') {
      token = malloc (2);
      strcpy (token, "\n\0");
      *current = malloc( sizeof( struct node_struct ) );
      (*current)->data = token;
      current = &((*current)->next);
      continue;
    }
    while (*str){
      token = get_word (&str);
      /*printf("%s ", token);*/
      if (*token != '\n') {
        *current = malloc( sizeof( struct node_struct ) );
        (*current)->data = token;
        current = &((*current)->next);
      } else {
        free (token);
      }
    }
    str = sptr;
  }

  *current = NULL;
  return head;
}

char *get_word (char **str) {
  unsigned char f = **str;
  char *final;
  char type;
  int i;
  /*if (f == ' '){
    *str = *str + 1;
    return get_word(str);
  }*/
  while (f == ' ') {
    *str = *str + 1;
    f = **str;
  }
  if ((f >= 'a' && f <= 'z') || (f >= 'A' && f <= 'Z') || (f >= '0' && f <= '9')) {
    type = 1;
  } else if (f == '\n') {
    type = 3;
  } else if (f == (*str)[1]) {
    type = 2;
  } else {
    type = 2;
  }

  /*printf("f: %c type: %d\n", f, type);*/

  if (type == 1) {
    for (i = 1; i < 255; i++){
      f = str[0][i];
      if (!(f >= 'a' && f <= 'z') && !(f >= 'A' && f <= 'Z') && !(f >= '0' && f <= '9')) {
        if (!(f == '-' && str[0][i+1] != '-') && !(f == '\'' && str[0][i+1] != '\'')) {
          break;
        }
      }
    }
    final = malloc (i + 1);
    strncpy (final, *str, i);
    final[i] = '\0';
    *str = &(str[0][i]);
    /*printf("final: %s\n", final);
    printf("tester %s\n", *str);*/
    return final;
  } else if (type == 2) {
      for (i = 1; i < 255; i++) {
        if (f != (*str)[i]){
          break;
        }
        f = (*str)[i];
      }
      final = malloc (i + 1);
      strncpy (final, *str, i);
      final[i] = '\0';
      *str = &(str[0][i]);
      return final;
  } else if (type == 3){
      final = malloc (2);
      strncpy (final, *str, 1);
      final[1] = '\0';
      *str = *str + 1;
      return final;
  } else {
      final = malloc (2);
      strncpy (final, *str, 1);
      final[1] = '\0';
      *str = *str + 1;
      return final;
  }
  *str = *str + 1;
  return NULL;
}

int fake_strcmp (const void *a, const void *b) {
  char *ptr_a, *ptr_b;

  ptr_a = (char *)a;
  ptr_b = (char *)b;

  return strcmp( ptr_a, ptr_b );
}


struct node_struct*search( struct node_struct *list, char *target, int(*compar)(const void*,const void*)){
  struct node_struct *final = NULL;
  struct node_struct *tail = list;

  while (tail) {
    if ((*compar)(tail->data, target) == 0){
      listAppend(&final, tail);
    }
    tail = tail->next;
  }

  return final;
}

struct node_struct *copy( struct node_struct *start, struct node_struct *end ) {
  struct node_struct *copied = NULL;

  while (start && start!=end) {
    listAppend (&copied, start->data);
    start = start->next;
  }

  return copied;
}

void ftext( FILE *fp, struct node_struct *list ){
  int i;
  int l;
  char *f;
  while (list) {
    f = list->data;
    fputs (f, fp);
    i = i + strlen(f);
    if (list->next == NULL) {
      break;
    }
    if (*f == ',' || *f == ';' || *f == '!' || *f == '\"' || *f == '.') {
      f = list->next->data;
      if (*f != '\"' && ((*f != '-') && (f[1] != '-'))) {
        if (i >= 80) {
          fputs ("\n", fp);
          i = 0;
        } else {
          fputs (" ", fp);
          i++;
        }
        list = list->next;
        continue;
      }
    }
    l = strlen(f);
    if ((f[l-1] >= 'a' && f[l-1] <= 'z') || (f[l-1] >= 'A' && f[l-1] <= 'Z') || (f[l-1] >= '0' && f[l-1] <= '9')) {
      f = list->next->data;
      if ((*f >= 'a' && *f <= 'z') || (*f >= 'A' && *f <= 'Z') || (*f >= '0' && *f <= '9')){
        if (i >= 80) {
          fputs ("\n", fp);
          i = 0;
        } else {
          fputs (" ", fp);
          i++;
        }
      }
    }
    list = list->next;
  }
}

void free_list( struct node_struct *list, int free_data){
  struct node_struct *temp;
  if (free_data) {
    while (list) {
      temp = list;
      list = list->next;
      free (temp->data);
      free (temp);
    }
  } else {
    while (list) {
      temp = list;
      list = list->next;
      free (temp);
    }
  }
}

int length( struct node_struct *list) {
  int i;
  for (i = 0; list; i++) {
    list = list->next;
  }
  return i;
}

void split (struct node_struct *output[], struct node_struct *input) {
  char alt = 0;
  struct node_struct **cur0, **cur1;
  cur0 = &(output[0]);
  cur1 = &(output[1]);
  while (input) {
    if (!alt) {
      *cur0 = malloc (sizeof(struct node_struct));
      (*cur0)->data = input->data;
      cur0 = &((*cur0)->next);
      alt = 1;
    } else {
      *cur1 = malloc (sizeof(struct node_struct));
      (*cur1)->data = input->data;
      cur1 = &((*cur1)->next);
      alt = 0;
    }
    input = input->next;
  }
  *cur0 = NULL;
  *cur1 = NULL;
}

struct node_struct *mini_sort ( struct node_struct **list1, struct node_struct **list2, int max_nodes, int(*compar)(const void*,const void*)) {
  struct node_struct *head, **current;
  int pop1 = 0;
  int pop2 = 0;
  current = &head;
  while (*list1 && *list2 && pop1 < max_nodes && pop2 < max_nodes) {
    if ((*compar)((*list1)->data, (*list2)->data) < 1) {
      *current = *list1;
      *list1 = (*list1)->next;
      (*current)->next = NULL;
      current = &((*current)->next);
      pop1++;
    } else {
      *current = *list2;
      *list2 = (*list2)->next;
      (*current)->next = NULL;
      current = &((*current)->next);
      pop2++;
    }
  }

  while (*list1 && pop1 < max_nodes) {
    *current = *list1;
    *list1 = (*list1)->next;
    (*current)->next = NULL;
    current = &((*current)->next);
    pop1++;
  }

  while (*list2 && pop2 < max_nodes) {
    *current = *list2;
    *list2 = (*list2)->next;
    (*current)->next = NULL;
    current = &((*current)->next);
    pop2++;
  }

  *current = NULL;
  return head;
}

struct node_struct *sort( struct node_struct *list, int(*compar)(const void*,const void*)) {
  return NULL;
}

int main(){
  /*struct node_struct *new = NULL;
  FILE *fp = fopen ("1342-0.txt", "r");
  FILE *fp2 = fopen ("output.txt", "w");
  new = txt2words(fp);
  ftext (fp2, new);
  fclose(fp);
  free_list (new, 1);*/
  /*struct node_struct *copied = NULL;
  char *char1 = malloc(sizeof(char)*6);
  char *char2 = malloc(sizeof(char)*6);
  char *char3 = malloc(sizeof(char)*6);
  char *char4 = malloc(sizeof(char)*6);
  strcpy (char1, "char1\0");
  strcpy (char2, "char2\0");
  strcpy (char3, "char3\0");
  strcpy (char4, "char2\0");
  listAppend(&new, char1);
  listAppend(&new, char2);
  listAppend(&new, char3);
  listAppend(&new, char4);
  copied = search (new, "char2", fake_strcmp);
  printList(new);
  printf("searched:\n");
  searchPrintList(copied);*/
  FILE *fp;

  struct node_struct *input, *sorted;

  struct node_struct *list[2];



  fp = fopen( "sort_test.txt", "r" );

  input = txt2words( fp );

  fclose( fp );



  printf( "input:\n" );

  ftext( stdout, input );

  printf( "\n" );



  split( list, input );



  printf( "%d %d %d\n", length(input), length(list[0]), length(list[1]) );



  printf( "list[0]:\n" );

  ftext( stdout, list[0] );

  printf( "\n" );



  printf( "list[1]:\n" );

  ftext( stdout, list[1] );

  printf( "\n" );



  sorted = mini_sort( list, list+1, 4, fake_strcmp );



  printf( "%d %d %d\n", length(sorted), length(list[0]), length(list[1]) );



  printf( "sorted:\n" );

  ftext( stdout, sorted );

  printf( "\n" );



  printf( "list[0]:\n" );

  ftext( stdout, list[0] );

  printf( "\n" );



  printf( "list[1]:\n" );

  ftext( stdout, list[1] );

  printf( "\n" );



  free_list( list[0], 0 );

  free_list( list[1], 0 );

  free_list( sorted, 0 );

  free_list( input, 1 );



  return 0;
}
