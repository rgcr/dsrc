#ifndef __NODE_H__
#define __NODE_H__

#include <stdlib.h>

#define DATA(N)		((N)->data)
#define NEXT(N)		((N)->next)
#define PREV(N) 	((N)->prev)

#define SET_DATA(N,X) 	(DATA(N) = (X))
#define SET_NEXT(N,X) 	(NEXT(N) = (X))
#define SET_PREV(N,X) 	(PREV(N) = (X))

#define MOVE_NEXT(N) 	((N) = NEXT(N))
#define MOVE_PREV(N) 	((N) = PREV(N))

#define SET_NULL(N) 	((N) = NULL)

#define NODE_NULL(N) do{  \
	SET_NEXT(N,NULL); \
	SET_PREV(N,NULL); \
	SET_DATA(N,NULL); \
	SET_NULL(N); 	  \
}while(0)

#ifdef __cplusplus
extern "C"{
#endif

typedef struct node{
	struct node *next;
	struct node *prev;
	void *data;
}node_t; 

void     free_node   (node_t *, void(*)(void*) );
node_t*  create_node (void *);

#ifdef __cplusplus
};
#endif

#endif // __NODE_H__
