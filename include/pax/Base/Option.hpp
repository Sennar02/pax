#ifndef PAX_BASE_OPTION_HPP
#define PAX_BASE_OPTION_HPP

namespace pax
{
    template <class Item>
    struct Option
    {
    public:
        /**
         * When the option is invalid this member is empty, otherwise contains a specific value.
         */
        Item item = {};

        /**
         * Determines if the option really contains a value.
         */
        bool valid = false;
    };

    /**
     * Generates an option from a value.
     */
    template <class Item>
    Option<Item>
    option_create(Item item);
} // pax

#include <pax/Base/inline/Option.inl>

#endif // PAX_BASE_OPTION_HPP