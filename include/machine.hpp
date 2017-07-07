//===-- elfLoader.hpp - Machine class definition -------*- C++ -*-===//
//
//                     The OpenISA Infrastructure
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the Machine class.
///
//===----------------------------------------------------------------------===//
#ifndef MACHINE_HPP
#define MACHINE_HPP

#include <cstdint>
#include <unordered_map>
#include <memory>
#include <vector>
#include <functional>

#define uptr std::unique_ptr

namespace dbt {
  union Word {
    char asC_[4];
    uint32_t asI_;
    float asF_;
  };

  union QWord {
    char asC_[8];
    uint32_t asI32_[2];
    uint64_t asI_;
    double asD_;
  };

  class RFT;

  class Machine {
  private:

    // Int Regs     0   -  63
    // LDI          64
    // Ijmphi       65
    // Float Regs   66  -  129
    // Double Regs  130 -  256
    // CC           257
    int32_t Register[258] __attribute__ ((aligned (16)));

    uptr<char[]> DataMemory;
    uptr<Word[]> CodeMemory;

    uint32_t DataMemOffset;
    uint32_t CodeMemOffset;

    uint32_t DataMemLimit;
    uint32_t CodeMemLimit;

    uint32_t LastPC;
    uint32_t PC;
  public:
    Machine() { Register[0] = 0; };

    void allocDataMemory(uint32_t, uint32_t);
    void setCodeMemory(uint32_t, uint32_t, const char*);
    void addDataMemory(uint32_t, uint32_t, const char*);

    uint32_t getLastPC();
    uint32_t getPC();
    void setPC(uint32_t);
    void incPC();

    Word getInstAt(uint32_t);
    Word getInstAtPC();
    Word getNextInst();

    void     setMemByteAt(uint32_t, uint8_t);
    uint8_t  getMemByteAt(uint32_t);
    uint16_t getMemHalfAt(uint32_t);
    Word     getMemValueAt(uint32_t);
    void     setMemValueAt(uint32_t, uint32_t);

    int32_t*  getRegisterPtr();
    uint32_t* getMemoryPtr();
    char* getByteMemoryPtr();

    uint32_t getNumInst();
    uint32_t getCodeStartAddrs();
    uint32_t getCodeEndAddrs();
    uint32_t getDataMemOffset();

    int32_t getRegister(uint16_t);
    float   getFloatRegister(uint16_t);
    double  getDoubleRegister(uint16_t);

    void setRegister(uint16_t, int32_t);
    void setFloatRegister(uint16_t, float);
    void setDoubleRegister(uint16_t, double);

    int loadELF(const std::string);
  };
}

#endif