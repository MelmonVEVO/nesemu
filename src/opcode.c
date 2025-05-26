#include "opcode.h"

u8 read_byte(CPU *cpu, u16 addr) { return cpu->mem[addr]; }

void write_byte(CPU *cpu, u16 addr, u8 val) { cpu->mem[addr] = val; }

u16 absolute_addr(CPU *cpu) {
  u8 lb = read_byte(cpu, cpu->PC + 1);
  u8 rb = read_byte(cpu, cpu->PC + 2);
  return (rb << 8) | lb;
}

u16 absolute_addr_at(CPU *cpu, u16 at) {
  u8 lb = read_byte(cpu, at);
  u8 rb = read_byte(cpu, at + 1);
  return (rb << 8) | lb;
}

u8 zeropage_read(CPU *cpu) {
  u8 addr = read_byte(cpu, (u16)cpu->PC + 1);
  return read_byte(cpu, (u16)addr);
}

void zeropage_write(CPU *cpu, u8 val) {
  u8 addr = read_byte(cpu, (u16)cpu->PC + 1);
  write_byte(cpu, (u16)addr, val);
}

u8 zeropage_offset_read(CPU *cpu, u8 offset) {
  u8 addr = read_byte(cpu, (u16)cpu->PC + 1) + offset;
  return read_byte(cpu, (u16)addr);
}

void zeropage_offset_write(CPU *cpu, u8 offset, u8 val) {
  u8 addr = read_byte(cpu, (u16)cpu->PC + 1) + offset;
  write_byte(cpu, (u16)addr, val);
}

u8 absolute_read(CPU *cpu) {
  u16 addr = absolute_addr(cpu);
  return read_byte(cpu, addr);
}

void absolute_write(CPU *cpu, u8 val) {
  u16 addr = absolute_addr(cpu);
  write_byte(cpu, addr, val);
}

u8 absolute_offset_read(CPU *cpu, u8 offset) {
  u16 addr = absolute_addr(cpu) + offset;
  return read_byte(cpu, addr);
}

void absolute_offset_write(CPU *cpu, u8 offset, u8 val) {
  u16 addr = absolute_addr(cpu) + offset;
  write_byte(cpu, addr, val);
}

u8 indexed_indirect_read_x(CPU *cpu) {
  u8 id_addr = read_byte(cpu, cpu->PC + 1) + cpu->X;
  u16 addr = absolute_addr_at(cpu, id_addr);
  return read_byte(cpu, addr);
}

void indexed_indirect_write_x(CPU *cpu, u8 val) {
  u8 id_addr = read_byte(cpu, cpu->PC + 1) + cpu->X;
  u16 addr = absolute_addr_at(cpu, id_addr);
  write_byte(cpu, addr, val);
}

u8 indirect_indexed_read_y(CPU *cpu) {
  u8 id_addr = read_byte(cpu, cpu->PC + 1);
  u16 addr = absolute_addr_at(cpu, id_addr) + cpu->Y;
  return read_byte(cpu, addr);
}

void indirect_indexed_write_y(CPU *cpu, u8 val) {
  u8 id_addr = read_byte(cpu, cpu->PC + 1);
  u16 addr = absolute_addr_at(cpu, id_addr) + cpu->Y;
  write_byte(cpu, addr, val);
}

void set_flag(CPU *cpu, Flag flag, u8 val) {
  if (val) {
    cpu->P |= flag;
    return;
  }
  cpu->P &= ~flag;
}

u8 get_flag(CPU *cpu, Flag flag) { return cpu->P & flag; }

void nop(CPU *cpu) {} // NOP

static void lda_common(CPU *cpu, u8 value) {
  cpu->A = value;
  set_flag(cpu, FLAG_NEGATIVE, value & 0x80);
  set_flag(cpu, FLAG_ZERO, value == 0);
}
void lda_immediate(CPU *cpu) {
  u8 value = read_byte(cpu, (u16)cpu->PC + 1);
  lda_common(cpu, value);
} // LDA #$nn
void lda_zeropage(CPU *cpu) { lda_common(cpu, zeropage_read(cpu)); } // LDA $nn
void lda_zeropage_x(CPU *cpu) {
  lda_common(cpu, zeropage_offset_read(cpu, cpu->X));
} // LDA $nn,X
void lda_absolute(CPU *cpu) {
  lda_common(cpu, absolute_read(cpu));
} // LDA $nnnn
void lda_absolute_x(CPU *cpu) {
  lda_common(cpu, absolute_offset_read(cpu, cpu->X));
} // LDA $nnnn,X
void lda_absolute_y(CPU *cpu) {
  lda_common(cpu, absolute_offset_read(cpu, cpu->Y));
} // LDA $nnnn,Y
void lda_indirect_x(CPU *cpu) {
  lda_common(cpu, indexed_indirect_read_x(cpu));
} // LDA ($nn,X)
void lda_indirect_y(CPU *cpu) {
  lda_common(cpu, indirect_indexed_read_y(cpu));
} // LDA ($nn),Y

static void ldx_common(CPU *cpu, u8 value) {
  cpu->X = value;
  set_flag(cpu, FLAG_NEGATIVE, value & 0x80);
  set_flag(cpu, FLAG_ZERO, value == 0);
}
void ldx_immediate(CPU *cpu) {
  u8 value = read_byte(cpu, (u16)cpu->PC + 1);
  ldx_common(cpu, value);
} // LDX #$nn
void ldx_zeropage(CPU *cpu) { ldx_common(cpu, zeropage_read(cpu)); } // LDX $nn
void ldx_zeropage_y(CPU *cpu) {
  ldx_common(cpu, zeropage_offset_read(cpu, cpu->Y));
} // LDX $nn,y
void ldx_absolute(CPU *cpu) {
  ldx_common(cpu, absolute_read(cpu));
} // LDX $nnnn
void ldx_absolute_y(CPU *cpu) {
  ldx_common(cpu, absolute_offset_read(cpu, cpu->Y));
} // LDX $nnnn,Y

static void ldy_common(CPU *cpu, u8 value) {
  cpu->Y = value;
  set_flag(cpu, FLAG_NEGATIVE, value & 0x80);
  set_flag(cpu, FLAG_ZERO, value == 0);
}
void ldy_immediate(CPU *cpu) {
  u8 value = read_byte(cpu, (u16)cpu->PC + 1);
  ldy_common(cpu, value);
} // LDY #$nn
void ldy_zeropage(CPU *cpu) { ldy_common(cpu, zeropage_read(cpu)); } // LDY $nn
void ldy_zeropage_x(CPU *cpu) {
  ldy_common(cpu, zeropage_offset_read(cpu, cpu->X));
} // LDY $nn,X
void ldy_absolute(CPU *cpu) {
  ldy_common(cpu, absolute_read(cpu));
} // LDY $nnnn
void ldy_absolute_x(CPU *cpu) {
  ldy_common(cpu, absolute_offset_read(cpu, cpu->X));
} // LDY $nnnn,X

void sta_zeropage(CPU *cpu) { zeropage_write(cpu, cpu->A); } // STA $nn
void sta_zeropage_x(CPU *cpu) {
  zeropage_offset_write(cpu, cpu->X, cpu->A);
} // STA $nn,X
void sta_absolute(CPU *cpu) { absolute_write(cpu, cpu->A); } // STA $nnnn
void sta_absolute_x(CPU *cpu) {
  absolute_offset_write(cpu, cpu->X, cpu->A);
} // STA $nnnn,X
void sta_absolute_y(CPU *cpu) {
  absolute_offset_write(cpu, cpu->Y, cpu->A);
} // STA $nnnn,Y
void sta_indirect_x(CPU *cpu) {
  indexed_indirect_write_x(cpu, cpu->A);
} // STA ($nn,X)
void sta_indirect_y(CPU *cpu) {
  indirect_indexed_write_y(cpu, cpu->A);
} // STA ($nn),Y

void stx_zeropage(CPU *cpu) { zeropage_write(cpu, cpu->X); } // STX $nn
void stx_zeropage_y(CPU *cpu) {
  zeropage_offset_write(cpu, cpu->Y, cpu->X);
} // STX $nn,Y
void stx_absolute(CPU *cpu) { absolute_write(cpu, cpu->X); } // STX $nnnn

void sty_zeropage(CPU *cpu) { zeropage_write(cpu, cpu->Y); } // STY $nn
void sty_zeropage_x(CPU *cpu) {
  zeropage_offset_write(cpu, cpu->X, cpu->Y);
} // STY $nn,X
void sty_absolute(CPU *cpu) { absolute_write(cpu, cpu->Y); } // STY $nnnn

void tax(CPU *cpu) {
  cpu->X = cpu->A;
  set_flag(cpu, FLAG_NEGATIVE, cpu->A & 0x80);
  set_flag(cpu, FLAG_ZERO, cpu->A == 0);
} // TAX
void tay(CPU *cpu) {
  cpu->Y = cpu->A;
  set_flag(cpu, FLAG_NEGATIVE, cpu->A & 0x80);
  set_flag(cpu, FLAG_ZERO, cpu->A == 0);
} // TAY
void txa(CPU *cpu) {
  cpu->A = cpu->X;
  set_flag(cpu, FLAG_NEGATIVE, cpu->X & 0x80);
  set_flag(cpu, FLAG_ZERO, cpu->X == 0);
} // TXA
void tya(CPU *cpu) {
  cpu->A = cpu->Y;
  set_flag(cpu, FLAG_NEGATIVE, cpu->Y & 0x80);
  set_flag(cpu, FLAG_ZERO, cpu->Y == 0);
} // TYA

void bcc(CPU *cpu) {
  if (get_flag(cpu, FLAG_CARRY))
    return;
  cpu->PC += (s8)read_byte(cpu, cpu->PC + 1);
} // BCC $nn
void bcs(CPU *cpu) {
  if (!get_flag(cpu, FLAG_CARRY))
    return;
  cpu->PC += (s8)read_byte(cpu, cpu->PC + 1);
} // BCS $nn
void beq(CPU *cpu) {
  if (!get_flag(cpu, FLAG_ZERO))
    return;
  cpu->PC += (s8)read_byte(cpu, cpu->PC + 1);
} // BEQ $nn
void bmi(CPU *cpu) {
  if (!get_flag(cpu, FLAG_NEGATIVE))
    return;
  cpu->PC += (s8)read_byte(cpu, cpu->PC + 1);
} // BMI $nn
void bne(CPU *cpu) {
  if (get_flag(cpu, FLAG_ZERO))
    return;
  cpu->PC += (s8)read_byte(cpu, cpu->PC + 1);
} // BNE $nn
void bpl(CPU *cpu) {
  if (get_flag(cpu, FLAG_NEGATIVE))
    return;
  cpu->PC += (s8)read_byte(cpu, cpu->PC + 1);
} // BPL $nn
void bvc(CPU *cpu) {
  if (get_flag(cpu, FLAG_OVERFLOW))
    return;
  cpu->PC += (s8)read_byte(cpu, cpu->PC + 1);
} // BVC $nn
void bvs(CPU *cpu) {
  if (!get_flag(cpu, FLAG_OVERFLOW))
    return;
  cpu->PC += (s8)read_byte(cpu, cpu->PC + 1);
} // BVS $nn

void push_stack(CPU *cpu, u8 val) {
  u16 addr = 0x0100 + cpu->S;
  write_byte(cpu, addr, val);
  cpu->S--;
}

void pop_stack(CPU *cpu, u8 *to) {
  cpu->S++;
  u16 addr = 0x0100 + cpu->S;
  u8 value = read_byte(cpu, addr);
  *to = value;
}

void pha(CPU *cpu) { push_stack(cpu, cpu->A); } // PHA
void php(CPU *cpu) { push_stack(cpu, cpu->P); } // PHP
void pla(CPU *cpu) { pop_stack(cpu, &cpu->A); } // PLA
void plp(CPU *cpu) { pop_stack(cpu, &cpu->P); } // PLP

static void and_common(CPU *cpu, u8 value) {
  cpu->A &= value;
  set_flag(cpu, FLAG_NEGATIVE, cpu->A & 0x80);
  set_flag(cpu, FLAG_ZERO, cpu->A == 0);
}
void and_immediate(CPU *cpu) {
  and_common(cpu, read_byte(cpu, cpu->PC + 1));
} // AND #$nn
void and_zeropage(CPU *cpu) { and_common(cpu, zeropage_read(cpu)); } // AND $nn
void and_zeropage_x(CPU *cpu) {
  and_common(cpu, zeropage_offset_read(cpu, cpu->X));
} // AND $nn,X
void and_absolute(CPU *cpu) {
  and_common(cpu, absolute_read(cpu));
} // AND $nnnn
void and_absolute_x(CPU *cpu) {
  and_common(cpu, absolute_offset_read(cpu, cpu->X));
} // AND $nnnn,X
void and_absolute_y(CPU *cpu) {
  and_common(cpu, absolute_offset_read(cpu, cpu->Y));
} // AND $nnnn,Y
void and_indirect_x(CPU *cpu) {
  and_common(cpu, indexed_indirect_read_x(cpu));
} // AND ($nn,X)
void and_indirect_y(CPU *cpu) {
  and_common(cpu, indirect_indexed_read_y(cpu));
} // AND ($nn),Y

static void ora_common(CPU *cpu, u8 value) {
  cpu->A |= value;
  set_flag(cpu, FLAG_NEGATIVE, cpu->A & 0x80);
  set_flag(cpu, FLAG_ZERO, cpu->A == 0);
}
void ora_immediate(CPU *cpu) {
  ora_common(cpu, read_byte(cpu, cpu->PC + 1));
} // ORA #$nn
void ora_zeropage(CPU *cpu) { ora_common(cpu, zeropage_read(cpu)); } // ORA $nn
void ora_zeropage_x(CPU *cpu) {
  ora_common(cpu, zeropage_offset_read(cpu, cpu->X));
} // ORA $nn,X
void ora_absolute(CPU *cpu) {
  ora_common(cpu, absolute_read(cpu));
} // ORA $nnnn
void ora_absolute_x(CPU *cpu) {
  ora_common(cpu, absolute_offset_read(cpu, cpu->X));
} // ORA $nnnn,X
void ora_absolute_y(CPU *cpu) {
  ora_common(cpu, absolute_offset_read(cpu, cpu->Y));
} // ORA $nnnn,Y
void ora_indirect_x(CPU *cpu) {
  ora_common(cpu, indexed_indirect_read_x(cpu));
} // ORA ($nn,X)
void ora_indirect_y(CPU *cpu) {
  ora_common(cpu, indirect_indexed_read_y(cpu));
} // ORA ($nn),Y

static void eor_common(CPU *cpu, u8 value) {
  cpu->A ^= value;
  set_flag(cpu, FLAG_NEGATIVE, cpu->A & 0x80);
  set_flag(cpu, FLAG_ZERO, cpu->A == 0);
}
void eor_immediate(CPU *cpu) {
  eor_common(cpu, read_byte(cpu, cpu->PC + 1));
} // EOR #$nn
void eor_zeropage(CPU *cpu) { eor_common(cpu, zeropage_read(cpu)); } // EOR $nn
void eor_zeropage_x(CPU *cpu) {
  eor_common(cpu, zeropage_offset_read(cpu, cpu->X));
} // EOR $nn,X
void eor_absolute(CPU *cpu) {
  eor_common(cpu, absolute_read(cpu));
} // EOR $nnnn
void eor_absolute_x(CPU *cpu) {
  eor_common(cpu, absolute_offset_read(cpu, cpu->X));
} // EOR $nnnn,X
void eor_absolute_y(CPU *cpu) {
  eor_common(cpu, absolute_offset_read(cpu, cpu->Y));
} // EOR $nnnn,Y
void eor_indirect_x(CPU *cpu) {
  eor_common(cpu, indexed_indirect_read_x(cpu));
} // EOR ($nn,X)
void eor_indirect_y(CPU *cpu) {
  eor_common(cpu, indirect_indexed_read_y(cpu));
} // EOR ($nn),Y

static void bit_common(CPU *cpu, u8 value) {
  u8 result = cpu->A & value;
  set_flag(cpu, FLAG_ZERO, !result);
  set_flag(cpu, FLAG_OVERFLOW, value & 0x40);
  set_flag(cpu, FLAG_NEGATIVE, value & 0x80);
}
void bit_zeropage(CPU *cpu) {
  u8 value = zeropage_read(cpu);
  bit_common(cpu, value);
} // BIT $nn
void bit_absolute(CPU *cpu) {
  u8 value = absolute_read(cpu);
  bit_common(cpu, value);
} // BIT $nnnn

static void adc_common(CPU *cpu, u8 add) {
  u16 result = (u16)cpu->A + (u16)add + (u16)(cpu->P & FLAG_CARRY);
  set_flag(cpu, FLAG_CARRY, result > 0x00FF);
  set_flag(cpu, FLAG_ZERO, !result);
  set_flag(cpu, FLAG_OVERFLOW, (result ^ cpu->A) & (result ^ add) & 0x0080);
  set_flag(cpu, FLAG_NEGATIVE, result & 0x0080);
  cpu->A = (u8)result;
}
void adc_immediate(CPU *cpu) {
  u8 mem = read_byte(cpu, cpu->PC + 1);
  adc_common(cpu, mem);
} // ADC #$nn
void adc_zeropage(CPU *cpu) {
  u8 mem = zeropage_read(cpu);
  adc_common(cpu, mem);
} // ADC $nn
void adc_zeropage_x(CPU *cpu) {
  u8 mem = zeropage_offset_read(cpu, cpu->X);
  adc_common(cpu, mem);
} // ADC $nn,X
void adc_absolute(CPU *cpu) {
  u8 mem = absolute_read(cpu);
  adc_common(cpu, mem);
} // ADC $nnnn
void adc_absolute_x(CPU *cpu) {
  u8 mem = absolute_offset_read(cpu, cpu->X);
  adc_common(cpu, mem);
} // ADC $nnnn,X
void adc_absolute_y(CPU *cpu) {
  u8 mem = absolute_offset_read(cpu, cpu->Y);
  adc_common(cpu, mem);
} // ADC $nnnn,Y
void adc_indirect_x(CPU *cpu) {
  u8 mem = indexed_indirect_read_x(cpu);
  adc_common(cpu, mem);
} // ADC ($nn,X)
void adc_indirect_y(CPU *cpu) {
  u8 mem = indirect_indexed_read_y(cpu);
  adc_common(cpu, mem);
} // ADC ($nn),Y

static void sbc_common(CPU *cpu, u8 sub) {}
void sbc_immediate(CPU *cpu);
void sbc_zeropage(CPU *cpu);
void sbc_zeropage_x(CPU *cpu);
void sbc_absolute(CPU *cpu);
void sbc_absolute_x(CPU *cpu);
void sbc_absolute_y(CPU *cpu);
void sbc_indirect_x(CPU *cpu);
void sbc_indirect_y(CPU *cpu);

void brk(CPU *cpu) {
  push_stack(cpu, cpu->PC + 2);
  push_stack(cpu, cpu->P);
  cpu->PC = 0xFFFE;
} // BRK
