#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <rnode.h>
#include <rlinked_list.h>

int* create_int_data(int);
void print_int_data(void*);
int  compare_int_data(void*, void*);


int 
main(int argc, char **argv)
{
	int c = 0;
	llist_t* list = 0;
	node_t* aux = 0;


	list = ll_create();	
	ll_initialize(list, free, compare_int_data);

	/* 0...9 */
	for(; c < 10; c++)
		ll_add_last(list, create_node( create_int_data(c) ) );

	/* 10 0...9 */
	ll_add_first(list, create_node( create_int_data(c) ) );

	/* 11 10 0...9 */
	ll_add_first(list, create_node( create_int_data(++c) ) ); 

	/* 11 10 12 0...9 */
	ll_add_before(list, list->first->next->next, create_node( create_int_data(++c) ) ); 

	/* 11 10 12 0...8 13 9 */
	ll_add_after(list, list->last->prev, create_node( create_int_data(++c) ));

	/* 11 10 12 0...8 13 14 9 */
	ll_add_after(list, list->last->prev, create_node( create_int_data(++c) ));

	/* 11 12 0...8 13 14 9	*/
	ll_remove(list, list->first->next, DESTROYNODE );

	/* 11 12 0...8 13 14 */
	ll_remove(list, list->last, DESTROYNODE);

	/* 12 0...8 13 14 */
	ll_remove(list, list->first, DESTROYNODE);

	/* to test "NOTDESTROY" option*/
	aux = list->last->prev;

	/* 12 0...8 14 */
	ll_remove(list, list->last->prev, NOTDESTROY);

	printf("\n");

	/* Forward: 12 0...8 14	*/
	ll_traverse(list, print_int_data, FORWARDTRAVERSE);  printf("\n");

	/* Backward: 14 8...0 12 */
	ll_traverse(list, print_int_data, BACKWARDTRAVERSE); printf("\n\n");

	/* Destroy node	"13"*/
	free_node(aux, list->free_data); printf("\n");	

	/* Deleted node, is not found*/
	int a = 10;
	aux = ll_search_node(list, &a);
	
	if(aux != NULL)
		printf("NODE: %p DATA: %d\n", aux ,*(int*)DATA(aux));

	a = 4;
	aux = ll_search_node(list, &a);

	if(aux != NULL)
		printf("NODE: %p DATA: %d\n", aux ,*(int*)DATA(aux));


	ll_free(list);
	list = 0;
	return EXIT_SUCCESS;
}

int* 
create_int_data(int x){
	int* new_data = (int*)malloc( sizeof(int) );
	if(new_data == NULL)
		return NULL;
	*new_data = x;
	return new_data;
}

void 
print_int_data(void *data)
{
	node_t *node = (node_t*)data;
	printf("%d ", *(int*)node->data);
}

int 
compare_int_data(void *x, void *y)
{
	return *(int*)x == *(int*)y;	
}
