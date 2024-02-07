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

    String::String(const char* data, u32 size)
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
    String::contains(char byte) const
    {
        for ( u32 i = 0; i < size; i++ ) {
            if ( data[i] == byte )
                return true;
        }

        return false;
    }

    String
    String::split(char byte)
    {
        String res;

        for ( u32 i = 0; i < size; i++ ) {
            if ( data[i] == byte ) {
                res = String(data, i);

                data += i + 1u;
                size -= i + 1u;

                break;
            }
        }
        
        return res;
    }

    void
    String::trim_left(String bytes)
    {
        u32 index = 0;

        while ( bytes.contains(data[index]) ) {
            data += 1u;
            size -= 1u;

            if ( size == 0 )
                break;
        }
    }

    void
    String::trim_right(String bytes)
    {
        u32 index = size - 1u;

        while ( bytes.contains(data[index]) ) {
            size  -= 1u;
            index -= 1u;

            if ( size == 0 )
                break;
        }
    }

    void
    String::trim(String bytes)
    {
        trim_left(bytes);
        trim_right(bytes);
    }
} // light
