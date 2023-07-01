#ifndef _SALE_RECORD_H
#define _SALE_RECORD_H
#include "list.h"

/*
	该结构体用于保存某一天的日期以及当天的销售记录
*/
typedef struct
{
	Node node;

	char szDate[64];			//日期
	ListContext	*m_pRecordList;	//当天记录.
}SaleRecords;


/*
	用于记录某一件已售商品的信息
*/
typedef struct
{
	Node node;

	unsigned int ID;			//编号
	char szName[128];			//名称
	char szType[128];			//品种
	unsigned int Unit;			//单位
	
	double	Purchaseingprice;	//进价
	double  Sellingprice;		//售价

	double	m_Rate;				//折扣,只在销售记录里面有效.
	
	double	Sell;				//出售数量.,购买数量.
	char	szTime[32];			//时间.

	char	szComment[128];		//备注.
	//
}Record;

/*
	函数说明 : 该函数将某一天的销售记录写入到指定的文件中,pRecordList中保存某一天的销售记录
	返回值   : 无返回值
*/
void WriteRecord(const char*szFileName, ListContext*pRecordList);

/*
	函数说明 : 该函数从指定的文件中读取某一天的销售记录,并将当天的销售信息保存在链表中,最后返回
	返回值   : 包含某一天销售信息的链表
*/
ListContext* ReadRecord(const char*szFileName);


/*
	函数说明  : 该函数从给定的pSaleRecords中，找到指定日期的销售记录，并返回一个SaleRecord指针
	返回值	 : SaleRecords指针,其中SaleRecords中的m_pRecordList为当天的销售信息
*/
SaleRecords* GetRecord(const char*szDate, ListContext*pSaleRecords, const char*path);
//添加某一天的销售记录.

/*
	该函数将某一条记录插入到指定日期的销售记录链表中.
		szDate指明了日期,pRecord为要添加的记录,
	emmmmm这个函数实际中没有用到.
*/
void AddSaleRecord(const char*szDate, ListContext*pSaleRecords, Record*pRecord, const char*Path);


//排序某一天的销售记录

bool SortCurDateSaleRecord(ListContext*pRecordList, int key, int ascending);

//删除某一天中的一条记录
void DeleteCurDateRecord(ListContext*pRecordList, char* szTime);
//删除某一天中的所有记录
void DeleteCurDateAllRecord(ListContext*pRecordList);

//输出报表.
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