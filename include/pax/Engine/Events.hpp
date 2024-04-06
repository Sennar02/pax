#ifndef PAX_ENGINE_EVENTS_HPP
#define PAX_ENGINE_EVENTS_HPP

#include <pax/Engine/define.hpp>

namespace pax
{
    struct Events
    {
        static const u64 DISPLAY  = 0;
        static const u64 KEYBOARD = 1;
        static const u64 MOUSE    = 2;
    };

    struct Display_Event
    {
    public:
        /**
         * todo: Comment.
         */
        static const u64 SIGNAL_TYPE;

        /**
         * todo: Comment.
         */
        static const u64 FLAGS_CLOSE;

    public:
        /**
         * todo: Comment.
         */
        u64 flags = 0;

    public:
        /**
         * todo: Comment.
         */
        bool
        is_close() const;
    };

    struct Keybd_Event
    {
    public:
        /**
         * todo: Comment.
         */
        static const u64 SIGNAL_TYPE;

        /**
         * todo: Comment.
         */
        static const u64 FLAGS_REPEAT;

        /**
         * todo: Comment.
         */
        static const u64 FLAGS_PRESS;

    public:
        /**
         * todo: Comment.
         */
        u64 code = 0;

        /**
         * todo: Comment.
         */
        u64 modifs = 0;

        /**
         * todo: Comment.
         */
        u64 flags = 0;

    public:
        /**
         * todo: Comment.
         */
        bool
        is_repeat() const;

        /**
         * todo: Comment.
         */
        bool
        is_press() const;

        /**
         * todo: Comment.
         */
        bool
        is_release() const;
    };

    struct Mouse_Event
    {
    public:
        /**
         * todo: Comment.
         */
        static const u64 SIGNAL_TYPE;

        /**
         * todo: Comment.
         */
        static const u64 FLAGS_PRESS;

    public:
        /**
         * todo: Comment.
         */
        v2s64 coords = {};

        /**
         * todo: Comment.
         */
        v2s64 motion = {};

        /**
         * todo: Comment.
         */
        v2s64 scroll = {};

        /**
         * todo: Comment.
         */
        s64 orient = 1;

        /**
         * todo: Comment.
         */
        u64 button = 0;

        /**
         * todo: Comment.
         */
        u64 clicks = 0;

        /**
         * todo: Comment.
         */
        u64 flags = 0;

    public:
        /**
         * todo: Comment.
         */
        bool
        is_repeat() const;

        /**
         * todo: Comment.
         */
        bool
        is_press() const;

        /**
         * todo: Comment.
         */
        bool
        is_release() const;
    };

    /**
     * todo: Comment.
     */
    bool
    event_poll(Dispatcher& dispat);

    /**
     * todo: Comment.
     */
    void
    event_update();
} // pax

#endif // PAX_ENGINE_EVENTS_HPP
