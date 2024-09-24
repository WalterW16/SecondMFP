#pragma once
#include<iostream>
#include<vector>
#include<memory>
#include<iomanip>
#include<algorithm>
#include "VeryLong.h"
static VeryLong sqrt(const VeryLong& n) {
    if (n == VeryLong(0) || n == VeryLong(1)) {
        return n; // ���������� ����� � 0 � 1 - �� ��� �����
    }

    VeryLong low(1), high = n, mid, result;

    while (low <= high) {
        mid = (low + high) / VeryLong(2);
        VeryLong midSquared = mid * mid;

        if (midSquared == n) {
            return mid; // ���� ��������� �������, ��������� �������
        }
        else if (midSquared < n) {
            low = mid + VeryLong(1);
            result = mid; // �������� ������� ������� �� ����������� ���������
        }
        else {
            high = mid - VeryLong(1);
        }
    }
    return result; // ��������� �������� ��������, ��� � ������� �� �������� n
}

// �������� �� ������ �����
static bool IsPrimary(const VeryLong& n) {
    if (n <= VeryLong(1)) {
        return false;
    }
    if (n == VeryLong(2) || n == VeryLong(3)) {
        return true;  // 2 � 3 � �������� �������
    }
    if (n % VeryLong(2) == VeryLong(0) || n % VeryLong(3) == VeryLong(0)) {
        return false;  // ���� ������� �� 2 ��� 3, �� ����� �� ������
    }
    if (n <= VeryLong(0)) {
        return false;
    }

    VeryLong divisor(5);  // �������� �������� � ����� 5
    VeryLong step(6);     // ���� ��� �������� ����� ���� 6k � 1
    VeryLong limit = sqrt(n); // ������� ���������� �����

    while (divisor <= limit) {
        if (n % divisor == VeryLong(0) || n % (divisor + VeryLong(2)) == VeryLong(0)) {
            return false;  // ���� ������� ������, �� ����� �� � �������
        }
        divisor += step;  // ���������� �� ���������� ����� 6k � 1
    }

    return true;  // ����� ������
}

// �������� �� �������� �����
static bool IsEven( const VeryLong& n) {
    return (n % VeryLong(2)) == VeryLong(0);
}

// �������� �� ���������� �����
static bool IsOdd( const VeryLong& n) {
    return (n % VeryLong(2)) == VeryLong(1);
}
