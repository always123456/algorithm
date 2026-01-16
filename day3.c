#include <stdio.h>
// 基本排序算法（以升序为例）

// 1、冒泡排序：  时间复杂度O(n**2)
void bubbleSort(int *arr, size_t length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
// 优化后：(最佳情况，时间复杂度退化到O(n) )
void bubbleSort_op(int *arr, size_t length) {
    for (int i = 0; i < length - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < length - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0) break;
    }
}



// 2、选择排序：    时间复杂度O(n**2)
void selectedSort(int *arr, size_t length) {
    for(int i = 0; i < length - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < length; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;      // 交换操作可能改变元素的相对顺序
    }
}

// 避免不必要的自交换
void selectedSort_op(int *arr, size_t length) {
    for (size_t i = 0; i < length - 1; i++) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < length - 1; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

// 不改变元素的相对顺序，从交换改为平移
void selectedSort_stable(int *arr, size_t length) {
    for (size_t i = 0; i < length - 1; i++) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < length - 1; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        /*将最小值取出，向右移动区间[i, min_idx - 1]，再插入到i处*/
        int min_val = arr[min_idx];
        while (min_idx > i) {
            arr[min_idx] = arr[min_idx - 1];
            min_idx--;
        }
        arr[i] = min_val;
    }
}



// 3、插入排序：
void insertSort(int *arr, size_t length) {
    int index0 = arr[0];
    for (size_t i = 1; i < length ; i++) {      // 无序数组的第一位
        int temp = arr[i];
        size_t index = 0;
        for (size_t j = i - 1; j >= 0; j--) {        // 有序数组的从尾到头的遍历
            if (arr[j] <= temp) {
                arr[j + 1] = temp;
                break;
            } else {
                arr[i - index] = arr[j];
            }
            index++;
        }
    }
}

// 优化实现：
void insertSort_op(int *arr, size_t length) {
    for (size_t i = 1; i < length; ++i) {
        int temp = arr[i];
        size_t j = i;
        while (j > 0 && arr[j - 1] > temp) {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = temp;
    }
}



// 4、希尔排序：插入排序的优化
// 错误的：
void hillSort(int *arr, size_t length) {
    size_t gap = length / 2;
    while (gap >= 1) {
        for (size_t i = 0; i < gap; i++) {
            size_t count = 1;
            int tmp = 0;
            while (i + gap * count < length) {
                if (arr[i + gap * count] >= arr[i + gap *(count - 1)]) {
                    ++count;
                } else {
                    tmp = arr[i + gap * count];
                    size_t back = 1;
                    while (back <= count - 1 && arr[i + gap * (count - back)] > tmp) {
                        arr[i + gap * (count - back + 1)] = arr[i + gap * (count - back)];
                        ++back;
                    }
                    arr[i + gap * (count - back + 1)] = tmp;
                }
                ++count;
            }
        }
        gap = gap / 2;
    }
}

// AI代码太完美了：
void shellSort_op(int *arr, size_t length) {
    for (size_t gap = length / 2; gap > 0; gap /= 2) {  // gap不断取半，缩小范围至 1
        for (size_t i = gap; i < length; ++i) {  // 对以gap长度为间隔的数组进行插入排序
            int temp = arr[i];
            size_t j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}



int main() {
    int arr[10] = {3,2,20,4,11,6,5,9,8,1};

    // 1、冒泡排序：
    // bubbleSort(arr, 10);

    // 2、选择排序：
    // selectedSort(arr, 10);

    // 3、插入排序：
    // insertSort_op(arr, 10);

    // 4、希尔排序
    shellSort_op(arr, 10);

    for (int i = 0; i < 10; i++) {
        printf("%d\n", arr[i]);
    }

    return 0;
}