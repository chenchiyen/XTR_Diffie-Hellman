//
//  GFP2.cpp
//  XTR
//
//  Implement operations in GF(P^2)
//
//  101062212
//  Created by chenchiyen on 6/17/16.
//  Copyright © 2016 chenchiyen. All rights reserved.
//

#include "GFP2.hpp"
// constructors
GFP2::GFP2() {
    this->first = 0;
    this->second = 0;
    
}
GFP2::GFP2(const GFP& first, const GFP& second) {
    this->first = first;
    this->second = second;
}
/**
 *  alpha^2 + alpha + 1 = 0
 *  1 = - alpha - alpha^2
 */
GFP2::GFP2(const GFP& ele) {
    this->first = -ele;
    this->second = -ele;
}
// overloaded arithmetic operators as member functions
const GFP2 operator+(const GFP2& lhs, const GFP2& rhs) {
    return GFP2(lhs.first + rhs.first, lhs.second + rhs.second);
}

const GFP2 operator-(const GFP2& lhs, const GFP2& rhs) {
    return GFP2(lhs.first - rhs.first, lhs.second - rhs.second);
}

/**
 *  z = x * y
 *
 *  z1 = x2 * y2 - (x1 * y2 + x2 * y1)
 *  z2 = x1 * y1 - (x1 * y2 + x2 * y1)
 */
const GFP2 operator*(const GFP2& lhs, const GFP2& rhs) {
    GFP temp = lhs.first * rhs.second + lhs.second * rhs.first;
    GFP first = lhs.second * rhs.second - temp;
    GFP second = lhs.first * rhs.first - temp;
    return GFP2(first, second);
}
// negation
const GFP2 operator-(const GFP2& rhs) {
    return GFP2(-rhs.first, -rhs.second);
}
/**
 *  y = n * x
 *
 *  y1 = n * x1
 *  y2 = n * x2
 */
const GFP2 operator*(const GFP& lhs, const GFP2& rhs) {
    GFP first = lhs * rhs.first;
    GFP second = lhs * rhs.second;
    return GFP2(first, second);
}
/**
 *  y = x^p
 *
 *  y1 = x2
 *  y2 = x1
 */
GFP2 power_p(GFP2& base) {
    return GFP2(base.second, base.first);
}
/**
 *  y = x^2
 *
 *  y1 = x2 * x2 - 2 * x1 * x2
 *  y2 = x1 * x1 - 2 * x1 * x2
 */
GFP2 power_2(GFP2& base) {
    GFP temp = 2 * base.first * base.second;
    GFP first = base.second * base.second - temp;
    GFP second = base.first * base.first - temp;
    
    return GFP2(first, second);
}

// ouput format for GFP2
std::ostream& operator<<(std::ostream& os, const GFP2& e) {
    os << "(" << e.first << ", " << e.second << ")";
    return os;
}
