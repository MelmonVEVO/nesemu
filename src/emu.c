#include "opcode.h"
#include "types.h"
#include <stdio.h>

typedef void (*InstructionFunc)(CPU *);

const InstructionFunc INSTRUCTION_TABLE[256] = {
    [BRK_IMP] = &brk,
    [LDA_IMM] = &lda_immediate,
    [LDA_ZP] = &lda_zeropage,
    [LDA_ZPX] = &lda_zeropage_x,
    [LDA_ABS] = &lda_absolute,
    [LDA_ABSX] = &lda_absolute_x,
    [LDA_ABSY] = &lda_absolute_y,
    [LDA_INDX] = &lda_indirect_x,
    [LDA_INDY] = &lda_indirect_y,
    [LDX_IMM] = &ldx_immediate,
    [LDX_ZP] = &ldx_zeropage,
    [LDX_ZPY] = &ldx_zeropage_y,
    [LDX_ABS] = &ldx_absolute,
    [LDX_ABSY] = &ldx_absolute_y,
    [LDY_IMM] = &ldy_immediate,
    [LDY_ZP] = &ldy_zeropage,
    [LDY_ZPX] = &ldy_zeropage_x,
    [LDY_ABS] = &ldy_absolute,
    [LDY_ABSX] = &ldy_absolute_x,
    [STA_ZP] = &sta_zeropage,
    [STA_ZPX] = &sta_zeropage_x,
    [STA_ABS] = &sta_absolute,
    [STA_ABSX] = &sta_absolute_x,
    [STA_ABSY] = &sta_absolute_y,
    [STA_INDX] = &sta_indirect_x,
    [STA_INDY] = &sta_indirect_y,
    [STX_ZP] = &stx_zeropage,
    [STX_ZPY] = &stx_zeropage_y,
    [STX_ABS] = &stx_absolute,
    [STY_ZP] = &sty_zeropage,
    [STY_ZPX] = &sty_zeropage_x,
    [STY_ABS] = &sty_absolute,
    [TAX_IMP] = &tax,
    [TAY_IMP] = &tay,
    [TXA_IMP] = &txa,
    [TYA_IMP] = &tya,
    [BCC_REL] = &bcc,
    [BCS_REL] = &bcs,
    [BEQ_REL] = &beq,
    [BMI_REL] = &bmi,
    [BNE_REL] = &bne,
    [BPL_REL] = &bpl,
    [BVC_REL] = &bvc,
    [BVS_REL] = &bvs,
    [PHA_IMP] = &pha,
    [PHP_IMP] = &php,
    [PLA_IMP] = &pla,
    [PLP_IMP] = &plp,
};

void execute(CPU *cpu) {
  u8 opcode = read_byte(cpu, cpu->PC);
  if (1) {
  }
}

void run_loop(CPU *cpu) {
  while (1) {
    execute(cpu);
    if (get_flag(cpu, FLAG_BREAK)) {
      break;
    }
  }
}

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
