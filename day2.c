#include <stdio.h>
#include <stdlib.h>
#include <uthash.h>


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

int main(void) {
    int nums[] = {2, 7, 11, 15};
    int target = 9;
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    /* test twonums (暴力枚举) */
    int *res1 = twonums(nums, target, numsSize);
    if (res1) {
        printf("twonums: %d %d\n", res1[0], res1[1]);
        free(res1);
    } else {
        printf("twonums: no solution\n");
    }

    /* test twoSum (uthash) */
    int returnSize = 0;
    int *res2 = twoSum_by_hash(nums, numsSize, target, &returnSize);    // &：取地址符
    if (res2 && returnSize == 2) {
        printf("twoSum(by hash): %d %d\n", res2[0], res2[1]);
        free(res2);
    } else {
        printf("twoSum: no solution\n");
    }

    /* 清理 hashtable 中的节点（如果有） */
    struct HashTable *cur, *tmp;
    HASH_ITER(hh, hashtable, cur, tmp) {
        HASH_DEL(hashtable, cur);
        free(cur);
    }

    return 0;
}


