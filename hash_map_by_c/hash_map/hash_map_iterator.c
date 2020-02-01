#include "hash_map_iterator.h"
#include "hash_map.h"

//	created by 2020/02/01
//	����:	����(gezhendong)
//	����:	hashMap�еĵ���

/*
	����
*/
struct map_iterator* iterator(struct hash_map* map)
{
	struct map_iterator* iter = (struct map_iterator*)malloc(sizeof(struct map_iterator));
	check_malloc_fail(iter);
	iter->map = map;
	iter->iter_index = 0;
	iter->index = map->index;
	iter->location = 0;
	iter->nodes = map->nodes;
	//��ʼ��iter->node
	if ((iter->node = *(map->nodes + iter->location++)) == NULL)
	{
		//�������ó���map���ĳ���,iter->nodeʼ��ָ����һ��,ֱ����ΪNULL
		do {} while ((iter->location < iter->map->size) && ((iter->node = *(map->nodes + iter->location++)) == NULL));
	}
	return iter;
}

/*
	�Ƿ񻹾�����һ��Ԫ��
*/
int has_next(struct map_iterator* iter)
{
	//��鲢���޸�
	if (iter->index != iter->map->index)
	{
		printf("�����޸��쳣!\n");
		exit(-2);
	}
	if (iter->iter_index == iter->index)
	{
		return 0;
	}
	return 1;
}

/*
	��һ��Ԫ��
*/
struct node* next(struct map_iterator* iter)
{
	if (iter->map->index == 0)
	{
		return NULL;
	}
	struct node* node = iter->node;
	if (node == NULL)
	{
		printf("Ԫ�س����쳣!\n");
		exit(-3);
	}
	if ((iter->node = iter->node->next) == NULL)
	{
		do {} while ((iter->location < iter->map->size) && ((iter->node = *(iter->nodes + iter->location++)) == NULL));
	}
	iter->iter_index++;
	return node;
}