//#include <iostream>
//#include <string>
//#include <cstdint>
#include "Registers.h"



Registers::Registers(int num) {
    for (int i = 0; i < num; ++i) {
        regArray[i].name = "Register " + std::to_string(i);
    }
}

void Registers::setBit(int regIndex, int bitIndex, bool state) {
    if (regIndex >= 0 && regIndex < 8 && bitIndex >= 0 && bitIndex < 8) {
        regArray[regIndex].bits[bitIndex].state = state;
        updateRegisterValue(regIndex);
    } else {
        std::cerr << "Invalid register index or bit index!" << std::endl;
    }
}
bool Registers::State(std::string name) {
    for (int j = 0; j < 8; ++j) {
        for (int i = 0; i < 8; ++i) {
            if (regArray[j].bits[i].name == name) {
                return regArray[j].bits[i].state;
            }
        }
    }
}
int Registers::RegisterValue(std::string name) {
    for (int i = 0; i < 8; ++i) {
        if (regArray[i].name == name) {
            return regArray[i].value;
        }
    }   
}
int Registers::RegisterAddress(std::string name) {
    for (int i = 0; i < 8; ++i) {
        if (regArray[i].name == name) {
            return i;
        }
    }
}
void Registers::setBit(std::string bitName, bool state) {
    for (int j = 0; j < 8; ++j) {
        //std::cout << "The number j is: " << j << std::endl;
        for (int i = 0; i < 8; ++i) {
            //std::cout << "The number i is: " << i << std::endl;
            if (regArray[j].bits[i].name == bitName) {
                regArray[j].bits[i].state = state;
                updateRegisterValue(j);
            }
        }
    }
}
void Registers::setRegister(int regIndex, char charValue) {
    if (regIndex >= 0 && regIndex < 8) {
        regArray[regIndex].value = charValue;
        for (int i = 0; i < 8; ++i) {
            regArray[regIndex].bits[i].state = (charValue >> i) & 1;
        }
    } else {
        std::cerr << "Invalid register index!" << std::endl;
    }
}

void Registers::setRegister(int regIndex, char charValue, std::string name) {
    if (regIndex >= 0 && regIndex < 8) {
        regArray[regIndex].value = charValue;
        regArray[regIndex].name = name;
        for (int i = 0; i < 8; ++i) {
            regArray[regIndex].bits[i].state = (charValue >> i) & 1;
        }
    } else {
        std::cerr << "Invalid register index!" << std::endl;
    }
}

void Registers::setRegisterName(int regIndex, std::string name) {
    if (regIndex >= 0 && regIndex < 8) {
        regArray[regIndex].name = name;
    } else {
        std::cerr << "Invalid register index!" << std::endl;
    }
}

void Registers::setBit(int regIndex, int bitIndex, bool state, std::string name) {
    if (regIndex >= 0 && regIndex < 8 && bitIndex >= 0 && bitIndex < 8) {
        regArray[regIndex].bits[bitIndex].state = state;
        regArray[regIndex].bits[bitIndex].name = name;
        updateRegisterValue(regIndex);
    } else {
        std::cerr << "Invalid register index or bit index!" << std::endl;
    }
}

void Registers::printRegisters() const {
    for (int i = 0; i < 8; ++i) {
        std::cout << "Register " << i << " Name: " << regArray[i].name << std::endl;
        std::cout << "Register " << i << " Value: 0x" << std::hex << static_cast<int>(regArray[i].value) << std::endl;
        std::cout << "Bits:" << std::endl;
        for (int j = 0; j < 8; ++j) {
            std::cout << "  Bit " << j << " Name: " << regArray[i].bits[j].name << ", State: " << regArray[i].bits[j].state << std::endl;
        }
        std::cout << std::endl;
    }
}
void Registers::updateRegisterValue(int regIndex) {
    uint8_t newValue = 0;
    for (int i = 0; i < 8; ++i) {
        newValue |= (regArray[regIndex].bits[i].state << i);
    }
    regArray[regIndex].value = newValue;
}
