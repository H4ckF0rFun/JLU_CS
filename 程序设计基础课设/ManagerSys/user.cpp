#include "stdafx.h"
#include "list.h"
#include "user.h"
#include "stdio.h"

//读取用户账号密码信息
ListContext* ReadUserData(const char*szFileName)
{
	ListContext*pList = createlist();

	FILE*fp = fopen(szFileName, "rb");
	if (fp == NULL)
		return pList;

	while (1)
	{
		UserData Temp;
		//fread返回读取成功的元素个数
		int nRead = fread(Temp.szUserName, sizeof(UserData) - sizeof(Node), 1, fp);
		if (nRead <= 0)
			break;
		//添加到链表.
		UserData*pUserData = (UserData*)malloc(sizeof(UserData));
		memcpy(pUserData->szUserName, Temp.szUserName, sizeof(UserData) - sizeof(Node));

		insertback(pList, (Node*)pUserData);
	}
	fclose(fp);
	return pList;
}

//保存用户账号密码信息
bool WriteUserData(const char*szFileName,ListContext*pList)
{
	FILE*fp = fopen(szFileName, "wb");
	if (fp == NULL)
		return false;
	//遍历链表写文件
	for (Node*pIt = pList->Head.next; pIt != &pList->Head; pIt = pIt->next)
	{
		UserData*pUserData = (UserData*)pIt;
		fwrite(pUserData->szUserName, sizeof(UserData) - sizeof(Node), 1, fp);
	}
	fclose(fp);
	return true;
}

//typedef int(*cmpfunc)(Node* it, Node* target);

int Compare(Node*it, Node*Target)
{
	UserData*pIt = (UserData*)it;
	UserData*pTarget = (UserData*)Target;
	//
	return strcmp(pIt->szUserName, pTarget->szUserName);
}

//
bool Login(ListContext*pUserList,UserData*pTarget)
{
	char szPassword[0x1000] = "123456789";
	UserData*pUserData = (UserData*)search(pUserList, pUserList->Head.next, Compare, pTarget);
	if (pUserData)
	{
		strcpy(szPassword, pUserData->szPassword);
	}
	//没有找到用户且不是管理员.
	if (pUserData == NULL && strcmp(pTarget->szUserName, "admin"))
	{
		return false;
	}
	return (!strcmp(szPassword, pTarget->szPassword));
}