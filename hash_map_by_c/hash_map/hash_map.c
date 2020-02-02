
//	Created by 葛振东 on 2020/01/31
//  Copyright  2020 葛振东. All rights reserved.

#include "hash_map.h"
#include "hash_map_iterator.h"
#define GROWTH_FACTOR  0.75			//增长因子
#define MULTIPLE 2					//扩大倍数
#define INITIAL_SIZE 16				//初始大小

/*
	创建hash_map
*/
struct hash_map* new_hash_map(int size)
{
	//创建hash_map
	struct hash_map* map = (struct hash_map*) malloc(sizeof(struct hash_map));
	//检查内存是否申请失败
	check_malloc_fail(map);
	//将内存置为0
	memset(map, NULL, sizeof(struct hash_map));
	//标明nodes的初始大小
	map->size = size;
	//标明初始实际node数量
	map->index = 0;
	//标明扩张因子
	map->growth_factor = GROWTH_FACTOR;
	//标明扩容倍数
	map->multiple = MULTIPLE;
	return map;
}

/*
	put
*/
void* map_put(struct hash_map* map, char* key, void* value)
{
	void* value_return = map_put_val(map, key_hash(key), key, value);
	map->index++;
	return value_return;
}

/*
	get
*/
void* map_get(struct hash_map* map, char* key)
{
	int index = get_node_index(map->size, key);
	struct node* node = *(map->nodes + index);
	if (node == NULL)
	{
		return NULL;
	}
	//遍历链表
	do
	{
		if (equals_key(node, key))
		{
			return node->value;
		}
	} while ((node = node->next) != NULL);
	return NULL;
}

/*
	size
*/
int map_size(struct hash_map* map)
{
	return map->index;
}

/*
	remove
*/
int map_remove(struct hash_map* map, char* key)
{
	//计算hash
	int hash = key_hash(key);
	//计算索引
	int index = get_node_index(map->size, key);
	//当前node
	struct node* node = *(map->nodes + index);
	//上一个node
	struct node* prev;
	if (node == NULL)
	{
		return 0;
	}
	//如果第一个就匹配到,并且next无元素,则释放
	if (node->next == NULL)
	{
		free(node->key);
		free(node->value);
		free(node);
		*(map->nodes + index) = NULL;
		map->index--;
		return 1;
	}
	//如果第一个匹配到,next有元素,则释放第一个,将该槽位放入next
	if (equals_key(node, key))
	{
		*(map->nodes + index) = node->next;
		free(node->key);
		free(node->value);
		free(node);
		map->index--;
		return 1;
	}
	//遍历链表
	while ((node = (prev = node)->next) != NULL)
	{
		if (equals_key(node, key))
		{
			prev->next = node->next;
			free(node->key);
			free(node->value);
			free(node);
			map->index--;
			return 1;
		}
	}
	return 0;
}

/*
	del当前map(释放内存)
*/
void del_map(struct hash_map* map)
{
	int i;
	for (i = 0; i < map->size; i++)
	{
		struct node* node = map->nodes[i];
		struct node* prev;
		//不使用递归
		//if (node != NULL)
		//{
		//	free_linked_node(node);
		//}
		if (node != NULL)
		{
			while ((node = (prev = node)->next) != NULL)
			{
				free(prev->key);
				free(prev->value);
				free(prev);
			}
			free(prev->key);
			free(prev->value);
			free(prev);
		}
	}
	free(map->nodes);
	free(map);
}

/*
	private put
*/
void* map_put_val(struct hash_map* map, int hash, char* key, void* value)
{
	struct node* node;
	struct node* prev;
	check_nodes_size(map);
	//计算nodes**指针数组位置
	int index = hash % map->size;
	node = *(map->nodes + index);
	//如果当前node有元素,则遍历链表到NULL插入node
	if (node != NULL)
	{
		do
		{
			if (equals_key(node, key))
			{
				node->value = value;
				return node->value;
			}
		} while ((node = (prev = node)->next) != NULL);
		//创建node
		node = create_node(hash, key, value);
		prev->next = node;
		return value;
	}
	node = create_node(hash, key, value);
	map->nodes[index] = node;
	return value;
}

/*
	计算hash值(自制瞎J8写的hash算法,冲不冲突我不管)
*/
int key_hash(char* key)
{
	if (key == NULL)
	{
		return 0;
	}
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
	unsigned int hash = 0;
	while (*key)
	{
		hash = hash * seed + (*key);
		key++;
	}
	return (hash & 0x7FFFFFFF);
}

/*
	获取索引
*/
int get_node_index(int size, char* key)
{
	return (size - 1) & key_hash(key);
}

/*
	检查map中的nodes是否为NULL或需要扩容
*/
void check_nodes_size(struct hash_map* map)
{
	//如果nodes为NULL
	if (map->nodes == NULL)
	{
		int size;
		//如果没有指定初始长度,默认为16
		size = map->size == 0 ? INITIAL_SIZE : map->size;
		//如果size为0则替换掉,否则保持不变
		map->size = size;
		//申请空间
		map->nodes = malloc_nodes(size);
	}
	//否则检查是否需要扩容
	if (map->size * map->growth_factor * 1.0 == map->index)
	{
		//扩容
		dilatation(map);
	}
}

/*
	检查内存是否申请失败
*/
void check_malloc_fail(void* memery)
{
	if (memery == NULL)
	{
		printf("该计算机中无可用的内存提供使用!\n");
		exit(-1);
	}
}

/*
	申请node指针空间
*/
struct node** malloc_nodes(int size)
{
	//申请nodes指针数组空间
	struct node** nodes = (struct node**)malloc(sizeof(struct node*) * size);
	check_malloc_fail(nodes);
	//将内存全部置为0
	memset(nodes, NULL, sizeof(struct nodes**) * size);
	return nodes;
}

/*
	创建node
*/
struct node* create_node(int hash, char* key, void* value)
{
	//申请node结构体内存
	struct node* node = (struct node*)malloc(sizeof(struct node));
	check_malloc_fail(node);
	//为node赋值
	node->hash = hash;
	node->key = key;
	node->value = value;
	node->next = NULL;
	return node;
}

/*
	扩容
*/
void dilatation(struct hash_map* map)
{
	struct node** old_nodes = map->nodes;
	//扩容后的大小
	int new_size = map->size * map->multiple;
	struct node** new_nodes = malloc_nodes(new_size);
	map->nodes = new_nodes;
	int i;
	for (i = 0; i < map->size; i++)
	{
		struct node* node = old_nodes[i];
		if (node != NULL)
		{
			do
			{
				struct node* next = node->next;
				again_allocation_hash_slot(map, node, new_size);
				node = next;
			} while (node != NULL);
		}
	}
	map->size = new_size;
	free(old_nodes);
}

/*
	递归释放链表节点
*/
void free_linked_node(struct node* node)
{
	if (node == NULL)
	{
		return;
	}
	free_linked_node(node->next);
	free(node);
}

/*
	比较key与node->key的值
*/
int equals_key(struct node* node, char* key)
{
	return node->key == NULL ? key == NULL : !strcmp(node->key, key);
}

/*
	再次分配hash槽
*/
void again_allocation_hash_slot(struct hash_map* map, struct node* node, int new_size)
{
	struct node** nodes = map->nodes;
	struct node* new_node;
	struct node* prev;
	node->next = NULL;
	int index = get_node_index(map->size, node->key);
	new_node = nodes[index];
	if (new_node == NULL)
	{
		nodes[index] = node;
		return;
	}
	do {} while ((new_node = (prev = new_node)->next) != NULL);
	prev->next = node;
}
