#include <pax/Base/String.hpp>

namespace pax
{
    const Byte_Table STRING_TRIM = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0,
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

    String
    String::build(const s8* data, u64 size)
    {
        String reslt;

        if ( data != 0 && size != 0 ) {
            reslt.data = data;
            reslt.size = size;
        }

        return reslt;
    }

    String
    String::build(const s8* data, u64 lower, u64 upper)
    {
        String reslt;
        u64    size = 0;

        if ( data != 0 && lower < upper ) {
            size = string_count(data, upper);

            if ( size >= lower ) {
                reslt.data = data;
                reslt.size = size;
            }
        }

        return reslt;
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
        Opt<u64> reslt;

        for ( u64 i = 0; i < size; i += 1u ) {
            if ( data[i] == byte )
                return Opt<u64>::build(i);
        }

        return reslt;
    }

    Buf<String, 2u>
    String::split(s8 byte) const
    {
        Buf<String, 2u> reslt;

        reslt[0] = String::build(data, size);

        for ( u64 i = 0; i < size; i += 1u ) {
            if ( data[i] == byte ) {
                reslt[0] = String::build(data, i);
                reslt[1] = String::build(
                    data + i + 1u,
                    size - i - 1u
                );

                break;
            }
        }

        return reslt;
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
        #if PAX_TEST_BOUNDS
            if ( index >= size )
                pax_panic("test-bounds", "index %lu exceeds %lu", index, size);
        #endif

        return data[index];
    }
} // pax
