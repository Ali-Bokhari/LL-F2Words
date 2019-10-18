/*
abokhari
0970498
abokhari@uoguelph.ca
*/

struct node_struct {
  void *data;
  struct node_struct *next;
};

char *get_word (char **str);
struct node_struct *txt2words( FILE *fp );
struct node_struct*search( struct node_struct *list, char *target, int(*compar)(const void*,const void*));
struct node_struct *copy( struct node_struct *start, struct node_struct *end );