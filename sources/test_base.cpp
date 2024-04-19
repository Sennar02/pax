#include <pax/Base/import.hpp>

using namespace pax;

#define FATAL_ERROR \
    "\x1b[31m" "ERROR" "\x1b[0m"

void
test_option()
{
    const u64 value = 5;

    Option<u64> none;
    Option<u64> some = option_create<u64>(value);

    if ( none.full == some.full )
        pax_show(FATAL_ERROR, "Valid and invalid are both valid");

    if ( none.full == true )
        pax_show(FATAL_ERROR, "Invalid is valid");

    if ( some.full == false )
        pax_show(FATAL_ERROR, "Valid is invalid");

    if ( some.item != value )
        pax_show(FATAL_ERROR, "Valid value is wrong");
}

void
test_storage()
{
    const u64 elem1 = 1;
    const u64 elem2 = 2;

    Storage<u64, 2u> storage =
        {elem1, elem2};

    if ( storage(0) != elem1 )
        pax_show(FATAL_ERROR, "First element is wrong");

    if ( storage(1) != elem2 )
        pax_show(FATAL_ERROR, "Second element is wrong");
}

void
test_string_count()
{
    const char* ptr = "Test";
    const u64   max = 4;

    u64 length = string_count(ptr, max);

    if ( length != max )
        pax_show(FATAL_ERROR, "String length is wrong");
}

void
test_string_create__limit()
{
    const char* ptr = "Test";
    const u64   max = 4;

    String string = string_create(ptr, max);

    if ( string.data != ptr )
        pax_show(FATAL_ERROR, "String data is wrong");

    if ( string.size != max )
        pax_show(FATAL_ERROR, "String size is wrong");
}

void
test_string_create__limit__zero_len()
{
    const char* ptr = "Test";

    String string = string_create(ptr, 0);

    if ( string.data != ptr )
        pax_show(FATAL_ERROR, "String data is wrong");

    if ( string.size != 0 )
        pax_show(FATAL_ERROR, "String size is wrong");
}

void
test_string_create__limit__null_ptr()
{
    const u64 max = 0;

    String string = string_create(0, max);

    if ( string.data == 0 )
        pax_show(FATAL_ERROR, "String data is wrong");

    if ( string.size != 0 )
        pax_show(FATAL_ERROR, "String size is wrong");
}

void
test_string_create__range()
{
    const char* ptr = "Test";
    const u64   min = 0;
    const u64   max = 4;

    String string = string_create(ptr, {min, max});

    if ( string.data != ptr )
        pax_show(FATAL_ERROR, "String data is wrong");

    if ( string.size != max )
        pax_show(FATAL_ERROR, "String size is wrong");
}

void
test_string_create__range__zero_len()
{
    const char* ptr = "Test";
    const u64   min = 0;
    const u64   max = 0;

    String string = string_create(ptr, {min, max});

    if ( string.data != ptr )
        pax_show(FATAL_ERROR, "String data is wrong");

    if ( string.size != 0 )
        pax_show(FATAL_ERROR, "String size is wrong");
}

void
test_string_create__range__null_ptr()
{
    const u64 min = 0;
    const u64 max = 4;

    String string = string_create(0, {min, max});

    if ( string.data == 0 )
        pax_show(FATAL_ERROR, "String data is wrong");

    if ( string.size != 0 )
        pax_show(FATAL_ERROR, "String size is wrong");
}

void
test_string_create__range__reverse()
{
    const u64 min = 4;
    const u64 max = 0;

    String string = string_create(0, {min, max});

    if ( string.data == 0 )
        pax_show(FATAL_ERROR, "String data is wrong");

    if ( string.size != 0 )
        pax_show(FATAL_ERROR, "String size is wrong");
}

void
test_string_create__range__truncate()
{
    const char* ptr = "Test";

    const u64 min = 0;
    const u64 max = 2;

    String string = string_create(ptr, {min, max});

    if ( string.data != ptr )
        pax_show(FATAL_ERROR, "String data is wrong");

    if ( string.size != max )
        pax_show(FATAL_ERROR, "String size is wrong");
}

void
test_string_create__range__discard()
{
    const char* ptr = "Test";

    const u64 min = 10;
    const u64 max = 12;

    String string = string_create(ptr, {min, max});

    if ( string.data == 0 )
        pax_show(FATAL_ERROR, "String data is wrong");

    if ( string.size != 0 )
        pax_show(FATAL_ERROR, "String size is wrong");
}

void
test_list_virtuals()
{
    static const u64 value = 1;

    struct Abstr { virtual u64 func() = 0; };

    struct Deriv : public Abstr {
        u64 func() { return value; }
    };

    Deriv        deriv;
    List<Abstr*> list = list_create<Abstr*>(10u);

    list.insert(&deriv, 0);

    if ( list(0)->func() != value )
        pax_show(FATAL_ERROR, "Virtual call returns wrong value");

    list.release();
}

void
test_list_slide_above_size()
{
    const u64 size = 5u;

    List<u64> list = list_create<u64>(size);

    if ( list.slide(0, size) == false )
        pax_show(FATAL_ERROR, "List doesn't reach max size");

    if ( list.slide(0, size + 1u) == true )
        pax_show(FATAL_ERROR, "List is bigger than max size");

    list.release();
}

void
test_list_slide_below_zero()
{
    const u64 size = 5u;

    List<u64> list = list_create<u64>(size);

    if ( list.slide(0, -size) == true )
        pax_show(FATAL_ERROR, "List reaches negative size");

    list.release();
}

void
test_list_slide_create_hole()
{
    const u64 size = 5u;

    List<u64> list = list_create<u64>(size);

    list.slide(0, 2u);

    list(0) = size;
    list(1) = size;

    if ( list.count != 2u )
        pax_show(FATAL_ERROR, "List has wrong size");

    list.slide(2u, 3u);

    if ( list.count != 5u )
        pax_show(FATAL_ERROR, "List has wrong size");

    for ( u64 i = 0; i < 2u; i += 1u ) {
        if ( list(i) != size )
            pax_show_fmt(FATAL_ERROR, "Element %lu is wrong", i);
    }

    for ( u64 i = 2u; i < 5u; i += 1u ) {
        if ( list(i) != 0 )
            pax_show_fmt(FATAL_ERROR, "Element %lu is wrong", i);
    }

    list.release();
}

void
test_base()
{
    test_option();
    test_storage();
    test_string_count();
    test_string_create__limit();
    test_string_create__limit__zero_len();
    test_string_create__limit__null_ptr();
    test_string_create__range();
    test_string_create__range__zero_len();
    test_string_create__range__null_ptr();
    test_string_create__range__reverse();
    test_string_create__range__discard();
    test_string_create__range__truncate();
    test_list_virtuals();
    test_list_slide_above_size();
    test_list_slide_below_zero();
    test_list_slide_create_hole();
}
