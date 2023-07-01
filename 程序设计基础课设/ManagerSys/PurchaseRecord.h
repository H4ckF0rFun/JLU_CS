#ifndef _PURCHASE_RECORD_H
#define _PURCHASE_RECORD_H
#include "SaleRecord.h"

typedef SaleRecords PurchaseRecords;

//输出报表.
bool ExportCurDatePurchaseReport(ListContext*pRecordList, const char*szCurDate, const char*szFileName);
//排序某一天的进货
bool SortCurDatePurchaseRecord(ListContext*pRecordList, int key, int ascending);
//通过进价总金额比较.
int CompareByAmount(Node*it, Node*target);

#endif