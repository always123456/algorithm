#include <stdio.h>
#include <stdlib.h>
#include <uthash.h>
#include <stdbool.h>


// 1、两数之和：
// 给定一个整数数组nums和一个整数目标值target，请你在该数组中找出和为目标值 target 的那两个整数，
//  并返回它们的数组下标。
//  假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。


// 暴力枚举：O(n**2)的时间复杂度
int *twonums(int *nums, int target, int numsSize) {
    int *result = malloc(2 * sizeof(int));      // 动态内存分配
    if (!result) return NULL;
    int flag = 0;
    for (int i = 0; i < numsSize - 1; i++ ) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                result[0] = i;
                result[1] = j;
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            break;
        }
    }

    if (!flag) {
        free(result);
        return NULL;
    }

    return result;          // 返回一个整数数组指针
}


// 哈希表：
// int *hash_int(int *nums, int target, int numsSize) {
//     int **map = malloc(numsSize * sizeof(int*));
//     用二维整数数组充当哈希表，在查找过程中，依旧是O(n2)时间复杂度

//     for (int i = 0; i < numsSize; i++) {

//     }
// }

// 有uthash.h文件进行哈希表的各种操作
struct HashTable {
    int key;
    int val;
    UT_hash_handle hh;  // hash handle (哈希句柄)的缩写
};

struct HashTable* hashtable;

// 寻找
struct HashTable* find(int ikey) {
    struct HashTable* tmp;
    HASH_FIND_INT(hashtable, &ikey, tmp);
    return tmp;
}   

// 插入
void insert(int ikey, int ival) {
    struct HashTable* it = find(ikey);
    if (it == NULL) {
        struct HashTable* tmp = malloc(sizeof(struct HashTable));
        tmp->key = ikey, tmp->val = ival;
        HASH_ADD_INT(hashtable, key, tmp);
    } else {
        it->val = ival;
    }
}

int* twoSum_by_hash(int* nums, int numsSize, int target, int* returnSize) {
    hashtable = NULL;

    for (int i = 0; i < numsSize; i++) {
        struct HashTable* it = find(target - nums[i]);
        if (it != NULL) {
            int* ret = malloc(sizeof(int) * 2);
            ret[0] = it->val, ret[1] = i;
            *returnSize = 2;
            return ret;
        }
        insert(nums[i], i);
    }

    *returnSize = 0;
    return NULL;
}

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
struct LNode {
    int data;
    struct LNode *next;
};

//单链表 头插法插入新节点
struct LNode *head = NULL, *middle = NULL, *last = NULL;

void insertHead (int e) {
    struct LNode *newNode = (struct LNode*)malloc(sizeof(struct LNode*));
    newNode->data = e;
    newNode -> next = head;

    head = newNode;
}

//单链表 尾插法插入新节点，最坏的情况的时间复杂度为O(n)
void insertLast (int e) {
    struct LNode *newNode = (struct LNode *)malloc(sizeof(struct LNode*));

    newNode -> data = e;
    newNode -> next = NULL;

    // 不使用last节点
    if (head == NULL) {
        head = newNode;
    } else {
        // 查找到最后一个节点
        struct LNode *lastNode = head;
        while (lastNode -> next != NULL) {
            lastNode = lastNode -> next;
        }
        lastNode -> next = newNode;
    }
}

//单链表 时间复杂度更低的尾插法，引入了额外的存储链表末尾节点的last指针，时间复杂度始终为O(1)
void insertLast_lesstime (int e) {
    struct LNode *newNode = (struct LNode *)malloc(sizeof(struct LNode*));

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

//单链表 删除元素 ??? 
bool deleteNode(struct LNode *head, int key) {
    struct LNode *temp = head;
    if ((head) -> data == key) {
        temp = head;
        head = head -> next;
        free(temp);         // 释放被删除节点的内存空间
        return true;
    } else {
        struct LNode *nowNode = head -> next;
        while (nowNode != NULL) {
            if (nowNode -> data == key) {
                temp = nowNode;
                nowNode = nowNode -> next;
                free(temp);
                return true;
            } else {
                nowNode = nowNode -> next;
            }
        }
    }
    return false;  
}

int main() {

    // // 链表简述：
    // head = (struct LNode *)malloc(sizeof(struct LNode *));
    // middle = (struct LNode *)malloc(sizeof(struct LNode *));
    // last = (struct LNode *)malloc(sizeof(struct LNode *));

    // head -> data = 20;
    // middle -> data = 10;
    // last -> data = 30;

    // head -> next = middle;
    // middle -> next = last;
    // last -> next = NULL;

    // // 遍历链表
    // struct LNode *temp = head;
    // while (temp != NULL) {
    //     printf("%d\n", temp -> data);
    //     temp = temp->next;
    // }


    // // 头插法插入新节点(以恰好相反的顺序插入)
    // int nums[3] = {10, 20, 30};

    // for (int i = 0; i <= 2; i++) {
    //     insertHead(nums[i]);
    // }

    // //遍历链表
    // struct LNode *temp = head;
    // while (temp != NULL) {
    //     printf("%d\n", temp->data);
    //     temp = temp -> next;
    // }

    
    // 尾插法插入新节点(以相同的顺序插入)
    int nums[3] = {10, 20, 30};

    for (int i = 0; i <= 2; i++) {
        insertLast_lesstime(nums[i]);
        // // 或用
        // insertLast(nums[i]);
    }

    // 遍历链表
    struct LNode *temp = head;
    while (temp != NULL) {
        printf("%d\n", temp->data);
        temp = temp -> next;
    }


    return 0;
}