#ifndef PAX_SIGNAL_SIGNAL_HPP
#define PAX_SIGNAL_SIGNAL_HPP

#include <pax/Signal/define.hpp>

namespace pax
{
    struct Signal
    {
    public:
        /**
         *
         */
        virtual u64
        kind() const = 0;
    };
} // pax

#endif // PAX_SIGNAL_SIGNAL_HPP
