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
  struct node_struct *final = NULL;
  char *str = malloc (256);
  char *token;

  while ( fgets (str, 256, fp) ) {
    /*printf("%s\n", str);*/
    if (*str == '\n') {
      token = malloc (2);
      strcpy (token, "\n\0");
      listAppend(&final, token);
      continue;
    }
    while (*str){
      token = get_word (&str);
      if (*str) {
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
  if (f == ' '){
    *str = *str + 1;
    return get_word(str);
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
    for (i = 1; i < 256; i++){
      f = str[0][i];
      if (!(f >= 'a' && f <= 'z') && !(f >= 'A' && f <= 'Z') && !(f >= '0' && f <= '9')) {
        if (!(f == '-' && str[0][i+1] != '-') && !(f == '\'' && str[0][i+1] != '\'')) {
          break;
        }
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
        if (f != (*str)[i]){
          break;
        }
        f = (*str)[i];
      }
      final = malloc (i + 1);
      strncpy (final, *str, i);
      *str = &(str[0][i]);
      return final;
  } else if (type == 3){
      final = malloc (2);
      strncpy (final, *str, 1);
      *str = *str + 1;
      return final;
  } else {
      final = malloc (2);
      strncpy (final, *str, 1);
      *str = *str + 1;
      return final;
  }
  *str = *str + 1;
  return NULL;
}

int fake_strcmp (const void *str1, const void *str2) {
  return strcmp(str1, str2);
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

int main(){
  struct node_struct *new = NULL;
  FILE *fp = fopen ("text.txt", "r");
  new = txt2words(fp);
  printList(new);
  fclose(fp);
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
  return 0;
}
