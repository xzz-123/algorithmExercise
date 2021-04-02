#pragma once
#include <vector>
#include <algorithm>
using namespace std;
//给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。
//保证base和exponent不同时为0
class ComputePower {
public:
	double Power(double base, int exponent) {

		bool isNegative = false;
		if (exponent < 0) {
			exponent = -exponent;
			isNegative = true;
		}
		double res = Pow(base, exponent);
		return isNegative ? 1 / res : res;
	}

	double Pow(double base, int exponent) {
		if (exponent == 0)return 1;
		if (exponent == 1)return base;
		double res = Pow(base, exponent / 2);
		res *= res;
		return exponent % 2 == 0 ? res : res * base;
	}
};