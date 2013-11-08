#include <rbinary_tree.h>
#include <stdio.h>
#include <string.h>

btree_t*
bt_create(void)
{
	btree_t *tree = NULL;
	tree = (btree_t*)malloc(sizeof(btree_t));

	if(tree == NULL)
		return NULL;
	memset(tree,0, sizeof(btree_t));
#ifdef DEBUG
	fprintf(stdout,"Data structure created [%p]\n",tree);
#endif
	return tree;
}

int 
bt_initialize(btree_t* tree, void (*free_data)(void*), int(*cmp_data)(void*,void*))
{
	if(tree == NULL)
		return 0;

	tree->free_data = free_data;
	tree->compare = cmp_data;
	BT_SET_ROOT(tree,NULL);
	return 1;
}

void
bt_insert_recursive(node_t **root, node_t *new_node, int (*cmp_function)(void*,void*))
{
	if(*root == NULL){
		*root = new_node;
#ifdef DEBUG
		fprintf(stdout,"Data structure[%p] insert node[%p]\n", *root, new_node);
#endif
	}
	else if( (cmp_function(DATA(new_node), DATA(*root)) ) < 0 )
		bt_insert_recursive(&(LEFT_CHILD(*root)), new_node, cmp_function);
	else if( (cmp_function(DATA(new_node), DATA(*root)) ) > 0 )
		bt_insert_recursive(&(RIGHT_CHILD(*root)), new_node, cmp_function);
	else
		return;
}

void
bt_inorden_walk(node_t *root, void(*function)(void*))
{
	if(root == NULL)
		return;
	bt_inorden_walk(LEFT_CHILD(root), function);
	function(DATA(root));
	bt_inorden_walk(RIGHT_CHILD(root), function);
}

void
bt_preorden_walk(node_t *root, void(*function)(void*))
{
	if(root == NULL)
		return;
	function(DATA(root));
	bt_preorden_walk(LEFT_CHILD(root), function);
	bt_preorden_walk(RIGHT_CHILD(root), function);
}

void
bt_postorden_walk(node_t *root, void(*function)(void*))
{
	if(root == NULL)
		return;
	bt_postorden_walk(LEFT_CHILD(root), function);
	bt_postorden_walk(RIGHT_CHILD(root), function);
	function(DATA(root));
}

node_t* 
bt_minimum(node_t *root)
{
	if(root == NULL)
		return NULL;

	node_t *aux = root;
	while(LEFT_CHILD(aux) != NULL)
		aux = LEFT_CHILD(aux);
	return aux;
}

node_t*
bt_maximum(node_t *root)
{
	if(root == NULL)
		return NULL;

	node_t *aux = root;
	while(RIGHT_CHILD(aux) != NULL)
		aux = RIGHT_CHILD(aux);
	return aux;
}

node_t*
bt_recursive_search(node_t* root, void *data, int (*cmp_function)(void*,void*))
{
	if(root == NULL  || (cmp_function(data, DATA(root)) ) == 0)
		return root;

	if( (cmp_function(data, DATA(root)) ) < 0 )
		return bt_recursive_search(LEFT_CHILD(root), data, cmp_function );
	else
		return bt_recursive_search(RIGHT_CHILD(root), data, cmp_function );
}

node_t*
bt_iterative_search(node_t* root, void* data, int (*cmp_function)(void*,void*))
{
	node_t *aux = root;
	while( aux != NULL && (cmp_function(data, DATA(aux)) ) != 0){
		if( (cmp_function(data, DATA(aux))) < 0 )
			aux = LEFT_CHILD(aux);
		else
			aux = RIGHT_CHILD(aux);
	}
	return aux;	
}

int
bt_size(node_t* root)
{
	if(root == NULL)
		return 0;
	else
		return ( bt_size(LEFT_CHILD(root)) + 1 + bt_size(RIGHT_CHILD(root)) );
}


// XXX: BUG, infinite loop
node_t*
bt_delete_node(node_t *root, void *data,
		int (*cmp_function)(void*, void*), void (*free_data)(void*))
{
	if(root == NULL)
		return NULL;

	node_t* cursor;
	int x = 0;

	x = cmp_function(DATA(root), data);
	if(x < 0)
		SET_LEFT_CHILD(root,bt_delete_node(LEFT_CHILD(root), data, cmp_function, free_data));
	else if(x > 0)
		SET_RIGTH_CHILD(root,bt_delete_node(RIGHT_CHILD(root), data, cmp_function, free_data));
	else{
		if(LEFT_CHILD(root) == NULL){
			cursor = RIGHT_CHILD(root);
			free_node(root, free_data);
			root = cursor;
		}
		else if(RIGHT_CHILD(root) == NULL){
			cursor = LEFT_CHILD(root);
			free_node(root, free_data);
			root = cursor;
		}
		else{
			cursor = RIGHT_CHILD(root);
			node_t *parent = NULL;
			while(LEFT_CHILD(cursor) != NULL){
				parent = cursor;
				cursor = LEFT_CHILD(root);
			}
			SET_DATA(root,DATA(cursor));
			if(parent != NULL )
				SET_LEFT_CHILD(parent,bt_delete_node(LEFT_CHILD(parent),DATA(LEFT_CHILD(parent)), cmp_function, free_data) );
			else
				SET_RIGTH_CHILD(root,bt_delete_node(RIGHT_CHILD(root), DATA(RIGHT_CHILD(root)), cmp_function, free_data) );
		}
	}
	return root;
}


int
bt_free(btree_t* tree)
{
	if(tree == NULL)
		return 0;
	bt_dispose(tree->root, tree->free_data);
	return 1;
}


void
bt_dispose(node_t *root, void (*free_data)(void*))
{
	if(root == NULL)
		return;
	bt_dispose(LEFT_CHILD(root), free_data);
	bt_dispose(RIGHT_CHILD(root), free_data);
	free_node(root, free_data);
}
