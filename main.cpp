//
// Created by Jingyuan Xu on 4/24/17.
//

#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "hashs.h"
using namespace std;

#define MOD1 20
#define MOD2 20

int ParseArgs(int argc, char** argv, char* dictionary,
              char* input, char* output3, char* output5) {
    if (argc != 8) {
        return 1;
    }
    if (strcmp(argv[1], "-d") != 0 || strcmp(argv[3], "-i") ||
        strcmp(argv[5], "-o") != 0) {
        return 1;
    }

    return 0;
}

unsigned int SDBMHash(const char *str)
{
    unsigned int hash = 0;

    while (*str)
    {
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }

    return (hash & 0x7FFFFFFF);
}

// RS Hash
unsigned int RSHash(const char *str)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;

    while (*str)
    {
        hash = hash * a + (*str++);
        a *= b;
    }

    return (hash & 0x7FFFFFFF);
}

// JS Hash
unsigned int JSHash(const char *str)
{
    unsigned int hash = 1315423911;

    while (*str)
    {
        hash ^= ((hash << 5) + (*str++) + (hash >> 2));
    }

    return (hash & 0x7FFFFFFF);
}

// P. J. Weinberger Hash
unsigned int PJWHash(const char *str)
{
    unsigned int BitsInUnignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    unsigned int ThreeQuarters    = (unsigned int)((BitsInUnignedInt  * 3) / 4);
    unsigned int OneEighth = (unsigned int)(BitsInUnignedInt / 8);
    unsigned int HighBits = (unsigned int)(0xFFFFFFFF) << (BitsInUnignedInt
                                                           - OneEighth);
    unsigned int hash    = 0;
    unsigned int test    = 0;

    while (*str)
    {
        hash = (hash << OneEighth) + (*str++);
        if ((test = hash & HighBits) != 0)
        {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return (hash & 0x7FFFFFFF);
}

// ELF Hash
unsigned int ELFHash(const char *str)
{
    unsigned int hash = 0;
    unsigned int x    = 0;

    while (*str)
    {
        hash = (hash << 4) + (*str++);
        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
            hash &= ~x;
        }
    }

    return (hash & 0x7FFFFFFF);
}

// BKDR Hash
unsigned int BKDRHash(const char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*str)
    {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

// DJB Hash
unsigned int DJBHash(const char *str)
{
    unsigned int hash = 5381;

    while (*str)
    {
        hash += (hash << 5) + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

// AP Hash
unsigned int APHash(const char *str)
{
    unsigned int hash = 0;
    int i;

    for (i=0; *str; i++)
    {
        if ((i & 1) == 0)
        {
            hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
        }
        else
        {
            hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
        }
    }

    return (hash & 0x7FFFFFFF);
}

int BuildBloomFilter1(const char* dictionary, bitset<MOD1>& bloom_filter) {
    ifstream in(dictionary);
    if (!in) {
        return 1;
    }
    string str;
    unsigned int h;
    while (!in.eof()) {
        in >> str;
        h = SDBMHash(str.c_str()) % MOD1;
        bloom_filter.set(h);
        h = RSHash(str.c_str()) % MOD1;
        bloom_filter.set(h);
        h = JSHash(str.c_str()) % MOD1;
        bloom_filter.set(h);
    }
    in.close();
    return 0;
}

int BuildBloomFilter2(const char* dictionary, bitset<MOD2>& bloom_filter) {
    ifstream in(dictionary);
    if (!in) {
        return 1;
    }
    string str;
    unsigned int h;
    while (!in.eof()) {
        in >> str;
        h = PJWHash(str.c_str()) % MOD2;
        bloom_filter.set(h);
        h = ELFHash(str.c_str()) % MOD2;
        bloom_filter.set(h);
        h = BKDRHash(str.c_str()) % MOD2;
        bloom_filter.set(h);
        h = DJBHash(str.c_str()) % MOD2;
        bloom_filter.set(h);
        h = APHash(str.c_str()) % MOD2;
        bloom_filter.set(h);
    }
    in.close();
    return 0;
}

int HandleOutput3(const char* input, const char* output,
                  const bitset<MOD1>& bloom_filter) {
    ifstream in(input);
    if (!in) {
        return 1;
    }
    ofstream out(output);
    if (!out) {
        in.close();
        return 1;
    }
    int num;
    string str;
    unsigned int h;
    struct timeval start;
    struct timeval end;
    unsigned long t = 0;
    in >> num;
    for (int i = 0; i < num; ++i) {
        in >> str;
        gettimeofday(&start, NULL);
        h = SDBMHash(str.c_str()) % MOD1;
        if (!bloom_filter.test(h)) {
            out << "no" << endl;
            gettimeofday(&end, NULL);
            t += end.tv_usec - start.tv_usec;
            continue;
        }
        h = RSHash(str.c_str()) % MOD1;
        if (!bloom_filter.test(h)) {
            out << "no" << endl;
            gettimeofday(&end, NULL);
            t += end.tv_usec - start.tv_usec;
            continue;
        }
        h = JSHash(str.c_str()) % MOD1;
        if (!bloom_filter.test(h)) {
            out << "no" << endl;
            gettimeofday(&end, NULL);
            t += end.tv_usec - start.tv_usec;
            continue;
        }
        out << "maybe" << endl;
        gettimeofday(&end, NULL);
        t += end.tv_usec - start.tv_usec;
    }
    cout << "output3 time: " << (double)t / num << endl;
    in.close();
    out.close();
    return 0;
}

int HandleOutput5(const char* input, const char* output,
                  const bitset<MOD2>& bloom_filter) {
    ifstream in(input);
    if (!in) {
        return 1;
    }
    ofstream out(output);
    if (!out) {
        in.close();
        return 1;
    }
    int num;
    string str;
    unsigned int h;
    struct timeval start;
    struct timeval end;
    unsigned long t = 0;
    in >> num;
    for (int i = 0; i < num; ++i) {
        in >> str;
        gettimeofday(&start, NULL);
        h = PJWHash(str.c_str()) % MOD2;
        if (!bloom_filter.test(h)) {
            out << "no" << endl;
            gettimeofday(&end, NULL);
            t += end.tv_usec - start.tv_usec;
            continue;
        }
        h = ELFHash(str.c_str()) % MOD2;
        if (!bloom_filter.test(h)) {
            out << "no" << endl;
            gettimeofday(&end, NULL);
            t += end.tv_usec - start.tv_usec;
            continue;
        }
        h = BKDRHash(str.c_str()) % MOD2;
        if (!bloom_filter.test(h)) {
            out << "no" << endl;
            gettimeofday(&end, NULL);
            t += end.tv_usec - start.tv_usec;
            continue;
        }
        h = DJBHash(str.c_str()) % MOD2;
        if (!bloom_filter.test(h)) {
            out << "no" << endl;
            gettimeofday(&end, NULL);
            t += end.tv_usec - start.tv_usec;
            continue;
        }
        h = APHash(str.c_str()) % MOD2;
        if (!bloom_filter.test(h)) {
            out << "no" << endl;
            gettimeofday(&end, NULL);
            t += end.tv_usec - start.tv_usec;
            continue;
        }
        out << "maybe" << endl;
        gettimeofday(&end, NULL);
        t += end.tv_usec - start.tv_usec;
    }
    cout << "output5 time: " << (double)t / num << endl;
    in.close();
    out.close();
    return 0;
}

int main(int argc, char** argv) {
    cout << MOD1 << endl;
    cout << MOD2 << endl;
    return 0;
}
