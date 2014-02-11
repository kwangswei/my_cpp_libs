/*
 * math.cpp
 *
 *  Created on: 2014. 2. 11.
 *      Author: kwangswei
 */
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

map<int, int> factorize(long long num) {
    map<int, int> result;
    int mul = 2;

    while (num != 1) {
        if (num % mul == 0) {
            result[mul]++;
            num /= mul;
        }
        else
            mul++;
    }

    return result;
}




