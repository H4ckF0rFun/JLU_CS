#ifndef _USER_H
#define _USER_H
#include "list.h"

/*
	该结构体保存了某个用户的信息,（用户名和密码）
*/
typedef struct
{
	Node node;
	char szUserName[128];
	char szPassword[128];
}UserData;

/*
	函数说明 : 该函数从给定的文件中读取出所有用户信息,并将这些信息保存到链表中,最后返回
	返回值   : 用户信息链表
*/
ListContext* ReadUserData(const char*szFileName);

/*
	函数说明 : 该函数将给定的用户信息链表中所有用户的信息写入到指定的文件中
	返回值   : 写入成功返回true,否则返回false
*/
bool WriteUserData(const char*szFileName, ListContext*pList);

/*
	函数说明  : 用于比较两个用户信息的函数
	返回值	 :  若两个用户信息相同,则返回0,否则返回非0
*/
int Compare(Node*it, Node*Target);

//
bool Login(ListContext*pUserList, UserData*pTarget);
#endif