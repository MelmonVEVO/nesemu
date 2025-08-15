#include <stdint.h>

#ifndef TYPES_H
#define TYPES_H

typedef uint8_t u8;
typedef uint16_t u16;
typedef int8_t s8;
typedef int16_t s16;

typedef enum : u8 {
  // ADC - Add with Carry
  ADC_IMM = 0x69,  // ADC #$nn
  ADC_ZP = 0x65,   // ADC $nn
  ADC_ZPX = 0x75,  // ADC $nn,X
  ADC_ABS = 0x6D,  // ADC $nnnn
  ADC_ABSX = 0x7D, // ADC $nnnn,X
  ADC_ABSY = 0x79, // ADC $nnnn,Y
  ADC_INDX = 0x61, // ADC ($nn,X)
  ADC_INDY = 0x71, // ADC ($nn),Y

  // AND - Logical AND
  AND_IMM = 0x29,  // AND #$nn
  AND_ZP = 0x25,   // AND $nn
  AND_ZPX = 0x35,  // AND $nn,X
  AND_ABS = 0x2D,  // AND $nnnn
  AND_ABSX = 0x3D, // AND $nnnn,X
  AND_ABSY = 0x39, // AND $nnnn,Y
  AND_INDX = 0x21, // AND ($nn,X)
  AND_INDY = 0x31, // AND ($nn),Y

  // ASL - Arithmetic Shift Left
  ASL_ACC = 0x0A,  // ASL A
  ASL_ZP = 0x06,   // ASL $nn
  ASL_ZPX = 0x16,  // ASL $nn,X
  ASL_ABS = 0x0E,  // ASL $nnnn
  ASL_ABSX = 0x1E, // ASL $nnnn,X

  // BCC - Branch if Carry Clear
  BCC_REL = 0x90, // BCC $nn

  // BCS - Branch if Carry Set
  BCS_REL = 0xB0, // BCS $nn

  // BEQ - Branch if Equal
  BEQ_REL = 0xF0, // BEQ $nn

  // BIT - Bit Test
  BIT_ZP = 0x24,  // BIT $nn
  BIT_ABS = 0x2C, // BIT $nnnn

  // BMI - Branch if Minus
  BMI_REL = 0x30, // BMI $nn

  // BNE - Branch if Not Equal
  BNE_REL = 0xD0, // BNE $nn

  // BPL - Branch if Positive
  BPL_REL = 0x10, // BPL $nn

  // BRK - Force Interrupt
  BRK_IMP = 0x00, // BRK

  // BVC - Branch if Overflow Clear
  BVC_REL = 0x50, // BVC $nn

  // BVS - Branch if Overflow Set
  BVS_REL = 0x70, // BVS $nn

  // CLC - Clear Carry Flag
  CLC_IMP = 0x18, // CLC

  // CLD - Clear Decimal Mode
  CLD_IMP = 0xD8, // CLD

  // CLI - Clear Interrupt Disable
  CLI_IMP = 0x58, // CLI

  // CLV - Clear Overflow Flag
  CLV_IMP = 0xB8, // CLV

  // CMP - Compare
  CMP_IMM = 0xC9,  // CMP #$nn
  CMP_ZP = 0xC5,   // CMP $nn
  CMP_ZPX = 0xD5,  // CMP $nn,X
  CMP_ABS = 0xCD,  // CMP $nnnn
  CMP_ABSX = 0xDD, // CMP $nnnn,X
  CMP_ABSY = 0xD9, // CMP $nnnn,Y
  CMP_INDX = 0xC1, // CMP ($nn,X)
  CMP_INDY = 0xD1, // CMP ($nn),Y

  // CPX - Compare X Register
  CPX_IMM = 0xE0, // CPX #$nn
  CPX_ZP = 0xE4,  // CPX $nn
  CPX_ABS = 0xEC, // CPX $nnnn

  // CPY - Compare Y Register
  CPY_IMM = 0xC0, // CPY #$nn
  CPY_ZP = 0xC4,  // CPY $nn
  CPY_ABS = 0xCC, // CPY $nnnn

  // DEC - Decrement Memory
  DEC_ZP = 0xC6,   // DEC $nn
  DEC_ZPX = 0xD6,  // DEC $nn,X
  DEC_ABS = 0xCE,  // DEC $nnnn
  DEC_ABSX = 0xDE, // DEC $nnnn,X

  // DEX - Decrement X Register
  DEX_IMP = 0xCA, // DEX

  // DEY - Decrement Y Register
  DEY_IMP = 0x88, // DEY

  // EOR - Exclusive OR
  EOR_IMM = 0x49,  // EOR #$nn
  EOR_ZP = 0x45,   // EOR $nn
  EOR_ZPX = 0x55,  // EOR $nn,X
  EOR_ABS = 0x4D,  // EOR $nnnn
  EOR_ABSX = 0x5D, // EOR $nnnn,X
  EOR_ABSY = 0x59, // EOR $nnnn,Y
  EOR_INDX = 0x41, // EOR ($nn,X)
  EOR_INDY = 0x51, // EOR ($nn),Y

  // INC - Increment Memory
  INC_ZP = 0xE6,   // INC $nn
  INC_ZPX = 0xF6,  // INC $nn,X
  INC_ABS = 0xEE,  // INC $nnnn
  INC_ABSX = 0xFE, // INC $nnnn,X

  // INX - Increment X Register
  INX_IMP = 0xE8, // INX

  // INY - Increment Y Register
  INY_IMP = 0xC8, // INY

  // JMP - Jump
  JMP_ABS = 0x4C, // JMP $nnnn
  JMP_IND = 0x6C, // JMP ($nnnn)

  // JSR - Jump to Subroutine
  JSR_ABS = 0x20, // JSR $nnnn

  // LDA - Load Accumulator
  LDA_IMM = 0xA9,  // LDA #$nn
  LDA_ZP = 0xA5,   // LDA $nn
  LDA_ZPX = 0xB5,  // LDA $nn,X
  LDA_ABS = 0xAD,  // LDA $nnnn
  LDA_ABSX = 0xBD, // LDA $nnnn,X
  LDA_ABSY = 0xB9, // LDA $nnnn,Y
  LDA_INDX = 0xA1, // LDA ($nn,X)
  LDA_INDY = 0xB1, // LDA ($nn),Y

  // LDX - Load X Register
  LDX_IMM = 0xA2,  // LDX #$nn
  LDX_ZP = 0xA6,   // LDX $nn
  LDX_ZPY = 0xB6,  // LDX $nn,Y
  LDX_ABS = 0xAE,  // LDX $nnnn
  LDX_ABSY = 0xBE, // LDX $nnnn,Y

  // LDY - Load Y Register
  LDY_IMM = 0xA0,  // LDY #$nn
  LDY_ZP = 0xA4,   // LDY $nn
  LDY_ZPX = 0xB4,  // LDY $nn,X
  LDY_ABS = 0xAC,  // LDY $nnnn
  LDY_ABSX = 0xBC, // LDY $nnnn,X

  // LSR - Logical Shift Right
  LSR_ACC = 0x4A,  // LSR A
  LSR_ZP = 0x46,   // LSR $nn
  LSR_ZPX = 0x56,  // LSR $nn,X
  LSR_ABS = 0x4E,  // LSR $nnnn
  LSR_ABSX = 0x5E, // LSR $nnnn,X

  // NOP - No Operation
  NOP_IMP = 0xEA, // NOP

  // ORA - Logical Inclusive OR
  ORA_IMM = 0x09,  // ORA #$nn
  ORA_ZP = 0x05,   // ORA $nn
  ORA_ZPX = 0x15,  // ORA $nn,X
  ORA_ABS = 0x0D,  // ORA $nnnn
  ORA_ABSX = 0x1D, // ORA $nnnn,X
  ORA_ABSY = 0x19, // ORA $nnnn,Y
  ORA_INDX = 0x01, // ORA ($nn,X)
  ORA_INDY = 0x11, // ORA ($nn),Y

  // PHA - Push Accumulator
  PHA_IMP = 0x48, // PHA

  // PHP - Push Processor Status
  PHP_IMP = 0x08, // PHP

  // PLA - Pull Accumulator
  PLA_IMP = 0x68, // PLA

  // PLP - Pull Processor Status
  PLP_IMP = 0x28, // PLP

  // ROL - Rotate Left
  ROL_ACC = 0x2A,  // ROL A
  ROL_ZP = 0x26,   // ROL $nn
  ROL_ZPX = 0x36,  // ROL $nn,X
  ROL_ABS = 0x2E,  // ROL $nnnn
  ROL_ABSX = 0x3E, // ROL $nnnn,X

  // ROR - Rotate Right
  ROR_ACC = 0x6A,  // ROR A
  ROR_ZP = 0x66,   // ROR $nn
  ROR_ZPX = 0x76,  // ROR $nn,X
  ROR_ABS = 0x6E,  // ROR $nnnn
  ROR_ABSX = 0x7E, // ROR $nnnn,X

  // RTI - Return from Interrupt
  RTI_IMP = 0x40, // RTI

  // RTS - Return from Subroutine
  RTS_IMP = 0x60, // RTS

  // SBC - Subtract with Carry
  SBC_IMM = 0xE9,  // SBC #$nn
  SBC_ZP = 0xE5,   // SBC $nn
  SBC_ZPX = 0xF5,  // SBC $nn,X
  SBC_ABS = 0xED,  // SBC $nnnn
  SBC_ABSX = 0xFD, // SBC $nnnn,X
  SBC_ABSY = 0xF9, // SBC $nnnn,Y
  SBC_INDX = 0xE1, // SBC ($nn,X)
  SBC_INDY = 0xF1, // SBC ($nn),Y

  // SEC - Set Carry Flag
  SEC_IMP = 0x38, // SEC

  // SED - Set Decimal Flag
  SED_IMP = 0xF8, // SED

  // SEI - Set Interrupt Disable
  SEI_IMP = 0x78, // SEI

  // STA - Store Accumulator
  STA_ZP = 0x85,   // STA $nn
  STA_ZPX = 0x95,  // STA $nn,X
  STA_ABS = 0x8D,  // STA $nnnn
  STA_ABSX = 0x9D, // STA $nnnn,X
  STA_ABSY = 0x99, // STA $nnnn,Y
  STA_INDX = 0x81, // STA ($nn,X)
  STA_INDY = 0x91, // STA ($nn),Y

  // STX - Store X Register
  STX_ZP = 0x86,  // STX $nn
  STX_ZPY = 0x96, // STX $nn,Y
  STX_ABS = 0x8E, // STX $nnnn

  // STY - Store Y Register
  STY_ZP = 0x84,  // STY $nn
  STY_ZPX = 0x94, // STY $nn,X
  STY_ABS = 0x8C, // STY $nnnn

  // TAX - Transfer Accumulator to X
  TAX_IMP = 0xAA, // TAX

  // TAY - Transfer Accumulator to Y
  TAY_IMP = 0xA8, // TAY

  // TSX - Transfer Stack Pointer to X
  TSX_IMP = 0xBA, // TSX

  // TXA - Transfer X to Accumulator
  TXA_IMP = 0x8A, // TXA

  // TXS - Transfer X to Stack Pointer
  TXS_IMP = 0x9A, // TXS

  // TYA - Transfer Y to Accumulator
  TYA_IMP = 0x98 // TYA

} Opcode;

typedef enum : u8 {
  FLAG_NEGATIVE = 0x80,
  FLAG_OVERFLOW = 0x40,
  FLAG_BREAK = 0x10,
  FLAG_DECIMAL = 0x08,
  FLAG_INTERRUPT_DISABLE = 0x04,
  FLAG_ZERO = 0x02,
  FLAG_CARRY = 0x01
} Flag;

// The memory handling is temporary until I get the CPU opcodes to a functional
// state.
typedef struct {
  u8 A;   // Accumulator
  u8 X;   // Index register X
  u8 Y;   // Index register Y
  u8 S;   // Stack pointer
  u16 PC; // Program counter
  u8 P;   // Status registers
  u8 mem[0x10000];
} CPU;

#endif // TYPES_H
