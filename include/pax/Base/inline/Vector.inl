#include <pax/Base/Vector.hpp>
#include <pax/Base/macros.hpp>

namespace pax
{
    template <class Item, u64 Size, class Type>
    Vector<Item, Size>
    vector_create(const Vector<Type, Size>& other)
    {
        Vector<Item, Size> value;

        for ( u64 i = 0; i < value.SIZE; i += 1u )
            value.data[i] = (Item) other.data[i];

        return value;
    }

    template <class Item, u64 Size>
    const Vector<Item, Size> Vector<Item, Size>::ZERO
        = {};

    template <class Item, u64 Size>
    template <class Type>
    Item
    Vector<Item, Size>::inner(const Vector<Type, Size>& other) const
    {
        Item value = {};

        for ( u64 i = 0; i < SIZE; i += 1u )
            value += data[i] * (Item) other.data[i];

        return value;
    }

    template <class Item, u64 Size>
    Vector<Item, Size>
    Vector<Item, Size>::normal() const
    {
        Item value =
            inner(pax_self);

        return pax_self / sqrt(value);
    }

    template <class Item, u64 Size>
    Item
    Vector<Item, Size>::norm() const
    {
        Item value =
            inner(pax_self);

        return sqrt(value);
    }

    template <class Item, u64 Size>
    template <class Type>
    Vector<Item, Size>
    Vector<Item, Size>::operator+(const Vector<Type, Size>& other) const
    {
        Vector<Item, Size> value;

        for ( u64 i = 0; i < SIZE; i += 1u )
            value.data[i] = data[i] + (Item) other.data[i];

        return value;
    }

    template <class Item, u64 Size>
    template <class Type>
    Vector<Item, Size>
    Vector<Item, Size>::operator+(Type other) const
    {
        Vector<Item, Size> value;

        for ( u64 i = 0; i < SIZE; i += 1u )
            value.data[i] = data[i] + (Item) other;

        return value;
    }

    template <class Item, u64 Size>
    template <class Type>
    Vector<Item, Size>&
    Vector<Item, Size>::operator+=(const Vector<Type, Size>& other)
    {
        for ( u64 i = 0; i < SIZE; i += 1u )
            data[i] += (Item) other.data[i];

        return pax_self;
    }

    template <class Item, u64 Size>
    template <class Type>
    Vector<Item, Size>&
    Vector<Item, Size>::operator+=(Type other)
    {
        for ( u64 i = 0; i < SIZE; i += 1u )
            data[i] += (Item) other;

        return pax_self;
    }

    template <class Item, u64 Size>
    template <class Type>
    Vector<Item, Size>
    Vector<Item, Size>::operator-(const Vector<Type, Size>& other) const
    {
        Vector<Item, Size> value;

        for ( u64 i = 0; i < SIZE; i += 1u )
            value.data[i] = data[i] - (Item) other.data[i];

        return value;
    }

    template <class Item, u64 Size>
    template <class Type>
    Vector<Item, Size>
    Vector<Item, Size>::operator-(Type other) const
    {
        Vector<Item, Size> value;

        for ( u64 i = 0; i < SIZE; i += 1u )
            value.data[i] = data[i] - (Item) other;

        return value;
    }

    template <class Item, u64 Size>
    template <class Type>
    Vector<Item, Size>&
    Vector<Item, Size>::operator-=(const Vector<Type, Size>& other)
    {
        for ( u64 i = 0; i < SIZE; i += 1u )
            data[i] -= (Item) other.data[i];

        return pax_self;
    }

    template <class Item, u64 Size>
    template <class Type>
    Vector<Item, Size>&
    Vector<Item, Size>::operator-=(Type other)
    {
        for ( u64 i = 0; i < SIZE; i += 1u )
            data[i] -= (Item) other;

        return pax_self;
    }

    template <class Item, u64 Size>
    template <class Type>
    Vector<Item, Size>
    Vector<Item, Size>::operator*(const Vector<Type, Size>& other) const
    {
        Vector<Item, Size> value;

        for ( u64 i = 0; i < SIZE; i += 1u )
            value.data[i] = data[i] * (Item) other.data[i];

        return value;
    }

    template <class Item, u64 Size>
    template <class Type>
    Vector<Item, Size>
    Vector<Item, Size>::operator*(Type other) const
    {
        Vector<Item, Size> value;

        for ( u64 i = 0; i < SIZE; i += 1u )
            value.data[i] = data[i] * (Item) other;

        return value;
    }

    template <class Item, u64 Size>
    template <class Type>
    Vector<Item, Size>&
    Vector<Item, Size>::operator*=(const Vector<Type, Size>& other)
    {
        for ( u64 i = 0; i < SIZE; i += 1u )
            data[i] *= (Item) other.data[i];

        return pax_self;
    }

    template <class Item, u64 Size>
    template <class Type>
    Vector<Item, Size>&
    Vector<Item, Size>::operator*=(Type other)
    {
        for ( u64 i = 0; i < SIZE; i += 1u )
            data[i] *= (Item) other;

        return pax_self;
    }

    template <class Item, u64 Size>
    template <class Type>
    Vector<Item, Size>
    Vector<Item, Size>::operator/(const Vector<Type, Size>& other) const
    {
        Vector<Item, Size> value;

        for ( u64 i = 0; i < SIZE; i += 1u )
            value.data[i] = data[i] / (Item) other.data[i];

        return value;
    }

    template <class Item, u64 Size>
    template <class Type>
    Vector<Item, Size>
    Vector<Item, Size>::operator/(Type other) const
    {
        Vector<Item, Size> value;

        for ( u64 i = 0; i < SIZE; i += 1u )
            value.data[i] = data[i] / (Item) other;

        return value;
    }

    template <class Item, u64 Size>
    template <class Type>
    Vector<Item, Size>&
    Vector<Item, Size>::operator/=(const Vector<Type, Size>& other)
    {
        for ( u64 i = 0; i < SIZE; i += 1u )
            data[i] /= (Item) other.data[i];

        return pax_self;
    }

    template <class Item, u64 Size>
    template <class Type>
    Vector<Item, Size>&
    Vector<Item, Size>::operator/=(Type other)
    {
        for ( u64 i = 0; i < SIZE; i += 1u )
            data[i] /= (Item) other;

        return pax_self;
    }

    template <class Item, u64 Size>
    Item&
    Vector<Item, Size>::item(u64 index)
    {
        pax_test_fmt(index < SIZE,
            "bounds", "index = %lu exceedes size = %lu", index, SIZE
        );

        return data[index];
    }

    template <class Item, u64 Size>
    const Item&
    Vector<Item, Size>::item(u64 index) const
    {
        pax_test_fmt(index < SIZE,
            "bounds", "index = %lu exceedes size = %lu", index, SIZE
        );

        return data[index];
    }

    template <class Item, u64 Size>
    Item&
    Vector<Item, Size>::operator()(u64 index)
    {
        pax_test_fmt(index < SIZE,
            "bounds", "index = %lu exceedes size = %lu", index, SIZE
        );

        return data[index];
    }

    template <class Item, u64 Size>
    const Item&
    Vector<Item, Size>::operator()(u64 index) const
    {
        pax_test_fmt(index < SIZE,
            "bounds", "index = %lu exceedes size = %lu", index, SIZE
        );

        return data[index];
    }

    template <class Item, u64 Size>
    bool
    Vector<Item, Size>::operator==(const Vector<Item, Size>& other) const
    {
        for ( u64 i = 0; i < SIZE; i += 1u ) {
            if ( data[i] != other.data[i] )
                return false;
        }

        return true;
    }

    template <class Item, u64 Size>
    bool
    Vector<Item, Size>::operator!=(const Vector<Item, Size>& other) const
    {
        for ( u64 i = 0; i < SIZE; i += 1u ) {
            if ( data[i] != other.data[i] )
                return true;
        }

        return false;
    }
} // pax