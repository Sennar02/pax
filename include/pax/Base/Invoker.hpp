#ifndef PAX_BASE_INVOKER_HPP
#define PAX_BASE_INVOKER_HPP

#include <pax/Base/define.hpp>

namespace pax
{
    struct Invoked
    {
    public:
        /**
         * todo: Comment.
         */
        void* func;

        /**
         * todo: Comment.
         */
        void* ctxt;
    };

    template <class Resl, class... Args>
    struct Invoker<Resl(Args...)>
    {
    public:
        /**
         * todo: Comment.
         */
        void* func = 0;

        /**
         * todo: Comment.
         */
        void* ctxt = 0;

    public:
        /**
         * todo: Comment.
         */
        Invoker();

        /**
         * todo: Comment.
         */
        template <class Ctxt>
        bool
        acquire(Resl (*func) (Ctxt*, Args...), Ctxt& ctxt);

        /**
         * todo: Comment.
         */
        bool
        acquire(Resl (*func) (Args...));

        /**
         * todo: Comment.
         */
        bool
        release();

        /**
         * todo: Comment.
         */
        bool
        is_valid() const;

        /**
         * todo: Comment.
         */
        Resl
        invoke(Args... args) const;

        /**
         * todo: Comment.
         */
        Resl
        operator()(Args... args) const;
    };

    /**
     * todo: Comment.
     */
    template <class Resl, class Ctxt, class... Args>
    Invoker<Resl(Args...)>
    invoker_create(Resl (*func) (Ctxt*, Args...), Ctxt& ctxt);

    /**
     * todo: Comment.
     */
    template <class Resl, class... Args>
    Invoker<Resl(Args...)>
    invoker_create(Resl (*func) (Args...));

    /**
     * todo: Comment.
     */
    template <class Resl, class... Args>
    Invoker<Resl(Args...)>
    invoker_create(Invoked invoked);

    /**
     * todo: Comment.
     */
    template <class Resl, class... Args>
    Resl
    invoke(Invoked invoked, Args... args);
} // namespace pax

#include <pax/Base/inline/Invoker.inl>

#endif // PAX_BASE_INVOKER_HPP
