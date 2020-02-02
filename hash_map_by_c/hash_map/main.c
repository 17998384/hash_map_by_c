
//	Created by 葛振东 on 2020/01/31
//  Copyright  2020 葛振东. All rights reserved.


#define _CRT_SECURE_NO_WARNINGS
#include "hash_map.h"

int test(void)
{
	char arr[] = "ceshi";
	struct hash_map* map = new_hash_map(0);
	int i;
	for (i = 0; i < 10000; i++)
	{
		char* key = malloc(sizeof(char) * 15);
		char* value = malloc(sizeof(char) * 15);
		sprintf(key, "%s%d", arr, i);
		strcpy(value, "ceshi");
		map_put(map, key, value);
	}
	//测试遍历
	//struct map_iterator* iter = iterator(map);
	//while (has_next(iter))
	//{
	//	struct node* node = next(iter);
	//	printf("key:%s  value:%s\n", node->key, (char*)node->value);
	//}
	del_map(map);
}

int main1(void)
{
	//创建hash_map
	struct hash_map* map = new_hash_map(0);
	char arr[] = "ceshi";
	//测试put
	int i;
	for (i = 0; i < 10; i++)
	{
		char* key = malloc(sizeof(char) * 15);
		char* value = malloc(sizeof(char) * 15);
		sprintf(key, "%s%d", arr, i);
		strcpy(value, "ceshi");
		map_put(map, key, value);
	}

	//测试map_remove
	int result = map_remove(map, "sevlet_context2");
	map_remove(map, "sevlet_context18");
	map_remove(map, "sevlet_context20");
	map_remove(map, "sevlet_context9");
	map_remove(map, NULL);
	printf("删除成功?%c\n", result == 1 ? 'y' : 'n');
	printf("map的长度是:%d\n", map_size(map));
	//测试遍历
	struct map_iterator* iter = iterator(map);
	while (has_next(iter))
	{
		struct node* node = next(iter);
		printf("key:%s  value:%s\n", node->key, (char*)node->value);
	}

	//测试get
	char* value = (char*)map_get(map, "sevlet_context19");
	printf("get到的字符串是:%s\n", value);
	//测试释放所有空间
	del_map(map);
	return 0;
}

int main(void)
{
	int i;
	for (i = 0; i < 10000; i++)
	{
		printf("测试第%d次\n", i + 1);
		test();
	}
	printf("全部测试通过!\n");
}
