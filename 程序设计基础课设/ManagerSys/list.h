#ifndef LIST_H
#define LIST_H

/*˫��������,NodeΪ�ڵ�*/
typedef struct Node
{
	struct Node*prev;
	struct Node*next;
}Node, *pNode;

//����������йص���Ϣ,
typedef struct ListContext
{
	Node    Head;       //
	int     Len;        //����
}ListContext, *pListContext;

//�ȽϺ���Ӧ���Լ�����,��������,0,����,�������,����,С��
typedef int(*cmpfunc)(Node* it, Node* target);

//Create a empty list
/*
	����˵��	: �ú������ڴ���һ���յ����� (ListContext),֮����������ListContext������/ɾ���ڵ�
	����ֵ	: 	����һ��ListContextָ��
	��ע		:   ����List����ʹ��ʱ,Ӧ��ʹ��dellistɾ����ListContext
*/
pListContext createlist();								

/*
	����˵��  : �ú�����free�������ڵ����нڵ�,�������free��ListContext
	����ֵ	 : �޷���ֵ
*/

void dellist(pListContext plist);						

/*
	����˵��  : �ú���������ָ����List��ͷ������һ���ڵ�
	����ֵ	 : �޷���ֵ
*/
void insertfront(pListContext plist, Node*pNewNode);

/*
	����˵��  : �ú���������ָ����List��β������һ���ڵ�
	����ֵ	 : �޷���ֵ
*/
void insertback(pListContext plist, Node*pNewNode);

/*
	����˵��  : �ú�������ɾ������List�е�һ���ڵ�
	����ֵ	 : �޷���ֵ
*/
void delnode(pListContext plist, Node*pNode);

/*
	����˵��  : �ú��������������List�е�����Ԫ��,cmpΪ�ڵ�ȽϵĻص�����,��sort�ڲ��Ƚ������ڵ��Сʱ,��
	ͨ��cmp�����Ƚ�,ascendingָ��������ķ�ʽ��������߽���.
	����ֵ	 : �޷���ֵ
*/
void sort(pListContext plist, cmpfunc cmp,int ascending);

/*
	����˵��  : �ú�����ָ���������в��ҳ���targetָ���Ԫ����ͬ��Ԫ��,pStartΪ��ʼ���ҵ�λ��.compareΪ
		���ڱȽϵĻص�����,��search�ڲ��Ƚ�����Ԫ��ʱ,������������
	����ֵ	 : ��û���ҵ�,����NULL,���򷵻ص�һ���ҵ���Ԫ��
*/
Node* search(pListContext plist, Node*pStart, cmpfunc compare, void* target);

#endif