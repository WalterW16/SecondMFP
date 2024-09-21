#pragma once
#include <iostream>
#include <string>

class VeryLong {
private:
    std::string vlstr;  // надвелике число як рядок
    bool isNegative;    // змінна для збереження знака числа
    VeryLong multdigit(int d2) const;    // допоміжна функція множення на цифру
    VeryLong mult10(const VeryLong& v) const;  // допоміжна функція множення на 10

public:
    VeryLong() : vlstr(""), isNegative(false) {}
    VeryLong(const std::string& s) : vlstr(s), isNegative(false) {
        this->removeLeadingZeros();
        if (!vlstr.empty() && vlstr[0] == '-') {
            isNegative = true;
            vlstr = vlstr.substr(1); // видаляємо мінус перед збереженням числа
        }
        std::reverse(vlstr.begin(), vlstr.end());  // зберігаємо у зворотному порядку
    }
    VeryLong(long long n) {
        if (n < 0) {
            isNegative = true;
            n = -n;
        }
        else {
            isNegative = false;
        }
        vlstr = std::to_string(n);
        std::reverse(vlstr.begin(), vlstr.end());  // зберігаємо у зворотному порядку
    }

    void putvl() const;  // виведення надвеликого числа
    void input_vl();     // введення надвеликого числа від користувача
    void removeLeadingZeros(); // видалення нулів на початку числа

    // Оператори
    VeryLong& operator=(const VeryLong& other);
    VeryLong operator+(const VeryLong& v) const;
    VeryLong operator-(const VeryLong& v) const;
    VeryLong operator*(const VeryLong& v) const;
    VeryLong& operator+=(const VeryLong& v);
    VeryLong& operator*=(const VeryLong& v);
    VeryLong operator/(const VeryLong& v)const;
    VeryLong operator%(const VeryLong& v)const;
    bool operator==(const VeryLong& v) const;
    bool operator!=(const VeryLong& v) const;
    bool operator<(const VeryLong& v) const;
    bool operator>(const VeryLong& v) const;
    bool operator<=(const VeryLong& v) const;
    bool operator>=(const VeryLong& v) const;
    VeryLong operator-() const;
    friend std::ostream& operator<<(std::ostream& os, const VeryLong& vl);
};
