#ifndef LIGHT_BASE_STRING_HPP
#define LIGHT_BASE_STRING_HPP

#include <light/Base/define.hpp>

#define light_string(ptr) \
    light::String(ptr, sizeof(ptr) - 1u)

namespace light
{
    struct String
    {
    public:
        // Commonly trimmed characters from strings.
        static const String TRIMS;

    public:
        // Pointer to each character.
        const char* data;

        // Amount of characters.
        u32 size;

    public:
        // Default constructor.
        String();
        
        // Constructor that can be used to trigger
        // a call on strlen in case of "size" == MAX_U32,
        // or provide the desired size manually.
        String(const char* data, u32 size = MAX_U32);
        
        // Checks if any of the characters matches.
        bool
        contains(char byte) const;

        // finds the first occurrence of "byte",
        // moves the current string forward and
        // returns the first part.
        String
        split(char byte);

        void
        trim_left(String bytes = TRIMS);

        void
        trim_right(String bytes = TRIMS);

        void
        trim(String bytes = TRIMS);
    };    
} // light

#endif // LIGHT_BASE_STRING_HPP
