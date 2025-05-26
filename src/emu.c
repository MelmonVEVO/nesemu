#include "types.h"
#include <stdio.h>

u8 memory[0x10000];

u8 read_byte(CPU *cpu, u16 addr) { return memory[addr]; }

void write_byte(CPU *cpu, u16 addr, u8 val) { memory[addr] = val; }

u16 absolute_addr(CPU *cpu) {
  u8 lb = read_byte(cpu, cpu->PC + 1);
  u8 rb = read_byte(cpu, cpu->PC + 2);
  return (rb << 8) | lb;
}

void set_flag(CPU *cpu, u16 flag, u8 val) {
  if (val) {
    cpu->P |= flag;
  } else {
    cpu->P &= ~flag;
  }
}

u8 get_flag(CPU *cpu, u16 flag) { return cpu->P & flag; }

void push_stack(CPU *cpu, u8 val);
u8 pop_stack(CPU *cpu);

static void brk(CPU *cpu) {
  push_stack(cpu, cpu->PC + 2);
  push_stack(cpu, cpu->P);
  cpu->PC = 0xFFFE;
} // BRK

static void nop(CPU *cpu) {} // NOP

static void lda_common(CPU *cpu, u8 value) {
  cpu->A = value;
  set_flag(cpu, FLAG_NEGATIVE, value & 0x80);
  set_flag(cpu, FLAG_ZERO, value == 0);
}
static void lda_immediate(CPU *cpu) {
  u8 value = read_byte(cpu, (u16)cpu->PC + 1);
  lda_common(cpu, value);
} // LDA #$nn
static void lda_zeropage(CPU *cpu) {
  u8 zp_addr = read_byte(cpu, (u16)cpu->PC + 1);
  u8 value = read_byte(cpu, (u16)zp_addr);
  lda_common(cpu, value);
} // LDA $nn
static void lda_zeropage_x(CPU *cpu) {
  u8 zp_addr = read_byte(cpu, cpu->PC + 1);
  zp_addr += cpu->X;
  u8 value = read_byte(cpu, (u16)zp_addr);
  lda_common(cpu, value);
} // LDA $nn,X
static void lda_absolute(CPU *cpu) {
  u16 addr = absolute_addr(cpu);
  u8 value = read_byte(cpu, addr);
  lda_common(cpu, value);
} // LDA $nnnn
static void lda_absolute_x(CPU *cpu) {
  u16 addr = absolute_addr(cpu);
  addr += (u16)cpu->X;
  u8 value = read_byte(cpu, addr);
  lda_common(cpu, value);
} // LDA $nnnn,X
static void lda_absolute_y(CPU *cpu) {
  u16 addr = absolute_addr(cpu);
  addr += (u16)cpu->Y;
  u8 value = read_byte(cpu, addr);
  lda_common(cpu, value);
} // LDA $nnnn,Y
static void lda_indirect_x(CPU *cpu) {
  u8 zp_addr = read_byte(cpu, cpu->PC + 1) + cpu->X;
  u16 addr = absolute_addr(cpu);
  u8 value = read_byte(cpu, addr);
  lda_common(cpu, value);
} // LDA ($nn,X)
static void lda_indirect_y(CPU *cpu) {
  u8 zp_addr = read_byte(cpu, cpu->PC + 1);
  u16 addr = absolute_addr(cpu);
  addr += cpu->Y;
  u8 value = read_byte(cpu, addr);
  lda_common(cpu, value);
} // LDA ($nn),Y

static void ldx_common(CPU *cpu, u8 value) {
  cpu->X = value;
  set_flag(cpu, FLAG_NEGATIVE, value & 0x80);
  set_flag(cpu, FLAG_ZERO, value == 0);
}
static void ldx_immediate(CPU *cpu) {
  u8 value = read_byte(cpu, (u16)cpu->PC + 1);
  ldx_common(cpu, value);
} // LDX #$nn
static void ldx_zeropage(CPU *cpu) {
  u8 zp_addr = read_byte(cpu, (u16)cpu->PC + 1);
  u8 value = read_byte(cpu, (u16)zp_addr);
  ldx_common(cpu, value);
} // LDX $nn
static void ldx_zeropage_y(CPU *cpu) {
  u8 zp_addr = read_byte(cpu, (u16)cpu->PC + 1);
  zp_addr += cpu->Y;
  u8 value = read_byte(cpu, (u16)zp_addr);
  ldx_common(cpu, value);
} // LDX $nn,y
static void ldx_absolute(CPU *cpu) {
  u16 addr = absolute_addr(cpu);
  u8 value = read_byte(cpu, addr);
  ldx_common(cpu, value);
} // LDX $nnnn
static void ldx_absolute_y(CPU *cpu) {
  u16 addr = absolute_addr(cpu);
  addr += cpu->Y;
  u8 value = read_byte(cpu, addr);
  ldx_common(cpu, value);
} // LDX $nnnn,Y

static void ldy_common(CPU *cpu, u8 value) {
  cpu->Y = value;
  set_flag(cpu, FLAG_NEGATIVE, value & 0x80);
  set_flag(cpu, FLAG_ZERO, value == 0);
}
static void ldy_immediate(CPU *cpu) {
  u8 value = read_byte(cpu, (u16)cpu->PC + 1);
  ldy_common(cpu, value);
} // LDY #$nn
static void ldy_zeropage(CPU *cpu) {
  u8 zp_addr = read_byte(cpu, (u16)cpu->PC + 1);
  u8 value = read_byte(cpu, (u16)zp_addr);
  ldy_common(cpu, value);
} // LDY $nn
static void ldy_zeropage_x(CPU *cpu) {
  u8 zp_addr = read_byte(cpu, (u16)cpu->PC + 1);
  zp_addr += cpu->X;
  u8 value = read_byte(cpu, (u16)zp_addr);
  ldy_common(cpu, value);
} // LDY $nn,X
static void ldy_absolute(CPU *cpu) {
  u16 addr = absolute_addr(cpu);
  u8 value = read_byte(cpu, addr);
  ldy_common(cpu, value);
} // LDY $nnnn
static void ldy_absolute_x(CPU *cpu) {
  u16 addr = absolute_addr(cpu);
  addr += cpu->X;
  u8 value = read_byte(cpu, addr);
  ldy_common(cpu, value);
} // LDY $nnnn,X

static void sta_zeropage(CPU *cpu) {
  u8 zp_addr = read_byte(cpu, cpu->PC + 1);
  write_byte(cpu, (u16)zp_addr, cpu->A);
} // STA $nn
static void sta_zeropage_x(CPU *cpu) {
  u8 zp_addr = read_byte(cpu, cpu->PC + 1);
  zp_addr += cpu->X;
  write_byte(cpu, (u16)zp_addr, cpu->A);
} // STA $nn,X
static void sta_absolute(CPU *cpu) {
  u16 addr = absolute_addr(cpu);
  write_byte(cpu, addr, cpu->A);
} // STA $nnnn
static void sta_absolute_x(CPU *cpu) {
  u16 addr = absolute_addr(cpu);
  addr += cpu->X;
  write_byte(cpu, addr, cpu->A);
} // STA $nnnn,X
static void sta_absolute_y(CPU *cpu) {
  u16 addr = absolute_addr(cpu);
  addr += cpu->Y;
  write_byte(cpu, addr, cpu->A);
} // STA $nnnn,Y
static void sta_indirect_x(CPU *cpu) {
  u8 addr = read_byte(cpu, cpu->PC + 1 + cpu->X);
  write_byte(cpu, (u16)addr, cpu->A);
} // STA ($nn,X)
static void sta_indirect_y(CPU *cpu) {
  u8 addr = read_byte(cpu, cpu->PC + 1) + cpu->Y;
  write_byte(cpu, (u16)addr, cpu->A);
} // STA ($nn),Y

static void stx_zeropage(CPU *cpu) {
  u8 addr = read_byte(cpu, cpu->PC + 1);
  write_byte(cpu, (u16)addr, cpu->X);
} // STX $nn
static void stx_zeropage_y(CPU *cpu) {
  u8 addr = read_byte(cpu, cpu->PC + 1);
  addr += cpu->Y;
  write_byte(cpu, (u16)addr, cpu->X);
} // STX $nn,Y
static void stx_absolute(CPU *cpu) {
  u16 addr = absolute_addr(cpu);
  write_byte(cpu, addr, cpu->X);
} // STX $nnnn

static void sty_zeropage(CPU *cpu) {
  u8 addr = read_byte(cpu, cpu->PC + 1);
  write_byte(cpu, (u16)addr, cpu->Y);
} // STY $nn
static void sty_zeropage_x(CPU *cpu) {
  u8 addr = read_byte(cpu, cpu->PC + 1);
  addr += cpu->X;
  write_byte(cpu, (u16)addr, cpu->Y);
} // STY $nn,X
static void sty_absolute(CPU *cpu) {
  u16 addr = absolute_addr(cpu);
  write_byte(cpu, addr, cpu->Y);
} // STY $nnnn

static void tax(CPU *cpu) {
  cpu->X = cpu->A;
  set_flag(cpu, FLAG_NEGATIVE, cpu->A & 0x80);
  set_flag(cpu, FLAG_ZERO, cpu->A == 0);
} // TAX
static void tay(CPU *cpu) {
  cpu->Y = cpu->A;
  set_flag(cpu, FLAG_NEGATIVE, cpu->A & 0x80);
  set_flag(cpu, FLAG_ZERO, cpu->A == 0);
} // TAY
static void txa(CPU *cpu) {
  cpu->A = cpu->X;
  set_flag(cpu, FLAG_NEGATIVE, cpu->X & 0x80);
  set_flag(cpu, FLAG_ZERO, cpu->X == 0);
} // TXA
static void tya(CPU *cpu) {
  cpu->A = cpu->Y;
  set_flag(cpu, FLAG_NEGATIVE, cpu->Y & 0x80);
  set_flag(cpu, FLAG_ZERO, cpu->Y == 0);
} // TYA

static void bcc(CPU *cpu) {
  if (get_flag(cpu, FLAG_CARRY))
    return;
  cpu->PC += (s8)read_byte(cpu, cpu->PC + 1);
} // BCC $nn
static void bcs(CPU *cpu) {
  if (!get_flag(cpu, FLAG_CARRY))
    return;
  cpu->PC += (s8)read_byte(cpu, cpu->PC + 1);
} // BCS $nn
static void beq(CPU *cpu) {
  if (!get_flag(cpu, FLAG_ZERO))
    return;
  cpu->PC += (s8)read_byte(cpu, cpu->PC + 1);
} // BEQ $nn
static void bmi(CPU *cpu) {
  if (!get_flag(cpu, FLAG_NEGATIVE))
    return;
  cpu->PC += (s8)read_byte(cpu, cpu->PC + 1);
} // BMI $nn
static void bne(CPU *cpu) {
  if (get_flag(cpu, FLAG_ZERO))
    return;
  cpu->PC += (s8)read_byte(cpu, cpu->PC + 1);
} // BNE $nn
static void bpl(CPU *cpu) {
  if (get_flag(cpu, FLAG_NEGATIVE))
    return;
  cpu->PC += (s8)read_byte(cpu, cpu->PC + 1);
} // BPL $nn
static void bvc(CPU *cpu) {
  if (get_flag(cpu, FLAG_OVERFLOW))
    return;
  cpu->PC += (s8)read_byte(cpu, cpu->PC + 1);
} // BVC $nn
static void bvs(CPU *cpu) {
  if (!get_flag(cpu, FLAG_OVERFLOW))
    return;
  cpu->PC += (s8)read_byte(cpu, cpu->PC + 1);
} // BVS $nn

static void bit_zeropage(CPU *cpu) {} // BIT $nn
static void bit_absolute(CPU *cpu) {} // BIT $nnnn

typedef void (*InstructionFunc)(CPU *);

InstructionFunc INSTRUCTION_TABLE[256] = {
    [BRK_IMP] = *brk,
    [LDA_IMM] = *lda_immediate,
    [LDA_ZP] = *lda_zeropage,
    [LDA_ZPX] = *lda_zeropage_x,
    [LDA_ABS] = *lda_absolute,
    [LDA_ABSX] = *lda_absolute_x,
    [LDA_ABSY] = *lda_absolute_y,
    [LDA_INDX] = *lda_indirect_x,
    [LDA_INDY] = *lda_indirect_y,
    [LDX_IMM] = *ldx_immediate,
    [LDX_ZP] = *ldx_zeropage,
    [LDX_ZPY] = *ldx_zeropage_y,
    [LDX_ABS] = *ldx_absolute,
    [LDX_ABSY] = *ldx_absolute_y,
    [LDY_IMM] = *ldy_immediate,
    [LDY_ZP] = *ldy_zeropage,
    [LDY_ZPX] = *ldy_zeropage_x,
    [LDY_ABS] = *ldy_absolute,
    [LDY_ABSX] = *ldy_absolute_x,
    [STA_ZP] = *sta_zeropage,
    [STA_ZPX] = *sta_zeropage_x,
    [STA_ABS] = *sta_absolute,
    [STA_ABSX] = *sta_absolute_x,
    [STA_ABSY] = *sta_absolute_y,
    [STA_INDX] = *sta_indirect_x,
    [STA_INDY] = *sta_indirect_y,
    [STX_ZP] = *stx_zeropage,
    [STX_ZPY] = *stx_zeropage_y,
    [STX_ABS] = *stx_absolute,
    [STY_ZP] = *sty_zeropage,
    [STY_ZPX] = *sty_zeropage_x,
    [STY_ABS] = *sty_absolute,
    [TAX_IMP] = *tax,
    [TAY_IMP] = *tay,
    [TXA_IMP] = *txa,
    [TYA_IMP] = *tya,
    [BCC_REL] = *bcc,
    [BCS_REL] = *bcs,
    [BEQ_REL] = *beq,
    [BMI_REL] = *bmi,
    [BNE_REL] = *bne,
    [BPL_REL] = *bpl,
    [BVC_REL] = *bvc,
    [BVS_REL] = *bvs,
};

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "file not provided.");
    return 1;
  }

  char *filename = argv[1];
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    fprintf(stderr, "error opening file. the file may not exist.");
    return 1;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  CPU cpu = {0};

  return 0;
}
