#ifndef _STOCK_H
#define _STOCK_H

#include "list.h"

/*
	�ýṹ�屣��������Ʒ�йص���Ϣ
*/
typedef struct
{
	Node node;

	unsigned int nID;		//��Ʒ���
	char szName[64];		//����
	char szType[64];		//Ʒ��
	unsigned int nUnit;		//���۵�λ.

	double Purchaseprice;	//����
	double Sellingprice;	//�ۼ�
	double Stock;			//���
	double Sell;			//������

}Goods;


/*
	����˵�� �� �ú����Ӹ������ļ��ж�ȡ����Ʒ��Ϣ,������Ʒ��Ϣ������������,��󷵻�
	����ֵ	�� ������Ʒ��Ϣ������
*/
ListContext* ReadStockData(const char*szFileName);

/*
	����˵�� �� �ú�������������Ʒ��Ϣ�����е�������Ϣд�뵽�������ļ���.
	����ֵ	�� �޷���ֵ
*/
void WriteStockData(const char*szFileName, ListContext*pStockList);
/*
	����˵��	 :  ��ӿ���¼.
	����ֵ	 :  �ɹ�����true,ʧ��(��ų�ͻ)����false;
*/

bool AddStockRecord(ListContext*pStockList, Goods*pGoods);

/*
	����˵��	 :  ɾ��һ����¼(ͨ����Ʒ���)
	����ֵ    :  �޷���ֵ
*/
void DeleteStockRecord(ListContext*pStockList, int ID);

/*
	����˵��   �� �޸Ŀ����Ϣ
	����ֵ     ���ɹ�����true,ʧ�ܷ���false(û���ҵ�.)
*/

bool ModifyStockInfo(ListContext* pStockList, int ID, Goods*pNewInfo);
/*
	����˵��   :  ��������Ϣ
	����:		:key �����ĸ��ؼ�������,ascending ����ʽ,����
	����ֵ	  :�������,true,ʧ��false(��Ч�Ĺؼ���)
*/
bool SortStock(ListContext* pStockList, int key, int ascending);
/*
	����˵�� �� �ú����Ӹ������ļ��е�����Ʒ��Ϣ��ĳ����Ʒ��Ϣ������,
		pTotal�����ܹ����ֵ���Ϣ����,pSuccess����ɹ��������Ϣ���� 
	����ֵ	�� �޷���ֵ
*/
void ImportFromFile(ListContext*pStockList, const char*szFileName, int*pTotal, int*pSuccess);

//�������.
bool ExportStockReport(ListContext*pStockList, const char*szFileName);

/*
	����˵�� : ͨ��Id���Ƚ�������Ʒ�Ļص�����
	����ֵ   : 0���,��0��ͬ
*/
int CompareById(Node*it, Node*target);

/*
	����˵�� : ͨ��Name���Ƚ�������Ʒ�Ļص�����
	����ֵ   : 0���,��0��ͬ
*/
int CompareByName(Node*it, Node*target);

/*
	����˵�� : ͨ����Ʒ�������Ƚ�������Ʒ�Ļص�����
	����ֵ   : 0���,��0��ͬ
*/
int CompareByType(Node*it, Node*target);

/*
	����˵�� : ͨ���������Ƚ�������Ʒ�Ļص�����
	����ֵ   : 0���,��0��ͬ
*/
int CompareByPurchaseprice(Node*it, Node*target);

/*
	����˵�� : ͨ���ۼ����Ƚ�������Ʒ�Ļص�����
	����ֵ   : 0���,��0��ͬ
*/
int CompareBySellprice(Node*it, Node*target);

/*
	����˵�� : ͨ����������Ƚ�������Ʒ�Ļص�����
	����ֵ   : 0���,��0��ͬ
*/
int CompareByStock(Node*it, Node*target);
/*
	����˵�� : ͨ�����������Ƚ�������Ʒ�Ļص�����
	����ֵ   : 0���,��0��ͬ
*/
int CompareBySell(Node*it, Node*target);
#endif