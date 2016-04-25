
//
//  big_number.cpp
//
//  Class that implements a BigNumber representation.
//
//  Created by Ryan Faulkner on 4/16/13.
//  Copyright (c) 2013. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;


class BigNumber {

    public:

        BigNumber()
        {
            this->digits = NULL;
            this->size = 0;
            this->is_neg = false;
            this->remainder = NULL;
        }

        BigNumber(const BigNumber& bn)
        {

            this->digits = new int[bn.get_size()];
            this->size = bn.get_size();
            this->is_neg = bn.is_negative_number();
            this->digits = bn.get_digits_copy();
            this->remainder = bn.get_remainder_copy();
        }

        BigNumber(int dim) {
            this->digits = new int[dim];
            this->size = dim;
            this->is_neg = false;
            for (int i = 0; i < dim; i++) this->digits[i] = 0;
            this->remainder = NULL;
        }

        BigNumber(int dim, long val) {
            int i;

            this->digits = new int[dim];
            this->size = dim;
            this->is_neg = false;
            for (i = 0; i < dim; i++) {
                this->digits[i] = val % 10;
                val /= 10;
            }
            this->remainder = NULL;
        }

        ~BigNumber() {
            delete[] this->digits;
            if (this->remainder != NULL)
                    delete[] this->remainder;
        }

        /*
         *  Prints the number
         */
        void print() const {
            for (int i = this->size - 1; i >= 0; i--) cout << this->digits[i];
            cout << endl;
        }

        /*
         *  Prints the remainder
         */
        void print_remainder() const {
            if (this->remainder != NULL)
            {
                for (int i = this->size - 1; i >= 0; i--) cout << this->remainder[i];
                cout << endl;
            }
        }

        bool is_negative_number() const { return this->is_neg; }
        int get_size() const { return this->size; }
        int get_digit(int index) const { return this->digits[index]; }

        int get_most_significant_digit() const
        {
            for (int i = this->size - 1; i >= 0; i--)
                if (digits[i] > 0)
                    return i;
             return 0;
        }

        int* get_digits_copy() const
        {
            int* digits_cp = new int[this->size];
            for (int i = 0; i < this->size; i++)
                digits_cp[i] = this->digits[i];
            return digits_cp;
        }

        int* get_remainder_copy() const
        {
            if (this->remainder != NULL)
            {
                int* rem_cp = new int[this->size];
                for (int i = 0; i < this->size; i++)
                    rem_cp[i] = this->remainder[i];
                return rem_cp;
            }
            return NULL;
        }

        bool has_remainder() {
            if (this->remainder != NULL)
            {
                for (int i = 0; i < this->size; i++)
                    if (this->remainder[i] > 0)
                        return true;
            }
            return false;
        }

        void set_digits(int* digits) {
            delete [] this->digits;
            this->digits = digits;
            this->size = sizeof(digits) / sizeof(int);
        }

        /*
         *  Set a digit in the array
         */
        bool set_digit(int index, int value)
        {
            int most_sigdig = this->get_most_significant_digit();
            if (value < 10 && value >= 0 && index >= 0 && index <= most_sigdig)
            {
                this->digits[index] = value;
                return true;
            }
            return false;
        }

        /*
         *  Right shift the digits
         */
        void right_shift()
        {
            int* new_digits = new int[this->size];

            for (int i = 1; i < this->size; i++)
                new_digits[i - 1] = this->digits[i];

            new_digits[this->size - 1] = 0;
            delete[] this->digits;
            this->digits = new_digits;
        }

        /*
         *  Left shift the digits
         */
        void left_shift() {
            int* new_digits = new int[this->size];

            for (int i = this->size - 1; i > 0; i--)
                new_digits[i] = this->digits[i-1];

            new_digits[0] = 0;
            delete[] this->digits;
            this->digits = new_digits;
        }

        BigNumber & operator=(const BigNumber &rhs)
        {
            // Check for self-assignment!
            if (this == &rhs)
                return *this;

            delete[] this->digits;

            this->size = rhs.get_size();
            this->digits = rhs.get_digits_copy();
            this->is_neg = rhs.is_negative_number();
            this->remainder = rhs.get_remainder_copy();

            return *this;
        }

        /*
         * Adds this big number by the arg - size of operands
         */
        BigNumber & operator+=(const BigNumber& other)
        {
            int i, new_val, carry = 0;

            // TODO - throw exception instead
            if (this->size != other.get_size())
            {
                cout << "BigNumber::operator+= - Mismatched sizes." << endl;
                return *(new BigNumber(1,0));
            }

            for (i=0; i < this->size; i++)
            {
                new_val = this->digits[i] + other.get_digit(i) + carry;

                this->digits[i] = new_val % 10;
                if (new_val >= 10)
                    carry = new_val / 10;
                else
                    carry = 0;
            }

            // TODO - throw exception instead
            if (carry > 0)
                cout << "BigNumber::operator+= - Overflow." << endl;

            return *this;
        }

        /*
         * Adds this big number by the arg - size of operands
         */
        BigNumber & operator-=(const BigNumber& other)
        {
            int i, new_val;
            int this_msd = this->get_most_significant_digit();
            int other_msd = other.get_most_significant_digit();
            bool this_larger = true;
            int last_idx = this->size - 1;
            int* digits_cp = other.get_digits_copy();

            int *large_ref, *small_ref;

            // TODO - throw exception instead
            if (this->size != other.get_size())
            {
                cout << "BigNumber::operator-= - Mismatched sizes." << endl;
                return *(new BigNumber(1,0));
            }

            // Determine which is larger
            if (other_msd > this_msd)
                this_larger = false;
            else if (other_msd == this_msd)
                for (i = this_msd; i >= 0; i--)
                {
                    if (this->digits[i] < digits_cp[i])
                    {
                        this_larger = false;
                        this->is_neg = true;
                        break;
                    }
                    else if (this->digits[i] > digits_cp[i])
                        break;
                }

            // Set refs
            if (this_larger)
            {
                large_ref = this->digits;
                small_ref = digits_cp;
            }
            else
            {
                small_ref = this->digits;
                large_ref = digits_cp;
            }

            // Perform subtraction
            for (i = 0; i < this->size-1; i++)
            {

                new_val = large_ref[i] - small_ref[i];

                // need to borrow?
                if (new_val < 0)
                {
                    large_ref[i] = new_val + 10;
                    large_ref[i+1] -= 1;
                }
                else
                    large_ref[i] = new_val;
            }

            new_val = large_ref[last_idx] - small_ref[last_idx];
            large_ref[last_idx] = new_val;

            if (large_ref != this->digits)
                for (i = 0; i < this->size; i++)
                    this->digits[i] = large_ref[i];
            delete[] digits_cp;

            return *this;
        }

        /*
         *  Divide this big number by the arg.  Uses long division.
         *
         */
        BigNumber & operator/=(const BigNumber& other)
        {
            int digit_value = 0;
            int digit_index = this->get_most_significant_digit();

            int* new_digits = new int[this->size];

            BigNumber remainder(this->size, 0);

            // Perform division
            while (digit_index >= 0) {

                digit_value = 0;

                remainder.left_shift();
                remainder.set_digit(0, this->digits[digit_index]);

                while (remainder >= other) {
                    digit_value++;
                    remainder -= other;
                }

                new_digits[digit_index] = digit_value;
                digit_index--;
            }

            // Keep the padding consistent
            for (int i = this->get_most_significant_digit() + 1; i < this->size; i++)
                new_digits[i] = 0;

            // Assign result and remainder
            delete[] this->digits;
            this->digits = new_digits;

            if (this->remainder != NULL)
                delete this->remainder;

            this->remainder = remainder.get_digits_copy();

            return *this;
        }

        /*
         * Multiplies this big number by the arg
         */
        BigNumber & operator*=(const int &other) {

            int i, new_val, carry = 0;

            for (i=0; i < this->size; i++) {
                new_val = digits[i] * other + carry;
                this->digits[i] = new_val % 10;
                if (new_val >= 10)
                    carry = new_val / 10;
                else
                    carry = 0;
            }

            return *this;
        }

        bool operator>(const BigNumber &rhs) const {

            if (this->size < rhs.get_size())
                for (int i = this->size; i < rhs.get_size(); i++)
                    if (rhs.get_digit(i) > 0)
                        return false;
            else if (this->size > rhs.get_size())
                for (int i = this->size - 1; i > rhs.get_size() - 1; i--)
                    if (this->digits[i] > 0)
                        return true;

            for (int i = this->size - 1; i >= 0; i--) {
                if (this->digits[i] > rhs.get_digit(i))
                    return true;
                else if (this->digits[i] < rhs.get_digit(i))
                    return false;
            }

            return false;
        }

        bool operator<(const BigNumber &rhs) const {
            return rhs > *this;
        }

        bool operator>=(const BigNumber &rhs) const {
            return *this > rhs || *this == rhs;
        }

        bool operator<=(const BigNumber &rhs) const {
            return *this < rhs || *this == rhs;
        }

        bool operator==(const BigNumber &other) const {

            // If the sizes are not the values are not equal
            if (this->size != other.size)
                return false;

            // Test each digit to ensure they match
            for (int i = 0; i < this->size; i++)
                if (this->digits[i] != other.get_digit(i))
                    return false;

            // Everything matches, success!
            return true;
        }

        bool operator!=(const BigNumber &other) const {
            return !(*this==other);
        }

    private:

        int* remainder;
        int* digits;
        int size;
        bool is_neg;
};

inline BigNumber operator+(BigNumber lhs, const BigNumber &other) {
    lhs += other;
    return lhs;
}

inline BigNumber operator-(BigNumber lhs, const BigNumber &other) {
    lhs -= other;
    return lhs;
}

inline BigNumber operator*(BigNumber lhs, const int &other) {
    lhs *= other;
    return lhs;
}

inline BigNumber operator/(BigNumber lhs, const BigNumber &other) {
    lhs /= other;
    return lhs;
}

/*
 *  Determines if the number is prime
 *
 */
inline bool is_prime(const BigNumber& value) {

    BigNumber divisor(value.get_size(), 2);
    BigNumber limit = value;
    const BigNumber one(value.get_size(), 1);

    while (divisor < limit) {
        limit = value / divisor;
        if (!limit.has_remainder())
            return false;
        divisor += one;
        limit += one;
    }
    return true;
}

/*
 *  Determines if the number is pandigital
 *
 */
inline bool is_pandigital(const BigNumber& value) {

    int size = value.get_most_significant_digit() + 1;
    int* buckets = new int[size];
    int digit;

    for (int i = 0; i < size; i ++) {
        digit = value.get_digit(i);
        if (digit == 0) {
            return false;
        } else if (buckets[digit] == 1)
            return false;
        else
            buckets[digit] = 1;
    }
    return true;
}

