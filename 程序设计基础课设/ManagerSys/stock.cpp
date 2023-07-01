#include "stdafx.h"
#include "stock.h"


ListContext* ReadStockData(const char*szFileName)
{
	ListContext*pStockList = createlist();
	FILE*fp = fopen(szFileName, "rb");
	if (fp == NULL)
		return pStockList;
	//
	while (true)
	{
		Goods temp = { 0 };
		int nRead = fread(&temp.nID, sizeof(Goods) - ((char*)&temp.nID - (char*)&temp), 1, fp);
		if (nRead <= 0)
			break;

		Goods*pNewGoods = (Goods*)malloc(sizeof(Goods));
		memcpy(pNewGoods, &temp, sizeof(Goods));
		//���뵽����β��.
		insertback(pStockList, (Node*)pNewGoods);
	}
	//
	fclose(fp);
	return pStockList;
}

void WriteStockData(const char*szFileName, ListContext*pStockList)
{
	FILE*fp = fopen(szFileName, "wb");
	if (fp == NULL)
		return ;
	
	for (Node*pIt = pStockList->Head.next; pIt != &pStockList->Head; pIt = pIt->next)
	{
		Goods*pGoods = (Goods*)pIt;
		fwrite(&pGoods->nID, sizeof(Goods) - ((char*)&pGoods->nID - (char*)pGoods), 1, fp);
	}
	//
	fclose(fp);
	return ;
}

//��txt�е����¼,�����ܼ�¼�����ͳɹ�����.
//txt����Ӧ����gb2312 (ANSI)

void ImportFromFile(ListContext*pStockList, const char*szFileName,int*pTotal,int*pSuccess)
{
	*pTotal = 0;
	*pSuccess = 0;
	FILE*fp = fopen(szFileName, "r");
	if (fp)
	{
		//
		while (true)
		{
			Goods goods = { 0 };
			//����ֵ: ���ͣ��ɹ����ض���Ĳ����ĸ���
			int nScanf = fscanf(fp, "%d%s%s%u%lf%lf%lf%lf", &goods.nID, goods.szName, goods.szType, &goods.nUnit,
				&goods.Purchaseprice, &goods.Sellingprice, &goods.Stock, &goods.Sell);
			//
			if (nScanf != 8)
				break;
			(*pTotal)++;
			//�����Ƿ����ظ��ı��.
			Node*pNode = NULL;
			for (pNode = pStockList->Head.next; pNode != &pStockList->Head; pNode = pNode->next)
			{
				if (((Goods*)pNode)->nID == goods.nID)
					break;
			}
			//
			if (pNode == &pStockList->Head)
			{
				//û���ҵ��ظ����.
				(*pSuccess)++;
				Goods* pGoods = (Goods*)malloc(sizeof(Goods));
				memcpy(pGoods, &goods, sizeof(Goods));
				//
				insertback(pStockList, (Node*)pGoods);
			}
		}
		fclose(fp);
	}
}

//�������¼����.
bool ExportStockReport(ListContext*pStockList,const char*szFileName)
{
	FILE*fp = fopen(szFileName, "w");
	if (fp == NULL)
		return false;
	//
	time_t t;
	time(&t);							//UTCʱ��,����ʱ���.
	tm*pLocalTime = localtime(&t);		//ת��Ϊ����ʱ��
	//
	for (int i = 0; i < 73; i++) fputc('*', fp);	fputc('\n', fp);
	//
	char szBuffer[256] = { 0 };
	sprintf(szBuffer, "*\t\t\t�ļ�˵��:����¼����\t\t\t\t*\n");
	fprintf(fp,szBuffer);

	sprintf(szBuffer, "*\t\t\t����ʱ��:%d-%d-%d  %d:%d:%d\t\t\t*\n", pLocalTime->tm_year + 1900
		,pLocalTime->tm_mon + 1,pLocalTime->tm_mday,pLocalTime->tm_hour,pLocalTime->tm_min,pLocalTime->tm_sec);
	fprintf(fp, szBuffer);
	for (int i = 0; i < 73; i++) fputc('*', fp);fputc('\n', fp);
	//
	fprintf(fp, "%-6s%-10s%-10s%-7s%-10s%-10s%-14s%-14s\n", "���", "����", "Ʒ��", "��λ", "����", "�ۼ�", "���", "����");
	for (int i = 0; i < 73; i++) fputc('*', fp); fputc('\n', fp);
	//�������.
	for (Node*pNode = pStockList->Head.next; pNode != &pStockList->Head; pNode = pNode->next)
	{
		Goods*pGoods = (Goods*)pNode;

		fprintf(fp, "%-6d%-10s%-10s%-7s%-10.2lf%-10.2lf%-14.2lf%-14.2lf\n", pGoods->nID, pGoods->szName, pGoods->szType, pGoods->nUnit?"��":"��",
			pGoods->Purchaseprice,pGoods->Sellingprice,pGoods->Stock,pGoods->Sell);
	}
	fclose(fp);
	return true;
}
bool AddStockRecord(ListContext*pStockList, Goods*pGoods)
{
	//�����Ƿ���������Ʒ��ͻ
	Node*pExist = search(pStockList, pStockList->Head.next, CompareById, pGoods);
	//
	if (pExist)
	{
		return false;
	}
	//��Ӽ�¼.
	Goods*pNewGoods = (Goods*)malloc(sizeof(Goods));
	memcpy(pNewGoods, pGoods, sizeof(Goods));
	//
	insertback(pStockList, (Node*)pNewGoods);

	return true;
}

void DeleteStockRecord(ListContext*pStockList, int ID)
{
	Goods Temp;
	Temp.nID = ID;
	Goods*pTarget = (Goods*)search(pStockList, pStockList->Head.next, CompareById, &Temp);
	if (pTarget)
	{
		delnode(pStockList, (Node*)pTarget);
	}
}

bool ModifyStockInfo(ListContext* pStockList, int ID, Goods*pNewInfo)
{
	Goods Temp;
	Temp.nID = ID;
	Goods*pTarget = (Goods*)search(pStockList, pStockList->Head.next, CompareById, &Temp);
	if (pTarget)
	{
		strcpy(pTarget->szName, pNewInfo->szName);
		strcpy(pTarget->szType, pNewInfo->szType);
		//
		pTarget->nUnit = pNewInfo->nUnit;
		pTarget->Sellingprice = pNewInfo->Sellingprice;
		pTarget->Purchaseprice = pNewInfo->Purchaseprice;

		return true;
	}
	return false;
}

//��������Ϣ.
bool SortStock(ListContext* pStockList, int key, int ascending)
{
	switch (key)
	{
	case 0:
		sort(pStockList, CompareById, ascending);
		break;
	case 1:
		sort(pStockList, CompareByName, ascending);
		break;
	case 2:
		sort(pStockList, CompareByType, ascending);
		break;
	case 3:
		sort(pStockList, CompareByPurchaseprice, ascending);
		break;
	case 4:
		sort(pStockList, CompareBySellprice, ascending);
		break;
	case 5:
		sort(pStockList, CompareByStock, ascending);
		break;
	case 6:
		sort(pStockList, CompareBySell, ascending);
		break;
	default:
		return false;
	}
	return true;
}

//typedef int(*cmpfunc)(Node* it, Node* target);

int CompareById(Node*it, Node*target)
{
	Goods*pGoods = (Goods*)it;
	Goods*pTarget = (Goods*)target;

	return pGoods->nID - pTarget->nID;
}

int CompareByName(Node*it, Node*target)
{
	Goods*pGoods = (Goods*)it;
	Goods*pTarget = (Goods*)target;

	return strcmp(pGoods->szName,pTarget->szName);
}

int CompareByType(Node*it, Node*target)
{
	Goods*pGoods = (Goods*)it;
	Goods*pTarget = (Goods*)target;
	return strcmp(pGoods->szType, pTarget->szType);
}

int CompareByPurchaseprice(Node*it, Node*target)
{
	Goods*pGoods = (Goods*)it;
	Goods*pTarget = (Goods*)target;
	int Result = pGoods->Purchaseprice > pTarget->Purchaseprice ? 1 : -1;
	return Result;
}
int CompareBySellprice(Node*it, Node*target)
{
	Goods*pGoods = (Goods*)it;
	Goods*pTarget = (Goods*)target;

	int Result = pGoods->Sellingprice > pTarget->Sellingprice ? 1 : -1;
	return Result;
}

int CompareByStock(Node*it, Node*target)
{
	Goods*pGoods = (Goods*)it;
	Goods*pTarget = (Goods*)target;
	int Result = pGoods->Stock > pTarget->Stock ? 1 : -1;
	return Result;
}
int CompareBySell(Node*it, Node*target)
{
	Goods*pGoods = (Goods*)it;
	Goods*pTarget = (Goods*)target;
	int Result = pGoods->Sell > pTarget->Sell ? 1 : -1;
	return Result;
}