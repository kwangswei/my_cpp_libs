/*
 * binary.cpp
 *
 *  Created on: 2014. 2. 11.
 *      Author: kwangswei
 */
#include <string>

using namespace std;

string bin(int num) {
    if (num <= 1)
        return num & 1 ? "1" : "0";
    return bin(num >> 1) + (num & 1 ? "1" : "0");
}

int bitCount(int num) {
    int count = 0;
    while (num != 0) {
        num &= num - 1;
        count++;
    }
    return count;
}

long long toInt(string bits, int base = 2) {
    long long result = 0;
    for (auto i = 0; i < bits.size(); ++i) {
        result *= base;
        result += bits[i] - '0';
    }
    return result;
}



