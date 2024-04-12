#include <pax/Base/Invoker.hpp>

namespace pax
{
    template <class Resl, class Ctxt, class... Args>
    Invoker<Resl(Args...)>
    invoker_create(Resl (*func) (Ctxt*, Args...), Ctxt& ctxt)
    {
        Invoker<Resl(Args...)> value;

        if ( func != 0 ) {
            value.func = (void*) func;
            value.ctxt = (void*) &ctxt;
        }

        return value;
    }

    template <class Resl, class... Args>
    Invoker<Resl(Args...)>
    invoker_create(Resl (*func) (Args...))
    {
        Invoker<Resl(Args...)> value;

        if ( func != 0 )
            value.func = (void*) func;

        return value;
    }

    template <class Resl, class... Args>
    Invoker<Resl(Args...)>
    invoker_create(Invoked invoked)
    {
        Invoker<Resl(Args...)> value;

        value.func = invoked.func;
        value.ctxt = invoked.ctxt;

        return value;
    }

    template <class Resl, class... Args>
    Resl
    invoke(Invoked invoked, Args... args)
    {
        Invoker<Resl(Args...)> value;

        value.func = invoked.func;
        value.ctxt = invoked.ctxt;

        return value.invoke(args...);
    }

    template <class Resl, class... Args>
    Invoker<Resl(Args...)>::Invoker()
    { }

    template <class Resl, class... Args>
    template <class Ctxt>
    bool
    Invoker<Resl(Args...)>::acquire(Resl (*func) (Ctxt*, Args...), Ctxt& ctxt)
    {
        if ( func != 0 ) {
            this->func = (void*) func;
            this->ctxt = (void*) &ctxt;

            return true;
        }

        return false;
    }

    template <class Resl, class... Args>
    bool
    Invoker<Resl(Args...)>::acquire(Resl (*func) (Args...))
    {
        if ( func != 0 ) {
            this->func = (void*) func;
            this->ctxt = (void*) 0;

            return true;
        }

        return false;
    }

    template <class Resl, class... Args>
    bool
    Invoker<Resl(Args...)>::release()
    {
        func = 0;
        ctxt = 0;

        return true;
    }

    template <class Resl, class... Args>
    bool
    Invoker<Resl(Args...)>::is_valid() const
    {
        return func != 0;
    }

    template <class Resl, class... Args>
    Resl
    Invoker<Resl(Args...)>::invoke(Args... args) const
    {
        using Free_Func = Resl(Args...);
        using Ctxt_Func = Resl(void*, Args...);

        pax_test(func != 0,
            "null", "pointer is null"
        );

        if ( ctxt != 0 )
            return ((Ctxt_Func*) func)(ctxt, args...);

        return ((Free_Func*) func)(args...);
    }

    template <class Resl, class... Args>
    Resl
    Invoker<Resl(Args...)>::operator()(Args... args) const
    {
        return invoke(args...);
    }
} // pax
