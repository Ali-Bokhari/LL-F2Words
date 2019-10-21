/*
Ali Bokhari
0970498
abokhari@uoguelph.ca
*/

struct node_struct {
  void *data;
  struct node_struct *next;
};

struct queue {
  struct node_struct *head;
  struct node_struct **tail;
};

char *get_word (char **str);
struct node_struct *txt2words( FILE *fp );
struct node_struct*search( struct node_struct *list, char *target, int(*compar)(const void*,const void*));
struct node_struct *copy( struct node_struct *start, struct node_struct *end );
void ftext( FILE *fp, struct node_struct *list );
struct node_struct *sort( struct node_struct *list, int(*compar)(const void*,const void*));
void free_list( struct node_struct *list, int free_data);
int length( struct node_struct *list);
void remove_repeats(struct node_struct *list, int(*compar)(const void*,const void*));
