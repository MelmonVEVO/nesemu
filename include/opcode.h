#ifndef OPCODE_H
#define OPCODE_H

#include "types.h"

// Memory access functions
u8 read_byte(CPU *cpu, u16 addr);
void write_byte(CPU *cpu, u16 addr, u8 val);
u16 absolute_addr(CPU *cpu);

// Flag operations
void set_flag(CPU *cpu, Flag flag, u8 val);
u8 get_flag(CPU *cpu, Flag flag);

// No operation
void nop(CPU *cpu);

// LDA instructions
void lda_common(CPU *cpu, u8 value);
void lda_immediate(CPU *cpu);
void lda_zeropage(CPU *cpu);
void lda_zeropage_x(CPU *cpu);
void lda_absolute(CPU *cpu);
void lda_absolute_x(CPU *cpu);
void lda_absolute_y(CPU *cpu);
void lda_indirect_x(CPU *cpu);
void lda_indirect_y(CPU *cpu);

// LDX instructions
void ldx_common(CPU *cpu, u8 value);
void ldx_immediate(CPU *cpu);
void ldx_zeropage(CPU *cpu);
void ldx_zeropage_y(CPU *cpu);
void ldx_absolute(CPU *cpu);
void ldx_absolute_y(CPU *cpu);

// LDY instructions
void ldy_common(CPU *cpu, u8 value);
void ldy_immediate(CPU *cpu);
void ldy_zeropage(CPU *cpu);
void ldy_zeropage_x(CPU *cpu);
void ldy_absolute(CPU *cpu);
void ldy_absolute_x(CPU *cpu);

// STA instructions
void sta_zeropage(CPU *cpu);
void sta_zeropage_x(CPU *cpu);
void sta_absolute(CPU *cpu);
void sta_absolute_x(CPU *cpu);
void sta_absolute_y(CPU *cpu);
void sta_indirect_x(CPU *cpu);
void sta_indirect_y(CPU *cpu);

// STX instructions
void stx_zeropage(CPU *cpu);
void stx_zeropage_y(CPU *cpu);
void stx_absolute(CPU *cpu);

// STY instructions
void sty_zeropage(CPU *cpu);
void sty_zeropage_x(CPU *cpu);
void sty_absolute(CPU *cpu);

// Transfer instructions
void tax(CPU *cpu);
void tay(CPU *cpu);
void txa(CPU *cpu);
void tya(CPU *cpu);

// Branch instructions
void bcc(CPU *cpu);
void bcs(CPU *cpu);
void beq(CPU *cpu);
void bmi(CPU *cpu);
void bne(CPU *cpu);
void bpl(CPU *cpu);
void bvc(CPU *cpu);
void bvs(CPU *cpu);

// Stack operations
void push_stack(CPU *cpu, u8 val);
void pop_stack(CPU *cpu, u8 *to);
void pha(CPU *cpu);
void php(CPU *cpu);
void pla(CPU *cpu);
void plp(CPU *cpu);

// Logic operations
void and_common(CPU *cpu, u8 value);
void and_immediate(CPU *cpu);
void and_zeropage(CPU *cpu);
void and_zeropage_x(CPU *cpu);
void and_absolute(CPU *cpu);
void and_absolute_x(CPU *cpu);
void and_absolute_y(CPU *cpu);
void and_indirect_x(CPU *cpu);
void and_indirect_y(CPU *cpu);

void ora_common(CPU *cpu, u8 value);
void ora_immediate(CPU *cpu);
void ora_zeropage(CPU *cpu);
void ora_zeropage_x(CPU *cpu);
void ora_absolute(CPU *cpu);
void ora_absolute_x(CPU *cpu);
void ora_absolute_y(CPU *cpu);
void ora_indirect_x(CPU *cpu);
void ora_indirect_y(CPU *cpu);

void eor_common(CPU *cpu, u8 value);
void eor_immediate(CPU *cpu);
void eor_zeropage(CPU *cpu);
void eor_zeropage_x(CPU *cpu);
void eor_absolute(CPU *cpu);
void eor_absolute_x(CPU *cpu);
void eor_absolute_y(CPU *cpu);
void eor_indirect_x(CPU *cpu);
void eor_indirect_y(CPU *cpu);

void cmp_common(CPU *cpu, u8 value);
void cmp_immediate(CPU *cpu);
void cmp_zeropage(CPU *cpu);
void cmp_zeropage_x(CPU *cpu);
void cmp_absolute(CPU *cpu);
void cmp_absolute_x(CPU *cpu);
void cmp_absolute_y(CPU *cpu);
void cmp_indirect_x(CPU *cpu);
void cmp_indirect_y(CPU *cpu);

// Arithmentic operations
void adc_immediate(CPU *cpu);
void adc_zeropage(CPU *cpu);
void adc_zeropage_x(CPU *cpu);
void adc_absolute(CPU *cpu);
void adc_absolute_x(CPU *cpu);
void adc_absolute_y(CPU *cpu);
void adc_indirect_x(CPU *cpu);
void adc_indirect_y(CPU *cpu);

void sbc_immediate(CPU *cpu);
void sbc_zeropage(CPU *cpu);
void sbc_zeropage_x(CPU *cpu);
void sbc_absolute(CPU *cpu);
void sbc_absolute_x(CPU *cpu);
void sbc_absolute_y(CPU *cpu);
void sbc_indirect_x(CPU *cpu);
void sbc_indirect_y(CPU *cpu);

void bit_zeropage(CPU *cpu);
void bit_absolute(CPU *cpu);
// System instructions
void brk(CPU *cpu);

#endif // OPCODE_H
