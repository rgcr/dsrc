#ifndef __LISTLINKED_H__
#define __LISTLINKED_H__

#include <stdlib.h>
#include "rnode.h"

#define FORWARDTRAVERSE  (1<<0) //0x00
#define BACKWARDTRAVERSE (1<<1) //0x01

#define NOTDESTROY 	(1<<0) //0x00
#define DESTROYNODE 	(1<<1) //0x01

#define LL_SIZE(L)	((L)->size)
#define LL_FIRST(L)	((L)->first)
#define LL_LAST(L)	((L)->last)

#define LL_FIRST_NEXT(L)  ((L)->first->next)
#define LL_FIRST_PREV(L)  ((L)->first->prev)
#define LL_LAST_NEXT(L)	  ((L)->last->next)
#define LL_LAST_PREV(L)	  ((L)->last->prev)

#define LL_SET_SIZE(L,X)  (LL_SIZE(L) = (X))
#define LL_SET_FIRST(L,X) (LL_FIRST(L) = (X))
#define LL_SET_LAST(L,X)  (LL_LAST(L) = (X))

#define LL_NULL(L)	 do{	\
	LL_SET_SIZE(L,0);	\
	LL_SET_FIRST(L,NULL); 	\
	LL_SET_LAST(L,NULL);  	\
	SET_NULL(L); 		\
}while(0);

#ifdef __cplusplus
extern "C"{
#endif

typedef struct linked_list{
	int size;
	node_t *first;
	node_t *last;
	void (*free_data)(void*);
	int  (*compare)(void *, void *);
}llist_t;

llist_t* ll_create	(void);
int ll_initialize	(llist_t *, void(*)(void*), int (*)(void*,void*));
void ll_free		(llist_t*);
void ll_traverse	(llist_t*, void (*)(void*), int);
int  ll_add_first 	(llist_t*, node_t*);
int  ll_add_last 	(llist_t*, node_t*);
int  ll_add_before 	(llist_t*, node_t*, node_t*);
int  ll_add_after 	(llist_t*, node_t*, node_t*);
int  ll_remove 		(llist_t*, node_t*, int);
int  ll_remove_first	(llist_t*, int);
int  ll_remove_last	(llist_t*, int);
int  ll_size 		(llist_t*);
node_t* ll_search_node	(llist_t*, void*);

#ifdef __cplusplus
};
#endif

#endif // __LISTLINKED_H__
