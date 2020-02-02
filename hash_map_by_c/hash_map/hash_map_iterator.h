
//	Created by 葛振东 on 2020/01/31
//  Copyright  2020 葛振东. All rights reserved.

#ifndef HASH_MAP_ITERATOR
#define HASH_MAP_ITERATOR
#include "hash_map.h"

struct map_iterator
{
	int iter_index;				//当前遍历到的位置
	int index;					//map中总实际元素
	int location;				//当前遍历到的指针数组下标
	struct node* node;			//当前node
	struct hash_map* map;		//hash_map
	struct node** nodes;		//nodes
};

/*
	迭代
*/
struct map_iterator* iterator(struct hash_map* map);

/*
	是否还具有下一个元素
*/
int has_next(struct map_iterator* iter);

/*
	下一个元素
*/
struct node* next(struct map_iterator* iter);

#endif