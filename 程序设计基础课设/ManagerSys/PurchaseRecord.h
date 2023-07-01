#ifndef _PURCHASE_RECORD_H
#define _PURCHASE_RECORD_H
#include "SaleRecord.h"

typedef SaleRecords PurchaseRecords;

//�������.
bool ExportCurDatePurchaseReport(ListContext*pRecordList, const char*szCurDate, const char*szFileName);
//����ĳһ��Ľ���
bool SortCurDatePurchaseRecord(ListContext*pRecordList, int key, int ascending);
//ͨ�������ܽ��Ƚ�.
int CompareByAmount(Node*it, Node*target);

#endif