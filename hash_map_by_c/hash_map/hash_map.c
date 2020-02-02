
//	Created by ���� on 2020/01/31
//  Copyright  2020 ����. All rights reserved.

#include "hash_map.h"
#include "hash_map_iterator.h"
#define GROWTH_FACTOR  0.75			//��������
#define MULTIPLE 2					//������
#define INITIAL_SIZE 16				//��ʼ��С

/*
	����hash_map
*/
struct hash_map* new_hash_map(int size)
{
	//����hash_map
	struct hash_map* map = (struct hash_map*) malloc(sizeof(struct hash_map));
	//����ڴ��Ƿ�����ʧ��
	check_malloc_fail(map);
	//���ڴ���Ϊ0
	memset(map, NULL, sizeof(struct hash_map));
	//����nodes�ĳ�ʼ��С
	map->size = size;
	//������ʼʵ��node����
	map->index = 0;
	//������������
	map->growth_factor = GROWTH_FACTOR;
	//�������ݱ���
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
	//��������
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
	//����hash
	int hash = key_hash(key);
	//��������
	int index = get_node_index(map->size, key);
	//��ǰnode
	struct node* node = *(map->nodes + index);
	//��һ��node
	struct node* prev;
	if (node == NULL)
	{
		return 0;
	}
	//�����һ����ƥ�䵽,����next��Ԫ��,���ͷ�
	if (node->next == NULL)
	{
		free(node->key);
		free(node->value);
		free(node);
		*(map->nodes + index) = NULL;
		map->index--;
		return 1;
	}
	//�����һ��ƥ�䵽,next��Ԫ��,���ͷŵ�һ��,���ò�λ����next
	if (equals_key(node, key))
	{
		*(map->nodes + index) = node->next;
		free(node->key);
		free(node->value);
		free(node);
		map->index--;
		return 1;
	}
	//��������
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
	del��ǰmap(�ͷ��ڴ�)
*/
void del_map(struct hash_map* map)
{
	int i;
	for (i = 0; i < map->size; i++)
	{
		struct node* node = map->nodes[i];
		struct node* prev;
		//��ʹ�õݹ�
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
	//����nodes**ָ������λ��
	int index = hash % map->size;
	node = *(map->nodes + index);
	//�����ǰnode��Ԫ��,���������NULL����node
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
		//����node
		node = create_node(hash, key, value);
		prev->next = node;
		return value;
	}
	node = create_node(hash, key, value);
	map->nodes[index] = node;
	return value;
}

/*
	����hashֵ(����ϹJ8д��hash�㷨,�岻��ͻ�Ҳ���)
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
	��ȡ����
*/
int get_node_index(int size, char* key)
{
	return (size - 1) & key_hash(key);
}

/*
	���map�е�nodes�Ƿ�ΪNULL����Ҫ����
*/
void check_nodes_size(struct hash_map* map)
{
	//���nodesΪNULL
	if (map->nodes == NULL)
	{
		int size;
		//���û��ָ����ʼ����,Ĭ��Ϊ16
		size = map->size == 0 ? INITIAL_SIZE : map->size;
		//���sizeΪ0���滻��,���򱣳ֲ���
		map->size = size;
		//����ռ�
		map->nodes = malloc_nodes(size);
	}
	//�������Ƿ���Ҫ����
	if (map->size * map->growth_factor * 1.0 == map->index)
	{
		//����
		dilatation(map);
	}
}

/*
	����ڴ��Ƿ�����ʧ��
*/
void check_malloc_fail(void* memery)
{
	if (memery == NULL)
	{
		printf("�ü�������޿��õ��ڴ��ṩʹ��!\n");
		exit(-1);
	}
}

/*
	����nodeָ��ռ�
*/
struct node** malloc_nodes(int size)
{
	//����nodesָ������ռ�
	struct node** nodes = (struct node**)malloc(sizeof(struct node*) * size);
	check_malloc_fail(nodes);
	//���ڴ�ȫ����Ϊ0
	memset(nodes, NULL, sizeof(struct nodes**) * size);
	return nodes;
}

/*
	����node
*/
struct node* create_node(int hash, char* key, void* value)
{
	//����node�ṹ���ڴ�
	struct node* node = (struct node*)malloc(sizeof(struct node));
	check_malloc_fail(node);
	//Ϊnode��ֵ
	node->hash = hash;
	node->key = key;
	node->value = value;
	node->next = NULL;
	return node;
}

/*
	����
*/
void dilatation(struct hash_map* map)
{
	struct node** old_nodes = map->nodes;
	//���ݺ�Ĵ�С
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
	�ݹ��ͷ�����ڵ�
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
	�Ƚ�key��node->key��ֵ
*/
int equals_key(struct node* node, char* key)
{
	return node->key == NULL ? key == NULL : !strcmp(node->key, key);
}

/*
	�ٴη���hash��
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
