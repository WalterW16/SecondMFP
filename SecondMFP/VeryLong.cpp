#include "VeryLong.h"
#include <algorithm>

void VeryLong::putvl() const {
    std::string temp = vlstr;
    std::reverse(temp.begin(), temp.end()); 
    std::cout << temp << ", ";
}

void VeryLong::input_vl() {
    std::cin >> vlstr;
    std::reverse(vlstr.begin(), vlstr.end()); 
}

VeryLong VeryLong::operator+(const VeryLong& v) const {
    std::string result = "";
    int carry = 0;
    size_t maxlen = std::max(vlstr.size(), v.vlstr.size());

    for (size_t i = 0; i < maxlen; i++) {
        int d1 = (i < vlstr.size()) ? vlstr[i] - '0' : 0;
        int d2 = (i < v.vlstr.size()) ? v.vlstr[i] - '0' : 0;
        int sum = d1 + d2 + carry;
        carry = sum / 10;
        result += (sum % 10) + '0';
    }

    if (carry) {
        result += '1';
    }

    std::reverse(result.begin(), result.end()); // Перевертаємо результат
    return VeryLong(result);
}


VeryLong VeryLong::operator-(const VeryLong& v) const {
    if (*this < v) {
        throw std::invalid_argument("Result of subtraction is negative!");
    }

    std::string result = "";
    int borrow = 0;

    for (size_t i = 0; i < vlstr.size(); i++) {
        int d1 = vlstr[i] - '0';
        int d2 = (i < v.vlstr.size()) ? v.vlstr[i] - '0' : 0;
        int diff = d1 - d2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        result += diff + '0';
    }

    while (result.size() > 1 && result.back() == '0') {
        result.pop_back();
    }

    std::reverse(result.begin(), result.end()); // Перевертаємо результат
    return VeryLong(result);
}



VeryLong VeryLong::operator*(const VeryLong& v) const {
    VeryLong pprod, tempsum;

    for (size_t j = 0; j < v.vlstr.size(); j++) {
        int digit = v.vlstr[j] - '0';
        pprod = multdigit(digit);

        for (size_t k = 0; k < j; k++) {
            pprod = mult10(pprod);
        }

        tempsum = tempsum + pprod;
    }

    return tempsum;
}


VeryLong VeryLong::multdigit(int d2) const {
    std::string temp = "";
    int carry = 0;

    for (size_t j = 0; j < vlstr.size(); j++) {
        int d1 = vlstr[j] - '0';
        int digitprod = d1 * d2 + carry;
        carry = digitprod / 10;
        digitprod %= 10;
        temp += (digitprod + '0');
    }

    if (carry != 0) {
        temp += (carry + '0');
    }

    return VeryLong(temp);
}

VeryLong VeryLong::mult10(const VeryLong& v) const {
    return VeryLong(v.vlstr + '0');
}

VeryLong& VeryLong::operator+=(const VeryLong& v) {
    *this = *this + v;
    return *this;
}

VeryLong& VeryLong::operator*=(const VeryLong& v) {
    *this = *this * v;
    return *this;
}

bool VeryLong::operator==(const VeryLong& v) const {
    return vlstr == v.vlstr;
}

bool VeryLong::operator!=(const VeryLong& v) const {
    return !(*this == v);
}

bool VeryLong::operator<(const VeryLong& v) const {
    if (vlstr.size() != v.vlstr.size()) {
        return vlstr.size() < v.vlstr.size();
    }
    return std::lexicographical_compare(vlstr.rbegin(), vlstr.rend(), v.vlstr.rbegin(), v.vlstr.rend());
}

bool VeryLong::operator>(const VeryLong& v) const {
    return v < *this;
}

bool VeryLong::operator<=(const VeryLong& v) const {
    return (*this < v) || (*this == v);
}

bool VeryLong::operator>=(const VeryLong& v) const {
    return (*this > v) || (*this == v);
}

VeryLong VeryLong::operator/(const VeryLong& v) {
    VeryLong dividend = *this;
    VeryLong divisor = v;
    VeryLong quotient("0");

    while (dividend >= divisor) {
        VeryLong temp("1");
        VeryLong tempDivisor = divisor;

        while ((tempDivisor * VeryLong("10")) <= dividend) {
            tempDivisor *= VeryLong("10");
            temp *= VeryLong("10");
        }

        dividend = dividend - tempDivisor;
        quotient = quotient + temp;
    }

    return quotient;
}

std::ostream& operator<<(std::ostream& os, const VeryLong& v) {
    std::string temp = v.vlstr;
    std::reverse(temp.begin(), temp.end());
    os << temp;
    return os;
}
#include "VeryLong.h"
#include <stdexcept>  // для обробки виключень

VeryLong VeryLong::operator%(const VeryLong& v) const {
    if (v == VeryLong(0)) {
        throw std::invalid_argument("Division by zero in operator %");
    }

    VeryLong dividend = *this;
    VeryLong divisor = v;

    // Проводимо ділення, поки поточний дільник не перевищить ділене
    while (dividend >= divisor) {
        VeryLong temp("1");
        VeryLong tempDivisor = divisor;

        // Збільшуємо тимчасовий дільник, поки він залишається меншим за ділене
        while ((tempDivisor * VeryLong("10")) <= dividend) {
            tempDivisor *= VeryLong("10");
            temp *= VeryLong("10");
        }

        // Віднімаємо найбільший можливий дільник від діленого
        dividend = dividend - tempDivisor;
    }

    // Залишок - це те, що залишилось після всіх віднімань
    return dividend;
}
VeryLong& VeryLong::operator=(const VeryLong& other) {
    if (this != &other) {  // Перевіряємо на самоприсвоєння
        vlstr = other.vlstr;  // Копіюємо рядок, що представляє число
    }
    return *this;  // Повертаємо поточний об'єкт
}



