﻿#pragma once
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdint>

// ----------------------------------------------------------------------------
// |represent range: from −170,141,183,460,469,231,731,687,303,715,884,105,728|
// |to 170,141,183,460,469,231,731,687,303,715,884,105,727                    |
// ----------------------------------------------------------------------------
std::vector<bool> BinStrToVectorBool(std::string binStr);
class QInt final
{
public:
	// Default Constructor, assign to 0
	QInt();
	// long long Constructor, convert a long long to QInt
	QInt(long long x);
	// Recommended Constructor
	// string Constructor, convert a string represent a number to QInt
	// if number is more than 127 character throw an out_of_range exception
	// if input string is not a number, throw an invalid_argument exception
	QInt(std::string number);
	// bits Constructor, convert a vector of bool to QInt
	// if the vector's size is larger than 128, the superfluous part will be cut 
	QInt(std::vector<bool> bits);
	// string Constructor, convert a string represent a Hex to QInt
	// Destructor
	virtual ~QInt();
	// Use default copy constructor
	QInt(const QInt& others) = default;
	// convert QInt to a string represent it in decimal form
	std::string to_string() const;
	// convert QInt to a string represent it in binary form
	std::string to_binary_string() const;
	// convert QInt to a string represent it in hex form
	std::string to_hex() const;
	
	// rotate the QInt [time] times to the left
	QInt& rol(QInt time);
	// rotate the QInt [time] times to the right
	QInt& ror(QInt time);

	// convert a binary (represent by a vector of bools)
	// to a hexadecimal (represent by a string)
	static std::string BintoHex(std::vector<bool> bits);
	// Multiply 2 big numbers represent by strings
	static std::string bigNumMultiply(std::string & num1, std::string num2);
	// Add 2 big numbers represent by strings
	static std::string bigNumAdd(std::string& num1, std::string& num2);
	// Subtract 2 big numbers represent by strings
	static std::string bigNumMinus(std::string& num1, std::string& num2);
	// Convert Hex to Bin
	static std::string HextoBin(std::string Hex);
	//C\get an QInt from Hex
	static QInt HexToQint(std::string Hex);

	// basic arithmetic operators for QInt
	friend QInt operator+(const QInt& lhs, const QInt& rhs);
	friend QInt operator-(const QInt& lhs, const QInt& rhs);
	friend QInt operator*(const QInt& lhs, const QInt& rhs);
	friend QInt operator/(const QInt& lhs, const QInt& rhs);
	friend QInt operator<<(const QInt& lhs, QInt shift);
	friend QInt operator>>(const QInt& lhs, QInt shift);
	friend QInt operator&(const QInt& lhs, const QInt& rhs);
	friend QInt operator|(const QInt& lhs, const QInt& rhs);
	friend QInt operator^(const QInt& lhs, const QInt& rhs);
	friend QInt operator~(const QInt& lhs);
	// convert a QInt to bool (false if that QInt is 0, true if not)
	operator bool() const;

	// overload the in-out operator for iostreams
	friend std::istream& operator>>(std::istream& stream, QInt& rhs);
	friend std::ostream& operator<<(std::ostream& stream, const QInt& rhs);

    // basic assign arithmetic operators for QInt
	QInt& operator+=(const QInt& rhs);
	QInt& operator-=(const QInt& rhs);
	QInt& operator*=(const QInt& rhs);
	QInt& operator/=(const QInt& rhs);
	QInt& operator<<=(QInt shift);
	QInt& operator>>=(QInt shift);
	QInt& operator&=(const QInt& rhs);
	QInt& operator|=(const QInt& rhs);
	QInt& operator^=(const QInt& rhs);

	// check if this QInt is a negative
	// can be delete if there is comparision
	bool isNegative() const;
	// change this QInt to 2's complement notation
	void to2ndComplement();
private:
	int64_t m_high;
	uint64_t m_low;

	// get bitset of QInt
	// return a vector of bool represent the bitset
	std::vector<bool> getBitset() const;
	// save a bitset represent in a vector of bools to this Qint
	void saveBits(std::vector<bool> &bits);
	//set N'th bit to value val
	void setNBit(int pos, bool val);
	// check if a string is representing a number
	static bool isAllDigits(const std::string &str) {
		return str.find_first_not_of("0123456789") == std::string::npos;
	}

	// divide a number represent by a string by 2
	// use exclusive to convert a number to binary
	static std::string divideBy2(std::string & input);
};

