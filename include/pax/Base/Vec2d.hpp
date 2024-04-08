#ifndef PAX_BASE_VEC_2D_HPP
#define PAX_BASE_VEC_2D_HPP

#include <pax/Base/define.hpp>
#include <pax/Base/Vector.hpp>

namespace pax
{
    template <class Item>
    struct Vector<Item, 2u>
    {
    public:
        /**
         * Special vector which contains (x, y) = (0, 0).
         */
        static const Vector<Item, 2u> ZERO;

        /**
         * Special vector which contains (x, y) = (1, 0).
         */
        static const Vector<Item, 2u> UNIT_X;

        /**
         * Special vector which contains (x, y) = (0, 1).
         */
        static const Vector<Item, 2u> UNIT_Y;

        /**
         * Amount of elements in the array.
         */
        static const u64 SIZE = 2u;

    public:
        /**
         * Static array of elements.
         */
        Item data[SIZE];

    public:
        /**
         * Returns the inner (or also dot) product of two vectors.
         */
        template <class Type>
        Item
        inner(const Vector<Type, 2u>& other) const;

        /**
         * Returns the cross product of two vectors.
         */
        template <class Type>
        Item
        cross(const Vector<Type, 2u>& other) const;

        /**
         * Returns an unit vector which points in the same direction as the original one.
         */
        Vector<Item, 2u>
        normal() const;

        /**
         * Returns the magnitude of the vector.
         */
        Item
        norm() const;

        /**
         * Returns the addition of two vectors.
         */
        template <class Type>
        Vector<Item, 2u>
        operator+(const Vector<Type, 2u>& other) const;

        /**
         * Returns the addition of a vector and a scalar.
         */
        template <class Type>
        Vector<Item, 2u>
        operator+(Type other) const;

        /**
         * Returns the addition of two vectors.
         */
        template <class Type>
        Vector<Item, 2u>&
        operator+=(const Vector<Type, 2u>& other);

        /**
         * Returns the addition of a vector and a scalar.
         */
        template <class Type>
        Vector<Item, 2u>&
        operator+=(Type other);

        /**
         * Returns the subtraction of two vectors.
         */
        template <class Type>
        Vector<Item, 2u>
        operator-(const Vector<Type, 2u>& other) const;

        /**
         * Returns the subtraction of a vector and a scalar.
         */
        template <class Type>
        Vector<Item, 2u>
        operator-(Type other) const;

        /**
         * Returns the subtraction of two vectors.
         */
        template <class Type>
        Vector<Item, 2u>&
        operator-=(const Vector<Type, 2u>& other);

        /**
         * Returns the subtraction of a vector and a scalar.
         */
        template <class Type>
        Vector<Item, 2u>&
        operator-=(Type other);

        /**
         * Returns the Hadamard multiplication of two vectors.
         */
        template <class Type>
        Vector<Item, 2u>
        operator*(const Vector<Type, 2u>& other) const;

        /**
         * Returns the Hadamard multiplication of a vector and a scalar.
         */
        template <class Type>
        Vector<Item, 2u>
        operator*(Type other) const;

        /**
         * Returns the Hadamard multiplication of two vectors.
         */
        template <class Type>
        Vector<Item, 2u>&
        operator*=(const Vector<Type, 2u>& other);

        /**
         * Returns the Hadamard multiplication of a vector and a scalar.
         */
        template <class Type>
        Vector<Item, 2u>&
        operator*=(Type other);

        /**
         * Returns the Hadamard division of two vectors.
         */
        template <class Type>
        Vector<Item, 2u>
        operator/(const Vector<Type, 2u>& other) const;

        /**
         * Returns the Hadamard division of a vector and a scalar.
         */
        template <class Type>
        Vector<Item, 2u>
        operator/(Type other) const;

        /**
         * Returns the Hadamard division of two vectors.
         */
        template <class Type>
        Vector<Item, 2u>&
        operator/=(const Vector<Type, 2u>& other);

        /**
         * Returns the Hadamard division of a vector and a scalar.
         */
        template <class Type>
        Vector<Item, 2u>&
        operator/=(Type other);

        /**
         * Returns the element contained in a particular index.
         */
        Item&
        item(u64 index);

        /**
         * Returns the element contained in a particular index.
         */
        const Item&
        item(u64 index) const;

        /**
         * Returns the element contained in a particular index.
         */
        Item&
        operator()(u64 index);

        /**
         * Returns the element contained in a particular index.
         */
        const Item&
        operator()(u64 index) const;

        /**
         * Returns true if two vectors contain the same elements, false otherwise.
         */
        bool
        operator==(const Vector<Item, 2u>& other) const;

        /**
         * Returns true if two vectors contain a different element in at least an index, false otherwise.
         */
        bool
        operator!=(const Vector<Item, 2u>& other) const;
    };

    /**
     * Generates a vector from another one.
     */
    template <class Item, class Type>
    Vector<Item, 2u>
    vec2d_create(const Vector<Type, 2u>& other);

    /**
     * Returns the determinant of the two by two matrix formed by two row vectors.
     */
    template <class Item>
    Item
    vec2d_determ(const Vector<Item, 2u>& v1, const Vector<Item, 2u>& v2);
} // pax

#include <pax/Base/inline/Vec2d.inl>

#endif // PAX_BASE_VEC_2D_HPP
