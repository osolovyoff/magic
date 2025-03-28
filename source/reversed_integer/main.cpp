#include <iostream>
#include <cstdint>
#include <limits>


int32_t reverseInteger(int32_t x)
{
    constexpr int32_t MAX = std::numeric_limits<int32_t>::max();
    constexpr int32_t MIN = std::numeric_limits<int32_t>::min();

    if (x == MIN) return 0;
    int32_t result = 0;

    const int32_t sign = x >= 0 ? 1 : -1;
    x = std::abs(x);
    while (x != 0)
    {
        const int32_t next_digit = x % 10;
        x = x / 10;

        if (result > (MAX - next_digit) / 10)
            return 0;

        result = result * 10 + next_digit;
    }
    return result * sign;
}

int main()
{
    const auto tests = {
        std::numeric_limits<int32_t>::max()-1, // 2147483646, 
        std::numeric_limits<int32_t>::min()+1, // -2147483647,
        0, 1234, -1234,
        12345, -12345,
        1234567890,-1234567890,
        // 5463847412, -6463847412,
    };
    
    for (const auto test : tests)
        if (const int32_t result = reverseInteger(test))
            std::cout << "test: " << test << " result: " << result << '\n';
        else
            std::cout << "failed test: " << test << '\n';
}