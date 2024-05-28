#ifndef REGISTERS_H
#define REGISTERS_H

#include <iostream>
#include <string>
#include <cstdint>

// Struct representing a single bit with a state (0 or 1) and a name
struct Bit {
    std::string name;
    bool state;
};

// Struct representing a register consisting of 8 bits
struct Register {
    std::string name;
    Bit bits[8]; // Array of 8 bits
    uint8_t value; // Value representing the state of 8 bits
};

// Class representing multiple registers
class Registers {
public:
    // Constructor to initialize registers with default names
    Registers(int num);

    // Function to set individual bits of a register
    void setBit(int regIndex, int bitIndex, bool state);
    void setBit(int regIndex, int bitIndex, bool state, std::string name);
    void setBit(std::string bitName, bool state);
    //void setBiteName(int regIndex, int bitIndex, string name)
    // Function to print the state of all registers
    void printRegisters() const;
    void setRegister(int regIndex, char value);
    void setRegister(std::string regName, char value);
    void setRegister(int regIndex, char value, std::string name);
    void setRegisterName(int regIndex, std::string name);
    bool State(std::string name);
    uint8_t RegisterValue(std::string name);
    uint8_t RegisterAddress(std::string name);
    uint8_t RegisterIndex(std::string name);

    Register regArray[8]; // Array of 8 registers
private:
    

    // Private function to update the value of a register based on its bits' states
    void updateRegisterValue(int regIndex);
};

#endif /* REGISTERS_H */
