#pragma once

#include <fmt/format.h>
#include <vector>
#include <array>
#include <cstdint>

#ifdef _MSC_VER
#define GCC_ALIGN(n)
#else
#define GCC_ALIGN(n) __attribute__((aligned(n)))
#endif

static inline uint8_t byte32(uint32_t x, int n)
{
    return (uint8_t)(x >> (8 * n));
}

static inline uint32_t min32(uint32_t a, uint32_t b)
{
    return a < b ? a : b;
}

static inline uint64_t min64(uint64_t a, uint64_t b)
{
    return a < b ? a : b;
}

static inline uint32_t max32(uint32_t a, uint32_t b)
{
    return a > b ? a : b;
}

static inline uint64_t max64(uint64_t a, uint64_t b)
{
    return a > b ? a : b;
}

static inline uint32_t ror32(uint32_t x, int n)
{
    return (x >> n) | (x << (32 - n));
}

static inline uint16_t get16le(const uint8_t* bytes)
{
    return (bytes[0]) | (bytes[1] << 8);
}

static inline uint32_t get32le(const uint8_t* bytes)
{
    return (bytes[0]) | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);
}

static inline uint64_t get64le(const uint8_t* bytes)
{
    return (uint64_t)bytes[0] | ((uint64_t)bytes[1] << 8) |
           ((uint64_t)bytes[2] << 16) | ((uint64_t)bytes[3] << 24) |
           ((uint64_t)bytes[4] << 32) | ((uint64_t)bytes[5] << 40) |
           ((uint64_t)bytes[6] << 48) | ((uint64_t)bytes[7] << 56);
}

static inline uint16_t get16be(const uint8_t* bytes)
{
    return (bytes[1]) | (bytes[0] << 8);
}

static inline uint32_t get32be(const uint8_t* bytes)
{
    return (bytes[3]) | (bytes[2] << 8) | (bytes[1] << 16) | (bytes[0] << 24);
}

static inline uint64_t get64be(const uint8_t* bytes)
{
    return (uint64_t)bytes[7] | ((uint64_t)bytes[6] << 8) |
           ((uint64_t)bytes[5] << 16) | ((uint64_t)bytes[4] << 24) |
           ((uint64_t)bytes[3] << 32) | ((uint64_t)bytes[2] << 40) |
           ((uint64_t)bytes[1] << 48) | ((uint64_t)bytes[0] << 56);
}

static inline void set16le(uint8_t* bytes, uint16_t x)
{
    bytes[0] = (uint8_t)x;
    bytes[1] = (uint8_t)(x >> 8);
}

static inline void set32le(uint8_t* bytes, uint32_t x)
{
    bytes[0] = (uint8_t)x;
    bytes[1] = (uint8_t)(x >> 8);
    bytes[2] = (uint8_t)(x >> 16);
    bytes[3] = (uint8_t)(x >> 24);
}

static inline void set64le(uint8_t* bytes, uint64_t x)
{
    bytes[0] = (uint8_t)x;
    bytes[1] = (uint8_t)(x >> 8);
    bytes[2] = (uint8_t)(x >> 16);
    bytes[3] = (uint8_t)(x >> 24);
    bytes[4] = (uint8_t)(x >> 32);
    bytes[5] = (uint8_t)(x >> 40);
    bytes[6] = (uint8_t)(x >> 48);
    bytes[7] = (uint8_t)(x >> 56);
}

static inline void set16be(uint8_t* bytes, uint16_t x)
{
    bytes[0] = (uint8_t)(x >> 8);
    bytes[1] = (uint8_t)x;
}

static inline void set32be(uint8_t* bytes, uint32_t x)
{
    bytes[0] = (uint8_t)(x >> 24);
    bytes[1] = (uint8_t)(x >> 16);
    bytes[2] = (uint8_t)(x >> 8);
    bytes[3] = (uint8_t)x;
}

static inline void set64be(uint8_t* bytes, uint64_t x)
{
    bytes[0] = (uint8_t)(x >> 56);
    bytes[1] = (uint8_t)(x >> 48);
    bytes[2] = (uint8_t)(x >> 40);
    bytes[3] = (uint8_t)(x >> 32);
    bytes[4] = (uint8_t)(x >> 24);
    bytes[5] = (uint8_t)(x >> 16);
    bytes[6] = (uint8_t)(x >> 8);
    bytes[7] = (uint8_t)x;
}

static inline uint8_t hexvalue(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return ch - '0';
    }
    else if (ch >= 'a' && ch <= 'f')
    {
        return ch - 'a' + 10;
    }
    else if (ch >= 'A' && ch <= 'F')
    {
        return ch - 'A' + 10;
    }
    return 0;
}

static inline std::array<uint8_t, 32> pkgi_hexbytes(
        const char* digest, uint32_t length)
{
    std::array<uint8_t, 32> result;

    for (uint32_t i = 0; i < length; i++)
    {
        char ch1 = digest[2 * i];
        char ch2 = digest[2 * i + 1];
        if (ch1 == 0 || ch2 == 0)
            return result;

        result[i] = hexvalue(ch1) * 16 + hexvalue(ch2);
    }

    return result;
}

static inline std::string pkgi_tohex(const std::vector<uint8_t>& data)
{
    std::string out;
    out.reserve(data.size() * 2);
    for (auto const& d : data)
        out += fmt::format("{:02x}", d);
    return out;
}

inline bool ends_with(std::string const& value, std::string const& ending)
{
    if (ending.size() > value.size())
        return false;
    return value.compare(value.size() - ending.size(), ending.size(), ending) ==
           0;
}
