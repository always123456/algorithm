#include <stdio.h>

// LCR 190 :   使用位运算完成加法
// int addWithoutArithmetic(int a, int b) {
//     while (b != 0) {
//         int carry = (a & b) << 1;       // 获取进位位置
//         a = a ^ b;                      // 不进位加法
//         b = carry;
//     }
//     return a;
// }

// int addWithoutArithmetic_by_ai(int a, int b) {
//     unsigned int ua = (unsigned int)a;
//     unsigned int ub = (unsigned int)b;
//     while (ub != 0u) {
//         unsigned int carry = (ua & ub) << 1;
//         ua = ua ^ ub;
//         ub = carry;
//     }
//     return (int)ua;
// }

// int main() {
//     int dataA, dataB;
//     scanf("%d %d", &dataA, &dataB);

//     int result = addWithoutArithmetic_by_ai(dataA, dataB);

//     printf("%d\n", result);

//     return 0;
// }








// 给定一个无符号整数或者有符号整数，编写一个函数，返回其32位的二进制字符串表示形式。
// 打印一个int类型的二进制字符串的函数：
char *toBinaryString(int n, char *buffer) {
    for (int i = 31; i >= 0; i--) {
        buffer[i] = (n & 1) ? '1' : '0';
        n = n >> 1;
    }
    buffer[32] = '\0'; // 末尾添加字符串结束符
    return buffer;
}

// 给定一个32位二进制字符串，返回其对应的int类型整数的函数：（以补码形式解释）
int fromBinaryString(const char *binaryString) {
    int result = 0;
    for (int i = 0; i < 32; i++) {
        // result = (result << 1) | (binaryString[i] - '0');
        int num = binaryString[i] - '0';
        result = result * 2 + num;
    }

    return result;
}

int main() {
    int number;
    char binaryString[33];

    scanf("%d", &number);
    toBinaryString(number, binaryString);

    int result = fromBinaryString(binaryString);

    unsigned int unumber = (unsigned int)result;        // 4294967295

    printf("%s\n", binaryString);
    printf("%d\n", result);
    // printf("%u\n", unumber);

    return 0;
}