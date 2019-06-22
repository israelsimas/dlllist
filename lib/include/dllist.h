/**************************************************************************
 * dllist.h
 *
 *  Create on: 21/06/2019
 *
 *  Header for Dynamically Linked Lists in C
 *
 * Copyrights, 2019
 *
 **************************************************************************/
#ifndef __DLLIST_H__
#define __DLLIST_H__

#include <stddef.h>

/**************************************************************************
 * DEFINITIONS
 **************************************************************************/
#ifndef malloc_fl
#  define malloc_fl(s, f, l) malloc(s)
#endif

#ifndef free_fl
#  define free_fl(p, f, l) free(p)
#endif

/*
 * Checks if the item's pointers are compatible.
 *
 * @param pItemA the first item to be compared.
 * @param pItemB Second item pointer to be compared.
 *
 * @return Value that determines whether items are compatible.
 */
long this_item(void *a, void *b);

/**************************************************************************
 * TYPEDEFS
 **************************************************************************/
/*
 * @struct DLLIST_ITEM
 *
 * Linked list item
 */
typedef struct DLLIST_ITEM {
	void *item;
	struct DLLIST_ITEM *prev;
	struct DLLIST_ITEM *next;
} DLLIST_ITEM;

#define DLLIST_ITEM_INITILIZER {NULL, NULL, NULL}

/*
 * @struct DLLIST
 *
 * Linked list
 */
typedef struct DLLIST {
	unsigned long count;
	DLLIST_ITEM *cur;
	DLLIST_ITEM *head;
	DLLIST_ITEM *tail;
	DLLIST_ITEM *free;
} DLLIST;

#define DLLIST_INITIALIZER {0, NULL, NULL, NULL, NULL}
#define LENGHT_STR_DLLIST   256

/*
 * Basic functions for the system chained list
 */
#define new_DLLIST() new_DLLIST_fl(__FILE__, __LINE__)
DLLIST *new_DLLIST_fl(char *pFile, int nLine);
#define del_DLLIST(pdll, pf) del_DLLIST_fl((pdll), (pf), __FILE__, __LINE__)
void del_DLLIST_fl(DLLIST *pDllist, void(*free_item)(void *), char *pFile, int nLine);
#define reserve_free_items_DLLIST(pdll, n)  reserve_free_items_DLLIST_fl((pdll), (n), __FILE__, __LINE__)
void reserve_free_items_DLLIST_fl(DLLIST *pdllist, int n, char *pFile, int nLine);

/*
 * Initiates a linked list.
 *
 * @param pDllist Linked list pointer
 */
void init_DLLIST(DLLIST *pDLList);
#define clear_DLLIST(pdll, pf) clear_DLLIST_fl((pdll), (pf), __FILE__, __LINE__)
void clear_DLLIST_fl(DLLIST *pDLList, void(*free_item)(void *), char *pFile, int nLine);

#define DLLIST_append(pdll, pitem)	DLLIST_append_fl((pdll), (pitem), __FILE__, __LINE__)
void *DLLIST_append_fl(DLLIST *pDllist, void *item, char *pFile, int nLine);
#define DLLIST_prepend(pdll, pitem)		DLLIST_prepend_fl((pdll), (pitem), __FILE__, __LINE__)
void *DLLIST_prepend_fl(DLLIST *pDllist, void *item, char *pFile, int nLine);
#define DLLIST_insert_before(pdll, pitem) 	DLLIST_insert_before_fl((pdll), (pitem), __FILE__, __LINE__)
void *DLLIST_insert_before_fl(DLLIST *pDllist, void *item, char *pFile, int nLine);
#define DLLIST_insert_after(pdll, pitem)	DLLIST_insert_after_fl((pdll), (pitem), __FILE__, __LINE__)
void *DLLIST_insert_after_fl(DLLIST *pDllist, void *item, char *pFile, int nLine);

#define DLLIST_add_sorted(pdll, pitem, pf)  DLLIST_add_sorted_fl((pdll), (pitem), (pf), __FILE__, __LINE__)
void *DLLIST_add_sorted_fl(DLLIST *pDllist, void *item, long(*sortfcn)(void *, void *), char *pFile, int nLine);

/*
 * Sort a linked list
 *
 * @param pDllist Linked list pointer to be duplicated
 */
void DLLIST_sort(DLLIST *pDllist, long(*sortfcn)(void *, void *));
void *DLLIST_find(DLLIST *pDllist, void *pKey, long(*sortfcn)(void *, void *));

/*
 * Retrieves the first item in the linked list
 *
 * @param linked list pointer
 *
 * @return pointer of the first item.
 */
void *DLLIST_head(DLLIST *pDllist);

/*
 * Retrieves the last item in the linked list
 *
 * @param linked list pointer
 *
 * @return the last item's pointer.
 */
void *DLLIST_tail(DLLIST *pDllist);

/*
 * Performs the progress of the threaded list for the successor item.
 *
 * @param pDllist linked list pointer
 */
void DLLIST_next(DLLIST *pDllist);

/*
 * Performs the forwarding of the linked list to the predecessor item.
 *
 * @param pDllist linked list pointer
 */
void DLLIST_prev(DLLIST *pDllist);
unsigned long DLLIST_count(DLLIST *pDllist);
#define DLLIST_count_inline(x) (((x)==NULL)?0:((x)->count))

/*
 * Retrieves the current item from a linked list
 *
 * @param pDllist Linked list pointer to be duplicated
 *
 * @return pointer of the threaded list item that was retrieved.
 */
void *DLLIST_read(DLLIST *pDllist);
long DLLIST_cur_is_null(DLLIST *pDllist);

/*
 * Removes the current item from a linked list
 *
 * @param pDllist Linked list pointer to be duplicated
 *
 * @return pointer of the chained list item that was removed.
 */
void *DLLIST_remove(DLLIST *pDllist);

/*
 * Copy one linked list to another.
 *
 * @param pDllDst Destination chained list pointer
 * @param pDllSrc list pointer to be copied
 */
void DLLIST_copy(DLLIST *pDllDst, DLLIST *pDllSrc);

/*
 * Handling functions for linked list items
 */
#define new_DLLIST_ITEM(pdll) new_DLLIST_ITEM_fl((pdll), __FILE__, __LINE__)
DLLIST_ITEM *new_DLLIST_ITEM_fl(DLLIST *pDllist, char *pFile, int nLine);

/*
 * Removes an item from the threaded list.
 *
 * @param pDllist Linked list pointer
 * @param pDllitem pointer of the item to be removed.
 */
void del_DLLIST_ITEM(DLLIST *pDllist, DLLIST_ITEM *pDllitem);
#define new_DLLIST_WithItems(n, sz)	new_DLLIST_WithItems_fl((n), (sz), __FILE__, __LINE__)
DLLIST *new_DLLIST_WithItems_fl(size_t n, size_t sz, char *pFile, int nLine);

/*
 * Insere um item na lista encadeada.
 *
 * @param pDllist Linked list pointer
 * @param pDllitem pointer of the item to be inserted.
 *
 * @return pDllitem ponteiro do item inserido.
 */
DLLIST_ITEM *DLLIST_append_ITEM(DLLIST *pDllist, DLLIST_ITEM *pDllitem);
DLLIST_ITEM *DLLIST_prepend_ITEM(DLLIST *pDllist, DLLIST_ITEM *pDllitem);
DLLIST_ITEM *DLLIST_insert_after_ITEM(DLLIST *pDllist, DLLIST_ITEM *pDllitem);
DLLIST_ITEM *DLLIST_insert_before_ITEM(DLLIST *pDllist, DLLIST_ITEM *pDllitem);

/*
 * Retrieves the current item from a linked list
 *
 * @param pDllist Linked list pointer to be duplicated
 *
 * @return pointer of the threaded list item that was retrieved.
 */
DLLIST_ITEM *DLLIST_read_ITEM(DLLIST *pDllist);

/*
 * Removes an item from a linked list
 *
 * @param pDllist Linked list pointer to be duplicated
 * @param pDllitem pointer of the item to be removed.
 *
 * @return pointer of the chained list item that was removed.
 */
DLLIST_ITEM *DLLIST_remove_ITEM(DLLIST *pDllist, DLLIST_ITEM *pDllitem);

#endif
