#include <rlinked_list.h>
#include <stdio.h>
#include <string.h>

llist_t* 
ll_create(void)
{
	llist_t *list = NULL;
	list = (llist_t*)malloc(sizeof(llist_t));

	if(list == NULL)
		return NULL;
	memset(list, 0, sizeof(llist_t));
#ifdef DEBUG
	fprintf(stdout,"Data structure created [%p]\n",list);
#endif
	return list;
}

int 
ll_initialize(llist_t* list, void (*free_data)(void*), int(*cmp_data)(void*,void*))
{
	if(list == NULL)
		return 0;

	list->free_data = free_data;
	list->compare = cmp_data;
	LL_SET_FIRST(list,NULL);
	LL_SET_LAST(list,NULL);
	return 1;	
}

void 
ll_free(llist_t* list)
{
	node_t *curr_node = LL_FIRST(list);
	node_t *aux_node = NULL;

	while(curr_node != NULL){
		aux_node = curr_node;
		curr_node = NEXT(curr_node);
		free_node(aux_node, list->free_data);
	}
#ifdef DEBUG
	fprintf(stdout, "Data structure cleared [%p]\n",list);
#endif
	free(list);
}

int 
ll_add_first(llist_t* list, node_t* new_node)
{
	if(list == NULL || new_node == NULL)
		return 0;

	if( LL_FIRST(list) != NULL)
		return ll_add_before(list, LL_FIRST(list), new_node);

	PREV(new_node) = NULL;
	LL_FIRST(list) = new_node;
	LL_LAST(list) = new_node;
	LL_SET_SIZE(list,LL_SIZE(list)+1);
#ifdef DEBUG
	fprintf(stdout,"Data structure[%p] insert node[%p]\n", list, new_node);
#endif
	return 1;
}


int 
ll_add_last(llist_t* list, node_t* new_node)
{
	if(list == NULL || new_node == NULL)
		return 0;
	if( LL_LAST(list) == NULL)
		return ll_add_first(list, new_node);
	else
		return ll_add_after(list, LL_LAST(list), new_node);
}

int 
ll_add_before(llist_t* list, node_t* reference, node_t* new_node)
{
	if( list  == NULL || reference == NULL || new_node == NULL)
		return 0;

	SET_PREV(new_node,PREV(reference));
	SET_NEXT(new_node,reference);

	if(PREV(reference) == NULL)
		LL_SET_FIRST(list,new_node);
	else
		SET_NEXT(PREV(reference),new_node);

	SET_PREV(reference,new_node);
	LL_SET_SIZE(list,LL_SIZE(list)+1);
#ifdef DEBUG
	fprintf(stdout,"Data structure[%p] insert node[%p]\n", list, new_node);
#endif
	return 1;
}

int 
ll_add_after(llist_t* list, node_t* reference, node_t* new_node)
{
	if( list  == NULL || reference == NULL || new_node == NULL)
		return 0;

	SET_PREV(new_node,reference);
	SET_NEXT(new_node,NEXT(reference));

	if(NEXT(reference) == NULL)
		LL_SET_LAST(list,new_node);
	else
		SET_PREV(NEXT(reference),new_node);

	SET_NEXT(reference,new_node);
	LL_SET_SIZE(list,LL_SIZE(list)+1);
#ifdef DEBUG
	fprintf(stdout,"Data structure[%p] insert node[%p]\n", list, new_node);
#endif
	return 1;
}

int 
ll_remove(llist_t* list, node_t* reference, int destroyed)
{
	if(list == NULL || reference == NULL)
		return 0;

	if(PREV(reference) == NULL)
		LL_SET_FIRST(list,NEXT(reference));
	else
		SET_NEXT(PREV(reference),NEXT(reference));
	if(NEXT(reference) == NULL)
		LL_SET_LAST(list,PREV(reference));
	else
		SET_PREV(NEXT(reference),PREV(reference));

	LL_SET_SIZE(list,LL_SIZE(list)-1);
	if(destroyed)
		free_node(reference, list->free_data);
	return 1;
}

int
ll_remove_first(llist_t* list, int destroyed)
{
	return ll_remove(list, LL_FIRST(list), destroyed);
}

int
ll_remove_last(llist_t* list, int destroyed)
{
	return ll_remove(list, LL_LAST(list), destroyed);
}

void 
ll_traverse(llist_t* list, void (*function)(void*), int mode)
{
	node_t* current = NULL;

	if(mode == FORWARDTRAVERSE)
		current = LL_FIRST(list);
	else if(mode == BACKWARDTRAVERSE)
		current = LL_LAST(list);
	else
		return;
	while(current != NULL){
		function(current);
		if( mode == FORWARDTRAVERSE)
			MOVE_NEXT(current);
		else
			MOVE_PREV(current);
	}
}

node_t*
ll_search_node(llist_t* list, void* data_compare)
{
	node_t* current = list->first;
	for(; (current != NULL &&
				(list->compare(current->data, data_compare) == 0 ));
			MOVE_NEXT(current) );
	return current;
}
