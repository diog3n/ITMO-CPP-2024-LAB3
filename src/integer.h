#ifndef _INTEGER_H_
#define _INTEGER_H_

#include <exception>
#include <iostream>
#include <iterator>

class Integer {
private:
    int *data_ = nullptr;
public:
    Integer() {
        *this = Integer(0);
    }

    Integer(int number) {
        data_ = new int;
        *data_ = number;
    }

    Integer(const Integer& other) {
        if (this == &other) return;

        if (data_) {
            *data_ = *other.data_;
            return;
        }

        data_ = new int;
        *data_ = *other.data_;
    }

    Integer& operator=(const Integer& other) {
        if (this == &other) return *this;

        if (data_) {
            *data_ = *other.data_;
            return *this;
        }

        data_ = new int;
        *data_ = *other.data_;

        return *this;
    }

    Integer& operator=(const int other) {
        *this = Integer(other);

        return *this;
    }

    Integer operator+(const Integer& other) const {
        return Integer(*this->data_ + *other.data_);
    }

    Integer operator-(const Integer& other) const {
        return Integer(*this->data_ - *other.data_);
    }

    Integer operator*(const Integer& other) const {
        return Integer(*this->data_ * *other.data_);
    }

    Integer operator/(const Integer& other) const {
        if (other.data_ == 0) {
            throw std::runtime_error("Division by zero");
        }
        return Integer(*this->data_ / *other.data_);
    }

    Integer operator%(const Integer &other) const {
        if (other.data_ == 0) {
            throw std::runtime_error("Division by zero");
        }
        return Integer(*this->data_ % *other.data_);
    }

    bool operator==(const Integer& other) const {
        return *this->data_ == *other.data_;
    }

    bool operator!=(const Integer& other) const {
        return !(*this == other);
    }

    bool operator<(const Integer& other) const {
        return *this->data_ < *other.data_;
    }

    bool operator>(const Integer& other) const {
        return *this->data_ > *other.data_;
    }

    bool operator<=(const Integer& other) const {
        return !(*this > other);
    }

    bool operator>=(const Integer& other) const {
        return !(*this < other);
    }

    int AsInt() const {
        return *data_;
    }

    ~Integer() {
        delete data_;
    }

};

std::ostream& operator<<(std::ostream& out, const Integer& i) {
    out << i.AsInt();
    return out;
}

#endif // _INTEGER_H_