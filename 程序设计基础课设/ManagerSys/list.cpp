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
		return;//Ӧ���д���
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


//������2�ϲ�������1����
void merge(pListContext plist1, pListContext plist2, cmpfunc cmp, int ascending)
{
	if (plist1 == plist2)
		return;             //������������
	Node*pIt = plist2->Head.next;
	Node*pInsertPos = plist1->Head.next;

	while (pIt != &(plist2->Head))
	{
		//��pIt����������ժ����
		pIt->prev->next = pIt->next;
		pIt->next->prev = pIt->prev;

		Node*pInsertNode = pIt;
		pIt = pIt->next;

		plist2->Len--;
		plist1->Len++;

		//��pInsertNode�뵽�ʵ���λ��
		int result = cmp(pInsertNode, pInsertPos);
		int ok = ascending ? (result < 0) : (result>0);
		while (pInsertPos != &(plist1->Head) && ok)
		{
			//��һ��λ��
			pInsertPos = pInsertPos->next;
			//
			result = cmp(pInsertNode, pInsertPos);
			ok = ascending ? (result < 0) : (result>0);
		}
		//��Ҫ����Ľڵ�ӵ�list1����,�ŵ�pInsertPosǰ��
		pInsertNode->next = pInsertPos;
		pInsertNode->prev = pInsertPos->prev;

		pInsertNode->next->prev = pInsertNode;
		pInsertNode->prev->next = pInsertNode;
		//��һ�β���ֱ�Ӵ����￪ʼ����,��Ϊlist2����������
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

//����ԭ��:
/*
	׼��һ��Temp list
	׼��16�� bin.ÿ��bin����һ��list

��ʼ����:
	loop:
		�� ������� list����ȡ��һ��Ԫ�طŵ�Templist�� (TempListһ���ǿ�����)

		����bins,��bins�ڵ���������ϲ���Templist��,ֱ��������λ�û��ߺϲ�������

		��Templist�ŵ�bins�Ŀ�λ��(���һ�����߱��������ĵ�һ����λ��)

		goto loop;

	�������list�Ѿ�����, ֻʣ��Bins�������������
	
	�ϲ�bins���������������һ��

	����bins���һ������ʹ������list
	�������
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
		//�����ϲ�,
		if (i<MAX_BIN)
			swap(Bin[i], pTempList);
		else
			swap(Bin[MAX_BIN - 1], pTempList);
	}

	//�ϲ�bin�����һ��
	for (int i = 1; i<MAX_BIN; i++)
	{
		merge(Bin[i], Bin[i - 1], cmp,ascending);
	}
	//�����һ����plist����
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