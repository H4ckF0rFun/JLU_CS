#ifndef _USER_H
#define _USER_H
#include "list.h"

/*
	�ýṹ�屣����ĳ���û�����Ϣ,���û��������룩
*/
typedef struct
{
	Node node;
	char szUserName[128];
	char szPassword[128];
}UserData;

/*
	����˵�� : �ú����Ӹ������ļ��ж�ȡ�������û���Ϣ,������Щ��Ϣ���浽������,��󷵻�
	����ֵ   : �û���Ϣ����
*/
ListContext* ReadUserData(const char*szFileName);

/*
	����˵�� : �ú������������û���Ϣ�����������û�����Ϣд�뵽ָ�����ļ���
	����ֵ   : д��ɹ�����true,���򷵻�false
*/
bool WriteUserData(const char*szFileName, ListContext*pList);

/*
	����˵��  : ���ڱȽ������û���Ϣ�ĺ���
	����ֵ	 :  �������û���Ϣ��ͬ,�򷵻�0,���򷵻ط�0
*/
int Compare(Node*it, Node*Target);

//
bool Login(ListContext*pUserList, UserData*pTarget);
#endif