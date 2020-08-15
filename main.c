#include "llist.h"


#define MAX 10

/*
 *struct cls_t{
 *    char name[64];
 *    int id;
 *    int age;
 *    char sex;
 *    float cn;
 *    float en;
 *    float result;
 *};
 */

int cmp_name(void *d1, void *d2)
{
	return strcmp((char *)d1, ((struct cls_t *)d2)->name);
}
int sort_name(void *d1, void *d2)
{
	return strcmp(((struct cls_t *)d1)->name, ((struct cls_t *)d2)->name);
}

int cmp_id(void *d1, void *d2)
{
	return *(int *)d1 - ((struct cls_t *)d2)->id;
}
int sort_id(void *d1, void *d2)
{
	return ((struct cls_t *)d1)->id - ((struct cls_t *)d2)->id;
}

int cmp_age(void *d1, void *d2)
{
	return *(int *)d1 - ((struct cls_t *)d2)->age;
}
int sort_age(void *d1, void *d2)
{
	return ((struct cls_t *)d1)->age - ((struct cls_t *)d2)->age;
}

int cmp_sex(void *d1, void *d2)
{
	return *(char *)d1 - ((struct cls_t *)d2)->sex;
}
int sort_sex(void *d1, void *d2)
{
	return ((struct cls_t *)d1)->sex - ((struct cls_t *)d2)->sex;
}

int cmp_cn(void *d1, void *d2)
{
	float ret;
	ret = *(float *)d1 - ((struct cls_t *)d2)->cn;


	if (ret < 0.005 && ret > -0.005)
		return 0;
	else if (ret > 0.005)
		return 1;
	else if (ret < -0.005)
		return -1;
}
int sort_cn(void *d1, void *d2)
{
	float ret;
	ret = ((struct cls_t *)d1)->cn - ((struct cls_t *)d2)->cn;

	if (ret < 0.005 && ret > -0.005)
		return 0;
	else if (ret > 0.005)
		return 1;
	else if (ret < -0.005)
		return -1;
}


int cmp_result(void *d1, void *d2)
{
	float ret;
	ret = *(float *)d1 - ((struct cls_t *)d2)->result;

	if (ret < 0.005 && ret > -0.005)
		return 0;
	else if (ret > 0.005)
		return 1;
	else if (ret < -0.005)
		return -1;
}
int sort_result(void *d1, void *d2)
{
	float ret;
	ret = ((struct cls_t *)d1)->result - ((struct cls_t *)d2)->result;

	if (ret < 0.005 && ret > -0.005)
		return 0;
	else if (ret > 0.005)
		return 1;
	else if (ret < -0.005)
		return -1;
}

void ls(void *data)
{
	struct cls_t *cls = (struct cls_t *)data;

	printf("name : %6s | id : %d | age : %d | sex : %c | cn : %.2f | en : %.2f | result : %.2f\n", cls->name, cls->id, cls->age, cls->sex, cls->cn, cls->en, cls->result);
}
char *china[11] = {"赵", "钱", "孙", "李", "周", "吴", "郑", "王", "东方", "诸葛", "欧阳"};


int main(int argc, char *argv[])
{
	int i;
	struct cls_t cls, stu = {"tom", 121107, 20, 'M', 88.88, 99.99, 88.88 + 99.99};
	LLIST *handle = NULL;
	int index;
	char name[64];
	int age;

	if (argc == 2)
	{
		printf("load : \n");
		handle = llist_load("./stu.db");
		llist_travel(handle, ls, NEXT);
		return 0;
	}


	//初始化
	handle = llist_create(sizeof(struct cls_t));
	ERRP(NULL == handle, llist_create, goto ERR1);

	for (i = 0; i < MAX; i++)
	{
		snprintf(cls.name, sizeof(cls.name), "stu_%c%c", rand() % 26 + 'A', rand() % 26 + 'a');
		cls.id = rand() % 80 + 20;
		cls.age = rand() % 3 + 18;
		cls.sex = "MF"[rand() % 2];
		cls.cn = rand() / (double)(RAND_MAX) * 30 + 70;
		cls.en = rand() / (double)(RAND_MAX) * 20 + 80;
		cls.result = cls.cn + cls.en;

		//添加数据到链表的结尾
		/*llist_end_insert(handle, &cls);*/
		llist_first_insert(handle, &cls);

	}

	//遍历
	
	llist_travel(handle, ls, NEXT);
	printf("==============\n");
	llist_sort(handle, sort_id);
	llist_store(handle, "./stu.db");
	llist_travel(handle, ls, NEXT);
    /*
	 *printf("==============\n");
	 *llist_travel(handle, ls, PREV);
     */
	/*llist_travel(handle, ls, PREV);*/
	printf("num : %d\n", llist_num(handle));

	/*GETLINES("please input del name : ", name);*/
	/*llist_front_del(handle, name, cmp_name);*/
    /*
	 *printf("please input find age : ");
	 *scanf("%d", &age);
     */
	/*llist_all_del(handle, &age, cmp_age);*/
	/*llist_index_del(handle, index);*/
	/*llist_end_del(handle, &age, cmp_age);*/
	/*llist_front_del(handle, &age, cmp_age);*/
	printf("==============\n");
	/*llist_travel(llist_all_find(handle, &age, cmp_age), ls, NEXT);*/
    /*
	 *llist_travel(handle, ls, NEXT);
	 *printf("num : %d\n", llist_num(handle));
     */



    /*
	 *printf("please input insert index : ");
	 *scanf("%d", &index);
	 *llist_index_insert(handle, &stu, index);
	 *printf("==============\n");
	 *llist_travel(handle, ls, NEXT);
	 *printf("num : %d\n", llist_num(handle));
     */

	//销毁
	llist_destroy(&handle);
	return 0;
ERR1:
	return -1;
}
