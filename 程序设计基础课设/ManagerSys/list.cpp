#include "stdafx.h"
#include <stdlib.h>
#include "list.h"


pListContext createlist()
{
	pListContext plist = (pListContext)malloc(sizeof(ListContext));
	plist->Len = 0;

	plist->Head.prev = &plist->Head;
	plist->Head.next = &plist->Head;
	return plist;
}


void insertback(pListContext plist, Node*pNewNode)
{
	Node*pHead = &plist->Head;
	Node*pTail = pHead->prev;

	pTail->next = pNewNode;
	pNewNode->prev = pTail;

	pNewNode->next = pHead;
	pHead->prev = pNewNode;

	plist->Len++;
}

void insertfront(pListContext plist, Node*pNewNode)
{
	Node*pHead = &plist->Head;
	Node*pNext = pHead->next;

	pNext->prev = pNewNode;
	pNewNode->next = pNext;

	pHead->next = pNewNode;
	pNewNode->prev = pHead;

	plist->Len++;
}

void delnode(pListContext plist, Node*pNode)
{
	if (plist->Len == 0)
		return;//应该有错误
	pNode->next->prev = pNode->prev;
	pNode->prev->next = pNode->next;
	free(pNode);
	plist->Len--;
}

void dellist(pListContext plist)
{
	Node*pHead = &(plist->Head);
	while (pHead->next != pHead)
		delnode(plist, pHead->next);
	free(plist);
}

void debug_print_list(pListContext plist)
{
	printf("\n==================================================================\n");
	printf("list len:%d\n", plist->Len);
	for (Node*p = plist->Head.next; p != &(plist->Head); p = p->next)
	{
		//printf("%d ", p->data);
	}
	printf("\n==================================================================\n");
}


//把链表2合并到链表1里面
void merge(pListContext plist1, pListContext plist2, cmpfunc cmp, int ascending)
{
	if (plist1 == plist2)
		return;             //不允许这样做
	Node*pIt = plist2->Head.next;
	Node*pInsertPos = plist1->Head.next;

	while (pIt != &(plist2->Head))
	{
		//把pIt从链表里面摘下来
		pIt->prev->next = pIt->next;
		pIt->next->prev = pIt->prev;

		Node*pInsertNode = pIt;
		pIt = pIt->next;

		plist2->Len--;
		plist1->Len++;

		//把pInsertNode入到适当的位置
		int result = cmp(pInsertNode, pInsertPos);
		int ok = ascending ? (result < 0) : (result>0);
		while (pInsertPos != &(plist1->Head) && ok)
		{
			//下一个位置
			pInsertPos = pInsertPos->next;
			//
			result = cmp(pInsertNode, pInsertPos);
			ok = ascending ? (result < 0) : (result>0);
		}
		//把要插入的节点加到list1里面,放到pInsertPos前面
		pInsertNode->next = pInsertPos;
		pInsertNode->prev = pInsertPos->prev;

		pInsertNode->next->prev = pInsertNode;
		pInsertNode->prev->next = pInsertNode;
		//下一次插入直接从这里开始就行,因为list2是有序链表
		pInsertPos = pInsertNode;
		//
		//debug_print_list(plist1);
		//debug_print_list(plist2);
	}
}

Node* removehead(pListContext plist)
{
	Node* result = plist->Head.next;

	plist->Head.next = result->next;
	plist->Head.next->prev = &plist->Head;
	plist->Len--;
	return result;
}

void swap(pListContext plist1, pListContext plist2)
{
	ListContext temp = { 0 };
	memcpy(&temp, plist1, sizeof(ListContext));
	memcpy(plist1, plist2, sizeof(ListContext));
	memcpy(plist2, &temp, sizeof(ListContext));
	if (plist1->Len == 0)
		plist1->Head.next = plist1->Head.prev = &plist1->Head;
	else
	{
		plist1->Head.next->prev = &plist1->Head;
		plist1->Head.prev->next = &plist1->Head;
	}
	if (plist2->Len == 0)
		plist2->Head.next = plist2->Head.prev = &plist2->Head;
	else
	{
		plist2->Head.next->prev = &plist2->Head;
		plist2->Head.prev->next = &plist2->Head;
	}
}

#define MAX_BIN 16
//STL list sort

//排序原理:
/*
	准备一个Temp list
	准备16个 bin.每个bin都是一个list

开始排序:
	loop:
		从 待排序的 list里面取出一个元素放到Templist内 (TempList一定是空链表)

		遍历bins,把bins内的有序链表合并到Templist内,直到遇到空位置或者合并完所有

		把Templist放到bins的空位置(最后一个或者遍历遇到的第一个空位置)

		goto loop;

	待排序的list已经空了, 只剩下Bins里面的有序链表
	
	合并bins里面的有序链表到下一个

	交换bins最后一个链表和待排序的list
	排序完成
*/

void sort(pListContext plist, cmpfunc cmp, int ascending)
{
	//alloc bins:
	pListContext Bin[MAX_BIN] = { 0 };
	for (int i = 0; i<MAX_BIN; i++)
	{
		Bin[i] = createlist();
	}
	//
	pListContext pTempList = createlist();
	while (plist->Len)
	{
		//================================
		Node*pNode = removehead(plist);
		insertback(pTempList, pNode);
		int i = 0;
		for (; i<MAX_BIN && Bin[i]->Len; i++)
		{
			merge(pTempList, Bin[i], cmp, ascending);
		}
		//遍历合并,
		if (i<MAX_BIN)
			swap(Bin[i], pTempList);
		else
			swap(Bin[MAX_BIN - 1], pTempList);
	}

	//合并bin到最后一个
	for (int i = 1; i<MAX_BIN; i++)
	{
		merge(Bin[i], Bin[i - 1], cmp,ascending);
	}
	//把最后一个和plist交换
	swap(plist, Bin[MAX_BIN - 1]);
	//del bins
	for (int i = 0; i<MAX_BIN; i++)
	{
		dellist(Bin[i]);
	}
	dellist(pTempList);
}


Node* search(pListContext plist, Node*pStart, cmpfunc compare, void* target)
{
	for (Node*pNode = pStart; pNode != &plist->Head; pNode = pNode->next)
	{
		if (compare((Node*)target, pNode) == 0)
		{
			return pNode;
		}
	}
	return NULL;
}