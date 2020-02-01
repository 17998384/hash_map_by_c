#include "hash_map_iterator.h"
#include "hash_map.h"

//	created by 2020/02/01
//	作者:	葛振东(gezhendong)
//	介绍:	hashMap中的迭代

/*
	迭代
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
	//初始化iter->node
	if ((iter->node = *(map->nodes + iter->location++)) == NULL)
	{
		//索引不得超过map最大的长度,iter->node始终指向下一个,直到不为NULL
		do {} while ((iter->location < iter->map->size) && ((iter->node = *(map->nodes + iter->location++)) == NULL));
	}
	return iter;
}

/*
	是否还具有下一个元素
*/
int has_next(struct map_iterator* iter)
{
	//检查并发修改
	if (iter->index != iter->map->index)
	{
		printf("并发修改异常!\n");
		exit(-2);
	}
	if (iter->iter_index == iter->index)
	{
		return 0;
	}
	return 1;
}

/*
	下一个元素
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
		printf("元素出现异常!\n");
		exit(-3);
	}
	if ((iter->node = iter->node->next) == NULL)
	{
		do {} while ((iter->location < iter->map->size) && ((iter->node = *(iter->nodes + iter->location++)) == NULL));
	}
	iter->iter_index++;
	return node;
}