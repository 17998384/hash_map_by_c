
//	Created by ���� on 2020/01/31
//  Copyright  2020 ����. All rights reserved.

#ifndef HASH_MAP_ITERATOR
#define HASH_MAP_ITERATOR
#include "hash_map.h"

struct map_iterator
{
	int iter_index;				//��ǰ��������λ��
	int index;					//map����ʵ��Ԫ��
	int location;				//��ǰ��������ָ�������±�
	struct node* node;			//��ǰnode
	struct hash_map* map;		//hash_map
	struct node** nodes;		//nodes
};

/*
	����
*/
struct map_iterator* iterator(struct hash_map* map);

/*
	�Ƿ񻹾�����һ��Ԫ��
*/
int has_next(struct map_iterator* iter);

/*
	��һ��Ԫ��
*/
struct node* next(struct map_iterator* iter);

#endif