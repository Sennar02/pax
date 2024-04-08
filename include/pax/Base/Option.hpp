#ifndef PAX_BASE_OPTION_HPP
#define PAX_BASE_OPTION_HPP

namespace pax
{
    template <class Item>
    struct Option
    {
    public:
        union {
            /**
             * When the option is full, the item is valid. Instead, when it's empty the state is undefined.
             */
            Item item;
        };

        /**
         * Determines if the option really contains a value.
         */
        bool full = false;

    public:
        /**
         * Default constructor to make the compiler happy in case of an ill-formed constructor.
         */
        Option();
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
