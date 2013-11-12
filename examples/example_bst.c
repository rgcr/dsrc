#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <rnode.h>
#include <rbinary_tree.h>

int* create_int_data(int);
void print_int_data(void*);
int  compare_int_data(void*, void*);

int 
main(int argc, char **argv)
{
	int c = 0;
	
	btree_t* tree = 0;
	node_t* aux = 0;
	int data_to_search = 13;

	const int array[]={15, 9, 20, 6 , 14, 17, 64, 13, 26, 72};

	tree = bt_create();
	bt_initialize(tree, free, compare_int_data);

	for(c = 0; c < 10; c++)
		bt_insert_recursive(&(tree->root), 
				create_node(create_int_data(array[c])), tree->compare);


	printf("\n");
	/*
	* Inorden = [6, 9, 13, 14, 15, 17, 20, 26, 64, 72].
	*/
	bt_inorden_walk(tree->root, print_int_data);

	printf("\n");
	/*
	* Preorden = [15, 9, 6, 14, 13, 20, 17, 64, 26, 72].
	*/
	bt_preorden_walk(tree->root, print_int_data);

	printf("\n");
	/*
	* Postorden =[6, 13, 14, 9, 17, 26, 72, 64, 20, 15].
	*/
	bt_postorden_walk(tree->root, print_int_data);

	printf("\n");
	/*
	 * Size = 10
	 */
	printf("%d\n", bt_size(tree->root)); 

	/*
	 * Minimum = 6
	 */
	aux = bt_minimum(tree->root);	
	printf("%d\n", *(int*)aux->data);

	/*
	 * Maximum = 72
	 */
	aux = bt_maximum(tree->root);	
	printf("%d\n", *(int*)aux->data);

	/*
	 * %p -> 13
	 */
	aux = bt_recursive_search(tree->root, &data_to_search, tree->compare);
	printf("[%p] ->  %d\n", aux->data, *(int*)aux->data); 

	/*
	 * %p -> 13
	 */
	aux = bt_iterative_search(tree->root, &data_to_search, tree->compare);
	printf("[%p] ->  %d\n", aux->data, *(int*)aux->data); 


	// XXX: BUG, infinite loop
	data_to_search = 15;
	tree->root =  bt_delete_node(&tree->root, &data_to_search, tree->compare, tree->free_data); 
	bt_inorden_walk(tree->root, print_int_data);


	bt_free(tree);
	tree = 0;
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
	printf("%d ", *(int*)data);
}

int 
compare_int_data(void *left, void *right)
{
	if (*(int*)left < *(int*)right )
		return -1;
	else if( *(int*)left > *(int*)right)
		return 1;
	else
		return 0;
}
