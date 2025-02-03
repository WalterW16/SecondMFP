#pragma once
#include <iostream>
#include <string>

class VeryLong {
private:
    std::string vlstr;  
    bool isNegative;   
    VeryLong multdigit(int d2) const;  
    VeryLong mult10(const VeryLong& v) const;  

public:
    VeryLong() : vlstr(""), isNegative(false) {}
    VeryLong(const std::string& s) : vlstr(s), isNegative(false) {
        this->removeLeadingZeros();
        if (!vlstr.empty() && vlstr[0] == '-') {
            isNegative = true;
            vlstr = vlstr.substr(1); 
        }
        std::reverse(vlstr.begin(), vlstr.end());  
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
        std::reverse(vlstr.begin(), vlstr.end());  
    }

    void putvl() const; 
    void input_vl();     
    void removeLeadingZeros(); 

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
