#include <light/Base/String.hpp>

namespace light
{
    const Byte_Table STRING_TRIM = {
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  1,  1,  0,  0,  1,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         1,  0,  0,  0,  0,  0,  0,  0,
    };

    u64
    string_count(const s8* data, u64 limit)
    {
        u64 size = 0;

        if ( data != 0 ) {
            for ( ; data[size] != 0; ) {
                size += 1u;

                if ( size == limit )
                    break;
            }
        }

        return size;
    }

    String::String() {}

    String::String(const s8* data, u64 size)
    {
        if ( data != 0 && size != 0 ) {
            this->data = data;
            this->size = size;
        }
    }

    String::String(const s8* data, u64 lower, u64 upper)
    {
        u64 size = 0;

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
        for ( u64 i = 0; i < size; i += 1u ) {
            if ( data[i] == byte )
                return true;
        }

        return false;
    }

    Opt<u64>
    String::index_of(s8 byte) const
    {
        for ( u64 i = 0; i < size; i += 1u ) {
            if ( data[i] == byte )
                return i;
        }

        return {};
    }

    Buf<String, 2u>
    String::split(s8 byte) const
    {
        Buf<String, 2u> res;

        res[0] = String(data, size);

        for ( u64 i = 0; i < size; i += 1u ) {
            if ( data[i] == byte ) {
                res[1] = String(data + i + 1u, size - i - 1u);
                res[0] = String(data, i);

                break;
            }
        }

        return res;
    }

    String&
    String::trim_left(const Byte_Table& table)
    {
        u8  byte  = 0;
        u64 index = 0;

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
        u64 index = size - 1u;

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

    const s8&
    String::operator[](u64 index) const
    {
        #if LIGHT_TEST_BOUNDS
            if ( index >= size )
                light_panic("test-bounds", "index %lu exceeds %lu", index, size);
        #endif

        return data[index];
    }

    u64
    parse_u64(String string)
    {
        u8  byte = 0;
        u64 idx  = 0;
        u64 res  = 0;

        if ( string.size == 0 ) return 0;

        for ( ; idx < string.size; idx += 1u ) {
            byte = string.data[idx] - '0';

            if ( byte < 10u ) {
                res *= 10u;
                res += byte;
            } else break;
        }

        return res;
    }

    s64
    parse_s64(String string)
    {
        u8  byte = 0;
        s64 sign = 1;
        u64 idx  = 0;
        s64 res  = 0;

        if ( string.size == 0 ) return 0;

        switch ( string.data[0] ) {
            case '+': idx += 1u; break;
            case '-': idx += 1u, sign = -1; break;
            default: break;
        }

        for ( ; idx < string.size; idx += 1u ) {
            byte = string.data[idx] - '0';

            if ( byte < 10u ) {
                res *= 10u;
                res += byte;
            } else break;
        }

        return res * sign;
    }

    f64
    parse_f64_base(String string, u64& idx)
    {
        u8   byte = 0;
        s64  sign = 1;
        bool frac = false;
        u64  div  = 1;
        f64  res  = 0;

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

            byte = string.data[idx] - '0';

            if ( byte < 10u ) {
                res *= 10u;
                res += byte;

                if ( frac )
                    div *= 10u;
            } else break;
        }

        if ( res == 0 ) return res;

        return res * sign / div;
    }

    f64
    parse_f64(String string)
    {
        u64    idx  = 0;
        f64    base = parse_f64_base(string, idx);
        f64    exp  = 0;
        s8*    stop = (s8*) string.data + idx;
        u64    left = string.size - idx;

        if ( base == 0 ) return 0;

        if ( left != 0 ) {
            string = String(stop + 1u, left - 1u);

            if ( *stop == 'e' || *stop == 'E' )
                exp = parse_s64(string);
        }

        return base * pow(10u, exp);
    }
} // light
