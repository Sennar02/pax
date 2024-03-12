#include <pax/Memory/Builder.hpp>

namespace pax
{
    Builder&
    Builder::reset()
    {
        alloc->reset();

        return * this;
    }
} // pax
