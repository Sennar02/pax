#include <pax/Base/Vec2d.hpp>
#include <pax/Base/macros.hpp>

namespace pax
{
    template <class Item, class Type>
    Vector<Item, 2u>
    vec2d_create(const Vector<Type, 2u>& other)
    {
        Vector<Item, 2u> value;

        value.data[0] = (Item) other.data[0];
        value.data[1] = (Item) other.data[1];

        return value;
    }

    template <class Item>
    Item
    vec2d_determ(const Vector<Item, 2u>& v1, const Vector<Item, 2u>& v2)
    {
        return v1.data[0] * v2.data[1] -
               v1.data[1] * v2.data[0];
    }

    template <class Item>
    const Vector<Item, 2u> Vector<Item, 2u>::ZERO
        = {0, 0};

    template <class Item>
    const Vector<Item, 2u> Vector<Item, 2u>::UNIT_X
        = {1, 0};

    template <class Item>
    const Vector<Item, 2u> Vector<Item, 2u>::UNIT_Y
        = {0, 1};

    template <class Item>
    template <class Type>
    Item
    Vector<Item, 2u>::inner(const Vector<Type, 2u>& other) const
    {
        return data[0] * (Item) other.data[0] +
               data[1] * (Item) other.data[1];
    }

    template <class Item>
    template <class Type>
    Item
    Vector<Item, 2u>::cross(const Vector<Type, 2u>& other) const
    {
        return vec2d_determ(pax_self, (Vector<Item, 2u>) other);
    }

    template <class Item>
    Vector<Item, 2u>
    Vector<Item, 2u>::normal() const
    {
        if ( pax_self != Vec2d<Item>::ZERO )
            return pax_self / norm();

        return pax_self;
    }

    template <class Item>
    Item
    Vector<Item, 2u>::norm() const
    {
        Item square = inner(pax_self);

        return sqrt(square);
    }

    template <class Item>
    template <class Type>
    Vector<Item, 2u>
    Vector<Item, 2u>::operator+(const Vector<Type, 2u>& other) const
    {
        Vector<Item, 2u> value;

        value.data[0] = data[0] + (Item) other.data[0];
        value.data[1] = data[1] + (Item) other.data[1];

        return value;
    }

    template <class Item>
    template <class Type>
    Vector<Item, 2u>
    Vector<Item, 2u>::operator+(Type other) const
    {
        Vector<Item, 2u> value;

        value.data[0] = data[0] + (Item) other;
        value.data[1] = data[1] + (Item) other;

        return value;
    }

    template <class Item>
    template <class Type>
    Vector<Item, 2u>&
    Vector<Item, 2u>::operator+=(const Vector<Type, 2u>& other)
    {
        data[0] += (Item) other.data[0];
        data[1] += (Item) other.data[1];

        return pax_self;
    }

    template <class Item>
    template <class Type>
    Vector<Item, 2u>&
    Vector<Item, 2u>::operator+=(Type other)
    {
        data[0] += (Item) other;
        data[1] += (Item) other;

        return pax_self;
    }

    template <class Item>
    template <class Type>
    Vector<Item, 2u>
    Vector<Item, 2u>::operator-(const Vector<Type, 2u>& other) const
    {
        Vector<Item, 2u> value;

        value.data[0] = data[0] - (Item) other.data[0];
        value.data[1] = data[1] - (Item) other.data[1];

        return value;
    }

    template <class Item>
    template <class Type>
    Vector<Item, 2u>
    Vector<Item, 2u>::operator-(Type other) const
    {
        Vector<Item, 2u> value;

        value.data[0] = data[0] - (Item) other;
        value.data[1] = data[1] - (Item) other;

        return value;
    }

    template <class Item>
    template <class Type>
    Vector<Item, 2u>&
    Vector<Item, 2u>::operator-=(const Vector<Type, 2u>& other)
    {
        data[0] -= (Item) other.data[0];
        data[1] -= (Item) other.data[1];

        return pax_self;
    }

    template <class Item>
    template <class Type>
    Vector<Item, 2u>&
    Vector<Item, 2u>::operator-=(Type other)
    {
        data[0] -= (Item) other;
        data[1] -= (Item) other;

        return pax_self;
    }

    template <class Item>
    template <class Type>
    Vector<Item, 2u>
    Vector<Item, 2u>::operator*(const Vector<Type, 2u>& other) const
    {
        Vector<Item, 2u> value;

        value.data[0] = data[0] * (Item) other.data[0];
        value.data[1] = data[1] * (Item) other.data[1];

        return value;
    }

    template <class Item>
    template <class Type>
    Vector<Item, 2u>
    Vector<Item, 2u>::operator*(Type other) const
    {
        Vector<Item, 2u> value;

        value.data[0] = data[0] * (Item) other;
        value.data[1] = data[1] * (Item) other;

        return value;
    }

    template <class Item>
    template <class Type>
    Vector<Item, 2u>&
    Vector<Item, 2u>::operator*=(const Vector<Type, 2u>& other)
    {
        data[0] *= (Item) other.data[0];
        data[1] *= (Item) other.data[1];

        return pax_self;
    }

    template <class Item>
    template <class Type>
    Vector<Item, 2u>&
    Vector<Item, 2u>::operator*=(Type other)
    {
        data[0] *= (Item) other;
        data[1] *= (Item) other;

        return pax_self;
    }

    template <class Item>
    template <class Type>
    Vector<Item, 2u>
    Vector<Item, 2u>::operator/(const Vector<Type, 2u>& other) const
    {
        Vector<Item, 2u> value;

        value.data[0] = data[0] / (Item) other.data[0];
        value.data[1] = data[1] / (Item) other.data[1];

        return value;
    }

    template <class Item>
    template <class Type>
    Vector<Item, 2u>
    Vector<Item, 2u>::operator/(Type other) const
    {
        Vector<Item, 2u> value;

        value.data[0] = data[0] / (Item) other;
        value.data[1] = data[1] / (Item) other;

        return value;
    }

    template <class Item>
    template <class Type>
    Vector<Item, 2u>&
    Vector<Item, 2u>::operator/=(const Vector<Type, 2u>& other)
    {
        data[0] /= (Item) other.data[0];
        data[1] /= (Item) other.data[1];

        return pax_self;
    }

    template <class Item>
    template <class Type>
    Vector<Item, 2u>&
    Vector<Item, 2u>::operator/=(Type other)
    {
        data[0] /= (Item) other;
        data[1] /= (Item) other;

        return pax_self;
    }

    template <class Item>
    Item&
    Vector<Item, 2u>::item(u64 index)
    {
        pax_test_fmt(index < SIZE,
            "bounds", "index = %lu exceedes size = %lu", index, SIZE
        );

        return data[index];
    }

    template <class Item>
    const Item&
    Vector<Item, 2u>::item(u64 index) const
    {
        pax_test_fmt(index < SIZE,
            "bounds", "index = %lu exceedes size = %lu", index, SIZE
        );

        return data[index];
    }

    template <class Item>
    Item&
    Vector<Item, 2u>::operator()(u64 index)
    {
        return item(index);
    }

    template <class Item>
    const Item&
    Vector<Item, 2u>::operator()(u64 index) const
    {
        return item(index);
    }

    template <class Item>
    bool
    Vector<Item, 2u>::operator==(const Vector<Item, 2u>& other) const
    {
        return data[0] == other.data[0] &&
               data[1] == other.data[1];
    }

    template <class Item>
    bool
    Vector<Item, 2u>::operator!=(const Vector<Item, 2u>& other) const
    {
        return data[0] != other.data[0] ||
               data[1] != other.data[1];
    }
} // pax
