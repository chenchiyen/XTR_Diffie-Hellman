//
//  BigNumber.cpp
//  XTR
//
//  Implement big number operations
//
//  101062212
//  Created by chenchiyen on 6/17/16.
//  Copyright © 2016 chenchiyen. All rights reserved.
//

#include "BigNumber.hpp"

// constructor
BigNumber::BigNumber() {
    BigNumber(0);
}

BigNumber::BigNumber(int input_number) {
    int unsign_number;
    
    // determine its positive(true) or negative(false)
    sign = (input_number < 0)? false: true;
    
    // make number positive
    unsign_number = (input_number < 0)? -input_number:input_number;
    
    // turn this integer to hex and store it to data
    while (unsign_number >= 16) {
        num.push_back(unsign_number % 16); // mod 16
        unsign_number = unsign_number / 16; // div 16
    }
    num.push_back(unsign_number);
}

BigNumber::BigNumber(const std::string& input_string) {
    sign = !(input_string.front() == '-');
    
    for (auto i = input_string.rbegin(), end = input_string.rend(); i != end; i++) {
        if (*i >= '0' && *i <= '9') {
            num.push_back(*i - '0');
        } else if (*i >= 'A' && *i <= 'F') {
            num.push_back(*i - 'A' + 10);
        } else if (*i >= 'a' && *i <= 'f') {
            num.push_back(*i - 'a' + 10);
        }
    }
    BigNumber::clearFrontZero(num);
}

BigNumber::BigNumber(bool input_sign, const std::vector<int8_t>& input_data) {
    sign = input_sign;
    num = input_data;
}
/*
BigNumber::BigNumber(bool input_sign, std::vector<int8_t>&& input_data) {
    sign = input_sign;
    data = std::move(input_data);
}
*/


// logical operators
bool operator==(const BigNumber& lhs, const BigNumber& rhs) {
    return (lhs.sign == rhs.sign) && (BigNumber::absCmp(lhs, rhs) == 0);
}

bool operator!=(const BigNumber& lhs, const BigNumber& rhs) {
    return !(lhs == rhs);
}

bool operator>(const BigNumber& lhs, const BigNumber& rhs) {
    int abs_cmp;
    
    if (lhs.sign == rhs.sign) {
        abs_cmp = BigNumber::absCmp(lhs, rhs);
        return ((lhs.sign && abs_cmp == 1) || (!lhs.sign && abs_cmp == -1));
    } else {
        return lhs.sign;
    }
}

bool operator<(const BigNumber& lhs, const BigNumber& rhs) {
    return rhs > lhs;
}

bool operator>=(const BigNumber& lhs, const BigNumber& rhs) {
    return !(lhs < rhs);
}

bool operator<=(const BigNumber& lhs, const BigNumber& rhs) {
    return !(lhs > rhs);
}


// private method
int BigNumber::absCmp(const BigNumber& lhs, const BigNumber& rhs) {
    // 1: >, 0: =, -1: <
    if (lhs.num.size() > rhs.num.size()) {
        return 1;
    } else if (lhs.num.size() < rhs.num.size()) {
        return -1;
    }
    
    // same size
    for (auto i = lhs.num.rbegin(), j = rhs.num.rbegin(), end = lhs.num.rend(); i != end; i++, ++j) {
        if(*i > *j) {
            return 1;
        } else if (*i < *j) {
            return -1;
        }
    }
    
    return 0;
}

void BigNumber::clearFrontZero(std::vector<int8_t>& input) {
    while (input.back() == 0 && input.size()!=1) {
        input.pop_back();
    }
}


// arithmetic operators
const BigNumber operator+(const BigNumber& lhs, const BigNumber& rhs) {
    bool sign;
    std::vector<int8_t> result;
    unsigned long min_size;
    uint8_t carry, tmp_sum;
    
    if (lhs.num.size() >= rhs.num.size())    min_size = rhs.num.size();
    else min_size = lhs.num.size();
    
    // check is add or sub
    if (lhs.sign == rhs.sign) {
        // same sign
        sign = lhs.sign;
        carry = 0;
        
        // add with min size and handle carry
        for (unsigned long i=0; i<min_size; i++) {
            tmp_sum = lhs.num.at(i) + rhs.num.at(i) + carry;
            carry = tmp_sum/16;
            tmp_sum %= 16;
            result.push_back(tmp_sum);
        }
        // deal with remend digit and deal with carry
        if (lhs.num.size() >= rhs.num.size()) {
            for (unsigned long i=min_size; i<lhs.num.size(); i++) {
                tmp_sum = lhs.num.at(i) + carry;
                carry = tmp_sum/16;
                tmp_sum %= 16;
                result.push_back(tmp_sum);
            }
        } else {
            for (unsigned long i=min_size; i<rhs.num.size(); i++) {
                tmp_sum = rhs.num.at(i) + carry;
                carry = tmp_sum/16;
                tmp_sum %= 16;
                result.push_back(tmp_sum);
            }
        }
        if (carry>0)    result.push_back(carry);
    } else {
        if (!lhs.sign) {
            return rhs - BigNumber(!lhs.sign, lhs.num);
        } else {
            return lhs - BigNumber(!rhs.sign, rhs.num);
        }
    }
    
    return BigNumber(sign, result);
}

const BigNumber operator-(const BigNumber& lhs, const BigNumber& rhs) {
    bool sign;
    std::vector<int8_t> result;
    unsigned long min_size;
    
    // see if they are same sign
    if (lhs.sign==rhs.sign) {
        // see if equal
        if (BigNumber::absCmp(lhs, rhs) == 0) {
            return BigNumber(0);
        }
        // see if lhs is larger
        else if (BigNumber::absCmp(lhs, rhs) == 1) {
            sign = lhs.sign;
            // substract all digit first
            min_size = rhs.num.size();
            result.resize(lhs.num.size());
            std::transform(lhs.num.begin(), lhs.num.begin()+min_size, rhs.num.begin(), result.begin(), std::minus<int8_t>());
            
            // insert remain digits
            std::copy(lhs.num.begin() + min_size, lhs.num.end(), result.begin() + min_size);
        }
        else {
            sign = !lhs.sign;
            // substract all digit first
            min_size = lhs.num.size();
            result.resize(rhs.num.size());
            std::transform(rhs.num.begin(), rhs.num.begin() + min_size, lhs.num.begin(), result.begin(), std::minus<int8_t>());
            
            // insert remain digits
            std::copy(rhs.num.begin() + min_size, rhs.num.end(), result.begin() + min_size);
        }
        // handle borrow
        for (unsigned long i = 0; i < result.size(); i++) {
            if (result.at(i) < 0){
                result.at(i) += 16;
                result.at(i+1)--;
            }
        }
        /* remove the redundant 0s from front */
        /* result might be 000000abd332, then it should be abd332 */
        BigNumber::clearFrontZero(result);
    }
    else {
        /* if lhs, rhs with different sign, then a-(-b) = a+b and -a-b = -(a+b), can be treated as addition */
        return lhs + BigNumber(lhs.sign, rhs.num);
    }
    
    return BigNumber(sign, result);
}

const BigNumber operator*(const BigNumber& lhs, const BigNumber& rhs) {
    bool sign;
    std::vector<int8_t> result;
    
    /* multiply by 0 */
    if(lhs == 0 || rhs == 0){
        return BigNumber(0);
    }
    
    if (lhs.sign == rhs.sign)   sign = true;
    else sign = false;
    
    result.resize(lhs.num.size()+rhs.num.size()+1, 0);
    int16_t sum = 0;
    for(unsigned long i = 0; i < lhs.num.size(); i++){
        for(unsigned long j = 0; j < rhs.num.size(); j++){
            sum = result.at(i+j) + lhs.num.at(i) * rhs.num.at(j);
            result.at(i+j) = sum % 16; // sum
            result.at(i+j+1) += sum / 16; // carry
        }
    }
    /* remove the redundant 0s from front */
    /* result might be 000000abd332, then it should be abd332 */
    BigNumber::clearFrontZero(result);
    
    return BigNumber(sign, result);
}

const BigNumber operator/(const BigNumber& lhs, const BigNumber& rhs) {
    BigNumber temp(0);
    BigNumber remainder(true, lhs.num);
    BigNumber divisor(true, rhs.num);
    BigNumber quotient(0);
    quotient.sign = (lhs.sign == rhs.sign);
    
    if (lhs==0) return BigNumber(0);
    if (lhs<rhs)    return BigNumber(0);
    if (BigNumber::absCmp(lhs, rhs)==0) {
        if (lhs.sign==rhs.sign) return BigNumber(1);
        else    return BigNumber(-1);
    }
    
    int8_t count = 0;
    while (remainder.num.size() != 0) {
        while(temp < divisor && remainder.num.size() != 0) {
            temp.num.insert(temp.num.begin(), remainder.num.back());
            remainder.num.pop_back();
            quotient.num.insert(quotient.num.begin(), 0);
        }
        BigNumber::clearFrontZero(temp.num);
        
        count = 0;
        while (temp >= divisor) {
            count ++;
            temp = temp - divisor;
        }
        quotient.num.front() = count;
    }
    BigNumber::clearFrontZero(quotient.num);
    
    // make -0 -> +0
    if (quotient.num.size()==1 && quotient.num.back()==0) {
        quotient.sign = true;
    }
    
    return quotient;
}

const BigNumber operator%(const BigNumber& lhs, const BigNumber& rhs) {
    BigNumber temp(0);
    BigNumber remainder(true, lhs.num);
    BigNumber divisor(true, rhs.num);
    
    if (BigNumber::absCmp(lhs, rhs)==0) {
        return BigNumber(0);
    }
    if (BigNumber::absCmp(lhs, rhs)==-1) {
        return lhs;
    }
//    remainder = lhs - lhs/rhs;
    
    while (remainder >= divisor) {
        temp.num.assign(remainder.num.end() - divisor.num.size(), remainder.num.end());
        remainder.num.erase(remainder.num.end() - divisor.num.size(), remainder.num.end());
        if (temp < divisor){
            temp.num.insert(temp.num.begin(), remainder.num.back());
            remainder.num.pop_back();
        }
        
        BigNumber::clearFrontZero(temp.num);
        
        while (temp >= divisor) {
            temp = temp - divisor;
        }
        remainder.num.insert(remainder.num.end(), temp.num.begin(), temp.num.end());
        temp.num.clear();
    }
    BigNumber::clearFrontZero(remainder.num);
    remainder.sign = lhs.sign;
    // make -0 -> +0
    if (remainder.num.size()==1 && remainder.num.back()==0) {
        remainder.sign = true;
    }
    
    return remainder;
}


// output format
std::ostream& operator<<(std::ostream& os, const BigNumber& rhs) {
    int ct=1;
    
    if (!rhs.sign) {
        os << "-";
    }
    
    for (auto i = rhs.num.rbegin(); i!= rhs.num.rend(); i++, ct++) {
        if (*i >= 10) {
            os << static_cast<char>(*i + 'A' - 10);
        } else {
            os << static_cast<char>(*i + '0');
        }
        if (ct>0 && ct%8==0) {
            os << " ";
        }
    }
    
    return os;
}

// transfer into binary representation
std::string BigNumber::to_binary() const{
    std::stringstream ss;
    std::string str;
    
    for (auto i = (*this).num.rbegin(); i!= (*this).num.rend(); i++ ) {
        ss << ((*i & 8) >> 3);
        ss << ((*i & 4) >> 2);
        ss << ((*i & 2) >> 1);
        ss << ((*i & 1));
    }
    ss >> str;
    
    while(str[0]=='0') {
        str.erase(str.begin());
    }
    return str;
}
