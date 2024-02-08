#include <light/Base/String.hpp>

extern "C" {
    #include <string.h>
}

namespace light
{
    const String String::TRIMS = String("\40\t\n\r", 4);

    String::String()
        : data {0}
        , size {0}
    {}

    String::String(const s8* data, u32 size)
        : String()
    {
        if ( data != 0 && size != 0 ) {
            if ( size == MAX_U32 )
                size = strlen(data);

            this->data = data;
            this->size = size;
        }
    }

    bool
    String::contains(s8 byte) const
    {
        for ( u32 i = 0; i < size; i++ ) {
            if ( data[i] == byte )
                return true;
        }

        return false;
    }

    Array<String, 2u>
    String::split(s8 byte) const
    {
        Array<String, 2u> res;

        res[0] = String(data, size);

        for ( u32 i = 0; i < size; i++ ) {
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
} // light
