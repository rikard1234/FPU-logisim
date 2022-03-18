#include <limits>
#include <iostream>
#include <bitset>
#include <fstream>
#include <cmath>

union FloatToInt
{
    float input;
    int32_t output;
};

FloatToInt NaN;
FloatToInt NegZero;

void AddTest(float* values, int length)
{
    std::fstream file;
    file.open("AddTestVector.txt", std::fstream::out);
    if(!file.is_open())
        return;

    file << "#Addition tests" << std::endl;
    file << "X[32] Y[32] Out[32]" << std::endl;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            FloatToInt x;
            x.input = values[i];
            FloatToInt y;
            y.input = values[j];

            FloatToInt res;
            res.input = x.input + y.input;

            if(_isnanf(res.input))
                res.output = NaN.output;

            file << std::bitset<32>(x.output) << ' ' << std::bitset<32>(y.output) << ' ' << std::bitset<32>(res.output);
            file << " #" << x.input << " + " << y.input << " = " << res.input << std::endl;
        }
    }

    file.close();
}

void MultTest(float *values, int length)
{
    std::fstream file;
    file.open("MultTestVector.txt", std::fstream::out);
    if (!file.is_open())
        return;

    file << "#Multiplication tests" << std::endl;
    file << "X[32] Y[32] Out[32]" << std::endl;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            FloatToInt x;
            x.input = values[i];
            FloatToInt y;
            y.input = values[j];

            FloatToInt res;
            res.input = x.input * y.input;

            if (_isnanf(res.input))
                res.output = NaN.output;

            file << std::bitset<32>(x.output) << ' ' << std::bitset<32>(y.output) << ' ' << std::bitset<32>(res.output);
            file << " #" << x.input << " * " << y.input << " = " << res.input << std::endl;
        }
    }
}

void CmpTests(float* values, int length)
{
    std::fstream file;
    file.open("CmpTestVector.txt", std::fstream::out);
    if (!file.is_open())
        return;

    file << "#Compare tests" << std::endl;
    file << "X[32] Y[32] X>Y X=Y X<Y Unordered" << std::endl;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            FloatToInt x;
            x.input = values[i];
            FloatToInt y;
            y.input = values[j];

            FloatToInt res;
            res.input = x.input * y.input;

            file << std::bitset<32>(x.output) << ' ' << std::bitset<32>(y.output) << ' ';

            if (x.input > y.input)
                file << "1 ";
            else
                file << "0 ";

            if (x.input == y.input)
                file << "1 ";
            else
                file << "0 ";

            if (x.input < y.input)
                file << "1 ";
            else
                file << "0 ";

            if (_isnanf(x.input) || _isnanf(y.input))
                file << "1 ";
            else
                file << "0 ";

            file << "#" << x.input << ", " << y.input << std::endl;
        }
    }
}

int main()
{
    NaN.output = std::numeric_limits<int32_t>::max();
    NegZero.output = -std::numeric_limits<int32_t>::max();

    float values[] = {
        0,
        NegZero.input,                           //-0
        std::numeric_limits<float>::infinity(),  //Inf
        -std::numeric_limits<float>::infinity(), //-Inf
        std::numeric_limits<float>::max(),       //Max
        -std::numeric_limits<float>::max(),      //-Max
        std::numeric_limits<float>::min(),       //Min normalny
        -std::numeric_limits<float>::min(),      //-Min normalny
        NaN.input,                               //NaN w naszej konwencji (C++ ma inną)
        14.5,
        879.25,
        4296,
        -2294.5,
        4874.625,
        -1750.0938,
        122.985886,
        -2146.8455,
        1817.5363,
        4923.988,
        3377.0886,
        439.34354,
        1295.7813,
        -4599.5156,
        4540.6724,
        4557.0293,
        1001.18066,
        2410.5623,
        4252.5283,
        -4583.443
    };
    int length = sizeof(values) / sizeof(float);

    AddTest(values, length);
    MultTest(values, length);
    CmpTests(values, length);
}