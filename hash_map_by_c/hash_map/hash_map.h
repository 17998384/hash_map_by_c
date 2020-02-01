#ifndef HASH_MAP
#define HASH_MAP
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
	@description 模仿java的HashMap(key只支持string类型(char*))
	@author	葛振东
	@by	2020/01/30
*/


//node节点
struct node
{
	char* key;				//key
	void* value;			//value
	int hash;				//hash值
	struct node* next;		//下一个节点
};

//定义hash_map结构体
struct hash_map
{
	struct node** nodes;	//nodes
	int size;				//nodes的大小
	int index;				//当前存储的元素个数
	float growth_factor;	//增长因子
	int multiple;			//扩容倍数
};

/*
	创建hash_map
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
	del当前map(释放内存)
*/
void del_map(struct hash_map* map);

/*
	private put
*/
void* map_put_val(struct hash_map* map, int hash, char* key, void* value);

/*
	计算hash值
*/
int key_hash(char* key);

/*
	检查map中的nodes是否为NULL或需要扩容
*/
void check_nodes_size(struct hash_map* map);

/*
	检查内存是否申请失败
*/
void check_malloc_fail(void* memery);

/*
	申请node指针空间
*/
struct node** malloc_nodes(int size);

/*
	创建node
*/
struct node* create_node(int hash, char* key, void* value);

/*
	扩容
*/
void dilatation(struct hash_map* map);

/*
	释放链表节点
*/
void free_linked_node(struct node* node);

/*
	比较key与node->key的值
*/
int equals_key(struct node* node, char* key);

/*
	再次分配hash槽
*/
void again_allocation_hash_slot(struct hash_map* map, struct node* node, int new_size);

#endif
