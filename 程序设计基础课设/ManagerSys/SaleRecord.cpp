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
		//���뵽������
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
		//д�������ۼ�¼.
		for (Node*it = pRecordList->Head.next; it != &pRecordList->Head; it = it->next)
		{
			Record*pRecord = (Record*)it;
			fwrite(&pRecord->ID, sizeof(Record) - ((char*)&pRecord->ID - (char*)pRecord), 1, fp);
		}
		fclose(fp);
	}
}

//���Ѿ����ص������в��Ҷ�Ӧ���ڵ����ۼ�¼.

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

//��ȡĳһ���Ӧ�����ۼ�¼.
SaleRecords* GetRecord(const char*szDate,ListContext*pSaleRecords,const char*path)
{
	//�ȿ����Ƿ��Ѿ�������һ������ۼ�¼
	SaleRecords*pSaleRecord = FindRecords(pSaleRecords, szDate);
	if (pSaleRecord == NULL)
	{
		//û���ҵ��Ļ��ͳ��Դ��ļ��м���.
		char szFileName[256] = { 0 };
		sprintf(szFileName, "%s\\%s", path,szDate);
		//û���ҵ�,���ļ��м���.
		ListContext*pRecord = ReadRecord(szFileName);

		pSaleRecord = (SaleRecords*)malloc(sizeof(SaleRecords));

		pSaleRecord->m_pRecordList = pRecord;
		strcpy(pSaleRecord->szDate, szDate);
		//���뵽������
		insertback(pSaleRecords, (Node*)pSaleRecord);
	}
	return pSaleRecord;
}

//������ۺͽ�����¼.��¼
void AddSaleRecord(const char*szDate, ListContext*pSaleRecords,Record*pRecord,const char*Path)
{
	//�ҵ�ָ�����ڵ����ۼ�¼����
	SaleRecords*pSaleRecord = GetRecord(szDate, pSaleRecords,Path);
	
	Record*pNewRecord = (Record*)malloc(sizeof(Record));
	memcpy(pNewRecord, pRecord,sizeof(Record));

	//���뵽����ĩβ.
	insertback(pSaleRecord->m_pRecordList, (Node*)pNewRecord);
}

//����ĳһ������ۼ�¼
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
	//ɾ�����нڵ�
	while (pRecordList->Len > 0)
	{
		delnode(pRecordList,pRecordList->Head.next);
	}
	//��Ҫɾ������
}

//�������.
bool ExportCurDateReport(ListContext*pRecordList, const char*szCurDate,const char*szFileName)
{
	FILE*fp = fopen(szFileName, "w");
	if (fp == NULL)
		return false;
	//
	time_t t;
	time(&t);							//UTCʱ��,����ʱ���.
	tm*pLocalTime = localtime(&t);		//ת��Ϊ����ʱ��
	
	for (int i = 0; i < 105; i++) fputc('*', fp);	fputc('\n', fp);
	//
	char szBuffer[256] = { 0 };
	sprintf(szBuffer, "*\t\t\t\t\t�ļ�˵��:���ۼ�¼����\t\t\t\t\t\t*\n");
	fprintf(fp, szBuffer);

	sprintf(szBuffer, "*\t\t\t\t\t��¼����:%s\t\t\t\t\t\t*\n",szCurDate);
	fprintf(fp, szBuffer);

	sprintf(szBuffer, "*\t\t\t\t\t��������:%d-%d-%d  %d:%d:%d\t\t\t\t\t*\n", pLocalTime->tm_year + 1900
		, pLocalTime->tm_mon + 1, pLocalTime->tm_mday, pLocalTime->tm_hour, pLocalTime->tm_min, pLocalTime->tm_sec);
	fprintf(fp, szBuffer);
	for (int i = 0; i < 105; i++) fputc('*', fp); fputc('\n', fp);
	////
	fprintf(fp, "%-6s%-10s%-10s%-7s%-10s%-10s%-10s%-10s%-14s%-10s%s\n", "���", "����", "Ʒ��", "��λ" ,"����","����", "�ۼ�","�ۿ�","����","ʱ��","��ע");
	for (int i = 0; i < 105; i++) fputc('*', fp); fputc('\n', fp);
	////�������.
	for (Node*pNode = pRecordList->Head.next; pNode != &pRecordList->Head; pNode = pNode->next)
	{
		Record*pRecord = (Record*)pNode;

		fprintf(fp, "%-6d%-10s%-10s%-7s%-10.2lf%-10.2lf%-10.2lf%-10.2lf%-14.2lf%-10s%s\n", pRecord->ID, pRecord->szName, pRecord->szType, pRecord->Unit ? "��" : "��",
			pRecord->Sell, pRecord->Purchaseingprice, pRecord->Sellingprice, pRecord->m_Rate,
			pRecord->Sell*(pRecord->Sellingprice * pRecord->m_Rate - pRecord->Purchaseingprice),
			pRecord->szTime,pRecord->szComment);
	}
	//
	fclose(fp);
	return true;
}

//�Ƚ� �ص�����
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