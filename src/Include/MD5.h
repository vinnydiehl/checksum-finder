/**
 * A program for verifying file integrity.
 * Copyright (C) 2012 Vinny Diehl
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
**/

/**
 * @file MD5.h - Header file for the MD5 class and MD5-related functions.
**/

#ifndef MD5_H_INCLUDED
#define MD5_H_INCLUDED

#include <ostream>
#include <cstdio>
#include <cstring>
#include <wx/string.h>

using namespace std;

class MD5
{
public:
    typedef unsigned int size_type; // Must be 32-bit

    MD5();
    MD5(const string &text);
    void update(const unsigned char *buf, size_type length);
    void update(const char *buf, size_type length);
    MD5 &finalize();
    string hexdigest() const;
    friend ostream& operator<<(ostream&, MD5 md5);

private:
    void init();
    typedef unsigned char uint1; // 8-bit
    typedef unsigned int uint4; // 32-bit
    enum { blocksize = 64 };

    void transform(const uint1 block[blocksize]);
    static void decode(uint4 output[], const uint1 input[], size_type len);
    static void encode(uint1 output[], const uint4 input[], size_type len);

    bool finalized;
    uint1 buffer[blocksize]; // Bytes that didn't fit in last 64 byte chunk
    uint4 count[2]; // 64-bit counter for number of bits (lo, hi)
    uint4 state[4]; // Digest so far
    uint1 digest[16]; // The result

    // Low level logic operations
    static inline uint4 F(uint4 x, uint4 y, uint4 z);
    static inline uint4 G(uint4 x, uint4 y, uint4 z);
    static inline uint4 H(uint4 x, uint4 y, uint4 z);
    static inline uint4 I(uint4 x, uint4 y, uint4 z);
    static inline uint4 rotate_left(uint4 x, int n);
    static inline void FF(uint4 &a, uint4 b, uint4 c, uint4 d,
                          uint4 x, uint4 s, uint4 ac);
    static inline void GG(uint4 &a, uint4 b, uint4 c, uint4 d,
                          uint4 x, uint4 s, uint4 ac);
    static inline void HH(uint4 &a, uint4 b, uint4 c, uint4 d,
                          uint4 x, uint4 s, uint4 ac);
    static inline void II(uint4 &a, uint4 b, uint4 c, uint4 d,
                          uint4 x, uint4 s, uint4 ac);
};

wxString encryptMD5(wxString str);

#endif // MD5_H_INCLUDED

