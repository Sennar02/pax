#include <light/Base/String.hpp>

extern "C" {
    #include <string.h>
}

namespace light
{
    const Byte_Table String::TRIMS = {
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  1,  1,  0,  0,  1,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         1,  0,  0,  0,  0,  0,  0,  0,
    };

    const Byte_Table String::BASE_2 = {
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         1,  2,  0,  0,  0,  0,  0,  0,
    };

    const Byte_Table String::BASE_8 = {
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         1,  2,  3,  4,  5,  6,  7,  8,
    };

    const Byte_Table String::BASE_10 = {
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         1,  2,  3,  4,  5,  6,  7,  8,
         9, 10,  0,  0,  0,  0,  0,  0,
    };

    const Byte_Table String::BASE_16 = {
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         1,  2,  3,  4,  5,  6,  7,  8,
         9, 10,  0,  0,  0,  0,  0,  0,
         0, 11, 12, 13, 14, 15, 16,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0, 11, 12, 13, 14, 15, 16,  0,
    };

    u32
    string_count(const s8* data, u32 limit)
    {
        u32 size = 0;

        if ( data != 0 ) {
            for ( ; data[size] != 0; ) {
                size += 1u;

                if ( size == limit )
                    break;
            }
        }

        return size;
    }

    String::String()
        : data {""}
        , size {0}
    {}

    String::String(const s8* data, u32 size)
        : String()
    {
        if ( data != 0 && size != 0 ) {
            this->data = data;
            this->size = size;
        }
    }

    String::String(const s8* data, u32 lower, u32 upper)
        : String()
    {
        u32 size = 0;

        if ( data != 0 && lower < upper ) {
            size = string_count(data, upper);

            if ( size >= lower ) {
                this->data = data;
                this->size = size;
            }
        }
    }

    bool
    String::contains(s8 byte) const
    {
        for ( u32 i = 0; i < size; i += 1u ) {
            if ( data[i] == byte )
                return true;
        }

        return false;
    }

    Opt<u32>
    String::index_of(s8 byte) const
    {
        for ( u32 i = 0; i < size; i += 1u ) {
            if ( data[i] == byte )
                return i;
        }

        return {};
    }

    Buffer<String, 2u>
    String::split(s8 byte) const
    {
        Buffer<String, 2u> res;

        res[0] = String(data, size);

        for ( u32 i = 0; i < size; i += 1u ) {
            if ( data[i] == byte ) {
                res[0] = String(data, i);
                res[1] = String(
                    data + i + 1u,
                    size - i - 1u
                );

                break;
            }
        }

        return res;
    }

    String&
    String::trim_left(const Byte_Table& table)
    {
        u8  byte  = 0;
        u32 index = 0;

        while ( true ) {
            byte = data[index];

            if ( table[byte] == 0 ) break;

            data += 1u;
            size -= 1u;

            if ( size == 0 )
                break;
        }

        return *this;
    }

    String&
    String::trim_right(const Byte_Table& table)
    {
        u8  byte  = 0;
        u32 index = size - 1u;

        while ( true ) {
            byte = data[index];

            if ( table[byte] == 0 ) break;

            size  -= 1u;
            index -= 1u;

            if ( size == 0 )
                break;
        }

        return *this;
    }

    String&
    String::trim(const Byte_Table& table)
    {
        return trim_left(table).trim_right(table);
    }

    char
    String::operator[](u32 index) const
    {
        return data[index];
    }

    s32
    parse_int_impl(String string, const Byte_Table& table, u8 base, u32* dist)
    {
        u8  byte = 0;
        s32 sign = 1;
        u32 idx  = 0;
        s32 res  = 0;

        if ( string.size == 0 ) return 0;

        switch ( string.data[0] ) {
            case '+': idx += 1u; break;
            case '-': idx += 1u, sign = -1; break;
            default: break;
        }

        for ( ; idx < string.size; idx += 1u ) {
            byte = table[string.data[idx]];

            if ( byte != 0 ) {
                res *= base;
                res += byte - 1u;
            } else break;
        }

        if ( dist != 0 ) *dist = idx;

        return res * sign;
    }

    f32
    parse_flt_impl(String string, const Byte_Table& table, u8 base, u32* dist)
    {
        u8   byte = 0;
        s32  sign = 1;
        bool frac = false;
        u32  div  = 1;
        u32  idx  = 0;
        f32  res  = 0;

        if ( string.size == 0 ) return 0;

        switch ( string.data[0] ) {
            case '+': idx += 1u; break;
            case '-': idx += 1u, sign = -1; break;
            default: break;
        }

        for ( ; idx < string.size; idx += 1u ) {
            if ( string.data[idx] == '.' ) {
                if ( frac == false )
                    frac = true, idx += 1u;
                else break;
            }

            byte = table[string.data[idx]];

            if ( byte != 0 ) {
                res *= base;
                res += byte - 1u;

                if ( frac )
                    div *= base;
            } else break;
        }

        if ( dist != 0 ) *dist = idx;

        return res * sign / div;
    }

    s32
    parse_int(String string, const Byte_Table& table, u8 base)
    {
        return parse_int_impl(string, table, base, 0);
    }

    f32
    parse_flt(String string, const Byte_Table& table, u8 base)
    {
        u32    dist   = 0;
        f32    lower  = parse_flt_impl(string, table, base, &dist);
        f32    upper  = 0;
        s8*    stop   = (s8*) string.data + dist;

        dist = string.size - dist;

        if ( string.size > dist ) {
            string = String(stop + 1u, dist - 1u);

            if ( *stop == 'e' || *stop == 'E' )
                upper  = parse_int_impl(string, table, base, 0);
        }

        return lower * pow(base, upper);
    }
} // light
