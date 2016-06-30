//
//  GFP2.hpp
//  XTR
//
//  Define GF(P^2) and the operations needed
//
//  101062212
//  Created by chenchiyen on 6/17/16.
//  Copyright © 2016 chenchiyen. All rights reserved.
//

#ifndef GaloisField2_hpp
#define GaloisField2_hpp

#include <iostream>
#include <sstream>
#include "GFP.hpp"

class GFP2{
public:
    GFP first;
    GFP second;
    
    // constructors
    GFP2();
    GFP2(const GFP&, const GFP&);
    GFP2(const GFP&);
    
    // overloaded arithmetic operators as member functions
    friend const GFP2 operator+(const GFP2&, const GFP2&);
    friend const GFP2 operator-(const GFP2&, const GFP2&);
    friend const GFP2 operator*(const GFP2&, const GFP2&);
    friend const GFP2 operator-(const GFP2&); // negation
    friend const GFP2 operator*(const GFP&, const GFP2&);
    
//    friend const GFP2 inv(const GFP2&);
    friend GFP2 power_p(GFP2& base);
    friend GFP2 power_2(GFP2& base);
    
    // ouput format for GFP2
    friend std::ostream& operator<<(std::ostream&, const GFP2&);
};

#endif