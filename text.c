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
  };
}

struct node_struct *txt2words( FILE *fp ) {
  struct node_struct *final = NULL;
  char *str = malloc (256);
  char *token;

  while ( fgets (str, 256, fp) ) {
    /*token = strtok (str, " ");
    while (token) {*/
    while (strlen(str) > 0){
      token = get_word (&str);
      if (*str) {
        printf("token: %s\n", token);
        listAppend(&final, token);
      }
    }
  }
  return final;
}

char *get_word (char **str) {
  char f = **str;
  char *final;
  char type;
  int i;
  if (f == ' ' || f == '\n'){
    *str = *str + 1;
    return get_word(str);
  }
  if ((f > 96 && f < 123) || (f > 64 && f < 91) || (f > 47 && f < 58)) {
    type = 1;
  } else if (f == '\n') {
    type = 3;
  } else if (f == *str[1]) {
    type = 2;
  } else {
    type = 1;
  }

  if (type == 1) {
    for (i = 1; i < 256; i++){
      f = str[0][i];
      if (!(f > 96 && f < 123) && !(f > 64 && f < 91) && !(f > 47 && f < 58)) {
        break;
      }
    }
    final = malloc (i + 1);
    strncpy (final, *str, i);
    *str = &(str[0][i]);
    /*printf("final: %s\n", final);
    printf("tester %s\n", *str);*/
    return final;
  } else if (type == 2) {
    for (i = 1; i < 256; i++) {
      if (f != *str[i]){
        break;
      }
      f = *str[i];
    }
    final = malloc (i + 1);
    strncpy (final, *str, i);
    *str = &(str[0][i]);
    return final;
  } else if (type == 3){
    if (f == str[0][1]){
      final = malloc (2);
      strcpy (final, "\n\0");
      *str = *str + 1;
      return final;
    }
  } else {

  }
  *str = *str + 1;
  return NULL;
}

int fake_strcmp (const void *str1, const void *str2) {
  return strcmp(str1, str2);
}


struct node_struct*search( struct node_struct *list, char *target, int(*compar)(const void*,const void*)){
  struct node_struct *final;
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
  struct node_struct *copied;

  while (start && start!=end) {
    listAppend (&copied, start->data);
    start = start->next;
  }

  return copied;
}

int main(){
  /* FILE *fp;
  struct node_struct *final;
  fp = fopen("text.txt", "r");
  final = txt2words (fp);*/
  struct node_struct *new;
  struct node_struct *edited;
  char *char1;
  /*char *char2;
  char *char3;
  char *char4;*/
  printf("mallocs");
  char1 = malloc(6);
  strcpy (char1, "char1\0");
  /*strcpy (char2, "char2\0");
  strcpy (char3, "char3\0");
  strcpy (char4, "char2\0");*/
  listAppend(&new, char1);
  /*printList(new);
  listAppend(&new, char2);
  printList(new);
  listAppend(&new, char3);
  printList(new);
  listAppend(&new, char4);
  printList(new);
  printf("Call time %s,%s,%s,%s\n", char1, char2, char3, char4);*/

  /*edited = copy (new, new->next);*/
  printList(new);
  return 0;
}
