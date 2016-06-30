//
//  XTR.hpp
//  XTR
//
//  Define Sn and the functions that's necessary for XTR
//
//  101062212
//  Created by chenchiyen on 6/17/16.
//  Copyright © 2016 chenchiyen. All rights reserved.
//

#ifndef XTR_hpp
#define XTR_hpp

#include <iostream>
#include <vector>

#include "GFP2.hpp"

class Sn {
public:
    GFP2 c0;
    GFP2 c1;
    GFP2 c2;
    
    // constructors
    Sn();
    Sn(GFP2&, GFP2&, GFP2&);
};

// Corollary 2.35
// (i)   C{2n} = C{n}^2 - 2*(C{n})^p
GFP2 C_2n(GFP2 cn);

// (ii)  C{n+2} = C * C{n+1} - C^p * C{n} + C{n-1}
GFP2 C_n_plus_2(GFP2 c, GFP2 cn_prev , GFP2 cn, GFP2 cn_next);

// (iii) C{2n-1} = C{n-1} * C{n} - C^p * C{n}^p + C{n+1}^p
GFP2 C_2n_minus_1(GFP2 c, GFP2 cn_prev , GFP2 cn, GFP2 cn_next);


// (iv)  C{2n+1} = C{n+1} * C{n} - C * C{n}^p + C{n-1}^p
GFP2 C_2n_plus_1(GFP2 c, GFP2 cn_prev , GFP2 cn, GFP2 cn_next);


// Algorithm 2.37
// Sn = (c{n-1}, c{n}, c{n+1})
Sn calculate_Sn(BigNumber n, GFP2 c);

#endif