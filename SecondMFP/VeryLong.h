#pragma once
#include <iostream>
#include <string>

class VeryLong {
private:
    std::string vlstr;  // ��������� ����� �� �����
    VeryLong multdigit(int d2) const;    // �������� ������� �������� �� �����
    VeryLong mult10(const VeryLong& v) const;  // �������� ������� �������� �� 10

public:
    VeryLong() : vlstr("") {}
    VeryLong(const std::string& s) : vlstr(s) {
        std::reverse(vlstr.begin(), vlstr.end());  // �������� � ���������� �������
    }
    VeryLong(unsigned long n) {
        vlstr = std::to_string(n);
        std::reverse(vlstr.begin(), vlstr.end());  // �������� � ���������� �������
    }
    void putvl() const;        // ��������� ����������� �����
    void input_vl();           // �������� ����������� ����� �� �����������    
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
