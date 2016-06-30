//
//  main.cpp
//  XTR
//
//  Impolement XTR Diffie Hellman Public Key Exchange
//
//  101062212
//  Created by chenchiyen on 6/17/16.
//  Copyright © 2016 chenchiyen. All rights reserved.
//
#include <iostream>
#include <cstdio>

#include "BigNumber.hpp"
#include "GFP.hpp"
#include "GFP2.hpp"
#include "XTR.hpp"

void input (std::string& input);
void inputTrace (std::string& input1, std::string& input2);

int main(int argc, const char * argv[]) {
    std::string str_p, str_q, str_g1, str_g2, str_a, str_b, str_Tr;
    
    input(str_p);
    input(str_q);
    inputTrace(str_g1, str_g2);
    input(str_a);
    input(str_b);
    
    BigNumber p =  BigNumber(str_p);
    GFP::mod_prime = p; // set prime p for GF(p)
    BigNumber q = BigNumber(str_q);
    BigNumber g1 = BigNumber(str_g1);
    BigNumber g2 = BigNumber(str_g2);
    GFP2 Tr_g = GFP2(g1,g2);
    BigNumber a = BigNumber(str_a);
    BigNumber b = BigNumber(str_b);

    
    std::cout << "p: " << p << std::endl;
    std::cout << "q: " << q << std::endl;
    std::cout << "Tr(g): " << Tr_g << std::endl;
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    
    // calculate Tr(g^a)
    Sn Sa = calculate_Sn(a, Tr_g);
    std::cout << "Tr(g^a) : " << Sa.c1 << std::endl;
    
    // calculate Tr(g^b)
    Sn Sb = calculate_Sn(b, Tr_g);
    std::cout << "Tr(g^b) : " << Sb.c1 << std::endl;
    
    // Exchange key, Tr(g^ab)
    Sn Sab = calculate_Sn(a,  Sb.c1);
    std::cout << "Tr(g^ab) : " << Sab.c1 << std::endl;
 
    return 0;
}

void input (std::string& input) {
    char c;
    std::string temp;
    
    while ((c=getchar())!='\n') {
        if (c!=' ') {
            input += c;
        }
    }
    
}

void inputTrace (std::string& input1, std::string& input2) {
    char c;
    
    if ((c=getchar())=='(') {
        while ((c=getchar())!=',') {
            if (c!=' ') {
                input1 += c;
            }
        }
        while ((c=getchar())!=')') {
            if (c!=' ') {
                input2 += c;
            }
        }
        getchar();
    }
}
