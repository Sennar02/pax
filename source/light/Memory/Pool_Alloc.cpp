#include <light/Memory/Pool_Alloc.hpp>

namespace light
{
    struct Pool_Alloc::Node {
        Node* next;
    };

    struct Pool_Alloc::Pref {
        u64 flag;
    };

    static const u64 FLAG_USED = 1;

    static const u64 LEN_NODE = sizeof(Pool_Alloc::Node);
    static const u64 LEN_PREF = sizeof(Pool_Alloc::Pref);

    Pool_Alloc::Pool_Alloc() {}

    Pool_Alloc::Pool_Alloc(void* data, u64 size, u64 page, u8 align)
    {
        if ( data != 0 && size != 0 ) {
            this->data = (s8*) data;
            this->size = size;

            reset(page, align);
        }
    }

    Opt<void*>
    Pool_Alloc::reserve(u64 bytes, u8 align)
    {
        s8*   pntr = remove(bytes, align);
        Pref* pref = (Pref*) (pntr - LEN_PREF);

        if ( pntr != 0 ) {
            pref->flag =
                bit_write(pref->flag, FLAG_USED, 1);

            for ( u64 i = 0; i < page; i += 1u )
                pntr[i] = 0;

            return pntr;
        }

        return {};
    }

    bool
    Pool_Alloc::reclaim(void* addr)
    {
        s8*   pntr = (s8*) addr;
        Pref* pref = (Pref*) (pntr - LEN_PREF);

        if ( pntr == 0 ) return true;

        if ( pntr != 0 ) {
            if ( bit_test(pref->flag, FLAG_USED) ) {
                pref->flag =
                    bit_write(pref->flag, FLAG_USED, 0);

                return insert(pntr);
            }
        }

        return false;
    }

    void
    Pool_Alloc::reset()
    {
        reset(page, 1u);
    }

    Opt<void*>
    Pool_Alloc::reserve()
    {
        return reserve(page, 1u);
    }

    void
    Pool_Alloc::reset(u64 page, u8 align)
    {
        s8* addr  = data + round_diff(data, align, LEN_PREF);
        u64 count = 0;

        if ( page < LEN_NODE ) return;

        if ( data != 0 ) {
            this->page = page;

            for ( u64 i = 0; i < size; i += 1u )
                data[i] = 0;

            count = size / (page + LEN_PREF);

            for ( u64 i = 0; i < count; i += 1u ) {
                insert(addr);

                addr += LEN_PREF;
                addr += page;
            }
        }
    }

    bool
    Pool_Alloc::insert(void* addr)
    {
        s8*   pntr = (s8*) addr + LEN_NODE;
        Node* node = (Node*) pntr;

        if ( addr != 0 ) {
            node->next = list;
            list       = node;
        }

        return addr != 0;
    }

    s8*
    Pool_Alloc::remove(u64 bytes, u8 align)
    {
        Node* node = list;
        u64   diff = round_diff(node, align, 0);

        if ( node == 0 ) return 0;

        if ( bytes <= page && diff == 0 ) {
            list = list->next;

            return (s8*) node;
        }

        return 0;
    }
} // light
