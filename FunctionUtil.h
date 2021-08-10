#pragma once
#ifndef FUNCTION_UTIL_H_
#define FUNCTION_UTIL_H_
#include<iostream>
#include<string>
#include<cmath>
#include"SHA1_Util.h"
using namespace std;

// A helper function for the Conversion of Haxa string into Binary.
// Return a Haxa Equivilance  string of the given hax character.
string Haxatobinary(char character)
{
    int val;
    if (character <= '9')
        val = static_cast<int>(character - '0');
    else
        val = static_cast<int>(character - 87);
    string Result, str;
    while (val)
    {
        Result += static_cast<char>((val % 2) + '0');
        val /= 2;
    }
    while (Result.size() < 4)
        Result += '0';
    for (int i = Result.size() - 1; i >= 0; i--)
        str += Result[i];
    return str;
}

// this function Converts a binary string to Integer
int To_Integer(string binary)
{
    int value = 0;
    int size = binary.size();
    int len = size - 1;
    for (int i = 0; i < size; i++)
    {
        value += pow(2, len) * static_cast<int>(binary[i] - 48);
        len--;
    }
    return value;
}


// Helper function Used for Generating  A Binary String.
//Return binary string value of given hexadecimal string.
string getbinary(const string str, int bit)
{
    string b, res;
    for (int i = 0; i < str.size(); i++)
    {
        b += Haxatobinary(str[i]);
        if (b.size() >= bit)
            break;
    }
    for (int i = 0; i < bit; i++)
    {
        res += b[i];
    }

    return res;
}

// This function Converts a Given integer ID to a binary Equivalance string
string To_Binary_String(int val, int Bits)
{
    string str, res;
    while (val)
    {
        str += static_cast<char>((val % 2) + '0');
        val /= 2;
    }
    int size = str.size();
    for (int i = size; i < Bits; i++)
        str += '0';
    for (int i = Bits - 1; i >= 0; i--)
        res += str[i];

    return res;
}

// This Function Utilize SHA1_Util liberies to Generate a hash and Returns
// the number of Bits string according to the Specified Range Specified by User
template<class T>
T Gethashedvalue(string Key, int Bits)
{
    SHA1 p;
    p.update(Key);
    string str = p.final();
    bool con = true;
    T Res = getbinary(str, Bits);
    return Res;
}
#endif