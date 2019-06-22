/**************************************************************************
 *
 * dllist.c
 *
 *    Dllist functions
 *
 * Copyright 2019
 *
 **************************************************************************/
#include <dllist.h>
#include <string.h>
#include <stdlib.h>

void *DLLIST_add_sorted_fl(DLLIST *pDllist, void *item, long(*sortfcn)(void *, void *), char *pFile, int nLine) {

	DLLIST_ITEM *tmpitem, *headitem;

	if (sortfcn == NULL) {
		sortfcn = this_item;
    }

	headitem = pDllist->head;

	if (headitem == NULL) {
		return DLLIST_append_fl(pDllist, item, pFile, nLine);
	}

	while ((sortfcn(headitem->item, item) <= 0) && (headitem->next))
		headitem = headitem->next;

	if ((headitem->next == NULL) && (sortfcn(headitem->item, item) <= 0)) {
		return DLLIST_append_fl(pDllist, item, pFile, nLine);
	}

	if ((headitem->prev == NULL) && (sortfcn(headitem->item, item) > 0)) {
		return DLLIST_prepend_fl(pDllist, item, pFile, nLine);
	}

	tmpitem = new_DLLIST_ITEM_fl(pDllist, pFile, nLine);

	if (tmpitem == NULL) {
		return (NULL);
	}

	tmpitem->item       = item;
	pDllist->count++;
	pDllist->cur        = tmpitem;
	tmpitem->next       = headitem;
	tmpitem->prev       = headitem->prev;
	tmpitem->next->prev = tmpitem;
	tmpitem->prev->next = tmpitem;

	return (tmpitem->item);
	}

void *DLLIST_append_fl(DLLIST *pDllist, void *item, char *pFile, int nLine) {
	DLLIST_ITEM *tmpitem;

	tmpitem = new_DLLIST_ITEM_fl(pDllist, pFile, nLine);
	if (tmpitem == NULL) {
		return NULL;
	}
	tmpitem->item = item;

	DLLIST_append_ITEM(pDllist, tmpitem);

	return (tmpitem->item);
}

DLLIST_ITEM *DLLIST_append_ITEM(DLLIST *pDllist, DLLIST_ITEM *pDllitem) {

	pDllitem->next  = NULL;
	pDllist->cur    = pDllitem;
	if (pDllist->tail) {
		pDllitem->prev      = pDllist->tail;
		pDllist->tail->next = pDllitem;
	} else {
		pDllitem->prev  = NULL;
		pDllist->head   = pDllitem;
	}
	pDllist->tail = pDllitem;
	pDllist->count++;

	return (pDllitem);
}

void DLLIST_copy(DLLIST *pDllDst, DLLIST *pDllSrc) {
	memcpy((void *) pDllDst, (void *) pDllSrc, sizeof(DLLIST));
}

unsigned long DLLIST_count(DLLIST *pDllist) {
	if (pDllist == NULL)
		return (0);

	return (pDllist->count);
}

long DLLIST_cur_is_null(DLLIST *pDllist) {
	return (pDllist->cur == NULL);
}

void del_DLLIST_fl(DLLIST *pDllist, void(*free_item)(void *), char *pFile, int nLine) {
	clear_DLLIST_fl(pDllist, free_item, pFile, nLine);
	free_fl((void *) pDllist, pFile, nLine);
}

void clear_DLLIST_fl(DLLIST *pDLList, void(*free_item)(void *), char *pFile, int nLine) {
	DLLIST_ITEM *tmp1, *tmp2;

	tmp1 = pDLList->head;
	while (tmp1 != NULL) {
		tmp2 = tmp1->next;
		if (free_item) {
			free_item(tmp1->item);
			tmp1->item = NULL;
		}free_fl((void *) tmp1, pFile, nLine);
		tmp1 = tmp2;
	}
	tmp1 = pDLList->free;
	while (tmp1 != NULL) {
		tmp2 = tmp1->next;
		free_fl((void *) tmp1, pFile, nLine);
		tmp1 = tmp2;
	}
}

void del_DLLIST_ITEM(DLLIST *pDllist, DLLIST_ITEM *pDllitem) {
	pDllitem->next = pDllist->free;
	pDllist->free = pDllitem;
}

void *DLLIST_find(DLLIST *pDllist, void *pKey, long(*sortfcn)(void *, void *)) {
	DLLIST_ITEM *pTmp1;

	if (sortfcn == NULL)
		sortfcn = this_item;

	pTmp1 = pDllist->cur;

	while (pTmp1 != NULL) {
		if (sortfcn(pTmp1->item, pKey) == 0) {
			break;
		}

		pTmp1 = pTmp1->next;
	}

	pDllist->cur = pTmp1;

	return (pTmp1 ? pTmp1->item : NULL);
}

void *DLLIST_head(DLLIST *pDllist) {
	pDllist->cur = pDllist->head;

	return DLLIST_read(pDllist);
}

DLLIST_ITEM *DLLIST_insert_after_ITEM(DLLIST *pDllist, DLLIST_ITEM *pDllitem) {
	DLLIST_ITEM *tmp2;

	if (pDllist->cur == NULL) {
		return DLLIST_append_ITEM(pDllist, pDllitem);
	}

	tmp2 = pDllist->cur;
	pDllist->cur = pDllitem;

	pDllitem->next  = tmp2->next;
	tmp2->next      = pDllitem;
	pDllitem->prev  = tmp2;
	if (pDllitem->next == NULL) {
		pDllist->tail = pDllitem;
	} else {
		pDllitem->next->prev = pDllitem;
	}
	pDllist->count++;

	return (pDllitem);
}

DLLIST_ITEM *DLLIST_insert_before_ITEM(DLLIST *pDllist, DLLIST_ITEM *pDllitem) {
	DLLIST_ITEM *tmp2;

	if (pDllist->cur == NULL) {
		return DLLIST_prepend_ITEM(pDllist, pDllitem);
	}

	tmp2 = pDllist->cur;
	pDllist->cur = pDllitem;

	pDllitem->prev  = tmp2->prev;
	tmp2->prev      = pDllitem;
	pDllitem->next  = tmp2;
	if (pDllitem->prev == NULL) {
		pDllist->head = pDllitem;
	} else {
		pDllitem->prev->next = pDllitem;
	}
	pDllist->count++;

	return (pDllitem);
}

void *DLLIST_insert_after_fl(DLLIST *pDllist, void *item, char *pFile, int nLine) {
	DLLIST_ITEM *pTmpItem;

	pTmpItem = new_DLLIST_ITEM_fl(pDllist, pFile, nLine);
	if (pTmpItem == NULL) {
		return NULL;
	}
	pTmpItem->item = item;

	return DLLIST_insert_after_ITEM(pDllist, pTmpItem)->item;
}

void *DLLIST_insert_before_fl(DLLIST *pDllist, void *item, char *pFile, int nLine) {
	DLLIST_ITEM *pTmpItem;

	pTmpItem = new_DLLIST_ITEM_fl(pDllist, pFile, nLine);

	if (pTmpItem == NULL) {
		return NULL;
	}

	pTmpItem->item = item;

	return DLLIST_insert_before_ITEM(pDllist, pTmpItem)->item;
}

DLLIST *new_DLLIST_fl(char *pFile, int nLine) {
	DLLIST *pTmp;

	pTmp = (DLLIST *) malloc_fl(sizeof(DLLIST), pFile, nLine);
	if (pTmp == NULL) {
		return (pTmp);
	}
	init_DLLIST(pTmp);

	return (pTmp);
}

void init_DLLIST(DLLIST *pDLList) {
	pDLList->count = 0;
	pDLList->cur = NULL;
	pDLList->head = NULL;
	pDLList->tail = NULL;
	pDLList->free = NULL;
}

DLLIST_ITEM *new_DLLIST_ITEM_fl(DLLIST *pDllist, char *pFile, int nLine) {
	DLLIST_ITEM *pTmp1;

	if (pDllist->free) {
		pTmp1 = pDllist->free;
		pDllist->free = pTmp1->next;
	} else {
		pTmp1 = (DLLIST_ITEM *) malloc_fl(sizeof(DLLIST_ITEM), pFile, nLine);
	}

	return (pTmp1);
}

void reserve_free_items_DLLIST_fl(DLLIST *pDllist, int n, char *pFile, int nLine) {
	DLLIST_ITEM **ppItem;

	/* Conta n itens para liberar na lista */
	ppItem = &(pDllist->free);
	while (n > 0) {
		/* Senão há, reserva (aloca) memória para ele */
		if (NULL == *ppItem) {
			*ppItem = (DLLIST_ITEM *) malloc_fl(sizeof(DLLIST_ITEM), pFile, nLine);
			(*ppItem)->next = NULL;
		}

		/* Próximo item */
		ppItem = &((*ppItem)->next);
		n--;
	}
}

DLLIST *new_DLLIST_WithItems_fl(size_t n, size_t sz, char *pFile, int nLine) {
	DLLIST *pTmp;
	int i;

	/* Nova dll */
	pTmp = new_DLLIST_fl(pFile, nLine);
	if (pTmp == NULL)
		return pTmp;

	/* Append todos os elementos */
	for (i = 0; i < n; i++) {
		void *item;
		item = malloc_fl(sz, pFile, nLine);
		DLLIST_append_fl(pTmp, item, pFile, nLine);
	}

	/* Remove todos os elementos */
	DLLIST_head(pTmp);
	for (i = 0; i < n; i++)
		DLLIST_remove(pTmp);

	return pTmp;
}

void DLLIST_next(DLLIST *pDllist) {
	if (pDllist->cur != NULL)
		pDllist->cur = pDllist->cur->next;
}

void *DLLIST_prepend_fl(DLLIST *pDllist, void *item, char *pFile, int nLine) {
	DLLIST_ITEM *tmpitem;

	tmpitem = new_DLLIST_ITEM_fl(pDllist, pFile, nLine);
	if (tmpitem == NULL) {
		return NULL;
	}
	tmpitem->item = item;

	DLLIST_prepend_ITEM(pDllist, tmpitem);
	return (tmpitem->item);
}

DLLIST_ITEM *DLLIST_prepend_ITEM(DLLIST *pDllist, DLLIST_ITEM *pDllitem) {

	pDllitem->prev = NULL;
	pDllist->cur = pDllitem;
	if (pDllist->head) {
		pDllitem->next = pDllist->head;
		pDllist->head->prev = pDllitem;
	} else {
		pDllitem->next = NULL;
		pDllist->tail = pDllitem;
	}
	pDllist->head = pDllitem;
	pDllist->count++;

	return (pDllitem);
}

void DLLIST_prev(DLLIST *pDllist) {
	if (pDllist->cur != NULL)
		pDllist->cur = pDllist->cur->prev;
}

void *DLLIST_read(DLLIST *pDllist) {

	if ((pDllist != NULL) && (pDllist->cur != NULL)) {
		return (pDllist->cur->item);
	} else {
		return (NULL);
	}
}

DLLIST_ITEM *DLLIST_read_ITEM(DLLIST *pDllist) {
	return pDllist->cur;
}

void *DLLIST_remove(DLLIST *pDllist) {
	DLLIST_ITEM *pTmp;

	pTmp = DLLIST_remove_ITEM(pDllist, pDllist->cur);
	if (pTmp == NULL) {
		return pTmp;
	}	else {
		return pTmp->item;
	}
}

DLLIST_ITEM *DLLIST_remove_ITEM(DLLIST *pDllist, DLLIST_ITEM *pDllitem) {

	DLLIST_ITEM *pTmp1;
	DLLIST_ITEM *pNew_cur;
	void *pTmpItem;

	pDllist->cur = pDllitem;

	if (pDllist->cur != NULL) {
		pTmp1    = pDllist->cur;
		pNew_cur = pTmp1->next;
		pTmpItem = pTmp1->item;
		if ((pTmp1->prev == NULL) && (pTmp1->next == NULL)) {
			pDllist->head = NULL;
			pDllist->tail = NULL;
			del_DLLIST_ITEM(pDllist, pDllist->cur);
		} else if (pTmp1->prev == NULL) {
			pTmp1 = pTmp1->next;
			pTmp1->prev = NULL;
			pDllist->head = pTmp1;
			del_DLLIST_ITEM(pDllist, pDllist->cur);
		} else if (pTmp1->next == NULL) {
			pTmp1 = pTmp1->prev;
			pTmp1->next = NULL;
			pDllist->tail = pTmp1;
			del_DLLIST_ITEM(pDllist, pDllist->cur);
		} else {
			pTmp1->prev->next = pTmp1->next;
			pTmp1->next->prev = pTmp1->prev;
			del_DLLIST_ITEM(pDllist, pDllist->cur);
		}
		pDllist->cur = pNew_cur;
		pDllist->count--;

		return (pDllitem);
	}

	return (NULL);
}

void DLLIST_sort(DLLIST *pDllist, long(*sortfcn)(void *, void *)) {
  
	DLLIST_ITEM *pTmpItem;
	unsigned long was_a_change;

	if (sortfcn == NULL)
		sortfcn = this_item;

	do {
		was_a_change = 0x0;
		pTmpItem = pDllist->head;

		while (pTmpItem != NULL) {
			if (pTmpItem->next != NULL) {
				if (sortfcn(pTmpItem->item, pTmpItem->next->item) > 0) {
					void *tmpdata;
					tmpdata = pTmpItem->item;
					pTmpItem->item = pTmpItem->next->item;
					pTmpItem->next->item = tmpdata;
					was_a_change++;
				}
			}

			pTmpItem = pTmpItem->next;
		}

	} while (was_a_change);
}

void *DLLIST_tail(DLLIST *pDllist) {
	pDllist->cur = pDllist->tail;
	return DLLIST_read(pDllist);
}

long this_item(void *pItemA, void *pItemB) {
	return (((unsigned long) pItemA) - ((unsigned long) pItemB));
}

/*
 * Duplica uma lista encadeada
 *
 * @param pDllist Ponteiro da lista encadeada a ser duplicada
 * @param bReverse Indica se a lista deve ser duplicada na ordem inversa.
 *
 * @return ponteiro da lista encadeada duplicada.
 */
DLLIST *dup_DLLIST(DLLIST *pDllist, void* (*dup_item)(void *), int bReverse) {

	DLLIST *pdllNew = new_DLLIST();
	void *pItem, *pItemNew;

	DLLIST_head(pDllist);
	while ((pItem = DLLIST_read(pDllist))) {
		pItemNew = dup_item(pItem);
		if (bReverse == 0) {
			DLLIST_append(pdllNew, pItemNew);
		} else {
			DLLIST_prepend(pdllNew, pItemNew);
		}
		DLLIST_next(pDllist);
	}

	return pdllNew;
}
