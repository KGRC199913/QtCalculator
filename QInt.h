#pragma once
#include <bitset>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdint>

class QInt
{
public:
	QInt();
	QInt(long long &x);
	QInt(std::string number);
	virtual ~QInt();
	void scanInput(std::istream &stream = std::cin);
	void printOutput(std::ostream &stream = std::cout);
	std::string to_string();
	std::string to_binary_string();
	std::string to_hex();
	
	static std::string BintoHex(std::vector<bool> bits);
	static std::string bigNumMultiply(std::string & num1, std::string num2);
	static std::string bigNumAdd(std::string& num1, std::string& num2);
	static std::string bigNumMinus(std::string& num1, std::string& num2);

	friend QInt operator+(const QInt& lhs, const QInt& rhs);
	friend QInt operator-(const QInt& lhs, const QInt& rhs);
	friend QInt operator*(const QInt& lhs, const QInt& rhs);
	friend QInt operator/(const QInt& lhs, const QInt& rhs);
private:
	int64_t high;
	uint64_t low;

	std::vector<bool> getBitset() const;
	void saveBits(std::vector<bool> &bits);
	void to2ndComplement();

	static bool isAllDigits(const std::string &str) {
		return str.find_first_not_of("0123456789") == std::string::npos;
	}

	static std::string divideBy2(std::string & input);
};

