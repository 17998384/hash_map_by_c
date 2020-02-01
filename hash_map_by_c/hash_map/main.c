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
	//���Ա���
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
	//����hash_map
	struct hash_map* map = new_hash_map(0);
	char arr[] = "ceshi";
	//����put
	int i;
	for (i = 0; i < 10; i++)
	{
		char* key = malloc(sizeof(char) * 15);
		char* value = malloc(sizeof(char) * 15);
		sprintf(key, "%s%d", arr, i);
		strcpy(value, "ceshi");
		map_put(map, key, value);
	}

	//����map_remove
	int result = map_remove(map, "sevlet_context2");
	map_remove(map, "sevlet_context18");
	map_remove(map, "sevlet_context20");
	map_remove(map, "sevlet_context9");
	map_remove(map, NULL);
	printf("ɾ���ɹ�?%c\n", result == 1 ? 'y' : 'n');
	printf("map�ĳ�����:%d\n", map_size(map));
	//���Ա���
	struct map_iterator* iter = iterator(map);
	while (has_next(iter))
	{
		struct node* node = next(iter);
		printf("key:%s  value:%s\n", node->key, (char*)node->value);
	}

	//����get
	char* value = (char*)map_get(map, "sevlet_context19");
	printf("get�����ַ�����:%s\n", value);
	//�����ͷ����пռ�
	del_map(map);
	return 0;
}

int main(void)
{
	int i;
	for (i = 0; i < 100000; i++)
	{
		printf("���Ե�%d��\n", i + 1);
		test();
	}
	printf("ȫ������ͨ��!\n");
}
