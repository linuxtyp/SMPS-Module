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
        std::cerr << "bit set. regIndex: " << regIndex << " bitIndex: " << bitIndex << std::endl;
    } else {
        std::cerr << "Invalid register index or bit index. regIndex: " << regIndex << " bitIndex: " << bitIndex << std::endl;
    }
}
bool Registers::State(std::string name) {
    for (int j = 0; j < 8; ++j) {
        for (int i = 0; i < 8; ++i) {
            if (regArray[j].bits[i].name == name) {
                return regArray[j].bits[i].state;
                std::cerr << "valid register name" << name << std::endl; //debug
            }
            else
            if (i==7)
            {
                std::cerr << "Invalid register name: " << name << " -> State" << std::endl;
                return -1;
            }
        }
    }
}
uint8_t Registers::RegisterValue(std::string name) {
    for (int i = 0; i < 8; ++i) {
        if (regArray[i].name == name) {
            return regArray[i].value;
            std::cerr << "valid register name: " << name << std::endl; //debug
        }
    }   
    std::cerr << "Invalid register name: " << name << " -> RegisterValue" << std::endl;
    return -1;
}
uint8_t Registers::RegisterAddress(std::string name) {
    for (int i = 0; i < 8; ++i) {
        if (regArray[i].name == name) {
            return i;
            std::cerr << "valid register name: " << name << std::endl; //debug
        }
    }
    std::cerr << "Invalid register name: " << name << " -> RegisterAddress" << std::endl;
    return -1;
}
void Registers::setBit(std::string bitName, bool state) {
    for (int i = 0; i < 8; ++i) {
        //std::cout << "The number j is: " << j << std::endl;
        for (int j = 0; j < 8; ++j) {
            //std::cout << "The number i is: " << i << std::endl;
            if (regArray[i].bits[j].name == bitName) {
                regArray[i].bits[j].state = state;
                updateRegisterValue(j);
                std::cerr << "bit set: " << bitName << std::endl; // debug
                break;
            }
            else
            if (j==7 && i==7)
            {
                std::cerr << "invalid bitname: " << bitName << std::endl; //debug
            }
        }
    }
}
void Registers::setRegister(int regIndex, char value) {
    if (regIndex >= 0 && regIndex < 8) {
        regArray[regIndex].value = value;
        for (int i = 0; i < 8; ++i) {
            regArray[regIndex].bits[i].state = (value >> i) & 1;
        }
        std::cerr << "Register set: " << regIndex << std::endl; //debug
    } else {
        std::cerr << "Invalid register index: " << regIndex << std::endl;
    }
}

void Registers::setRegister(std::string regName, char value)
{
    for (int i = 0; i < 8; ++i) {
        if (regArray[i].name == regName) {
            regArray[i].value = value;
            for (int j = 0; j < 8; ++j) {
                regArray[i].bits[j].state = (value >> j) & 1;
            }
            std::cerr << "Register set: " << regName << std::endl; //debug
        }
        else
        if (i==7)
        {
            std::cerr << "Invalid register name: " << regName << " -> setRegister" << std::endl;  /* code */
        }
    }
}

void Registers::setRegister(int regIndex, char  value, std::string name) {
    if (regIndex >= 0 && regIndex < 8) {
        regArray[regIndex].value = value;
        regArray[regIndex].name = name;
        for (int i = 0; i < 8; ++i) {
            regArray[regIndex].bits[i].state = (value >> i) & 1;
        }
        std::cerr << "Register set: " << regIndex << std::endl; //debug
    } else {
        std::cerr << "Invalid register index: " << regIndex << std::endl;
    }
}

void Registers::setRegisterName(int regIndex, std::string name) {
    if (regIndex >= 0 && regIndex < 8) {
        regArray[regIndex].name = name;
        std::cerr << "Register Name set: " << regIndex << std::endl; //debug
    } else {
        std::cerr << "Invalid register index: " << regIndex << std::endl;
    }
}

void Registers::setBit(int regIndex, int bitIndex, bool state, std::string name) {
    if (regIndex >= 0 && regIndex < 8 && bitIndex >= 0 && bitIndex < 8) {
        regArray[regIndex].bits[bitIndex].state = state;
        regArray[regIndex].bits[bitIndex].name = name;
        updateRegisterValue(regIndex);
        std::cerr << "bit set. regIndex: " << regIndex << " bitIndex: " << bitIndex << std::endl;
    } else {
        std::cerr << "Invalid register index or bit index. regIndex: " << regIndex << " bitIndex: " << bitIndex << std::endl;
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
