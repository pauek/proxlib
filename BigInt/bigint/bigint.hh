#ifndef PRO2_BIGINT_HH
#define PRO2_BIGINT_HH

#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

namespace pro2 {

class bigint {
   public:
	bigint() : digits(1, 0), sign(0) {}

	bigint(int64_t n) : digits(1, n) {
		if (n < 0) {
			sign = -1;
		} else if (n > 0) {
			sign = 1;
		} else {
			sign = 0;
		}
	}

	bigint(const char *str) {
		std::string s(str);
		if (s.empty()) {
			digits.push_back(0);
			sign = 0;
			return;
		}
		sign = (s[0] == '-' ? sign = -1 : sign = 1);
		uint64_t digit = 0;
		for (const char& c : s) {
			digit = digit * 10 + (c - '0');
			if (digit >= MAX_DIGIT) {
				digits.push_back(digit);
				digit = 0;
			}
		}
	}

	bigint(const bigint& b) : digits(b.digits) {}

	bigint& operator=(const bigint& b) {
		digits = b.digits;
		return *this;
	}

	bigint operator+(const bigint& b) const {
		if (sign == b.sign) {
			return _addition(sign, digits, b.digits);
		} else {
			if (digits.size() >= b.digits.size()) {
				return _addition(digits, b.digits);
			} else {
				return _addition(b.digits, digits);
			}
		}
	}

	bigint operator-(const bigint& b) const { return bigint(); }

	friend std::ostream& operator<<(std::ostream& o, const bigint& bi);

   private:
	static const uint64_t MAX_DIGIT = 1000000000000000000L;

	typedef std::vector<uint64_t> vec_digits;
	int8_t						  sign = 0;

	vec_digits digits;

	bigint(int8_t sign, vec_digits& d) : sign(sign), digits(std::move(d)) {}

	/**
	 * Pre: adigits.size() > bdigits.size()
	 */
	bigint _addition(uint8_t sign, const vec_digits& adigits, const vec_digits& bdigits) const {
		vec_digits result(adigits.size(), 0);
		uint64_t   carry = 0;
		size_t	   i = 0;
		while (i < bdigits.size()) {
			__uint128_t sum = (adigits[i] + bdigits[i] + carry);
			result[i] = static_cast<uint64_t>(sum % MAX_DIGIT);
			carry = static_cast<uint64_t>(sum / MAX_DIGIT);
			i++;
		}
		while (i < adigits.size()) {
			__uint128_t sum = adigits[i] + carry;
			result[i] = static_cast<uint64_t>(sum % MAX_DIGIT);
			carry = static_cast<uint64_t>(sum / MAX_DIGIT);
			i++;
		}
		if (carry) {
			result.push_back(carry);
		}
		return bigint(sign, result);
	}

    /**
     * Pre: abs(a) > abs(b)
     */
    bigint _subtraction(uint8_t sign, const vec_digits& adigits, const vec_digits& bdigits) const {
        vec_digits result(adigits.size(), 0);
        uint64_t   carry = 0;
        size_t     i = 0;
        while (i < bdigits.size()) {
            __int128_t sum = (adigits[i] - bdigits[i] + carry);
            result[i] = static_cast<uint64_t>(sum % MAX_DIGIT);
            carry = static_cast<uint64_t>(sum / MAX_DIGIT);
            i++;
        }
        while (i < adigits.size()) {
            __int128_t sum = adigits[i] - carry;
            result[i] = static_cast<uint64_t>(sum % MAX_DIGIT);
            carry = static_cast<uint64_t>(sum / MAX_DIGIT);
            i++;
        }
        if (carry) {
            result.push_back(carry);
        }
        return bigint(sign, result);
    }
};

std::ostream& operator<<(std::ostream& o, const bigint& bi) {
	assert(bi.digits.size() > 0);
	const size_t sz = bi.digits.size();
	o << bi.digits[sz - 1];
	if (bi.digits.size() > 1) {
		for (size_t i = sz - 2; i >= 0; --i) {
			o << bi.digits[i - 1];
		}
	}
	return o;
}

}  // namespace pro2

#endif