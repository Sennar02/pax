#include <pax/Base/import.hpp>

using namespace pax;

void
test_option()
{
    const u64 value = 5;

    Option<u64> none;
    Option<u64> some = option_create<u64>(value);

    if ( none.valid == some.valid )
        pax_show("test", "Valid and invalid are both valid");

    if ( none.valid == true )
        pax_show("test", "Invalid is valid");

    if ( some.valid == false )
        pax_show("test", "Valid is invalid");

    if ( some.item != value )
        pax_show("test", "Valid value is wrong");
}

void
test_store()
{
    const u64 elem1 = 1;
    const u64 elem2 = 2;

    Store<u64, 2u> store =
        {elem1, elem2};

    if ( store(0) != elem1 )
        pax_show("test", "First element is wrong");

    if ( store(1) != elem2 )
        pax_show("test", "Second element is wrong");
}

void
test_string_count()
{
    const char* ptr = "Test";
    const u64   max = 4;

    u64 length = string_count(ptr, max);

    if ( length != max )
        pax_show("test", "String length is wrong");
}

void
test_string_create__limit()
{
    const char* ptr = "Test";
    const u64   max = 4;

    String string = string_create(ptr, max);

    if ( string.data != ptr )
        pax_show("test", "String data is wrong");

    if ( string.size != max )
        pax_show("test", "String size is wrong");
}

void
test_string_create__limit__zero_len()
{
    const char* ptr = "Test";

    String string = string_create(ptr, 0);

    if ( string.data != ptr )
        pax_show("test", "String data is wrong");

    if ( string.size != 0 )
        pax_show("test", "String size is wrong");
}

void
test_string_create__limit__null_ptr()
{
    const u64 max = 0;

    String string = string_create(0, max);

    if ( string.data == 0 )
        pax_show("test", "String data is wrong");

    if ( string.size != 0 )
        pax_show("test", "String size is wrong");
}

void
test_string_create__range()
{
    const char* ptr = "Test";
    const u64   min = 0;
    const u64   max = 4;

    String string = string_create(ptr, {min, max});

    if ( string.data != ptr )
        pax_show("test", "String data is wrong");

    if ( string.size != max )
        pax_show("test", "String size is wrong");
}

void
test_string_create__range__zero_len()
{
    const char* ptr = "Test";
    const u64   min = 0;
    const u64   max = 0;

    String string = string_create(ptr, {min, max});

    if ( string.data != ptr )
        pax_show("test", "String data is wrong");

    if ( string.size != 0 )
        pax_show("test", "String size is wrong");
}

void
test_string_create__range__null_ptr()
{
    const u64 min = 0;
    const u64 max = 4;

    String string = string_create(0, {min, max});

    if ( string.data == 0 )
        pax_show("test", "String data is wrong");

    if ( string.size != 0 )
        pax_show("test", "String size is wrong");
}

void
test_string_create__range__reverse()
{
    const u64 min = 4;
    const u64 max = 0;

    String string = string_create(0, {min, max});

    if ( string.data == 0 )
        pax_show("test", "String data is wrong");

    if ( string.size != 0 )
        pax_show("test", "String size is wrong");
}

void
test_string_create__range__truncate()
{
    const char* ptr = "Test";

    const u64 min = 0;
    const u64 max = 2;

    String string = string_create(ptr, {min, max});

    if ( string.data != ptr )
        pax_show("test", "String data is wrong");

    if ( string.size != max )
        pax_show("test", "String size is wrong");
}

void
test_string_create__range__discard()
{
    const char* ptr = "Test";

    const u64 min = 10;
    const u64 max = 12;

    String string = string_create(ptr, {min, max});

    if ( string.data == 0 )
        pax_show("test", "String data is wrong");

    if ( string.size != 0 )
        pax_show("test", "String size is wrong");
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

    list.insert(&deriv, list.count);

    if ( list(0)->func() != value )
        pax_show("test", "Virtual call returns wrong value");
}

void
test_base()
{
    test_option();
    test_store();
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
}