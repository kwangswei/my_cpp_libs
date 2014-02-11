/*
 * main.cpp
 *
 *  Created on: 2014. 2. 11.
 *      Author: kwangswei
 */

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

map<int, int> factorize(long long num);
string bin(int num);
int bitCount(int num);
long long toInt(string bits, int base = 2);

int main() {
    map<int,int> result = {{2,1},{3,2},{5,1}};
    assert(result == factorize(90));

    assert(bin(90) == "1011010");
    assert(bin(0) == "0");
    assert(bin(1) == "1");
    assert(bin(7) == "111");

    assert(bitCount(90) == 4);
    assert(bitCount(0) == 0);
    assert(bitCount(1) == 1);
    assert(bitCount(7) == 3);

    assert(toInt("1011010") == 90);
    assert(toInt("0") == 0);
    assert(toInt("1") == 1);
    assert(toInt("111") == 7);

   assert(toInt("1011", 16) == 4113);

    cout << "All success" << endl;

    return 0;
}


