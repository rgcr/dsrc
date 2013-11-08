#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<rnode.h>

node_t* 
create_node(void *data)
{
    node_t *new_node=NULL;
    new_node = (node_t*)malloc(sizeof(node_t));
    if(new_node == NULL)
		return NULL;
	memset(new_node, 0, sizeof(node_t));
    SET_DATA(new_node,data);
#ifdef DEBUG
    fprintf(stdout,"Node created [%p]\n", new_node);
#endif
return new_node;    
}

void 
free_node(node_t *node, void (*free_data)(void*) )
{  
#ifdef DEBUG
    fprintf(stdout,"Node cleared [%p]\n", node);
#endif
	free_data(node->data);
    free(node);
}

