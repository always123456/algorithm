#include <stdio.h>
#include <string.h>
#include <stdlib.h>



// 1、两数之和：
// 给定一个整数数组nums和一个整数目标值target，请你在该数组中找出和为目标值 target 的那两个整数，
//  并返回它们的数组下标。
//  假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。


// // 暴力枚举：O(n**2)的时间复杂度
// int *twonums(int *nums, int target, int numsSize) {
//     int *result = malloc(2 * sizeof(int));      // 动态内存分配
//     if (!result) return NULL;
//     int flag = 0;
//     for (int i = 0; i < numsSize - 1; i++ ) {
//         for (int j = i + 1; j < numsSize; j++) {
//             if (nums[i] + nums[j] == target) {
//                 result[0] = i;
//                 result[1] = j;
//                 flag = 1;
//                 break;
//             }
//         }
//         if (flag == 1) {
//             break;
//         }
//     }

//     if (!flag) {
//         free(result);
//         return NULL;
//     }

//     return result;          // 返回一个整数数组指针
// }


// 哈希表：
// int *hash_int(int *nums, int target, int numsSize) {
//     int **map = malloc(numsSize * sizeof(int*));
//     用二维整数数组充当哈希表，在查找过程中，依旧是O(n2)时间复杂度

//     for (int i = 0; i < numsSize; i++) {

//     }
// }

// // 有uthash.h文件进行哈希表的各种操作
// struct HashTable {
//     int key;
//     int val;
//     UT_hash_handle hh;  // hash handle (哈希句柄)的缩写
// };

// struct HashTable* hashtable;

// // 寻找
// struct HashTable* find(int ikey) {
//     struct HashTable* tmp;
//     HASH_FIND_INT(hashtable, &ikey, tmp);
//     return tmp;
// }   

// // 插入
// void insert(int ikey, int ival) {
//     struct HashTable* it = find(ikey);
//     if (it == NULL) {
//         struct HashTable* tmp = malloc(sizeof(struct HashTable));
//         tmp->key = ikey, tmp->val = ival;
//         HASH_ADD_INT(hashtable, key, tmp);
//     } else {
//         it->val = ival;
//     }
// }

// int* twoSum_by_hash(int* nums, int numsSize, int target, int* returnSize) {
//     hashtable = NULL;

//     for (int i = 0; i < numsSize; i++) {
//         struct HashTable* it = find(target - nums[i]);
//         if (it != NULL) {
//             int* ret = malloc(sizeof(int) * 2);
//             ret[0] = it->val, ret[1] = i;
//             *returnSize = 2;
//             return ret;
//         }
//         insert(nums[i], i);
//     }

//     *returnSize = 0;
//     return NULL;
// }

// int main(void) {
//     int nums[] = {2, 7, 11, 15};
//     int target = 9;
//     int numsSize = sizeof(nums) / sizeof(nums[0]);

//     /* test twonums (暴力枚举) */
//     int *res1 = twonums(nums, target, numsSize);
//     if (res1) {
//         printf("twonums: %d %d\n", res1[0], res1[1]);
//         free(res1);
//     } else {
//         printf("twonums: no solution\n");
//     }

//     /* test twoSum (uthash) */
//     int returnSize = 0;
//     int *res2 = twoSum_by_hash(nums, numsSize, target, &returnSize);    // &：取地址符
//     if (res2 && returnSize == 2) {
//         printf("twoSum(by hash): %d %d\n", res2[0], res2[1]);
//         free(res2);
//     } else {
//         printf("twoSum: no solution\n");
//     }

//     /* 清理 hashtable 中的节点（如果有） */
//     struct HashTable *cur, *tmp;
//     HASH_ITER(hh, hashtable, cur, tmp) {
//         HASH_DEL(hashtable, cur);
//         free(cur);
//     }

//     return 0;
// }







// 链表

// 单链表：
// struct LNode {
//     int data;
//     struct LNode *next;
// };

// //单链表 头插法插入新节点
// struct LNode *head = NULL, *middle = NULL, *last = NULL;

// void insertHead (int e) {
//     struct LNode *newNode = (struct LNode*)malloc(sizeof(struct LNode));
//     // 动态内存空间使用sizeof(struct LNode)的大小，分配内存空间不足，写入
//     // newNode->data和newNode -> next时会越界，破坏内存布局，触发段错误。
//     newNode->data = e;
//     newNode -> next = head;

//     head = newNode;
// }

// //单链表 尾插法插入新节点，最坏的情况的时间复杂度为O(n)
// void insertLast (int e) {
//     struct LNode *newNode = (struct LNode *)malloc(sizeof(struct LNode));

//     newNode -> data = e;
//     newNode -> next = NULL;

//     // 不使用last节点
//     if (head == NULL) {
//         head = newNode;
//     } else {
//         // 查找到最后一个节点
//         struct LNode *lastNode = head;
//         while (lastNode -> next != NULL) {
//             lastNode = lastNode -> next;
//         }
//         lastNode -> next = newNode;
//     }
// }

// //单链表 时间复杂度更低的尾插法，引入了额外的存储链表末尾节点的last指针，时间复杂度始终为O(1)
// void insertLast_lesstime (int e) {
//     struct LNode *newNode = (struct LNode *)malloc(sizeof(struct LNode));

//     newNode -> data = e;
//     newNode -> next = NULL;

//     if (head == NULL) {
//         head = newNode;
//         last = newNode;
//     } else {
//         last -> next = newNode;
//         last = newNode;
//     }
// }


// /*
// 上面添加节点的时候，内存大小分配错误，遍历输出链表时只是读取数据，不会碰校验信息
// 但是删除节点时，利用到了free()函数，分配8字节大小，却填入16字节数据，
// 会覆盖内存块头部的校验信息，判定为非法内存操作。
// */
// //单链表 删除元素  (由于需要对头节点指针进行更改，所以采用二级指针)
// bool deleteNode(struct LNode **head, int key) {
//     // 处理空链表
//     if (head == NULL || *head == NULL) {
//         return false;
//     }
//     struct LNode *temp1 = NULL;

//     if ((*head) -> data == key) {   // 删除头节点
//         temp1 = *head;
//         *head = (*head) -> next;
//         free(temp1);         // 释放被删除节点的内存空间
//         return true;
//     } else {
//         struct LNode *pre = *head;
//         /*
//         由于链表具有单向性，无法从当前节点获取到上一个节点，因此需要提前一个节点读取，
//         而对下一节点执行判断删除操作。
//         */
//         while (pre -> next != NULL) {
//             if (pre -> next -> data == key) {
//                 temp1 = pre -> next;             // 记得释放被删除节点的内存
//                 pre -> next = pre -> next -> next;
//                 free(temp1);    
//                 return true;
//             } else {
//                 pre = pre -> next;
//             }
//         }
//     }
//     return false;  
// }


// // 搜索节点
// struct LNode* searchNode (struct LNode *head, int key) {
//     struct LNode *temp = head;
//     while (temp != NULL) {
//         if (temp -> data == key) {
//             return temp;
//         } else {
//             temp = temp -> next;
//         }
//     }
//     return NULL;
// }



// //带头结点和不带头结点链表
// typedef struct LNode {
//     int data;
//     struct LNode *next;
// }LNode, *Linklist;

// // 不带头结点：
// Linklist head = NULL;

// // 带头结点：
// // 封装内存分配逻辑：
// void init_global_head(int size) {
//     head = (Linklist)malloc(size);
//     if (head == NULL) {
//         perror("malloc failed");
//     }
// }

// // 带头结点与不带头结点的头插法
// void insertHead (int e) {       // 不带
//     Linklist newNode = (Linklist)malloc(sizeof(LNode));
//     newNode -> data = e;

//     newNode -> next = head;
//     head = newNode;
// }

// void List_Insert (int e) {         // 带
//     LNode *newNode = (LNode *)malloc(sizeof(LNode));
//     newNode -> data = e;

//     newNode -> next = head -> next;
//     head -> next = newNode;
// }


// // 带头单链表的尾插法   (无需判断链表是否为空)
// void insertLast (int e) {
//     LNode *newNode = (LNode *)malloc(sizeof(LNode));
//     newNode -> data = e;
//     newNode -> next = NULL;

//     LNode *lastNode = head;
//     while (lastNode -> next != NULL) {
//         lastNode = lastNode -> next;
//     }
//     lastNode -> next = newNode;
//     head -> data++;
// }

// // 带头单链表中删除节点
// bool deleteNode (Linklist *head, int key) {
//     // 或者写成 LNode **head
//     LNode *pre = *head;
//     while (pre -> next != NULL) {
//         if (pre -> next -> data == key) {
//             LNode *temp = pre -> next;
//             pre -> next = pre -> next -> next;
//             free(temp);
//             return true;
//         } else {
//             pre = pre -> next;
//         }
//     }
//     return false;
// }



// // 双链表
// typedef struct DNode {
//     int data;
//     struct DNode *prior;
//     struct DNode *next;
// }DNode, *DLinkList;

// // 双链表的头插法(带头结点)
// bool List_Insert (DLinkList pHead, int e) {
//     DNode* newNode = (DNode *)malloc(sizeof(DNode));
//     newNode -> data = e;

//     newNode ->next = pHead -> next;
//     newNode -> prior = pHead;
//     if (pHead -> next != NULL) {
//         // 将前一个首元节点的前驱指向新节点
//         pHead -> next -> prior = newNode;
//     }
//     pHead -> next = newNode;
//     return true;
// }

// // 双链表的尾插法(带头结点)
// void addLast (DLinkList pHead, int e) {
//     DNode* newNode = (DNode *)malloc(sizeof(DNode));
//     newNode -> data = e;
    
//     // 找到尾结点
//     DNode *lastNode = pHead;
//     while (lastNode -> next != NULL) {
//         lastNode = lastNode -> next;
//     }
//     lastNode -> next = newNode;
//     newNode -> prior = lastNode;
//     newNode -> next = NULL;
// }


// int main() {

//     // // 链表简述：
//     // head = (struct LNode *)malloc(sizeof(struct LNode *));
//     // middle = (struct LNode *)malloc(sizeof(struct LNode *));
//     // last = (struct LNode *)malloc(sizeof(struct LNode *));

//     // head -> data = 20;
//     // middle -> data = 10;
//     // last -> data = 30;

//     // head -> next = middle;
//     // middle -> next = last;
//     // last -> next = NULL;

//     // // 遍历链表
//     // struct LNode *temp = head;
//     // while (temp != NULL) {
//     //     printf("%d\n", temp -> data);
//     //     temp = temp->next;
//     // }


//     // // 头插法插入新节点(以恰好相反的顺序插入)
//     // int nums[3] = {10, 20, 30};

//     // for (int i = 0; i <= 2; i++) {
//     //     insertHead(nums[i]);
//     // }

//     // //遍历链表
//     // struct LNode *temp = head;
//     // while (temp != NULL) {
//     //     printf("%d\n", temp->data);
//     //     temp = temp -> next;
//     // }

    
//     // // 尾插法插入新节点(以相同的顺序插入)
//     // int nums[3] = {10, 20, 30};

//     // for (int i = 0; i <= 2; i++) {
//     //     insertLast_lesstime(nums[i]);
//     //     // // 或用
//     //     // insertLast(nums[i]);
//     // }

//     // // 遍历链表
//     // struct LNode *temp = head;
//     // while (temp != NULL) {
//     //     printf("%d\n", temp->data);
//     //     temp = temp -> next;
//     // }

//     // // 删除节点
//     // int nums[4] = {10, 20, 30, 40};

//     // // 插入节点
//     // for (int i = 0; i < 4; i++) {
//     //     insertLast_lesstime(nums[i]);
//     // }
//     // // 删除节点
//     // bool result = deleteNode(&head, 30);
//     // // 遍历链表
//     // struct LNode *temp = head;
//     // while (temp != NULL) {
//     //     printf("%d\n", temp -> data);
//     //     temp = temp -> next;
//     // }

//     // // 搜索节点
//     // struct LNode *result1 = searchNode(head, 10);
//     // struct LNode *result2 = searchNode(head, 30);

//     // if (result1 == NULL) {
//     //     printf("未搜索到\n");
//     // } else {
//     //     printf("%d\n", result1->data);
//     // }

//     // if (result2 == NULL) {
//     //     printf("未搜索到\n");
//     // } else {
//     //     printf("%d\n", result2->data);
//     // }



//     // // 带头结点的赋值
//     // init_global_head(sizeof(LNode));
//     // head -> next = NULL;
//     // head -> data = 0;



//     // 双链表的构建(可以实现循环链表，即last的next指向head，head的prior指向last)
//     DLinkList head = (DNode *)malloc(sizeof(DNode));
//     DNode* first = (DNode *)malloc(sizeof(DNode));
//     DNode* middle = (DNode *)malloc(sizeof(DNode));
//     DNode* last = (DNode *)malloc(sizeof(DNode));

//     head -> data = NULL;
//     first -> data = 10;
//     middle -> data = 20;
//     last -> data = 30;

//     head -> next = first;
//     first -> prior = head;
//     first -> next = middle;
//     middle -> prior = first;
//     middle -> next = last;
//     last -> prior = middle;
//     last -> next = NULL;

//     return 0;
// }






// 哈希表
// 哈希链表数据结构的定义
#define DEFAULT_SIZE 16

// 链表节点
typedef struct _ListNode {
    struct _ListNode* next;
    int key;      // 表明在Thelists中的索引位置
    int data;     // 键值对
}ListNode, *List;


// 尾插法插入带头节点链表的新节点
void insertLast (int e, ListNode *head) {
    ListNode *temp = head;
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        printf("newNode malloc error\n");
        return ;
    }

    newNode -> key = 0;
    newNode -> data = e;

    while (temp -> next != NULL) {
        temp = temp -> next;
    }

    temp -> next = newNode;
    newNode -> next = NULL;
}

// 哈希表
typedef struct _HashTable {
    int TableSize;
    List *Thelists;    // 每个元素是哈希链表头节点的指针，需要用二级指针形式充当数组形式储存
}HashTable;

// 哈希函数:传递一个key 计算索引，定位Hash桶的位置
int Hash(int key, int TableSize) {
    return (key % TableSize);
}

// 初始化哈希表
HashTable *InitHash(int TableSize) {
    HashTable *hTable = NULL;       // 哈希表指针

    if (TableSize <= 0) {
        TableSize = DEFAULT_SIZE;
    }

    // 给哈希表分配空间
    hTable = (HashTable *)malloc(sizeof(HashTable));

    // 判断是否分配成功
    if (hTable == NULL) {
        printf("HashTable malloc error\n");
        return NULL;
    }

    hTable ->TableSize = TableSize;

    // 为Hash桶分配内存空间，为一个指针数组，存储各条链表的头节点
    hTable -> Thelists = (List *)malloc(TableSize*sizeof(List));

    // 为Hash桶对应的指针数组初始化链表节点
    for (int i = 0; i < TableSize; i++) {
        // 第i+1个链表的头节点指针内存的分配
        hTable -> Thelists[i] = (ListNode *)malloc(sizeof(ListNode));

        if (hTable -> Thelists[i] == NULL) {
            printf("HastTable malloc error\n");
            free(hTable -> Thelists);
            free(hTable);
            return NULL;
        } else {
            memset(hTable->Thelists[i], 0, sizeof(ListNode)); 
        }
    }
    return hTable;
}


int main() {
    // 数据存储示例
    int nums[10] = {0,1,3,4,5,8,9,16,17,19};

    // 初始化一个哈希表
    HashTable *hTable1 = InitHash(DEFAULT_SIZE);
    if (hTable1 == NULL) {
        return -1;
    }

    for (int i = 0; i < 10; i++) {
        int value = nums[i];
        int Hash_value = Hash(value, hTable1->TableSize);

        // 数据插入对应的Hash桶中的位置链表中
        insertLast(value, hTable1->Thelists[Hash_value]);
    }

    // 试试遍历哈希表数据
    ListNode *circleNode = hTable1 -> Thelists[0] -> next;
    while (circleNode != NULL) {
        printf("%d\n", circleNode->data);
        circleNode = circleNode -> next;            // 输出 0,16 正确
    }

    free(hTable1);
    hTable1 = NULL;

    return 0;
}




