#ifndef _STOCK_H
#define _STOCK_H

#include "list.h"

/*
	该结构体保存了与商品有关的信息
*/
typedef struct
{
	Node node;

	unsigned int nID;		//商品编号
	char szName[64];		//名称
	char szType[64];		//品种
	unsigned int nUnit;		//销售单位.

	double Purchaseprice;	//进价
	double Sellingprice;	//售价
	double Stock;			//库存
	double Sell;			//已销售

}Goods;


/*
	函数说明 ： 该函数从给定的文件中读取出商品信息,并将商品信息保存在链表中,最后返回
	返回值	： 包含商品信息的链表
*/
ListContext* ReadStockData(const char*szFileName);

/*
	函数说明 ： 该函数将给定的商品信息链表中的所有信息写入到给定的文件中.
	返回值	： 无返回值
*/
void WriteStockData(const char*szFileName, ListContext*pStockList);
/*
	函数说明	 :  添加库存记录.
	返回值	 :  成功返回true,失败(编号冲突)返回false;
*/

bool AddStockRecord(ListContext*pStockList, Goods*pGoods);

/*
	函数说明	 :  删除一条记录(通过商品编号)
	返回值    :  无返回值
*/
void DeleteStockRecord(ListContext*pStockList, int ID);

/*
	函数说明   ： 修改库存信息
	返回值     ：成功返回true,失败返回false(没有找到.)
*/

bool ModifyStockInfo(ListContext* pStockList, int ID, Goods*pNewInfo);
/*
	函数说明   :  排序库存信息
	参数:		:key 按找哪个关键字排序,ascending 排序方式,升序
	返回值	  :排序完成,true,失败false(无效的关键字)
*/
bool SortStock(ListContext* pStockList, int key, int ascending);
/*
	函数说明 ： 该函数从给定的文件中导入商品信息到某个商品信息链表中,
		pTotal保存总共发现的信息条数,pSuccess保存成功导入的信息条数 
	返回值	： 无返回值
*/
void ImportFromFile(ListContext*pStockList, const char*szFileName, int*pTotal, int*pSuccess);

//输出报表.
bool ExportStockReport(ListContext*pStockList, const char*szFileName);

/*
	函数说明 : 通过Id来比较两个商品的回调函数
	返回值   : 0相等,非0不同
*/
int CompareById(Node*it, Node*target);

/*
	函数说明 : 通过Name来比较两个商品的回调函数
	返回值   : 0相等,非0不同
*/
int CompareByName(Node*it, Node*target);

/*
	函数说明 : 通过商品类型来比较两个商品的回调函数
	返回值   : 0相等,非0不同
*/
int CompareByType(Node*it, Node*target);

/*
	函数说明 : 通过进价来比较两个商品的回调函数
	返回值   : 0相等,非0不同
*/
int CompareByPurchaseprice(Node*it, Node*target);

/*
	函数说明 : 通过售价来比较两个商品的回调函数
	返回值   : 0相等,非0不同
*/
int CompareBySellprice(Node*it, Node*target);

/*
	函数说明 : 通过库存量来比较两个商品的回调函数
	返回值   : 0相等,非0不同
*/
int CompareByStock(Node*it, Node*target);
/*
	函数说明 : 通过销售量来比较两个商品的回调函数
	返回值   : 0相等,非0不同
*/
int CompareBySell(Node*it, Node*target);
#endif