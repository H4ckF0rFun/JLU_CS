#ifndef _SALE_RECORD_H
#define _SALE_RECORD_H
#include "list.h"

/*
	�ýṹ�����ڱ���ĳһ��������Լ���������ۼ�¼
*/
typedef struct
{
	Node node;

	char szDate[64];			//����
	ListContext	*m_pRecordList;	//�����¼.
}SaleRecords;


/*
	���ڼ�¼ĳһ��������Ʒ����Ϣ
*/
typedef struct
{
	Node node;

	unsigned int ID;			//���
	char szName[128];			//����
	char szType[128];			//Ʒ��
	unsigned int Unit;			//��λ
	
	double	Purchaseingprice;	//����
	double  Sellingprice;		//�ۼ�

	double	m_Rate;				//�ۿ�,ֻ�����ۼ�¼������Ч.
	
	double	Sell;				//��������.,��������.
	char	szTime[32];			//ʱ��.

	char	szComment[128];		//��ע.
	//
}Record;

/*
	����˵�� : �ú�����ĳһ������ۼ�¼д�뵽ָ�����ļ���,pRecordList�б���ĳһ������ۼ�¼
	����ֵ   : �޷���ֵ
*/
void WriteRecord(const char*szFileName, ListContext*pRecordList);

/*
	����˵�� : �ú�����ָ�����ļ��ж�ȡĳһ������ۼ�¼,���������������Ϣ������������,��󷵻�
	����ֵ   : ����ĳһ��������Ϣ������
*/
ListContext* ReadRecord(const char*szFileName);


/*
	����˵��  : �ú����Ӹ�����pSaleRecords�У��ҵ�ָ�����ڵ����ۼ�¼��������һ��SaleRecordָ��
	����ֵ	 : SaleRecordsָ��,����SaleRecords�е�m_pRecordListΪ�����������Ϣ
*/
SaleRecords* GetRecord(const char*szDate, ListContext*pSaleRecords, const char*path);
//���ĳһ������ۼ�¼.

/*
	�ú�����ĳһ����¼���뵽ָ�����ڵ����ۼ�¼������.
		szDateָ��������,pRecordΪҪ��ӵļ�¼,
	emmmmm�������ʵ����û���õ�.
*/
void AddSaleRecord(const char*szDate, ListContext*pSaleRecords, Record*pRecord, const char*Path);


//����ĳһ������ۼ�¼

bool SortCurDateSaleRecord(ListContext*pRecordList, int key, int ascending);

//ɾ��ĳһ���е�һ����¼
void DeleteCurDateRecord(ListContext*pRecordList, char* szTime);
//ɾ��ĳһ���е����м�¼
void DeleteCurDateAllRecord(ListContext*pRecordList);

//�������.
bool ExportCurDateReport(ListContext*pRecordList, const char*szCurDate, const char*szFileName);

int CompareByID2(Node*it, Node*target);
int CompareByName2(Node*it, Node*target);
int CompareByType2(Node*it, Node*target);
int CompareBySellCount(Node*it, Node*target);
int CompareByPurchasingprice(Node*it, Node*target);
int CompareBySellingprice(Node*it, Node*target);
int CompareByProfit(Node*it, Node*target);

int CompareByTime(Node*it, Node*target);
#endif