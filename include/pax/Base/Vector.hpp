#ifndef PAX_BASE_VECTOR_HPP
#define PAX_BASE_VECTOR_HPP

#include <pax/Base/define.hpp>

namespace pax
{
    template <class Item, u64 Size>
    struct Vector
    {
    public:
        /**
         * Special vector which equals (x_1, ..., x_n) = (0, ..., 0).
         */
        static const Vector<Item, Size> ZERO;

        /**
         * Amount of elements in the array.
         */
        static const u64 SIZE = Size;

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
        inner(const Vector<Type, Size>& other) const;

        /**
         * Returns an unit vector which points in the same direction as the original one.
         */
        Vector<Item, Size>
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
        Vector<Item, Size>
        operator+(const Vector<Type, Size>& other) const;

        /**
         * Returns the addition of a vector and a scalar.
         */
        template <class Type>
        Vector<Item, Size>
        operator+(Type other) const;

        /**
         * Returns the addition of two vectors.
         */
        template <class Type>
        Vector<Item, Size>&
        operator+=(const Vector<Type, Size>& other);

        /**
         * Returns the addition of a vector and a scalar.
         */
        template <class Type>
        Vector<Item, Size>&
        operator+=(Type other);

        /**
         * Returns the subtraction of two vectors.
         */
        template <class Type>
        Vector<Item, Size>
        operator-(const Vector<Type, Size>& other) const;

        /**
         * Returns the subtraction of a vector and a scalar.
         */
        template <class Type>
        Vector<Item, Size>
        operator-(Type other) const;

        /**
         * Returns the subtraction of two vectors.
         */
        template <class Type>
        Vector<Item, Size>&
        operator-=(const Vector<Type, Size>& other);

        /**
         * Returns the subtraction of a vector and a scalar.
         */
        template <class Type>
        Vector<Item, Size>&
        operator-=(Type other);

        /**
         * Returns the Hadamard multiplication of two vectors.
         */
        template <class Type>
        Vector<Item, Size>
        operator*(const Vector<Type, Size>& other) const;

        /**
         * Returns the Hadamard multiplication of a vector and a scalar.
         */
        template <class Type>
        Vector<Item, Size>
        operator*(Type other) const;

        /**
         * Returns the Hadamard multiplication of two vectors.
         */
        template <class Type>
        Vector<Item, Size>&
        operator*=(const Vector<Type, Size>& other);

        /**
         * Returns the Hadamard multiplication of a vector and a scalar.
         */
        template <class Type>
        Vector<Item, Size>&
        operator*=(Type other);

        /**
         * Returns the Hadamard division of two vectors.
         */
        template <class Type>
        Vector<Item, Size>
        operator/(const Vector<Type, Size>& other) const;

        /**
         * Returns the Hadamard division of a vector and a scalar.
         */
        template <class Type>
        Vector<Item, Size>
        operator/(Type other) const;

        /**
         * Returns the Hadamard division of two vectors.
         */
        template <class Type>
        Vector<Item, Size>&
        operator/=(const Vector<Type, Size>& other);

        /**
         * Returns the Hadamard division of a vector and a scalar.
         */
        template <class Type>
        Vector<Item, Size>&
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
        operator==(const Vector<Item, Size>& other) const;

        /**
         * Returns true if two vectors contain a different element in at least an index, false otherwise.
         */
        bool
        operator!=(const Vector<Item, Size>& other) const;
    };

    /**
     * Generates a vector from another one.
     */
    template <class Item, u64 Size, class Type>
    Vector<Item, Size>
    vector_create(const Vector<Type, Size>& other);
} // pax

#include <pax/Base/inline/Vector.inl>

#endif // PAX_BASE_VECTOR_HPP