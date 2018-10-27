#pragma once
#include <bitset>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdint>

class QInt final
{
public:
	QInt();
	QInt(long long x);
	QInt(std::string number);
	QInt(std::vector<bool> bits);
	virtual ~QInt();
	std::string to_string() const;
	std::string to_binary_string() const;
	std::string to_hex() const;
	
	QInt& rol(unsigned time);
	QInt& ror(unsigned time);

	static std::string BintoHex(std::vector<bool> bits);
	static std::string bigNumMultiply(std::string & num1, std::string num2);
	static std::string bigNumAdd(std::string& num1, std::string& num2);
	static std::string bigNumMinus(std::string& num1, std::string& num2);

	friend QInt operator+(const QInt& lhs, const QInt& rhs);
	friend QInt operator-(const QInt& lhs, const QInt& rhs);
	friend QInt operator*(const QInt& lhs, const QInt& rhs);
	friend QInt operator/(const QInt& lhs, const QInt& rhs);
	friend QInt operator<<(const QInt& lhs, unsigned int shift);
	friend QInt operator>>(const QInt& lhs, unsigned int shift);
	friend QInt operator&(const QInt& lhs, const QInt& rhs);
	friend QInt operator|(const QInt& lhs, const QInt& rhs);
	friend QInt operator^(const QInt& lhs, const QInt& rhs);
	friend QInt operator~(const QInt& lhs);

	friend std::istream& operator>>(std::istream& stream, QInt& rhs);
	friend std::ostream& operator<<(std::ostream& stream, const QInt& rhs);

	QInt& operator+=(const QInt& rhs);
	QInt& operator-=(const QInt& rhs);
	QInt& operator*=(const QInt& rhs);
	QInt& operator/=(const QInt& rhs);
	QInt& operator<<=(unsigned shift);
	QInt& operator>>=(unsigned shift);
	QInt& operator&=(const QInt& rhs);
	QInt& operator|=(const QInt& rhs);
	QInt& operator^=(const QInt& rhs);
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

