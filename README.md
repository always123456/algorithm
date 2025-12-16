# Algorithm
## Day1
### 1.以二进制位运算形式实现两个整数之间的加法运算
原理如下：
``` c
int addWithoutArithmetic(int a, int b) {
	while (b != 0) {
		int carry = (a & b) << 1;
		a = a ^ b;
		b = carry;
	}
	return a;
}
```
细节考虑，对有符号类型整数进行左移运算，如果导致符号位改变，即溢出，此为危险的未定义操作，因此考虑将a, b均先更换为无符号整数
``` c
int addWithoutArithmetic(int a, int b) {
	unsigned int ua = (unsigned int) a;
	unsigned int ub = (unsigned int）b;
	while (b != 0u) {
		unsigned int carry = (ua & ub) << 1;
		ua = ua ^ ub;
		ub = carry;
	}
	return (int)ua;
}
```
### 2.十进制的有符号整数（或无符号整数）与32位二进制之间的互换
``` c
char *toBinaryString(int n, char *buffer) {
	for (int i = 31; i >= 0; i--) {
		buffer[i] = (n & 1) ? '1' : '0';
		n = n >> 1;
	}
	buffer[32] = '\0';		// 记得添加结束符
	return buffer;
}

int fromBinaryString(const char *binaryString) {
	int result = 0;
	for (int i = 0; i <= 31; i++) {
		int num = (binaryString[i] - '0');
		result = result * 2 + num;
		// 或写成
		// result = (result << 1) | (binaryString[i] - '0');
	}
	return result;
}
```
### 3.前后缀乘积