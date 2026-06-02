#include <iostream>
#include <string>
#include <algorithm>
#include <bitset>
#include <cstdint>
#include <stdexcept>

using namespace std;

uint32_t convertInternalToIEEE(uint32_t internalCode) {
    if (internalCode == 0) return 0;

    uint32_t e_int = (internalCode >> 24) & 0xFF;
    uint32_t s     = (internalCode >> 23) & 0x01;
    uint32_t m     = internalCode & 0x7FFFFF;

    uint32_t e_ieee = e_int - 1; 

    return (s << 31) | (e_ieee << 23) | m;
}

uint32_t convertIEEEToInternal(uint32_t ieeeCode) {
    if (ieeeCode == 0) return 0;


    uint32_t s      = (ieeeCode >> 31) & 0x01;
    uint32_t e_ieee = (ieeeCode >> 23) & 0xFF;
    uint32_t m      = ieeeCode & 0x7FFFFF;

    uint32_t e_int = e_ieee + 1; 

    return (e_int << 24) | (s << 23) | m;
}

int main() {
    int choice;
    string binaryInput;

    cout << "=== KONWERTER ZMIENNOPRZECINKOWY 32-bit ===" << endl;
    cout << "Wybierz tryb dzialania:" << endl;
    cout << "1. Kod wewnetrzny -> IEEE 754" << endl;
    cout << "2. IEEE 754 -> Kod wewnetrzny" << endl;
    cout << "Wybor: ";
    cin >> choice;

    if (choice != 1 && choice != 2) {
        cout << "Nieprawidlowy wybor!" << endl;
        return 1;
    }

    cout << "\nPodaj liczbe w 32-bitowym kodzie binarnym lub 8-znakowym HEX(pomin 0x):\n";
    cin >> ws;
    getline(cin, binaryInput);

    binaryInput.erase(remove(binaryInput.begin(), binaryInput.end(), ' '), binaryInput.end());

    try {
        uint32_t inputNum = 0;

        if (binaryInput.length() == 32) {
            inputNum = bitset<32>(binaryInput).to_ulong();
        } else if (binaryInput.length() == 8) {
            inputNum = static_cast<uint32_t>(stoul(binaryInput, nullptr, 16));
        } else {
            cout << "Blad! Wprowadzony ciag musi miec 32 znaki binarne lub 8 znakow HEX." << endl;
            cout << "\nNacisnij Enter, aby zamknac program...";
            cin.get();
            return 1;
        }

        uint32_t resultNum = 0;

        if (choice == 1) {
            resultNum = convertInternalToIEEE(inputNum);
            cout << "\nWynik konwersji do IEEE 754" << endl;
        } else {
            resultNum = convertIEEEToInternal(inputNum);
            cout << "\nWynik konwersji do kodu wewnetrznego" << endl;
        }
        cout << "Wartosc binarna: ";
        string resultStr = bitset<32>(resultNum).to_string();
        
        cout << resultStr.substr(0, 8) << " " 
             << resultStr.substr(8, 8) << " " 
             << resultStr.substr(16, 8) << " " 
             << resultStr.substr(24, 8) << endl;

        cout << "Wartosc HEX: 0x" << hex << uppercase << resultNum << endl;

        cout << "\nNacisnij Enter, aby zamknac program...";
        cin.get();

    } catch (const invalid_argument& e) {
        cout << "Blad! Ciag zawiera niedozwolone znaki (binarnie: tylko 0 i 1, HEX: tylko 0-9 i A-F)." << endl;

        cout << "\nNacisnij Enter, aby zamknac program...";
        cin.get();
        return 1;
    }

    return 0;
}