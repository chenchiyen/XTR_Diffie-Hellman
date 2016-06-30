//
//  XTR.cpp
//  XTR
//
//  Implement corollary 2.35 and algorithm 2.37 from the paper
//
//  101062212
//  Created by chenchiyen on 6/17/16.
//  Copyright © 2016 chenchiyen. All rights reserved.
//

#include "XTR.hpp"

// constructors
Sn::Sn() {
    this->c0 = GFP2();
    this->c1 = GFP2();
    this->c2 = GFP2();
}
Sn::Sn(GFP2& cn_prev, GFP2& cn, GFP2& cn_next) {
    this->c0 = cn_prev;
    this->c1 = cn;
    this->c2 = cn_next;
}

// C{2n} = C{n}^2 - 2*(C{n})^p
GFP2 C_2n(GFP2 cn) {
    return power_2(cn) - 2 * power_p(cn);
}

// C{n+2} = C * C{n+1} - C^p * C{n} + C{n-1}
GFP2 C_n_plus_2(GFP2 c, GFP2 cn_prev , GFP2 cn, GFP2 cn_next) {
    return c * cn_next - power_p(c) * cn + cn_prev;
}

// C{2n-1} = C{n-1} * C{n} - C^p * C{n}^p + C{n+1}^p
GFP2 C_2n_minus_1(GFP2 c, GFP2 cn_prev , GFP2 cn, GFP2 cn_next) {
    return cn_prev * cn - power_p(c) * power_p(cn) + power_p(cn_next);
}

// C{2n+1} = C{n+1} * C{n} - C * C{n}^p + C{n-1}^p
GFP2 C_2n_plus_1(GFP2 c, GFP2 cn_prev , GFP2 cn, GFP2 cn_next) {
    return cn_next * cn - c * power_p(cn) + power_p(cn_prev);
}

// Algorithm 2.37
// Sn = (c{n-1}, c{n}, c{n+1})
Sn calculate_Sn (BigNumber n, GFP2 c) {
    
    // Notice that, This function only consider the case n > 2
    GFP2 c_neg1 = power_p(c);   // C{-1} = C^p
    GFP2 c0 = GFP2(3);          // C{0} = 3
    GFP2 c1 = c;                // C{1} = C
    GFP2 c2 = C_2n(c1);         // C{2} = C^2 - 2*C^p
    GFP2 c3 = C_n_plus_2(c, c0, c1, c2); // get C{3} by corollary 2.35(ii), apply n=1
    GFP2 c4 = C_2n(c2);
    
    if (n==0)   return  Sn(c_neg1, c0, c1); // return S{0}
    if (n==1)   return  Sn(c0, c1, c2);     // return S{1}
    if (n==2)   return  Sn(c1, c2, c3);     // return S{2}
    
    BigNumber tmp_m, m, k;
    Sn S3, Sk_bar, Sm;
    
    S3 = Sn(c2, c3, c4);
    if (n%2==0) m = n-1;
    else  m = n;
    
    k=1;
    Sk_bar = S3;
    
    tmp_m = (m-1)/2;
    std::string m_str = tmp_m.to_binary();
    
    
    for (int i=1; i<m_str.size(); i++) {
        if (m_str.at(i)=='0') {
            // use S{k}_bar to calculate S{2k}_bar
            // S{k}_bar = (C{2k}, C{2k+1}, C{2k+2}), S{2k}_bar = (C{4k}, C{4k+1}, C{4k+2})
            // apply corollary 2.35(i), (iii)
            GFP2 C_4k = C_2n(Sk_bar.c0);
            GFP2 C_4k_1 = C_2n_minus_1(c, Sk_bar.c0, Sk_bar.c1, Sk_bar.c2);
            GFP2 C_4k_2 = C_2n(Sk_bar.c1);
            Sk_bar.c0 = C_4k;
            Sk_bar.c1 = C_4k_1;
            Sk_bar.c2 = C_4k_2;
            k = 2*k;
        } else {
            // use S{k}_bar to calculate S{2k+1}_bar
            // S{k}_bar = (C{2k}, C{2k+1}, C{2k+2}), S{2k+1}_bar = (C{4k+2}, C{4k+3}, C{4k+4})
            // apply corollary 2.35(i), (iv)
            GFP2 C_4k_2 = C_2n(Sk_bar.c1);
            GFP2 C_4k_3 = C_2n_plus_1(c, Sk_bar.c0, Sk_bar.c1, Sk_bar.c2);
            GFP2 C_4k_4 = C_2n(Sk_bar.c2);
            Sk_bar.c0 = C_4k_2;
            Sk_bar.c1 = C_4k_3;
            Sk_bar.c2 = C_4k_4;
            k = 2*k+1;
        }
    }

    if (n%2==0) {
        // use S{m} to calculate S{m+1}
        // S{m} = (C{m-1}, C{m}, C{m+1}), S{m+1} = (C{m}, C{m+1}, C{m+2})
        // apply corollary 2.35(ii)
        GFP2 C_m_2 = C_n_plus_2(c, Sk_bar.c0, Sk_bar.c1, Sk_bar.c2);
        m = m+1;
        Sk_bar.c0 = Sk_bar.c1;
        Sk_bar.c1 = Sk_bar.c2;
        Sk_bar.c2 = C_m_2;
    }
    
    
    return Sk_bar;
    
}
