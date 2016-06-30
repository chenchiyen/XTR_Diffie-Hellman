//
//  GaloisField.hpp
//  XTR
//
//  Define GF(P) and the operations needed
//
//  101062212
//  Created by chenchiyen on 6/17/16.
//  Copyright © 2016 chenchiyen. All rights reserved.
//

#ifndef GaloisField_hpp
#define GaloisField_hpp

#include <iostream>
#include <sstream>
#include "BigNumber.hpp"

class GFP{
private:
    BigNumber extend_eculidean(BigNumber a, BigNumber b) const;
public:
    // member
    static BigNumber mod_prime; // let all Finite Field Share the same memory
    BigNumber i;
    
    // constructors
    GFP();
    GFP(int); // directly convert from an int
    GFP(const std::string&);
    GFP(BigNumber);
    
    // overloaded logical operators as member functions
    friend bool operator==(const GFP&, const GFP&);
    friend bool operator!=(const GFP&, const GFP&);
    friend bool operator>(const GFP&, const GFP&);
    friend bool operator<(const GFP&, const GFP&);
    friend bool operator>=(const GFP&, const GFP&);
    friend bool operator<=(const GFP&, const GFP&);
    
    // overloaded arithmetic operators as member functions
    friend const GFP operator+(const GFP&, const GFP&);
    friend const GFP operator-(const GFP&, const GFP&);
    friend const GFP operator*(const GFP&, const GFP&);
    friend const GFP operator/(const GFP&, const GFP&);
    friend const GFP operator%(const GFP&, const GFP&);
    friend const GFP operator-(const GFP&); // negation
    
    friend const GFP inv(const GFP&);
    
    // ouput format for GFP
    friend std::ostream& operator<<(std::ostream&, const GFP&);
    
};

#endif