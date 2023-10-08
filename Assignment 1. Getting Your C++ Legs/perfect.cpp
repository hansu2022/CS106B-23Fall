/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "console.h"
#include <iostream>
#include "SimpleTest.h"
#include "perfect.h"
#include <cmath>
using namespace std;

/* The divisorSum function takes one argument `n` and calculates the
 * sum of proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division using the modulus operator %
 *
 * Note: the C++ long type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long divisorSum(long n) {
    long total = 0;
    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

/* The isPerfect function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* The findPerfects function takes one argument `stop` and performs
 * an exhaustive search for perfect numbers over the range 1 to `stop`.
 * Each perfect number found is printed to the console.
 */
void findPerfects(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* smarterSum 接受一个参数"n"进行计算
 * 求除自身之外的真因数之和
 * 循环迭代到1到n的平方根
 * 因为n有因子a，它必有与之匹配的因子b，因为a*b=n
 * 所以我们只要寻找小于或等于n的平方根的因子即可
 */
long smarterSum(long n) {
    /* TODO: Fill in this function. */
    long total = 0;
    if(n==1){
        return total;
    }
    int n1;
    for (long divisor = 2; divisor < sqrt(n); divisor++) {
        if (n % divisor == 0) {
            n1 = n / divisor;
            total += divisor + n1;
        }
    }
    total++;
    return total;
}

/* isPerfectSmarter函数接受一个参数n，并返回一个布尔值（true/false），指示n是否是完美数。完美数是一个非零正数，其真正除数的和等于它本身。
 */
bool isPerfectSmarter(long n) {
    return (n != 0) && (n == smarterSum(n));
}

/* findNthPerfectEuclid函数接受一个参数n，并在范围从1到n内执行对完美数的详尽搜索。找到的每个完美数都会被打印到控制台。
 */
void findPerfectsSmarter(long stop) {
     /* TODO: Fill in this function. */
    for (long num = 1; num < stop; num++) {
        if (isPerfectSmarter(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* 查找第n个完美数，它使用欧几里得的方法
 * 其中k是梅森指数，m是梅森数，pn是完美数，j用于计数。
 * 在每次迭代中，它计算梅森数，然后检查它是否是素数，如果是素数，则计算相应的完美数，并增加j以跟踪找到的完美数的数量。
 * 最终，它返回第n个完美数。
 */
long findNthPerfectEuclid(long n) {
    /* TODO: Fill in this function. */
    int k = 1;       // 初始梅森指数为1
    int m = 0;       // 存储梅森数
    int pn;          // 存储完美数
    int j = 0;       // 计数器，用于跟踪找到的完美数数量

    while (j != n) {  // 当找到第n个完美数之前，继续搜索
        m = pow(2, k) - 1;  // 计算梅森数，2^k - 1

        if (divisorSum(m) == 1) {  // 如果梅森数是素数（其除数之和为1）
            pn = pow(2, k - 1) * (pow(2, k) - 1);  // 计算对应的完美数
            j++;  // 增加找到的完美数计数
        }

        k++;  // 增加梅森指数以检查下一个梅森数
    }

    return pn;  // 返回第n个完美数
}


/* * * * * * Test Cases * * * * * */

// TODO: add your STUDENT_TEST test cases here!
STUDENT_TEST("28的total是否等于28"){
    EXPECT_EQUAL(smarterSum(28), 28);
}
STUDENT_TEST("质数7的total是否等于1"){
    EXPECT_EQUAL(smarterSum(7), 1);
}
STUDENT_TEST("验证6和28和122是否为完美数"){
    EXPECT(isPerfectSmarter(6));
    EXPECT(isPerfectSmarter(28));
    EXPECT(!isPerfectSmarter(122));
}
STUDENT_TEST("Time trial of findPerfects on input size 1000") {
    TIME_OPERATION(1000, findPerfectsSmarter(1000));
}
STUDENT_TEST("验证第五个是不是完美数"){
    EXPECT_EQUAL(findNthPerfectEuclid(2), 28);
}
STUDENT_TEST("验证第五个是不是完美数"){
    EXPECT(isPerfect(findNthPerfectEuclid(5)));
}



/*
 * Here is sample test demonstrating how to use a loop to set the input sizes
 * for a sequence of time trials.
 */
//STUDENT_TEST("Multiple time trials of findPerfects on increasing input sizes") {
//    int smallest = 1000, largest = 8000;
//    for (int size = smallest; size <= largest; size *= 2) {
//        TIME_OPERATION(size, findPerfects(size));
//    }
//}


/* Please not add/modify/remove the PROVIDED_TEST entries below.
 * Place your student tests cases above the provided tests.
 */

PROVIDED_TEST("Confirm divisorSum of small inputs") {
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

PROVIDED_TEST("Confirm 6 and 28 are perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("Confirm 12 and 98765 are not perfect") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Test oddballs: 0 and 1 are not perfect") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
}

PROVIDED_TEST("Confirm 33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

PROVIDED_TEST("Time trial of findPerfects on input size 1000") {
    TIME_OPERATION(1000, findPerfects(1000));

}

