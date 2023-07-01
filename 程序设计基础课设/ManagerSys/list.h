#ifndef LIST_H
#define LIST_H

/*双向环形链表,Node为节点*/
typedef struct Node
{
	struct Node*prev;
	struct Node*next;
}Node, *pNode;

//保存和链表有关的信息,
typedef struct ListContext
{
	Node    Head;       //
	int     Len;        //长度
}ListContext, *pListContext;

//比较函数应该自己定义,返回正数,0,负数,代表大于,等于,小于
typedef int(*cmpfunc)(Node* it, Node* target);

//Create a empty list
/*
	函数说明	: 该函数用于创建一个空的链表 (ListContext),之后可以在这个ListContext中增加/删除节点
	返回值	: 	返回一个ListContext指针
	备注		:   当该List不在使用时,应该使用dellist删除该ListContext
*/
pListContext createlist();								

/*
	函数说明  : 该函数会free掉链表内的所有节点,并在最后free掉ListContext
	返回值	 : 无返回值
*/

void dellist(pListContext plist);						

/*
	函数说明  : 该函数用于往指定的List的头部插入一个节点
	返回值	 : 无返回值
*/
void insertfront(pListContext plist, Node*pNewNode);

/*
	函数说明  : 该函数用于往指定的List的尾部插入一个节点
	返回值	 : 无返回值
*/
void insertback(pListContext plist, Node*pNewNode);

/*
	函数说明  : 该函数用于删除给定List中的一个节点
	返回值	 : 无返回值
*/
void delnode(pListContext plist, Node*pNode);

/*
	函数说明  : 该函数用于排序给定List中的所有元素,cmp为节点比较的回调函数,当sort内部比较两个节点大小时,会
	通过cmp函数比较,ascending指定了排序的方式，升序或者降序.
	返回值	 : 无返回值
*/
void sort(pListContext plist, cmpfunc cmp,int ascending);

/*
	函数说明  : 该函数从指定的链表中查找出与target指向的元素相同的元素,pStart为开始查找的位置.compare为
		用于比较的回调函数,当search内部比较两个元素时,会调用这个函数
	返回值	 : 若没有找到,返回NULL,否则返回第一个找到的元素
*/
Node* search(pListContext plist, Node*pStart, cmpfunc compare, void* target);

#endif