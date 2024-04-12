#include <pax/Base/String.hpp>

namespace pax
{
    u64
    string_count(const s8* data, u64 limit)
    {
        u64 count = 0;

        if ( data != 0 ) {
            while ( data[count] != 0 && count < limit )
                count += 1u;
        }

        return count;
    }

    String
    string_create(const s8* data, u64 size)
    {
        String value;

        if ( data != 0 ) {
            value.data = data;
            value.size = size;
        }

        return value;
    }

    String
    string_create(const s8* data, Store<u64, 2u> range)
    {
        String value;
        u64    count = 0;

        if ( data != 0 && range(0) <= range(1) ) {
            count = string_count(data, range(1));

            if ( range(0) <= count ) {
                value.data = data;
                value.size = count;
            }
        }

        return value;
    }

    String::String()
    { }

    s8
    String::item(u64 index) const
    {
        pax_test_fmt(index < size,
            "bounds", "index = %lu exceedes size = %lu", index, size
        );

        return data[index];
    }

    s8
    String::operator()(u64 index) const
    {
        return item(index);
    }
} // pax
