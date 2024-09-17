#pragma once
#include<iostream>
#include<vector>
#include<memory>
#include<iomanip>
#include<algorithm>
#include "VeryLong.h"
static VeryLong sqrt(const VeryLong& n) {
        VeryLong low("1"), high = n, mid, result;

        while (low <= high) {
            mid = (low + high) / VeryLong(2);
            VeryLong midSquared = mid * mid;

            if (midSquared == n) {
                return mid;
            }
            else if (midSquared < n) {
                low = mid + VeryLong(1);
                result = mid;
            }
            else {
                high = mid - VeryLong(1);
            }
        }

        return result;
    }
// Перевірка на просте число
static bool IsPrimary(const VeryLong& n) {
    if (n <= VeryLong("1")) {
        return false;
    }
    if (n == VeryLong("2") || n == VeryLong("3")) {
        return true;  // 2 і 3 є простими числами
    }
    if (n % VeryLong("2") == VeryLong("0") || n % VeryLong("3") == VeryLong("0")) {
        return false;  // Якщо ділимося на 2 або 3, то число не просте
    }

    VeryLong divisor("5");  // Починаємо перевірку з числа 5
    VeryLong step("6");     // Крок для перевірки чисел виду 6k ± 1
    VeryLong limit = sqrt(n); // Потрібно реалізувати корінь

    while (divisor <= limit) {
        if (n % divisor == VeryLong("0") || n % (divisor + VeryLong("2")) == VeryLong("0")) {
            return false;  // Якщо знайшли дільник, то число не є простим
        }
        divisor += step;  // Переходимо до наступного числа 6k ± 1
    }

    return true;  // Число просте
}

// Перевірка на парність числа
static bool IsEven( const VeryLong& n) {
    return (n % VeryLong(2)) == VeryLong(0);
}

// Перевірка на непарність числа
static bool IsOdd( const VeryLong& n) {
    return (n % VeryLong(2)) == VeryLong(1);
}
