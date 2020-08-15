#include "llist.h"

LLIST *llist_create(int size)
{
	LLIST *handle = NULL;

	//申请空间地址
	handle = (LLIST *)malloc(sizeof(LLIST));
	ERRP(NULL == handle, malloc, goto ERR1);

	//循环链表
	handle->head.data = NULL;//数据域 
	handle->head.next = &handle->head;//指向本身
	handle->head.prev = &handle->head;//指向本身

	handle->size = size;//数据类型
	handle->num = 0;//数据长度 

	return handle;
ERR1:
	return NULL;
}

void llist_end_insert(LLIST *handle, void *data)
{
	struct node_t *new = NULL;

	ERRP(data == NULL, option data, goto ERR1);
	
	new = (struct node_t *)malloc(sizeof(struct node_t));
	ERRP(NULL == new, malloc node, goto ERR1);

	new->data = (void *)malloc(handle->size);
	ERRP(NULL == new->data, malloc data, goto ERR2);

	memmove(new->data, data, handle->size);

	
	new->next = &handle->head;
	new->prev = handle->head.prev;
	handle->head.prev->next = new;
	handle->head.prev = new;
	handle->num++;

	return ;
ERR2:
	free(new);
ERR1:
	return ;
}

void llist_first_insert(LLIST *handle, void *data)
{
	struct node_t *new = NULL;

	ERRP(data == NULL, option data, goto ERR1);
	
	new = (struct node_t *)malloc(sizeof(struct node_t));
	ERRP(NULL == new, malloc node, goto ERR1);

	new->data = (void *)malloc(handle->size);
	ERRP(NULL == new->data, malloc data, goto ERR2);

	memmove(new->data, data, handle->size);
	
	new->next = handle->head.next;
	new->prev = &handle->head;
	handle->head.next->prev = new;
	handle->head.next = new;
	handle->num++;

	return ;
ERR2:
	free(new);
ERR1:
	return ;
}

void llist_index_insert(LLIST *handle, void *data, int index)
{
	struct node_t *tail = &handle->head;
	
	struct node_t *new = NULL;

	ERRP(data == NULL, option data, goto ERR1);
	ERRP(index < 0 || index > handle->num, option index, goto ERR1);

	while(index--)
	{
		tail = tail->next;
	}
	
	new = (struct node_t *)malloc(sizeof(struct node_t));
	ERRP(NULL == new, malloc node, goto ERR1);

	new->data = (void *)malloc(handle->size);
	ERRP(NULL == new->data, malloc data, goto ERR2);

	memmove(new->data, data, handle->size);
	
	new->next = tail->next;
	new->prev = tail;
	tail->next->prev = new;
	tail->next = new;
	handle->num++;
	
	return ;
ERR2:
	free(new);
ERR1:
	return ;
}

int llist_num(LLIST *handle)
{
	return handle->num;
}

//删除
void llist_front_del(LLIST *handle, void *key, llist_cmp_t *cmp)
{
	struct node_t *tail = NULL;

	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (cmp(key, tail->data) == 0)
		{
			tail->next->prev = tail->prev;
			tail->prev->next = tail->next;
			free(tail->data);
			free(tail);
			handle->num--;

			return ;
		}
	}
	return ;
}

void llist_end_del(LLIST *handle, void *key, llist_cmp_t *cmp)
{
	struct node_t *tail = NULL;

	for (tail = handle->head.prev; tail != &handle->head; tail = tail->prev)
	{
		if (cmp(key, tail->data) == 0)
		{
			tail->next->prev = tail->prev;
			tail->prev->next = tail->next;
			free(tail->data);
			free(tail);
			handle->num--;

			return ;
		}
	}
	return ;

}

void llist_index_del(LLIST *handle, int index)
{
	
	struct node_t *tail = handle->head.next;
	ERRP(index < 0 || index >= handle->num, option index, goto ERR1);

	while(index--)
	{
		tail = tail->next;
	}
	if (tail != NULL)
	{
		tail->next->prev = tail->prev;
		tail->prev->next = tail->next;
		free(tail->data);
		free(tail);
		tail = NULL;
		handle->num--;
		return ;
	}
	return ;
ERR1:
	return ;
}

void llist_all_del(LLIST *handle, void *key, llist_cmp_t *cmp)
{

	struct node_t *tail = NULL, *save = NULL;

	for (tail = handle->head.next; tail != &handle->head; tail = save)
	{
		save = tail->next;
		if (cmp(key, tail->data) == 0)
		{
			tail->next->prev = tail->prev;
			tail->prev->next = tail->next;
			free(tail->data);
			free(tail);
			handle->num--;
		}
	}
	return ;
}

//===========================================
//查找
void *llist_front_find(LLIST *handle, void *key, llist_cmp_t *cmp)
{
	struct node_t *tail = NULL;

	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (cmp(key, tail->data) == 0)
		{
			return tail->data;
		}
	}
	return NULL;

}
void *llist_end_find(LLIST *handle, void *key, llist_cmp_t *cmp)
{
	struct node_t *tail = NULL;

	for (tail = handle->head.prev; tail != &handle->head; tail = tail->prev)
	{
		if (cmp(key, tail->data) == 0)
		{
			return tail->data;
		}
	}
	return NULL;

}
void *llist_index_find(LLIST *handle, int index)
{
	struct node_t *tail = handle->head.next;
	ERRP(index < 0 || index >= handle->num, option index, goto ERR1);

	while(index--)
	{
		tail = tail->next;
	}

	return tail->data;
ERR1:
	return NULL;
}

LLIST *llist_all_find(LLIST *handle, void *key, llist_cmp_t *cmp)
{
	LLIST *ind = NULL;
	struct node_t *tail = NULL;
	
	ind = llist_create(handle->size);
	ERRP(NULL == ind, llist_create, goto ERR1);


	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (cmp(key, tail->data) == 0)
		{
			llist_end_insert(ind, tail->data);
		}
	}
	
	return ind;
ERR1:
	return NULL;

}


void llist_travel(LLIST *handle, llist_op_t *op, int flag)
{
	struct node_t *tail = NULL;
	
	if (flag == NEXT)
	{
		for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
		{
			op(tail->data);
		}
	}
	else if (flag == PREV)
	{
		for (tail = handle->head.prev; tail != &handle->head; tail = tail->prev)
		{
			op(tail->data);
		}
	}
}

void llist_destroy(LLIST **handle)
{
	LLIST *h = *handle;
	struct node_t *tail = NULL, *save = NULL;

	for (tail = h->head.next; tail != &h->head; tail = save)
	{
		save = tail->next;
		free(tail->data);
		free(tail);
	}
	
	free(*handle);
}
//升序
void llist_sort(LLIST *handle, llist_cmp_t *cmp)
{
	struct node_t *val1 = NULL, *val2 = NULL;
	void *tmp = NULL;
	struct node_t *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8;
	struct node_t *save = NULL;//用于保存最小值

	for (val1 = handle->head.next; val1->next != &handle->head; val1 = t7)
	{
		t7 = val1->next;
		save = val1;
		printf("**********************\n");
		llist_travel(handle, ls, NEXT);
		printf("**********************\n");
		getchar();
		for (val2 = val1->next; val2 != &handle->head; val2 = t8)
		{
			t8 = val2->next;
			if (cmp(save->data, val2->data) > 0)
			{
				save = val2;
			}
		}
		printf("save : %d\n", ((struct cls_t*)save->data)->id);
			t1 = val1->prev;
			t2 = val1->next;
			t3 = save->prev;
			t4 = save->next;
			t5 = val1;
			t6 = save;

			t4->prev = t5;
			t3->next = t5;
			save->next = NULL;
			save->prev = NULL;

			t1->next = t6;
			t2->prev = t6;
			val1->next = NULL;
			val1->prev = NULL;

			save->next = t2;
			save->prev = t1;

			val1->next = t4;
			val1->prev = t3;

	}
}

//升序
void llist_ascend_sort(LLIST *handle, llist_cmp_t *cmp)
{
	struct node_t *val1 = NULL, *val2 = NULL;
	void *tmp = NULL;

	for (val1 = handle->head.next; val1->next != &handle->head; val1 = val1->next)
	{
		for (val2 = val1->next; val2 != &handle->head; val2 = val2->next)
		{
			if (cmp(val1->data, val2->data) > 0)
			{
				tmp = val1->data;
				val1->data = val2->data;
				val2->data = tmp;
			}
		}
	}
}

//降序
void llist_descend_sort(LLIST *handle, llist_cmp_t *cmp)
{
	struct node_t *val1 = NULL, *val2 = NULL;
	void *tmp = NULL;

	tmp = (void *)malloc(handle->size);
	ERRP(NULL == tmp, malloc, goto ERR1);

	for (val1 = handle->head.next; val1->next != &handle->head; val1 = val1->next)
	{
		for (val2 = val1->next; val2 != &handle->head; val2 = val2->next)
		{
			if (cmp(val1->data, val2->data) < 0)
			{
				memcpy(tmp, val1->data, handle->size);
				memcpy(val1->data, val2->data, handle->size);
				memcpy(val2->data, tmp, handle->size);
			}
		}
	}
	free(tmp);
	return ;
ERR1:
	return ;
}
//存储
void llist_store(LLIST *handle, const char *path)
{
	FILE *fp = NULL;
	struct node_t *tail = NULL;

	fp = fopen(path, "w");
	ERRP(NULL == fp, fopen, goto ERR1);

	//size
	ERRP(fwrite(&handle->size, sizeof(handle->size), 1, fp) != 1, fwrite size, goto ERR2);

	//num
	ERRP(fwrite(&handle->num, sizeof(handle->num), 1, fp) != 1, fwrite num, goto ERR2);

	//data
	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		ERRP(fwrite(tail->data, handle->size, 1, fp) != 1, fwrite data, goto ERR2);
	}

	fclose(fp);
	return ;
ERR2:
	fclose(fp);
ERR1:
	return ;
}
//加载
LLIST *llist_load(const char *path)
{
	LLIST *handle = NULL;
	FILE *fp = NULL;
	int size, num;
	int i;
	void *tmp = NULL;

	//打开文件
	ERRP((fp = fopen(path, "r")) == NULL, fopen, goto ERR1);

	//size
	ERRP(fread(&size, sizeof(size), 1, fp) != 1, fread size, goto ERR2);

	//num
	ERRP(fread(&num, sizeof(num), 1, fp) != 1, fread num, goto ERR2);

	//init => handle
	ERRP((handle = llist_create(size)) == NULL, llist_create, goto ERR2);

	//tmp 临时存储数据空间
	ERRP((tmp = (void *)malloc(size)) == NULL, malloc tmp, goto ERR3);
	
	//data
	for (i = 0; i < num; i++)
	{
		ERRP(fread(tmp, size, 1, fp) != 1, fread data, goto ERR4);	
		llist_end_insert(handle, tmp);
	}

	free(tmp);
	fclose(fp);
	return handle;

ERR4:
	free(tmp);
ERR3:
	free(handle);
ERR2:
	fclose(fp);
ERR1:
	return NULL;
}














