#ifndef PAX_SIGNAL_SOURCE_HPP
#define PAX_SIGNAL_SOURCE_HPP

#include <pax/Signal/define.hpp>
#include <pax/Signal/Dispatcher.hpp>

namespace pax
{
    struct Source
    {
    public:
        /**
         *
         */
        virtual void
        provide(Dispatcher& dispat) = 0;
    };
} // pax

#endif // PAX_SIGNAL_SOURCE_HPP