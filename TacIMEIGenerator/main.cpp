#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>

int checksum(const std::string& digitSequence) {
    int odd_sum = 0, even_sum = 0;
    for (int i = digitSequence.length() - 1; i >= 0; i -= 2) {
        odd_sum += digitSequence[i] - '0';
    }
    for (int i = digitSequence.length() - 2; i >= 0; i -= 2) {
        int double_digit = 2 * (digitSequence[i] - '0');
        even_sum += double_digit / 10 + double_digit % 10;
    }
    return (odd_sum + even_sum) % 10;
}

int generate(const std::string& digitSequence) {
    int cksum = checksum(digitSequence + '0');
    return (10 - cksum) % 10;
}

std::string append_luhn(const std::string& digitSequence) {
    return digitSequence + std::to_string(generate(digitSequence));
}

std::string generate_imei(const std::string& baseIMEI) {
    std::string imei_digits = baseIMEI.substr(0, 14);
    while (imei_digits.length() < 14) {
        imei_digits += std::to_string(rand() % 10);
    }
    return append_luhn(imei_digits);
}

void generate_list(const std::string& tacCode) {
    std::cout << "TAC: " << tacCode << std::endl;
    std::cout << "IMEIs:" << std::endl;

    for (int i = 0; i < 20; ++i) {
        std::cout << generate_imei(tacCode) << std::endl;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    std::string tac;
    while (true) {
        std::cout << "Enter TAC code: ";
        std::cin >> tac;
        try {
            if (tac.length() < 8 || tac.length() > 14 || !std::all_of(tac.begin(), tac.end(), ::isdigit)) {
                throw std::invalid_argument("Not a valid TAC code");
            }
            generate_list(tac);
            std::cout << "---------------------" << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}
