#include <light/Base/String.hpp>

extern "C" {
    #include <string.h>
}

namespace light
{
    const String String::TRIMS   = String("\40\t\n\r", 4u);

    const String String::BASE_10 = String("0123456789", 10u);
    const String String::BASE_16 = String("0123456789abcdef", 16u);

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

    Array<String, 2u>
    String::split(s8 byte) const
    {
        Array<String, 2u> res;

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
    String::trim_left(String bytes)
    {
        u32 index = 0;

        while ( bytes.contains(data[index]) ) {
            data += 1u;
            size -= 1u;

            if ( size == 0 )
                break;
        }

        return *this;
    }

    String&
    String::trim_right(String bytes)
    {
        u32 index = size - 1u;

        while ( bytes.contains(data[index]) ) {
            size  -= 1u;
            index -= 1u;

            if ( size == 0 )
                break;
        }

        return *this;
    }

    String&
    String::trim(String bytes)
    {
        return trim_left(bytes).trim_right(bytes);
    }

    char
    String::operator[](u32 index) const
    {
        return data[index];
    }

    s32
    parse_int(String string, String digits)
    {
        u32 base = digits.size;
        s32 sign = 1;
        u32 idx  = 0;
        s32 res  = 0;

        if ( string.size == 0 ) return 0;

        switch ( string[0] ) {
            case '+': idx += 1u; break;
            case '-': idx += 1u, sign = -1; break;
            default: break;
        }

        for ( ; idx < string.size; idx += 1u ) {
            auto opt = digits.index_of(string[idx]);

            if ( opt.full ) {
                res *= base;
                res += opt.item;
            } else break;
        }

        return res * sign;
    }

    f32
    parse_flt(String string, String digits)
    {
        u32  base = digits.size;
        s32  sign = 1;
        bool dot  = false;
        u32  div  = 1;
        u32  idx  = 0;
        f32  res  = 0;

        if ( string.size == 0 ) return 0;

        switch ( string[0] ) {
            case '+': idx += 1u; break;
            case '-': idx += 1u, sign = -1; break;
            case '.': idx += 1u, dot = true; break;
            default: break;
        }

        for ( ; idx < string.size; idx += 1u ) {
            if ( string[idx] == '.' ) {
                if ( dot == false )
                    dot = true, idx += 1u;
                else break;
            }

            auto opt = digits.index_of(string[idx]);

            if ( opt.full ) {
                res *= base;
                res += opt.item;

                if ( dot )
                    div *= base;
            } else break;
        }

        return res * sign / div;
    }
} // light
