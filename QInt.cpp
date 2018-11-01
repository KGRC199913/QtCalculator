#include "QInt.h"

QInt::QInt()
{
	this->m_low = this->m_high = 0;
}

QInt::QInt(long long x)
{
	*this = QInt(std::to_string(x));
}

QInt::QInt(std::string number)
{
	bool isNegative = false;
	if (number[0] == '-') {
		number[0] = '0';
		isNegative = true;
	}
	auto not0pos = number.find_first_not_of('0');
	if (not0pos != std::string::npos)
		number.erase(0, not0pos);
	else 
		number = "";

	if (number.length() > 128)
		throw new std::out_of_range("Number too long");

	this->m_low = this->m_high = 0;
	if (number.length() == 0)
		return;
	
	if (!isAllDigits(number))
		throw new std::invalid_argument("NaN");

	std::vector<bool> bits(128);

	int lastDigit = 0;
	int bitIndex = 0;
	while (number != "0")
	{
		lastDigit = number[number.length() - 1] - '0';
		bits[bitIndex++] = lastDigit & 1;
		number = divideBy2(number);
	}
	
	if (isNegative) {
		saveBits(bits);
		this->to2ndComplement();
	}
	else
		saveBits(bits);
}

QInt::QInt(std::vector<bool> bits)
{
	if (bits.size() < 128)
		bits.insert(bits.end(), 128 - bits.size(), false);
	if (bits.size() > 128)
		bits.erase(bits.end() - 1 - (bits.size() - 128));
	this->saveBits(bits);
}


QInt::~QInt()
{
}

std::string QInt::to_string() const
{
	if (this->m_high == 0 && this->m_low == 0)
		return "0";
	long double tempNum;
	std::string tempString;
	std::string ans;
	int dotPos = 0;
	std::vector<bool> bits = getBitset();

	for (int i = 0; i < 127; ++i) {
		tempNum = bits[i] * pow(2, i);
		if (tempNum < DBL_EPSILON)
			continue;
		tempString = std::to_string(tempNum);
		dotPos = tempString.find_first_of(".");
		tempString.erase(dotPos, tempString.size() - dotPos);
		ans = bigNumAdd(ans, tempString);
	}

	if (bits[127])
	{
		tempString = "170141183460469231731687303715884105728";
		ans = bigNumMinus(ans, tempString);
	}
	
	return ans;
}

std::string QInt::to_binary_string() const
{
	std::string binary;
	std::vector<bool> bits = getBitset();

	for (int i = 0; i < 128; ++i) {
		binary = std::to_string(bits[i]) + binary;
	}

	return binary;
}

std::string QInt::to_hex() const
{
	std::string hex;
	std::string bin = this->to_binary_string();
	
	std::string tempStr;
	for (int i = 0; i < 32; ++i) {
		tempStr = bin.substr(4 * i, 4);
		if (tempStr == "0000")
			hex += "0";
		else
			if (tempStr == "0001")
				hex += "1";
			else
				if (tempStr == "0010")
					hex += "2";
				else
					if (tempStr == "0011")
						hex += "3";
					else
						if (tempStr == "0100")
							hex += "4";
						else
							if (tempStr == "0101")
								hex += "5";
							else
								if (tempStr == "0110")
									hex += "6";
								else
									if (tempStr == "0111")
										hex += "7";
									else
										if (tempStr == "1000")
											hex += "8";
										else
											if (tempStr == "1001")
												hex += "9";
											else
												if (tempStr == "1010")
													hex += "A";
												else
													if (tempStr == "1011")
														hex += "B";
													else
														if (tempStr == "1100")
															hex += "C";
														else
															if (tempStr == "1101")
																hex += "D";
															else
																if (tempStr == "1110")
																	hex += "E";
																else
																	hex += "F";
	}

	hex = "0x" + hex;
	return hex;
}

QInt & QInt::rol(unsigned time)
{
	std::vector<bool> bits = this->getBitset();

	bool temp = false;
	while (time > 0) {
		temp = bits[127];
		bits.erase(bits.end() - 1);
		bits.emplace(bits.begin(), temp);
		--time;
	}

	this->saveBits(bits);
	return *this;
}

QInt & QInt::ror(unsigned time)
{
	std::vector<bool> bits = this->getBitset();

	bool temp = false;
	while (time > 0) {
		temp = bits[0];
		bits.erase(bits.begin());
		bits.emplace_back(temp);
		--time;
	}

	this->saveBits(bits);
	return *this;
}

std::string QInt::divideBy2(std::string & number)
{
	std::string ans("");
	
	auto not0pos = number.find_first_not_of('0');
	if (not0pos != std::string::npos)
		number.erase(0, not0pos);

	int currDivideNumber = 0;
	for (size_t i = 0; i < number.length(); ++i) {
		currDivideNumber = currDivideNumber * 10 + (number[i] - '0');
		ans += (currDivideNumber / 2) + '0';
		currDivideNumber &= 1;
	}
 
	return ans;
}

std::string QInt::BintoHex(std::vector<bool> bits)
{
	QInt tempQInt;
	tempQInt.saveBits(bits);

	return tempQInt.to_hex();
}

std::string QInt::bigNumMultiply(std::string & num1, std::string num2)
{
	int l1 = num1.size();
	int l2 = num2.size();
	if (l1 == 0 || l2 == 0)
		return "0";
	bool isNegative = false;

	if (num1[0] == '-' && num2[0] == '-') {
		num1[0] = '0';
		num2[0] = '0';
	}
	else {
		if (num1[0] == '-') {
			isNegative = true;
			num1[0] = '0';
		} else
			if (num2[0] == '-') {
				isNegative = true;
				num2[0] = '0';
			}
	}

	{
		auto not0pos = num1.find_first_not_of('0');
		if (not0pos != std::string::npos)
			num1.erase(0, not0pos);
		not0pos = num2.find_first_not_of('0');
		if (not0pos != std::string::npos)
			num2.erase(0, not0pos);
	}

	l1 = num1.size();
	l2 = num2.size();
	std::vector<int> result(l1 + l2, 0);

	int i_n1 = 0;
	int i_n2 = 0;
	int carry = 0;

	int n1 = 0;
	int n2 = 0;
	for (int i = l1 - 1; i >= 0; i--)
	{
		carry = 0;
		n1 = num1[i] - '0';
 
		i_n2 = 0;
            
		for (int j = l2 - 1; j >= 0; j--)
		{ 
			n2 = num2[j] - '0';
 
			int sum = n1 * n2 + result[i_n1 + i_n2] + carry; 
			carry = sum / 10;

			result[i_n1 + i_n2] = sum % 10;

			++i_n2;
		}
 
		if (carry)
			result[i_n1 + i_n2] += carry;

		++i_n1;
	}

	std::string ans = "";
	for (size_t i = 0; i < result.size(); ++i) {
		ans = std::to_string(result[i]) + ans;
	}

	int not0pos = ans.find_first_not_of("0");
	if (not0pos != std::string::npos) {
		ans.erase(0, not0pos);
	}

	if (ans.length() == 0)
		return "0";

	if (isNegative)
		ans = "-" + ans;

	return ans;
}

std::string QInt::bigNumAdd(std::string & num1, std::string & num2)
{
	bool isNegative = false;
	if ((num1[0] == '-') && (num2[0] == '-')) {
		num1[0] = '0';
		num2[0] = '0';
		isNegative = !isNegative;
	}
	else {
		if (num1[0] == '-') {
			num1[0] = '0';
			return bigNumMinus(num2, num1);
		} else
			if (num2[0] == '-') {
				num2[0] = '0';
				return bigNumMinus(num1, num2);
			}
	}

	{
		auto not0pos = num1.find_first_not_of('0');
		if (not0pos != std::string::npos)
			num1.erase(0, not0pos);
		not0pos = num2.find_first_not_of('0');
		if (not0pos != std::string::npos)
			num2.erase(0, not0pos);
	}

	if (num1.length() > num2.length())
		std::swap(num1, num2);

	std::string ans = "";

	int n1 = num1.length(), n2 = num2.length();
	int diff = n2 - n1;

	int carry = 0;

	int sum = 0;
	for (int i = n1 - 1; i >= 0; i--)
	{
		sum = ((num1[i] - '0') +
			(num2[i + diff] - '0') +
			carry);
		ans += sum % 10 + '0';
		carry = sum / 10;
	}

	for (int i = n2 - n1 - 1; i >= 0; i--)
	{
		int sum = ((num2[i] - '0') + carry);
		ans += sum % 10 + '0';
		carry = sum / 10;
	}

	if (carry)
		ans += carry + '0';

	std::reverse(ans.begin(), ans.end());
	if (isNegative)
		ans = "-" + ans;

	return ans;
}

std::string QInt::bigNumMinus(std::string & num1, std::string & num2)
{
	if (num1[0] == '-' && num2[0] == '-') {
		num2[0] = '0';
		return bigNumAdd(num1, num2);
	}
	else {
		if (num2[0] == '-') {
			num2[0] = '0';
			return bigNumAdd(num1, num2);
		}
		if (num1[0] == '-') {
			num1[0] = '0';
			return "-" + bigNumAdd(num1, num2);
		}
	}

	{
		auto not0pos = num1.find_first_not_of('0');
		if (not0pos != std::string::npos)
			num1.erase(0, not0pos);
		not0pos = num2.find_first_not_of('0');
		if (not0pos != std::string::npos)
			num2.erase(0, not0pos);
	}

	bool isNegative = false;
	int n1 = num1.length(), n2 = num2.length();
	if ([&]() ->bool {
		if (n1 < n2)
			return true;
		if (n2 < n1)
			return false;

		for (int i = 0; i < n1; i++)
		{
			if (num1[i] < num2[i])
				return true;
			else if (num1[i] > num2[i])
				return false;
		}
		return false;
	}()) {
		std::swap(num1, num2);
		std::swap(n1, n2);
		isNegative = !isNegative;
	}
		

	int diff = n1 - n2; 
	std::string ans = "";

	int carry = 0;

	int sub = 0; //subtract
	for (int i = n2 - 1; i >= 0; i--)
	{
		sub = ((num1[i + diff] - '0') - (num2[i] - '0') - carry);
		if (sub < 0)
		{
			sub = sub + 10;
			carry = 1;
		}
		else
			carry = 0;

		ans += sub + '0';
	}

	sub = 0;
	for (int i = n1 - n2 - 1; i >= 0; i--)
	{
		if (num1[i] == '0' && carry)
		{
			ans += "9";
			continue;
		}

		sub = ((num1[i] - '0') - carry);
		if (i>0 || sub>0) 
			ans += sub + '0';
		carry = 0;
	}

	std::reverse(ans.begin(), ans.end());
	{
		auto not0pos = ans.find_first_not_of('0');
		if (not0pos != std::string::npos)
			ans.erase(0, not0pos);
	}

	if (isNegative)
		ans = "-" + ans;

	return ans;
}

QInt::operator bool() const
{
	return (this->m_high == 0 && this->m_low == 0);
}

QInt & QInt::operator+=(const QInt & rhs)
{
	*this = *this + rhs;
	return *this;
}

QInt & QInt::operator-=(const QInt & rhs)
{
	*this = *this - rhs;
	return *this;
}

QInt & QInt::operator*=(const QInt & rhs)
{
	*this = *this * rhs;
	return *this;
}

QInt & QInt::operator/=(const QInt & rhs)
{
	*this = *this / rhs;
	return *this;
}

QInt & QInt::operator<<=(unsigned shift)
{
	*this = *this << shift;
	return *this;
}

QInt & QInt::operator>>=(unsigned shift)
{
	*this = *this >> shift;
	return *this;
}

QInt & QInt::operator&=(const QInt & rhs)
{
	*this = *this & rhs;
	return *this;
}

QInt & QInt::operator|=(const QInt & rhs)
{
	*this = *this | rhs;
	return *this;
}

QInt & QInt::operator^=(const QInt & rhs)
{
	*this = *this | rhs;
	return *this;
}

std::vector<bool> QInt::getBitset() const
{
	std::vector<bool> bits(128);
	int64_t temp = this->m_low;

	for (int i = 0; i < 64; ++i) {
		bits[i] = (temp & 1);
		temp >>= 1;
	}

	temp = this->m_high;
	for (int i = 64; i < 128; ++i) {
		bits[i] = (temp & 1);
		temp >>= 1;
	}

	return bits;
}

void QInt::saveBits(std::vector<bool> &bits)
{
	for (int i = 63; i >=0; --i) {
		this->m_low <<= 1;
		this->m_low |= bits[i];
	}
	
	for (int i = 127; i >= 64; --i) {
		this->m_high <<= 1;
		this->m_high |= bits[i];
	}
}

void QInt::to2ndComplement()
{
	bool meet1bit = false;
	std::vector<bool> bits = getBitset();

	for (int i = 0; i < 128; ++i) {
		if (meet1bit)
			bits[i] = !bits[i];
		else {
			meet1bit = bits[i];
		}
	}

	saveBits(bits);
}

void QInt::setNBit(int pos, bool val)
{
	std::vector<bool> bits = this->getBitset();
	bits[pos] = val;
	this->saveBits(bits);
}

bool QInt::isNegative() const
{
	return (this->m_high < 0);
}

QInt operator+(const QInt & lhs, const QInt & rhs)
{
	std::vector<bool> lhsBits, rhsBits;
	lhsBits = lhs.getBitset();
	rhsBits = rhs.getBitset();

	std::vector<bool> sum(128);
	bool carry = 0;
	for (int i = 0; i < 128; ++i) {
		sum[i] = ((lhsBits[i] ^ rhsBits[i]) ^ carry);
		carry = ((lhsBits[i] & rhsBits[i]) 
			| (lhsBits[i] & carry))
			| (rhsBits[i] & carry);
	}

	QInt ans;
	ans.saveBits(sum);
	return ans;
}

QInt operator-(const QInt & lhs, const QInt & rhs)
{
	QInt rhs2sComplement = rhs;
	rhs2sComplement.to2ndComplement();

	return lhs + rhs2sComplement;
}

QInt operator*(const QInt & lhs, const QInt & rhs)
{
	std::vector<bool> rhsBits = rhs.getBitset();

	QInt temp = lhs, ans;

	for (int i = 0; i < 128; ++i) {
		if (rhsBits[i]) {
			ans += temp;
		}
		temp <<= 1;
	}
	
	return ans;
}

QInt operator/(const QInt & lhs, const QInt & rhs)
{
	bool isNegative = lhs.isNegative() ^ rhs.isNegative();
	
	std::vector<bool> lhsBits, rhsBits;

	QInt A, Q, M;
	Q = lhs;
	M = rhs;
	A = 0;
	
	bool carryBit = false;
	for (int i = 0; i < 128; ++i) {
		carryBit = false; // = 0
		if (A.isNegative()) {
			carryBit = Q.isNegative();
			A <<= 1;		
			Q <<= 1;			
			A.setNBit(0, carryBit);
			A += M;
		}
		else {
			carryBit = Q.isNegative();
			A <<= 1;
			Q <<= 1;
			A.setNBit(0, carryBit);
			A -= M;
		}

		Q.setNBit(0, !A.isNegative());
	}
	if (isNegative)
		Q.to2ndComplement();

	return Q;
}

QInt operator<<(const QInt & lhs, unsigned int shift)
{
	std::vector<bool> lhsBits = lhs.getBitset();
	while (shift > 0) {
		lhsBits.erase(lhsBits.end() - 1);
		lhsBits.emplace(lhsBits.begin(), false);
		--shift;
	}

	QInt result;
	result.saveBits(lhsBits);
	return result;

}

QInt operator>>(const QInt & lhs, unsigned int shift)
{
	std::vector<bool> lhsBits = lhs.getBitset();
	bool isNegative = *(lhsBits.end() - 1);

	while (shift > 0) {
		lhsBits.erase(lhsBits.begin());
		lhsBits.emplace_back(isNegative);
		--shift;
	}


	QInt result;
	result.saveBits(lhsBits);
	return result;
}

QInt operator&(const QInt & lhs, const QInt & rhs)
{
	std::vector<bool> lhsBits = lhs.getBitset(), rhsBits = rhs.getBitset();
	std::vector<bool> resultBits(128);

	for (int i = 0; i < 128; ++i)
		resultBits[i] = lhsBits[i] & rhsBits[i];

	QInt result;
	result.saveBits(resultBits);
	return result;
}

QInt operator|(const QInt & lhs, const QInt & rhs)
{
	std::vector<bool> lhsBits = lhs.getBitset(), rhsBits = rhs.getBitset();
	std::vector<bool> resultBits(128);

	for (int i = 0; i < 128; ++i)
		resultBits[i] = lhsBits[i] | rhsBits[i];

	QInt result;
	result.saveBits(resultBits);
	return result;
}

QInt operator^(const QInt & lhs, const QInt & rhs)
{
	std::vector<bool> lhsBits = lhs.getBitset(), rhsBits = rhs.getBitset();
	std::vector<bool> resultBits(128);

	for (int i = 0; i < 128; ++i)
		resultBits[i] = lhsBits[i] ^ rhsBits[i];

	QInt result;
	result.saveBits(resultBits);
	return result;
}

QInt operator~(const QInt & lhs)
{
	std::vector<bool> lhsBits = lhs.getBitset();
	std::vector<bool> resultBits(128);

	for (int i = 0; i < 128; ++i)
		resultBits[i] = !lhsBits[i];

	QInt result;
	result.saveBits(resultBits);
	return result;
}

std::istream& operator>>(std::istream & stream, QInt & rhs)
{
	std::string temp;
	stream >> temp;

	rhs = QInt(temp);
	return stream;
}

std::ostream& operator<<(std::ostream & stream, const QInt & rhs)
{
	stream << rhs.to_string();
	return stream;
}
