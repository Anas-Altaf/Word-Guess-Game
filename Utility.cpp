// Utility.cpp

#include "Utility.h"

std::string toUpperCase(const std::string& str) {
    std::string upperStr;
    for (char c : str) {
        if (c >= 'a' && c <= 'z') {
            upperStr += c - 'a' + 'A';
        } else {
            upperStr += c;
        }
    }
    return upperStr;
}