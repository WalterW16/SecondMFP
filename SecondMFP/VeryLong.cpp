#include "VeryLong.h"
#include <algorithm>

void VeryLong::putvl() const {
    // Якщо число нульове
    if (vlstr == "0") {
        std::cout << "0";
        return;
    }

    std::string result = vlstr;
    std::reverse(result.begin(), result.end());  // Зворотний порядок для виводу

    // Додаємо знак для від'ємних чисел
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

    // Перевірка на ведучі нулі
    size_t start = 0;
    while (start < input.size() && input[start] == '0') {
        start++;
    }

    // Обробка знака
    if (start < input.size()) {
        if (input[start] == '-') {
            isNegative = true;
            start++;  // Переходимо до наступного символу
        }
        else {
            isNegative = false;
        }
    }
    else {
        // Якщо введене число нульове
        vlstr = "0";
        isNegative = false;
        return;
    }

    // Зберігаємо число без ведучих нулів
    vlstr = input.substr(start);

    // Якщо введене число пусте після обробки, це нуль
    if (vlstr.empty()) {
        vlstr = "0";
        isNegative = false;
    }

    // Перевертаємо рядок для зберігання у зворотному порядку
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
        res.isNegative = isNegative; // зберігаємо знак
        return res;
    }
    else {
        if (isNegative) {
            return v - (-(*this)); // якщо перше число від'ємне
        }
        else {
            return *this - (-v); // якщо друге число від'ємне
        }
    }
}

VeryLong VeryLong::operator-(const VeryLong& v) const {
    if (isNegative != v.isNegative) {
        // Якщо числа мають різні знаки, фактично це додавання
        return *this + (-v);
    }

    // Якщо поточне число менше від вхідного, результат буде від'ємним
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

    // Якщо результат від'ємний
    while (result.size() > 1 && result.back() == '0') {
        result.pop_back();
    }

    std::reverse(result.begin(), result.end());
    VeryLong res(result);
    res.isNegative = isNegative; // залишаємо знак
    return res;
}

VeryLong VeryLong::operator*(const VeryLong& v) const {
    // Якщо одне з чисел — 0, результат — 0
    if (vlstr == "0" || v.vlstr == "0") {
        return VeryLong("0");
    }

    VeryLong result("0");

    // Зберігаємо кількість нулів в кінці множника
    int trailingZeros = 0;
    std::string v_str = v.vlstr;

    // Визначаємо кількість нулів в кінці v
    while (!v_str.empty() && v_str.back() == '0') {
        v_str.pop_back();
        trailingZeros++;
    }

    // Виконуємо множення по розрядах
    for (size_t i = 0; i < vlstr.size(); ++i) {
        VeryLong temp = v.multdigit(vlstr[i] - '0');

        for (size_t j = 0; j < i; ++j) {
            temp = mult10(temp); // Додаємо нулі для розряду
        }

        result += temp; // Додаємо до результату
    }

    // Додаємо нулі в кінці результату
    for (int k = 0; k < trailingZeros; ++k) {
        result.vlstr += '0';
    }

    // Визначаємо знак результату
    result.isNegative = (isNegative != v.isNegative);
    return result;
}
VeryLong VeryLong::operator/(const VeryLong& v) const {
    if (v.vlstr == "0") {
        throw std::invalid_argument("Division by zero!");
    }

    // Якщо ділене — нуль, результат теж нуль
    if (vlstr == "0") {
        return VeryLong("0");
    }

    // Працюємо з абсолютними значеннями
    VeryLong numerator = *this;
    VeryLong denominator = v;
    numerator.isNegative = false;
    denominator.isNegative = false;

    // Якщо ділене менше за дільник, результат 0
    if (numerator < denominator) {
        return VeryLong("0");
    }

    std::string result = ""; // Тут будемо зберігати результат
    VeryLong current("");    // Поточне ділене

    // Обчислюємо частку шляхом поступового ділення
    for (size_t i = vlstr.size(); i > 0; --i) {
        current.vlstr.insert(current.vlstr.begin(), vlstr[i - 1]);  // Додаємо цифру справа
        current.removeLeadingZeros();

        // Шукаємо максимальне число, на яке можна поділити
        int count = 0;
        while (current >= denominator) {
            current = current - denominator;
            count++;
        }

        result += (count + '0');  // Додаємо частку
    }

    // Видаляємо ведучі нулі
    while (result.size() > 1 && result[0] == '0') {
        result.erase(result.begin());
    }

    VeryLong finalResult(result);
    // Визначаємо знак результату
    finalResult.isNegative = isNegative != v.isNegative;

    return finalResult;
}

void VeryLong::removeLeadingZeros() {
    // Поки в рядку є більше одного символу і перший символ є '0'
    while (vlstr.size() > 1 && vlstr[0] == '0') {
        vlstr.erase(0, 1); // Видаляємо перший символ
    }
}
VeryLong VeryLong::multdigit(int d2) const {
    VeryLong result;
    int carry = 0;

    // Якщо множимо на 0, результат завжди 0
    if (d2 == 0) {
        return VeryLong("0");
    }

    // Множимо на одиницю
    bool isNegativeResult = (isNegative != (d2 < 0));
    d2 = std::abs(d2); // Беремо абсолютне значення

    for (size_t i = 0; i < vlstr.size(); i++) {
        int d1 = vlstr[i] - '0';
        int prod = d1 * d2 + carry;
        carry = prod / 10;
        result.vlstr += (prod % 10) + '0';
    }

    if (carry) {
        result.vlstr += carry + '0';
    }

    result.isNegative = isNegativeResult; // Визначаємо знак
    result.removeLeadingZeros();
    return result;
}


VeryLong VeryLong::mult10(const VeryLong& v) const {
    VeryLong result = v;
    result.vlstr = '0' + result.vlstr; // Додаємо 0 до числа
    result.isNegative = v.isNegative; // Копіюємо знак
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
    // Якщо числа мають різні знаки, від'ємне число завжди менше
    if (isNegative != v.isNegative) {
        return isNegative;
    }

    // Якщо обидва числа позитивні або обидва від'ємні, порівнюємо їх
    if (vlstr.size() != v.vlstr.size()) {
        return (vlstr.size() < v.vlstr.size()) ^ isNegative; // враховуємо знак
    }

    for (int i = vlstr.size() - 1; i >= 0; --i) {
        if (vlstr[i] != v.vlstr[i]) {
            return (vlstr[i] < v.vlstr[i]) ^ isNegative; // враховуємо знак
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
        os << "-";  // Виводимо мінус для від'ємних чисел
    }
    os << vl.vlstr;
    return os;
}

#include <stdexcept>  // для обробки виключень




 VeryLong& VeryLong::operator=(const VeryLong& other) {
     // Перевіряємо на самоприсвоєння
     if (this != &other) {
         // Копіюємо значення рядка, що представляє число
         vlstr = other.vlstr;

         // Копіюємо знак числа
         isNegative = other.isNegative;
     }

     // Повертаємо поточний об'єкт
     return *this;
 }


VeryLong VeryLong::operator-() const {
    VeryLong result = *this;
    if (vlstr != "0") {
        result.isNegative = !isNegative; // змінюємо знак числа
    }
    return result;
}
VeryLong VeryLong::operator%(const VeryLong& v) const {
    if (v.vlstr == "0") {
        throw std::invalid_argument("Division by zero!");
    }

    // Використовуємо абсолютні значення для обчислень
    VeryLong numerator = *this;
    VeryLong denominator = v;

    numerator.isNegative = false; // Беремо абсолютне значення
    denominator.isNegative = false; // Беремо абсолютне значення

    // Обчислюємо залишок
    VeryLong quotient = numerator / denominator;
    VeryLong result = numerator - (quotient * denominator);

    // Якщо ділене від'ємне і залишок не нульовий, коригуємо залишок
    if (isNegative && result.vlstr != "0") {
        result = denominator - result;
        result.isNegative = false; // Оскільки коригуємо залишок, результат позитивний
    }

    // Якщо залишок дорівнює нулю, знак не має значення
    if (result.vlstr == "0") {
        result.isNegative = false; // Нуль завжди не має знака
    }

    result.removeLeadingZeros(); // Видаляємо ведучі нулі
    return result;
}

