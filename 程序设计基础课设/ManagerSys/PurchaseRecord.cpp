#include "stdafx.h"
#include "PurchaseRecord.h"

//
int CompareByAmount(Node*it, Node*target)
{
	Record*pIt = (Record*)it;
	Record*pTarget = (Record*)target;

	int Result = pIt->Sell*pIt->Purchaseingprice >
		pTarget->Sell*pTarget->Purchaseingprice ? 1:-1;
	return Result;
}

//排序某一天的进货
bool SortCurDatePurchaseRecord(ListContext*pRecordList, int key, int ascending)
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
		sort(pRecordList, CompareByAmount, ascending);
		break;
	case 7:
		sort(pRecordList, CompareByTime, ascending);
		break;
	default:
		return false;
	}
	return true;
}

//输出报表.
bool ExportCurDatePurchaseReport(ListContext*pRecordList, const char*szCurDate, const char*szFileName)
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
	sprintf(szBuffer, "*\t\t\t\t\t文件说明:进货记录报表\t\t\t\t\t\t*\n");
	fprintf(fp, szBuffer);

	sprintf(szBuffer, "*\t\t\t\t\t记录日期:%s\t\t\t\t\t\t*\n", szCurDate);
	fprintf(fp, szBuffer);

	sprintf(szBuffer, "*\t\t\t\t\t生成日期:%d-%d-%d  %d:%d:%d\t\t\t\t\t*\n", pLocalTime->tm_year + 1900
		, pLocalTime->tm_mon + 1, pLocalTime->tm_mday, pLocalTime->tm_hour, pLocalTime->tm_min, pLocalTime->tm_sec);
	fprintf(fp, szBuffer);
	for (int i = 0; i < 105; i++) fputc('*', fp); fputc('\n', fp);
	////
	fprintf(fp, "%-6s%-10s%-10s%-7s%-10s%-10s%-10s%-12s%-10s%s\n", "编号", "名称", "品种", "单位", "数量", "进价", "售价", "金额", "时间", "备注");
	for (int i = 0; i < 105; i++) fputc('*', fp); fputc('\n', fp);
	////输出内容.
	for (Node*pNode = pRecordList->Head.next; pNode != &pRecordList->Head; pNode = pNode->next)
	{
		Record*pRecord = (Record*)pNode;

		fprintf(fp, "%-6d%-10s%-10s%-7s%-10.2lf%-10.2lf%-10.2lf%-12.2lf%-10s%s\n", pRecord->ID, pRecord->szName, pRecord->szType, pRecord->Unit ? "斤" : "个",
			pRecord->Sell, pRecord->Purchaseingprice, pRecord->Sellingprice,
			pRecord->Sell*(pRecord->Purchaseingprice),
			pRecord->szTime, pRecord->szComment);
	}
	//
	fclose(fp);
	return true;
}