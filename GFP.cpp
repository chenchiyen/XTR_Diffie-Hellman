//
//  GFP.cpp
//  XTR
//
//  Implement operations in GF(P^2)
//
//  101062212
//  Created by chenchiyen on 6/17/16.
//  Copyright © 2016 chenchiyen. All rights reserved.
//

#include "GFP.hpp"
// Initial Finite Field Prime Number
BigNumber GFP::mod_prime = 1;

BigNumber GFP::extend_eculidean(BigNumber a, BigNumber b) const {
    BigNumber q, x, lastx, temp1, temp2;
    x=0;
    lastx=1;

    while (b!=0) {
        q= a/b;
        temp1= a%b;
        a=b;
        b=temp1;
        
        temp2 = x;
        x=lastx-q*x;
        lastx = temp2;
    }
    return lastx;
}



// constructors
GFP::GFP() {
    this->i = BigNumber(0);
}

GFP::GFP(int input) {
    this->i = input % mod_prime;
}

GFP::GFP(const std::string& input) {
    this->i = BigNumber(input) % mod_prime;
    
}

GFP::GFP(BigNumber input) {
    this->i = input % mod_prime;
}


// overloaded logical operators as member functions
bool operator==(const GFP& lhs, const GFP& rhs) {
    return lhs.i == rhs.i;
}

bool operator!=(const GFP& lhs, const GFP& rhs) {
    return lhs.i != rhs.i;
}

bool operator>(const GFP& lhs, const GFP& rhs) {
    return lhs.i > rhs.i;
}

bool operator<(const GFP& lhs, const GFP& rhs) {
    return lhs.i < rhs.i;
}

bool operator>=(const GFP& lhs, const GFP& rhs) {
    return lhs.i >= rhs.i;
}

bool operator<=(const GFP& lhs, const GFP&rhs) {
    return lhs.i <= rhs.i;
}


// arithmetic
const GFP operator+(const GFP& lhs, const GFP& rhs) {
    BigNumber add = lhs.i + rhs.i;
    if (add < 0) {
        add = rhs.mod_prime + add;
    }
    
    return GFP(add % rhs.mod_prime);
}

const GFP operator-(const GFP& lhs, const GFP& rhs) {
    BigNumber sub = lhs.i - rhs.i;
    if (sub < 0) {
        sub = rhs.mod_prime + sub ;
    }
    return GFP(sub% rhs.mod_prime);
}

const GFP operator*(const GFP& lhs, const GFP& rhs) {
    BigNumber mul = lhs.i * rhs.i;
    if (mul < 0) {
        mul = rhs.mod_prime + mul;
    }
    return GFP(mul % rhs.mod_prime);
}

const GFP operator/(const GFP& lhs, const GFP& rhs) {
    BigNumber rhs_inv = inv(rhs).i;
    BigNumber div = lhs.i * rhs_inv % rhs.mod_prime;
    return GFP(div);
}

const GFP operator%(const GFP& lhs, const GFP& rhs) {
    BigNumber mod = lhs.i % rhs.i;
    if (mod < 0) {
        mod = rhs.mod_prime + mod;
    }
    return GFP(mod % rhs.mod_prime);
}

const GFP operator-(const GFP& rhs) {
    BigNumber sub = (rhs.mod_prime - rhs.i) % rhs.mod_prime;
    return GFP(sub);
}

const GFP inv(const GFP& rhs) {
    BigNumber result = rhs.extend_eculidean(rhs.i, rhs.mod_prime);
    BigNumber inv = result % rhs.mod_prime;
    if (inv < 0 ) {
        inv =  (rhs.mod_prime + inv) % rhs.mod_prime;
    }
    
    return GFP(inv);
}

// output
std::ostream& operator<<(std::ostream& os, const GFP& rhs) {
    os << rhs.i;
    return os;
}

