# Day2 链表及哈希表
## 1.链表
### 1.1 单链表
#### 1.1.1 不带头节点单链表：
***
1、不带头节点的单链表的生成：
``` c
struct LNode {
	int data;
	struct LNode* next;
};
	
struct LNode *head = NULL;	//首元节点
struct LNode *last = NULL;	// 末尾节点
```
2、头插法插入新节点：将head节点地址作为全局变量存储，可以不使用二级指针。
``` c
void insertHead (int e) {
	struct LNode *newNode = (struct LNode *)malloc(sizeof(struct LNode));
	newNode -> data = e;
	newNode -> next = head;	// 直接插到首元节点之前

	head = newNode;	// 更新首元节点
}
```
3、尾插法插入新节点（不使用last节点对链表末尾节点作特殊储存的条件下）， 最坏的情况，时间复杂度为O(n)：
``` c
void insertLast (int e) {
	struct LNode *newNode = (struct LNode *)malloc(sizeof(struct LNode));
	newNode -> data = e;
	newNode -> next = NULL;
	
	// 对链表是否为空做判断
	if (head == NULL) {
		head = newNode;
	} else {
		struct LNode *lastNode = head;
		while (lastNode -> next != NULL) {
			lastNode = lastNode -> next;
		}
		lastNode -> next = newNode;
	}
}
```
4、尾插法插入新节点（用last节点对链表末尾节点作特殊储存）：
``` c
void insertLast_lesstime (int e) {
	struct LNode *newNode = (struct LNode *)malloc(sizeof(struct LNode));
	newNode -> data = e;
	newNode -> next = NULL;

	if (head == NULL) {
		head = newNode;
		last = newNode;
	} else {
		last -> next = newNode;
		last = newNode;
	}
}
```
上面插入节点时，分配给**newNode**的内存空间必须为`sizeof(struct LNode)`，否则写入`newNode -> data`和`newNode -> next` 时会越界，影响后续的删除操作。
5、删除节点：在这里没有将head节点当做全局变量，传入二级指针才可以对head节点作操作。
``` c
bool deleteNode (struct LNode **head, int key) {
	// 处理空链表
	if (head == NULL || *head == NULL) {
		return false;
	}
	struct LNode *temp1 = NULL;

	if ((*head) -> data == key) {	// 首元节点需要被删除的情况
		temp1 = *head;
		*head = (*head) -> next;
		free(temp1);	// 释放被删除节点的内存空间
		return true;
	} else {
		struct LNode *pre = *head;
		while (pre -> next != NULL) {
			if (pre -> next -> data == key) {
				temp1 = pre -> next;
				pre -> next = pre -> next -> next;
				free(temp1);
				return true;
			} else {
				pre = pre -> next;
			}
		}
	}
	return false;
}
```
6、搜索节点：
``` c
struct LNode *searchNode {struct LNode *head, int key) {
	struct LNode *temp = head;
	while (temp != NULL) {
		if (temp -> data == key) {
			return temp;
		} else {
			temp = temp -> next;
		}
	}
	return NULL;
}
```
***
#### 1.1.2 带头节点的单链表：
1、创建带头节点的单链表（返回头节点地址）：
``` c
typedef struct LNode {
	int data;
	struct LNode *next;
}LNode , *LinkList;

// 创建一个带头节点的单链表（返回头节点地址）
LNode* createHeadLinkList () {
	// 分配内存
	LNode *headNode = (LNode*)malloc(sizeof(LNode));
	if (headNode == NULL) {
		printf("头节点内存分配失败\n");
		return NULL;
	}	
	// 头节点初始化：data可以为0，next指向NULL(空链表)
	headNode -> data = 0;
	headNode -> next = NULL;

	return headNode;
}

// 创建一个普通节点（用于插入链表）
LNode* createNode(int value) {
	LNode *newNode = (LNode *)malloc(sizeof(LNode));
	if (newNode == NULL) {
		printf("创建新节点失败\n");
		return NULL;
	}
	newNode -> data = value;
	newNode -> next = NULL;
	return newNode;
}
```
2、头部插入（带头节点，无需二级指针）：
``` c
void insertAtHead (LNode *headNode, int value) {
	if (headNode == NULL) {
		printf("头节点不存在，无法插入\n");
		return;
	}
	// 创建新节点
	LNode *newNode = createNode(value);
	if (newNode == NULL) return;

	// 插入逻辑：
	newNode -> next = headNode -> next;
	headNode -> next = newNode;

	// 更新headNode存储的链表长度data（可选）
	headNode -> data ++;
}
```
3、尾部插入：（无需判断链表是否为空）
``` c
void insertAtTail (LNode *headNode, int value) {
	if (headNode == NULL) {
		printf("头节点不存在，无法插入\n");
	}
	LNode *newNode = createNode(value);
	if (newNode == NULL) return;

	// 遍历到链表末尾
	LNode *temp = headNode;
	while (temp -> next != NULL) {
		temp = temp -> next;
	}
	temp -> next = newNode;

	headNode -> data++;
	printf("插入成功\n");
}
```
4、删除节点：
``` c
bool deleteNode (LNode **head, int key) {
	LNode *pre = *head;
	while (pre -> next != NULL) {
		if (pre -> next -> data == key) {
			LNode *temp = pre -> next;
			pre -> next = pre -> next -> next;
			free(temp);
			return true;
		} else {
			pre = pre -> next;
		}
	}
	return false;
}
```
***
#### 1.1.3 双链表：
1、双链表的构建：（不循环的链表）
``` c
typedef struct DNode {
	int data;
	struct DNode *prior;
	struct DNode *next;
}DNode, *DLinkList;

int main() {
	DLinkList head = (DNode *)malloc(sizeof(DNode));
	DNode *first = (DNode *)malloc(sizeof(DNode));
	DNode *middle = (DNode *)malloc(sizeof(DNode));
	DNode *last = (DNode *)malloc(sizeof(DNode));

	head -> data = NULL;
	first -> data = 10;
	middle -> data = 20;
	last -> data = 30;
	head -> next = first;
	first -> prior = head;
	first -> next = middle
	middle -> prior = first;
	middle -> next = last;
	last -> prior = middle;
	last -> next = NULL;

	return 0;
}
```
2、双链表头插法：（带头节点）
``` c
bool List_Insert (DLinkList pHead, int e) {
	DNode *newNode = (DNode *)malloc(sizeof(DNode));
	newNode -> data = e;

	newNode -> next = pHead -> next;
	newNode -> prior = pHead;
	if (pHead -> next != NULL) {
		// 将之前的首元节点的前驱指向新节点
		pHead -> next -> prior = newNode;
	}
	pHead -> next = newNode;
	return true;
}
```
3、双链表尾插法（带头节点）：
``` c
void addLast (DNode *pHead, int e) {
	DNode *newNode = (DNode *)malloc(sizeof(DNode));
	newNode -> data = e;

	// 找到尾节点
	DNode *lastNode = pHead;
	while (lastNode -> next != NULL) {
		lastNode = lastNode -> next;
	}
	lastNode -> next = newNode;
	newNode -> prior = lastNode;
	newNode -> next =  NULL;
}
```
























