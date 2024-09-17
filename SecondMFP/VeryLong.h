#pragma once
#include <iostream>
#include <string>

class VeryLong {
private:
    std::string vlstr;  // надвелике число як рядок
    VeryLong multdigit(int d2) const;    // допоміжна функція множення на цифру
    VeryLong mult10(const VeryLong& v) const;  // допоміжна функція множення на 10

public:
    VeryLong() : vlstr("") {}
    VeryLong(const std::string& s) : vlstr(s) {
        std::reverse(vlstr.begin(), vlstr.end());  // зберігаємо у зворотному порядку
    }
    VeryLong(unsigned long n) {
        vlstr = std::to_string(n);
        std::reverse(vlstr.begin(), vlstr.end());  // зберігаємо у зворотному порядку
    }
    void putvl() const;        // виведення надвеликого числа
    void input_vl();           // введення надвеликого числа від користувача    
    VeryLong& operator=(const VeryLong& other);
    VeryLong operator+(const VeryLong& v) const;
    VeryLong operator-(const VeryLong& v) const;
    VeryLong operator*(const VeryLong& v) const;
    VeryLong& operator+=(const VeryLong& v);
    VeryLong& operator*=(const VeryLong& v);
    VeryLong operator/(const VeryLong& v);
    VeryLong operator%(const VeryLong& v) const;
    bool operator==(const VeryLong& v) const;
    bool operator!=(const VeryLong& v) const;
    bool operator<(const VeryLong& v) const;
    bool operator>(const VeryLong& v) const;
    bool operator<=(const VeryLong& v) const;
    bool operator>=(const VeryLong& v) const;
    friend std::ostream& operator<<(std::ostream& os, const VeryLong& v);
};
