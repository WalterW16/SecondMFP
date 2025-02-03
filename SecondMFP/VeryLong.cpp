#include "VeryLong.h"
#include <algorithm>

void VeryLong::putvl() const {
    
    if (vlstr == "0") {
        std::cout << "0";
        return;
    }

    std::string result = vlstr;
    std::reverse(result.begin(), result.end()); 

    
    if (isNegative) {
        std::cout << "-" << result<<", ";
    }
    else {
        std::cout << result<<", ";
    }
}

void VeryLong::input_vl() {
    std::string input;
    std::cin >> input;

   
    size_t start = 0;
    while (start < input.size() && input[start] == '0') {
        start++;
    }

    
    if (start < input.size()) {
        if (input[start] == '-') {
            isNegative = true;
            start++;  
        }
        else {
            isNegative = false;
        }
    }
    else {
       
        vlstr = "0";
        isNegative = false;
        return;
    }

   
    vlstr = input.substr(start);

 
    if (vlstr.empty()) {
        vlstr = "0";
        isNegative = false;
    }

   
    std::reverse(vlstr.begin(), vlstr.end());
}


VeryLong VeryLong::operator+(const VeryLong& v) const {
    if (isNegative == v.isNegative) {
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
            result += carry + '0';
        }

        std::reverse(result.begin(), result.end());
        VeryLong res(result);
        res.isNegative = isNegative; 
        return res;
    }
    else {
        if (isNegative) {
            return v - (-(*this)); 
        }
        else {
            return *this - (-v); 
        }
    }
}

VeryLong VeryLong::operator-(const VeryLong& v) const {
    if (isNegative != v.isNegative) {
    
        return *this + (-v);
    }


    if (*this < v) {
        VeryLong result = v - *this;
        result.isNegative = !isNegative;
        return result;
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

    std::reverse(result.begin(), result.end());
    VeryLong res(result);
    res.isNegative = isNegative;
    return res;
}

VeryLong VeryLong::operator*(const VeryLong& v) const {
    
    if (vlstr == "0" || v.vlstr == "0") {
        return VeryLong("0");
    }

    VeryLong result("0");

    
    int trailingZeros = 0;
    std::string v_str = v.vlstr;

    
    while (!v_str.empty() && v_str.back() == '0') {
        v_str.pop_back();
        trailingZeros++;
    }

   
    for (size_t i = 0; i < vlstr.size(); ++i) {
        VeryLong temp = v.multdigit(vlstr[i] - '0');

        for (size_t j = 0; j < i; ++j) {
            temp = mult10(temp); 
        }

        result += temp; 
    }

   
    for (int k = 0; k < trailingZeros; ++k) {
        result.vlstr += '0';
    }

    result.isNegative = (isNegative != v.isNegative);
    return result;
}
VeryLong VeryLong::operator/(const VeryLong& v) const {
    if (v.vlstr == "0") {
        throw std::invalid_argument("Division by zero!");
    }

  
    if (vlstr == "0") {
        return VeryLong("0");
    }

  
    VeryLong numerator = *this;
    VeryLong denominator = v;
    numerator.isNegative = false;
    denominator.isNegative = false;

   
    if (numerator < denominator) {
        return VeryLong("0");
    }

    std::string result = ""; 
    VeryLong current("");    

    
    for (size_t i = vlstr.size(); i > 0; --i) {
        current.vlstr.insert(current.vlstr.begin(), vlstr[i - 1]);  
        current.removeLeadingZeros();

        
        int count = 0;
        while (current >= denominator) {
            current = current - denominator;
            count++;
        }

        result += (count + '0'); 
    }

   
    while (result.size() > 1 && result[0] == '0') {
        result.erase(result.begin());
    }

    VeryLong finalResult(result);
   
    finalResult.isNegative = isNegative != v.isNegative;

    return finalResult;
}

void VeryLong::removeLeadingZeros() {
   
    while (vlstr.size() > 1 && vlstr[0] == '0') {
        vlstr.erase(0, 1);
    }
}
VeryLong VeryLong::multdigit(int d2) const {
    VeryLong result;
    int carry = 0;


    if (d2 == 0) {
        return VeryLong("0");
    }


    bool isNegativeResult = (isNegative != (d2 < 0));
    d2 = std::abs(d2); 

    for (size_t i = 0; i < vlstr.size(); i++) {
        int d1 = vlstr[i] - '0';
        int prod = d1 * d2 + carry;
        carry = prod / 10;
        result.vlstr += (prod % 10) + '0';
    }

    if (carry) {
        result.vlstr += carry + '0';
    }

    result.isNegative = isNegativeResult; 
    result.removeLeadingZeros();
    return result;
}


VeryLong VeryLong::mult10(const VeryLong& v) const {
    VeryLong result = v;
    result.vlstr = '0' + result.vlstr; 
    result.isNegative = v.isNegative; 
    return result;
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
    return vlstr == v.vlstr && isNegative == v.isNegative;
}


bool VeryLong::operator!=(const VeryLong& v) const {
    return !(*this == v);
}

bool VeryLong::operator<(const VeryLong& v) const {
    
    if (isNegative != v.isNegative) {
        return isNegative;
    }

    
    if (vlstr.size() != v.vlstr.size()) {
        return (vlstr.size() < v.vlstr.size()) ^ isNegative;
    }

    for (int i = vlstr.size() - 1; i >= 0; --i) {
        if (vlstr[i] != v.vlstr[i]) {
            return (vlstr[i] < v.vlstr[i]) ^ isNegative; 
        }
    }

    return false;
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





 std::ostream& operator<<(std::ostream& os, const VeryLong& vl) {
    if (vl.isNegative) {
        os << "-";  
    }
    os << vl.vlstr;
    return os;
}

#include <stdexcept>  




 VeryLong& VeryLong::operator=(const VeryLong& other) {
     
     if (this != &other) {
      
         vlstr = other.vlstr;

        
         isNegative = other.isNegative;
     }

     
     return *this;
 }


VeryLong VeryLong::operator-() const {
    VeryLong result = *this;
    if (vlstr != "0") {
        result.isNegative = !isNegative; 
    }
    return result;
}
VeryLong VeryLong::operator%(const VeryLong& v) const {
    if (v.vlstr == "0") {
        throw std::invalid_argument("Division by zero!");
    }

  
    VeryLong numerator = *this;
    VeryLong denominator = v;

    numerator.isNegative = false; 
    denominator.isNegative = false; 

   
    VeryLong quotient = numerator / denominator;
    VeryLong result = numerator - (quotient * denominator);

    if (isNegative && result.vlstr != "0") {
        result = denominator - result;
        result.isNegative = false; 
    }

    if (result.vlstr == "0") {
        result.isNegative = false; 
    }

    result.removeLeadingZeros(); 
    return result;
}

