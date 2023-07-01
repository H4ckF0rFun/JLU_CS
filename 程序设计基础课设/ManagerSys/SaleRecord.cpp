#include "stdafx.h"
#include "SaleRecord.h"
/*
	
*/

ListContext* ReadRecord(const char*szFileName)
{
	ListContext*pRecords = createlist();
	FILE*fp = fopen(szFileName, "rb");
	if (!fp)
		return pRecords;

	while (true)
	{
		Record temp = { 0 };
		int nRead = fread(&temp.ID,sizeof(Record) - ((char*)&temp.ID - (char*)&temp) , 1, fp);
		if (nRead <= 0)
			break;
		//插入到链表中
		Record*pNewRecord = (Record*)malloc(sizeof(Record));
		memcpy(pNewRecord, &temp, sizeof(Record));

		insertback(pRecords, (Node*)pNewRecord);
	}
	fclose(fp);
	return pRecords;
}

void WriteRecord(const char*szFileName, ListContext*pRecordList)
{
	FILE*fp = fopen(szFileName, "wb");
	if (fp)
	{
		//写当天销售记录.
		for (Node*it = pRecordList->Head.next; it != &pRecordList->Head; it = it->next)
		{
			Record*pRecord = (Record*)it;
			fwrite(&pRecord->ID, sizeof(Record) - ((char*)&pRecord->ID - (char*)pRecord), 1, fp);
		}
		fclose(fp);
	}
}

//从已经加载的链表中查找对应日期的销售记录.

SaleRecords*FindRecords(ListContext*pSaleRecords,const char*szDate)
{
	for (Node*it = pSaleRecords->Head.next; it != &pSaleRecords->Head; it = it->next)
	{
		SaleRecords*pRecord = (SaleRecords*)it;
		if (!strcmp(pRecord->szDate, szDate))
		{
			return pRecord;
		}
	}
	return NULL;
}

//获取某一天对应的销售记录.
SaleRecords* GetRecord(const char*szDate,ListContext*pSaleRecords,const char*path)
{
	//先看看是否已经加载这一天的销售记录
	SaleRecords*pSaleRecord = FindRecords(pSaleRecords, szDate);
	if (pSaleRecord == NULL)
	{
		//没有找到的话就尝试从文件中加载.
		char szFileName[256] = { 0 };
		sprintf(szFileName, "%s\\%s", path,szDate);
		//没有找到,从文件中加载.
		ListContext*pRecord = ReadRecord(szFileName);

		pSaleRecord = (SaleRecords*)malloc(sizeof(SaleRecords));

		pSaleRecord->m_pRecordList = pRecord;
		strcpy(pSaleRecord->szDate, szDate);
		//插入到链表中
		insertback(pSaleRecords, (Node*)pSaleRecord);
	}
	return pSaleRecord;
}

//添加销售和进货记录.记录
void AddSaleRecord(const char*szDate, ListContext*pSaleRecords,Record*pRecord,const char*Path)
{
	//找到指定日期的销售记录链表
	SaleRecords*pSaleRecord = GetRecord(szDate, pSaleRecords,Path);
	
	Record*pNewRecord = (Record*)malloc(sizeof(Record));
	memcpy(pNewRecord, pRecord,sizeof(Record));

	//加入到链表末尾.
	insertback(pSaleRecord->m_pRecordList, (Node*)pNewRecord);
}

//排序某一天的销售记录
bool SortCurDateSaleRecord(ListContext*pRecordList, int key, int ascending)
{
	switch (key)
	{
	case 0:
		sort(pRecordList, CompareByID2, ascending);
		break;
	case 1:
		sort(pRecordList, CompareByName2, ascending);
		break;
	case 2:
		sort(pRecordList, CompareByType2, ascending);
		break;
	case 3:
		sort(pRecordList, CompareBySellCount, ascending);
		break;
	case 4:
		sort(pRecordList, CompareByPurchasingprice, ascending);
		break;
	case 5:
		sort(pRecordList, CompareBySellingprice, ascending);
		break;
	case 6:
		sort(pRecordList, CompareByProfit, ascending);
		break;
	case 7:
		sort(pRecordList, CompareByTime, ascending);
		break;
	default:
		false;
	}
	return true;
}
//
void DeleteCurDateRecord(ListContext*pRecordList, char* szTime)
{
	Record temp = { 0 };
	strcpy(temp.szTime, szTime);

	Node*pRecord = search(pRecordList, pRecordList->Head.next, CompareByTime, &temp);
	if (pRecord)
	{
		delnode(pRecordList, pRecord);
	}
}

void DeleteCurDateAllRecord(ListContext*pRecordList)
{
	//删除所有节点
	while (pRecordList->Len > 0)
	{
		delnode(pRecordList,pRecordList->Head.next);
	}
	//不要删除链表
}

//输出报表.
bool ExportCurDateReport(ListContext*pRecordList, const char*szCurDate,const char*szFileName)
{
	FILE*fp = fopen(szFileName, "w");
	if (fp == NULL)
		return false;
	//
	time_t t;
	time(&t);							//UTC时间,返回时间戳.
	tm*pLocalTime = localtime(&t);		//转换为当地时间
	
	for (int i = 0; i < 105; i++) fputc('*', fp);	fputc('\n', fp);
	//
	char szBuffer[256] = { 0 };
	sprintf(szBuffer, "*\t\t\t\t\t文件说明:销售记录报表\t\t\t\t\t\t*\n");
	fprintf(fp, szBuffer);

	sprintf(szBuffer, "*\t\t\t\t\t记录日期:%s\t\t\t\t\t\t*\n",szCurDate);
	fprintf(fp, szBuffer);

	sprintf(szBuffer, "*\t\t\t\t\t生成日期:%d-%d-%d  %d:%d:%d\t\t\t\t\t*\n", pLocalTime->tm_year + 1900
		, pLocalTime->tm_mon + 1, pLocalTime->tm_mday, pLocalTime->tm_hour, pLocalTime->tm_min, pLocalTime->tm_sec);
	fprintf(fp, szBuffer);
	for (int i = 0; i < 105; i++) fputc('*', fp); fputc('\n', fp);
	////
	fprintf(fp, "%-6s%-10s%-10s%-7s%-10s%-10s%-10s%-10s%-14s%-10s%s\n", "编号", "名称", "品种", "单位" ,"数量","进价", "售价","折扣","利润","时间","备注");
	for (int i = 0; i < 105; i++) fputc('*', fp); fputc('\n', fp);
	////输出内容.
	for (Node*pNode = pRecordList->Head.next; pNode != &pRecordList->Head; pNode = pNode->next)
	{
		Record*pRecord = (Record*)pNode;

		fprintf(fp, "%-6d%-10s%-10s%-7s%-10.2lf%-10.2lf%-10.2lf%-10.2lf%-14.2lf%-10s%s\n", pRecord->ID, pRecord->szName, pRecord->szType, pRecord->Unit ? "斤" : "个",
			pRecord->Sell, pRecord->Purchaseingprice, pRecord->Sellingprice, pRecord->m_Rate,
			pRecord->Sell*(pRecord->Sellingprice * pRecord->m_Rate - pRecord->Purchaseingprice),
			pRecord->szTime,pRecord->szComment);
	}
	//
	fclose(fp);
	return true;
}

//比较 回调函数
int CompareByID2(Node*it, Node*target)
{
	Record*pIt = (Record*)it;
	Record*pTarget = (Record*)target;

	return pIt->ID - pTarget->ID;
}

int CompareByName2(Node*it, Node*target)
{
	Record*pIt = (Record*)it;
	Record*pTarget = (Record*)target;

	return strcmp(pIt->szName,pTarget->szName);
}

int CompareByType2(Node*it, Node*target)
{
	Record*pIt = (Record*)it;
	Record*pTarget = (Record*)target;

	return strcmp(pIt->szType, pTarget->szType);
}
int CompareBySellCount(Node*it, Node*target)
{
	Record*pIt = (Record*)it;
	Record*pTarget = (Record*)target;

	int Result = pIt->Sell >
		pTarget->Sell ? 1:-1;
	return Result;
}

int CompareByPurchasingprice(Node*it, Node*target)
{
	Record*pIt = (Record*)it;
	Record*pTarget = (Record*)target;

	int Result = pIt->Purchaseingprice > 
		pTarget->Purchaseingprice? 1: -1;
	return Result;
}
int CompareBySellingprice(Node*it, Node*target)
{
	Record*pIt = (Record*)it;
	Record*pTarget = (Record*)target;

	int Result = pIt->Sellingprice > 
		pTarget->Sellingprice? 1:-1;
	return Result;
}

int CompareByProfit(Node*it, Node*target)
{
	Record*pIt = (Record*)it;
	Record*pTarget = (Record*)target;

	int Result  =  (pIt->Sellingprice - pIt->Purchaseingprice)*pIt->Sell >
		(pTarget->Sellingprice - pTarget->Purchaseingprice)*pTarget->Sell ? 1:-1;
	return Result;
}

int CompareByTime(Node*it, Node*target)
{
	Record*pIt = (Record*)it;
	Record*pTarget = (Record*)target;

	return strcmp(pIt->szTime, pTarget->szTime);
}