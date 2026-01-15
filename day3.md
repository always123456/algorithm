# Day3 基本排序方法
## 1.冒泡排序
1、粗糙实现：
``` c
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
```
2、优化：最佳情况，时间复杂度退化到O(n)
``` c
void bubbleSort_op(int *arr, size_t length) {
	for (int i = 0; i < length -1 ; i++) {
		int swapped = 0;
		for (int j = 0; j < length - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				swapped = 1;
			}
		}
		if (!swapped) break;
	}
}
```
## 2. 选择排序
1、对选定的元素直接做交换操作：
``` c
void selectedSort(int *arr, size_t length) {
	for (int i = 0; i < length - 1; i++) {
		int min_index = i;
		for (int j = i + 1; j < length; j++) {
			if (arr[j] < arr[min_index]) {
				min_index = j;
			}
		}
		if (min_index != i) {		// 避免不必要的自交换
			int temp = arr[i];
			arr[i] = arr[min_index];
			arr[min_index] = temp;
		}
	}
}
```
2、做平移操作，不改变剩下未排序数组元素的相对位置
``` c
void selectedSort_op(int *arr, size_t length) {
	for (size_t i = 0; i < length - 1; i++) {
		int min_idx = i;
		for (int j = i + 1; j < length; j++) {
			if (arr[j] < arr[min_idx]) {
				min_idx = j;
			}
		}
		/*将最小值取出，向右移动区间[i, min_idx - 1]，再将最小值插入到i处*/
		int min_val = arr[min_idx];
		while (min_idx > i) {
			arr[min_idx] = arr[min_idx - 1];
			--min_idx;
		}
		arr[i] = min_val;
	}
}
```
## 3.插入排序
1、一坨
``` c
void insertSort(int *arr, size_t length) {
	int index0 = arr[0];
	for (size_t i = 1; i < length; i++) {			// 无序数组的第一位
		int temp = arr[i];
		size_t index = 0;
		for (size_t j = i - 1; j >= 0 ; j--) {		// 有序数组从头到尾遍历
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
```
2、优化实现：
``` c
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
```
