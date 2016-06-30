//
//  BigNumber.hpp
//  XTR
//
//  Define big number operations
//
//  101062212
//  Created by chenchiyen on 6/17/16.
//  Copyright © 2016 chenchiyen. All rights reserved.
//

#ifndef BigNumber_hpp
#define BigNumber_hpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <sstream>




// Big number class definition
class BigNumber{
private:
    bool sign; /* true:+, false:- */
    std::vector<int8_t> num;
    
    static void clearFrontZero(std::vector<int8_t>&);
    static int absCmp(const BigNumber&, const BigNumber&);

public:
    // constructors
    BigNumber();
    BigNumber(int); // create a big number from an int
    BigNumber(const std::string&);
    BigNumber(bool, const std::vector<int8_t>&);
    
    // overloaded logical operators as member functions
    friend bool operator==(const BigNumber&, const BigNumber&);
    friend bool operator!=(const BigNumber&, const BigNumber&);
    friend bool operator>(const BigNumber&, const BigNumber&);
    friend bool operator<(const BigNumber&, const BigNumber&);
    friend bool operator>=(const BigNumber&, const BigNumber&);
    friend bool operator<=(const BigNumber&, const BigNumber&);
    
    // overloaded arithmetic operators as member functions
    friend const BigNumber operator+(const BigNumber&, const BigNumber&);
    friend const BigNumber operator-(const BigNumber&, const BigNumber&);
    friend const BigNumber operator*(const BigNumber&, const BigNumber&);
    friend const BigNumber operator/(const BigNumber&, const BigNumber&);
    friend const BigNumber operator%(const BigNumber&, const BigNumber&);
    
    // ouput format for BigNumber
    friend std::ostream& operator<<(std::ostream&, const BigNumber&);
    
    // convert into binary string
    std::string to_binary() const;
    
};


#endif