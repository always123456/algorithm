#include <stdio.h>
#include <time.h>

// 冒泡排序：
void bubbleSort(int *arr, size_t length) {
    for (int i = length - 1; i > 0; i--) {
        int swapped = 0;
        for (int j = 0; j < i; j++) {
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

// 选择排序：
void selectedSort(int *arr, size_t length) {
    for (size_t i = 0; i < length - 1; i++) {
        size_t min_idx = i;

        // 找未排序序列中的最小值，[i, length - 1]
        for (size_t j = i + 1; j <= length - 1; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        // 取出最小值，进行交换操作
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

// 插入排序：
void insertSort(int *arr, size_t length) {
    // 从第二个元素开始遍历
    for (size_t i = 1; i <= length - 1; i++) {
        // 当前要插入的元素值
        int ist_val = arr[i];
        // 已排序区的最后一个索引
        int j = (int)i - 1;     
        // 注意这里j在下面的while循环中可能变成负数，
        // 不要使用size_t(无符号整数)定义了，否则发生下溢，变成SIZE_MAX
        
        while (j >= 0 && arr[j] > ist_val) {
            arr[j + 1] = arr[j];    // 后移元素
            j--;
        }
        arr[j + 1] = ist_val;       // 插入元素
    }
}

// 希尔排序：
void hillSort(int *arr, size_t length) {
    for (size_t gap = length / 2; gap >= 1; gap /= 2) {
        for (size_t i = gap; i < length; i++) {
            // 需要插入的元素值
            int ist_val = arr[i];

            int j = (int)(i - gap);
            while (j >= 0 && arr[j] > ist_val) {
                arr[j + gap] = arr[j];
                j -= gap;
            }
            arr[j + gap] = ist_val;
        }
    }
}

int main() {
    // 程序开始时间
    clock_t start = clock();

    int arr[13] = {3,1,5,4,7,6,1,4,9,100,40,30,25};

    hillSort(arr, 13);

    for (int i = 0; i < 13; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 程序结束时间
    clock_t end = clock();
    
    double execution_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("该程序执行时间为: %f 秒\n", execution_time);

    return 0;
}