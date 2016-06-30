# XTR version of Diffie-Hellman
This repository is an implementation of XTR Diffie Hellman public key exchange protocol.

XTR (Efficient Compace Subgroup Trace Representation, ECSTR) is a method to represent elements of a multiplication group of a finite field. It uses traces over GF(P^2) to represent elements of a subgroup of GF(P^6).

Please read [The XTR Public Key System](http://link.springer.com/chapter/10.1007/3-540-44598-6_1) for more details.

## Structure
```
- BigNumber             // Bignumber arithmetic.
- GFP                   // Finite field, representation of GF(P).
- GFP2                  // Finite field, representation of GF(P^2).
- XTR                   // Calculation of Sn(C) and Cn.
```
## Example
#####Input:
```
p = 0ED63D1E 55533501 0A551576 3B2A9D57 DAD4CFE6 2E98A34B
q = 0B507397 0D0FEDC5 4F45BA84 36122A02 29C0CF9F B4F6D7
Tr(g) = ( 05979DD0 F29B6D57 87458232 E258C35C 12898230 E4610C58 , 0C328613 C13A98B2 42CEF504 BBFAAE70 15C6C0F4 D3BCF162 )
a = 9166EB14 BA0E8757 A9FBCF6A D13710AE A4EC4CF3 288A
b = 09C4B2B4 734B0E8B 24119D8C 350AC19F 199FDEB2 BA5DA6
```
#####Output:
```
Tr(g^a) = ( 02C5E47C A6F54961 1E8AFF5E 1FD9774A DC595F96 C423B05F , 02AF7114 8BF8B99C 70443E40 6D25BEBA 51B649EF C8F15B09 )
Tr(g^b) = ( 09D4B23A 30472600 9A7ED23D 399F03AE 06249BD5 DBAE4EB8 , 0EBF9B6E 2684C98D 7E197AC1 4EF5B706 07E9CAD6 515ACB83 )
Tr(g^ab) = ( 0A1C846D 71723116 87581025 4D5AB395 76197AC2 3AE0B176 , 0870082D 9DB05C2F 6052BBC5 2B144D16 7C5CB5FF 1FB13D62 )
```
