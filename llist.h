#ifndef __KEN_LLIST_H__
#define __KEN_LLIST_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <share.h>


#define NEXT 1
#define PREV 2


typedef void (llist_op_t)(void *);
typedef int (llist_cmp_t)(void *, void *);
struct cls_t{
	char name[64];
	int id;
	int age;
	char sex;
	float cn;
	float en;
	float result;
};



//定义双向链表节点
struct node_t{
	void *data;//数据域
	struct node_t *next;//保存下一个节点地址
	struct node_t *prev;//保存上一个节点地址
};

//有头 无序 循环 双向链表
//抽象数据类型
typedef struct llist_t{
	struct node_t head;//头结点
	int size;//数据类型
	int num;//数据长度
}LLIST;


//函数声明
//初始化
LLIST *llist_create(int);
//尾插
void llist_end_insert(LLIST *, void *);
//头插
void llist_first_insert(LLIST *, void *);
//指定位置插入
void llist_index_insert(LLIST *, void *, int);
//================================================
//表示从前到后删除
void llist_front_del(LLIST *handle, void *key, llist_cmp_t *cmp);
//从后到前删除
void llist_end_del(LLIST *handle, void *key, llist_cmp_t *cmp);
//指定位置删除
void llist_index_del(LLIST *handle, int index);
//删除所有匹配信息
void llist_all_del(LLIST *handle, void *key, llist_cmp_t *cmp);
//=================================================
//求数据个数
int llist_num(LLIST *handle);
//表示从前到后查找
void *llist_front_find(LLIST *handle, void *key, llist_cmp_t *cmp);
//从后到前查找
void *llist_end_find(LLIST *handle, void *key, llist_cmp_t *cmp);
//指定位置查找
void *llist_index_find(LLIST *handle, int index);
//查找所有匹配信息
LLIST *llist_all_find(LLIST *handle, void *key, llist_cmp_t *cmp);
//===============================
void llist_sort(LLIST *handle, llist_cmp_t *cmp);

//排序 升序
void llist_ascend_sort(LLIST *handle, llist_cmp_t *cmp);
//降序
void llist_descend_sort(LLIST *handle, llist_cmp_t *cmp);
//存储
void llist_store(LLIST *handle, const char *path);
//加载
LLIST *llist_load(const char *path);

//遍历
void llist_travel(LLIST *, llist_op_t *, int flag);
//销毁
void llist_destroy(LLIST **);

void ls(void *);


















#endif //LLLIST_H
