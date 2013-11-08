#ifndef __BTREE_H__
#define __BTREE_H__

#include <stdlib.h>
#include <rnode.h>
#include <rlinked_list.h>

#define RIGHT_CHILD(X)		NEXT(X)
#define LEFT_CHILD(X)		PREV(X)

#define SET_RIGTH_CHILD(N,X) 	SET_NEXT(N,X)
#define SET_LEFT_CHILD(N,X) 	SET_PREV(N,X)

#define BT_ROOT(T)		((T)->root)
#define BT_SET_ROOT(T,X) 	(BT_ROOT(T) = (X))

#ifdef __cplusplus
extern "C"{
#endif

typedef struct binary_tree{
	node_t* root;
	void (*free_data)(void*);
	int (*compare)(void*, void*);
}btree_t;

btree_t* bt_create 	(void);
int bt_initialize 	(btree_t*, void(*)(void*), int (*)(void*,void*));
int bt_size 		(node_t*);
int bt_free 		(btree_t *);
void bt_insert_recursive(node_t**, node_t*, int(*)(void*,void*) );
void bt_inorden_walk 	(node_t*, void(*)(void*));
void bt_preorden_walk 	(node_t*, void(*)(void*));
void bt_postorden_walk 	(node_t*, void(*)(void*));
void bt_dispose 	(node_t*, void (*)(void*));
node_t* bt_minimum 	(node_t*); 
node_t* bt_maximum 	(node_t*); 
node_t* bt_recursive_search (node_t*, void*, int (*)(void*,void*));
node_t* bt_iterative_search (node_t*, void*, int (*)(void*,void*));
node_t* bt_delete_node	(node_t*, void*, int (*)(void*,void*), void (*)(void*) );
#ifdef __cplusplus
};
#endif

#endif 
