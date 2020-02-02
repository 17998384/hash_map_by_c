
//	Created by ���� on 2020/01/31
//  Copyright  2020 ����. All rights reserved.

#ifndef HASH_MAP
#define HASH_MAP
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//node�ڵ�
struct node
{
	char* key;				//key
	void* value;			//value
	int hash;				//hashֵ
	struct node* next;		//��һ���ڵ�
};

//����hash_map�ṹ��
struct hash_map
{
	struct node** nodes;	//nodes
	int size;				//nodes�Ĵ�С
	int index;				//��ǰ�洢��Ԫ�ظ���
	float growth_factor;	//��������
	int multiple;			//���ݱ���
};

/*
	����hash_map
*/
struct hash_map* new_hash_map(int size);

/*
	put
*/
void* map_put(struct hash_map* map, char* key, void* value);

/*
	get
*/
void* map_get(struct hash_map* map, char* key);

/*
	size
*/
int map_size(struct hash_map* map);

/*
	remove
*/
int map_remove(struct hash_map* map, char* key);

/*
	del��ǰmap(�ͷ��ڴ�)
*/
void del_map(struct hash_map* map);

/*
	private put
*/
void* map_put_val(struct hash_map* map, int hash, char* key, void* value);

/*
	����hashֵ
*/
int key_hash(char* key);

/*
	���map�е�nodes�Ƿ�ΪNULL����Ҫ����
*/
void check_nodes_size(struct hash_map* map);

/*
	����ڴ��Ƿ�����ʧ��
*/
void check_malloc_fail(void* memery);

/*
	����nodeָ��ռ�
*/
struct node** malloc_nodes(int size);

/*
	����node
*/
struct node* create_node(int hash, char* key, void* value);

/*
	����
*/
void dilatation(struct hash_map* map);

/*
	�ͷ�����ڵ�
*/
void free_linked_node(struct node* node);

/*
	�Ƚ�key��node->key��ֵ
*/
int equals_key(struct node* node, char* key);

/*
	�ٴη���hash��
*/
void again_allocation_hash_slot(struct hash_map* map, struct node* node, int new_size);

#endif
