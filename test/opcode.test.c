#include "opcode.h"
#include "unity.h"

CPU cpu;

void setUp(void) {
  // Initialize CPU state
  cpu.P = 0b00100000;
  cpu.S = 0xFF;
  cpu.PC = 0;
}

void tearDown(void) {
  // Clean up if needed
}

void test_lda_instructions(void) {
  // Test LDA Immediate
  cpu.mem[0] = LDA_IMM;
  cpu.mem[1] = 0x42;
  lda_immediate(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x42, cpu.A);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Zero Page
  cpu.mem[0] = LDA_ZP;
  cpu.mem[1] = 0x20;
  cpu.mem[0x20] = 0x55;
  lda_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x55, cpu.A);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Zero Page X
  cpu.mem[0] = LDA_ZPX;
  cpu.mem[1] = 0x20;
  cpu.X = 0x05;
  cpu.mem[0x25] = 0x66;
  lda_zeropage_x(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x66, cpu.A);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Absolute
  cpu.mem[0] = LDA_ABS;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.mem[0x1234] = 0x77;
  lda_absolute(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x77, cpu.A);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Absolute X
  cpu.mem[0] = LDA_ABSX;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.X = 0x02;
  cpu.mem[0x1236] = 0x88;
  lda_absolute_x(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x88, cpu.A);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Absolute Y
  cpu.mem[0] = LDA_ABSY;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.Y = 0x03;
  cpu.mem[0x1237] = 0x99;
  lda_absolute_y(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x99, cpu.A);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Indirect X
  cpu.mem[0] = LDA_INDX;
  cpu.mem[1] = 0x20;
  cpu.X = 0x05;
  cpu.mem[0x25] = 0x34;
  cpu.mem[0x26] = 0x12;
  cpu.mem[0x1234] = 0xAA;
  lda_indirect_x(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0xAA, cpu.A);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Indirect Y
  cpu.mem[0] = LDA_INDY;
  cpu.mem[1] = 0x20;
  cpu.Y = 0x05;
  cpu.mem[0x20] = 0x34;
  cpu.mem[0x21] = 0x12;
  cpu.mem[0x1239] = 0xBB;
  lda_indirect_y(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0xBB, cpu.A);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Zero Flag
  cpu.mem[0] = LDA_IMM;
  cpu.mem[1] = 0x00;
  lda_immediate(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.A);
  TEST_ASSERT_EQUAL_HEX8(FLAG_ZERO, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Negative Flag
  cpu.mem[0] = LDA_IMM;
  cpu.mem[1] = 0x80;
  lda_immediate(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x80, cpu.A);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(FLAG_NEGATIVE, get_flag(&cpu, FLAG_NEGATIVE));
}

void test_ldx_instructions(void) {
  // Test LDX Immediate
  cpu.mem[0] = LDX_IMM;
  cpu.mem[1] = 0x42;
  ldx_immediate(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x42, cpu.X);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDX Zero Page
  cpu.mem[0] = LDX_ZP;
  cpu.mem[1] = 0x20;
  cpu.mem[0x20] = 0x55;
  ldx_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x55, cpu.X);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDX Zero Page Y
  cpu.mem[0] = LDX_ZPY;
  cpu.mem[1] = 0x20;
  cpu.Y = 0x05;
  cpu.mem[0x25] = 0x66;
  ldx_zeropage_y(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x66, cpu.X);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDX Absolute
  cpu.mem[0] = LDX_ABS;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.mem[0x1234] = 0x77;
  ldx_absolute(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x77, cpu.X);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDX Absolute Y
  cpu.mem[0] = LDX_ABSY;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.Y = 0x02;
  cpu.mem[0x1236] = 0x88;
  ldx_absolute_y(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x88, cpu.X);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDX Zero Flag
  cpu.mem[0] = LDX_IMM;
  cpu.mem[1] = 0x00;
  ldx_immediate(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.X);
  TEST_ASSERT_EQUAL_HEX8(FLAG_ZERO, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDX Negative Flag
  cpu.mem[0] = LDX_IMM;
  cpu.mem[1] = 0x80;
  ldx_immediate(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x80, cpu.X);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(FLAG_NEGATIVE, get_flag(&cpu, FLAG_NEGATIVE));
}

void test_ldy_instructions(void) {
  // Test LDY Immediate
  cpu.mem[0] = LDY_IMM;
  cpu.mem[1] = 0x42;
  ldy_immediate(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x42, cpu.Y);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDY Zero Page
  cpu.mem[0] = LDY_ZP;
  cpu.mem[1] = 0x20;
  cpu.mem[0x20] = 0x55;
  ldy_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x55, cpu.Y);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDY Zero Page X
  cpu.mem[0] = LDY_ZPX;
  cpu.mem[1] = 0x20;
  cpu.X = 0x05;
  cpu.mem[0x25] = 0x66;
  ldy_zeropage_x(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x66, cpu.Y);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDY Absolute
  cpu.mem[0] = LDY_ABS;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.mem[0x1234] = 0x77;
  ldy_absolute(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x77, cpu.Y);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDY Absolute X
  cpu.mem[0] = LDY_ABSX;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.X = 0x02;
  cpu.mem[0x1236] = 0x88;
  ldy_absolute_x(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x88, cpu.Y);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDY Zero Flag
  cpu.mem[0] = LDY_IMM;
  cpu.mem[1] = 0x00;
  ldy_immediate(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.Y);
  TEST_ASSERT_EQUAL_HEX8(FLAG_ZERO, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDY Negative Flag
  cpu.mem[0] = LDY_IMM;
  cpu.mem[1] = 0x80;
  ldy_immediate(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x80, cpu.Y);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(FLAG_NEGATIVE, get_flag(&cpu, FLAG_NEGATIVE));
}

void test_sta_instructions(void) {
  // Test STA Zero Page
  cpu.A = 0x42;
  cpu.mem[0] = STA_ZP;
  cpu.mem[1] = 0x20;
  sta_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x42, cpu.mem[0x20]);

  // Test STA Zero Page X
  cpu.A = 0x55;
  cpu.X = 0x05;
  cpu.mem[0] = STA_ZPX;
  cpu.mem[1] = 0x20;
  sta_zeropage_x(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x55, cpu.mem[0x25]);

  // Test STA Absolute
  cpu.A = 0x66;
  cpu.mem[0] = STA_ABS;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  sta_absolute(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x66, cpu.mem[0x1234]);

  // Test STA Absolute X
  cpu.A = 0x77;
  cpu.X = 0x02;
  cpu.mem[0] = STA_ABSX;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  sta_absolute_x(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x77, cpu.mem[0x1236]);

  // Test STA Absolute Y
  cpu.A = 0x88;
  cpu.Y = 0x03;
  cpu.mem[0] = STA_ABSY;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  sta_absolute_y(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x88, cpu.mem[0x1237]);

  // Test STA Indirect X
  cpu.A = 0x99;
  cpu.X = 0x05;
  cpu.mem[0] = STA_INDX;
  cpu.mem[1] = 0x20;
  cpu.mem[0x25] = 0x34;
  cpu.mem[0x26] = 0x12;
  sta_indirect_x(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x99, cpu.mem[0x1234]);

  // Test STA Indirect Y
  cpu.A = 0xAA;
  cpu.Y = 0x05;
  cpu.mem[0] = STA_INDY;
  cpu.mem[1] = 0x20;
  cpu.mem[0x20] = 0x34;
  cpu.mem[0x21] = 0x12;
  sta_indirect_y(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0xAA, cpu.mem[0x1239]);

  // Test that STA doesn't affect flags
  u8 original_flags = cpu.P;
  cpu.A = 0x00; // Zero value
  cpu.mem[0] = STA_ZP;
  cpu.mem[1] = 0x30;
  sta_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.mem[0x30]);
  TEST_ASSERT_EQUAL_HEX8(original_flags, cpu.P); // Flags unchanged

  cpu.A = 0x80; // Negative value
  cpu.mem[0] = STA_ZP;
  cpu.mem[1] = 0x31;
  sta_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x80, cpu.mem[0x31]);
  TEST_ASSERT_EQUAL_HEX8(original_flags, cpu.P); // Flags unchanged
}

void test_stx_instructions(void) {
  // Test STX Zero Page
  cpu.X = 0x42;
  cpu.mem[0] = STX_ZP;
  cpu.mem[1] = 0x20;
  stx_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x42, cpu.mem[0x20]);

  // Test STX Zero Page Y
  cpu.X = 0x55;
  cpu.Y = 0x05;
  cpu.mem[0] = STX_ZPY;
  cpu.mem[1] = 0x20;
  stx_zeropage_y(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x55, cpu.mem[0x25]);

  // Test STX Absolute
  cpu.X = 0x66;
  cpu.mem[0] = STX_ABS;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  stx_absolute(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x66, cpu.mem[0x1234]);

  // Test that STX doesn't affect flags
  u8 original_flags = cpu.P;
  cpu.X = 0x00; // Zero value
  cpu.mem[0] = STX_ZP;
  cpu.mem[1] = 0x30;
  stx_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.mem[0x30]);
  TEST_ASSERT_EQUAL_HEX8(original_flags, cpu.P); // Flags unchanged

  cpu.X = 0x80; // Negative value
  cpu.mem[0] = STX_ZP;
  cpu.mem[1] = 0x31;
  stx_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x80, cpu.mem[0x31]);
  TEST_ASSERT_EQUAL_HEX8(original_flags, cpu.P); // Flags unchanged
}

void test_sty_instructions(void) {
  // Test STY Zero Page
  cpu.Y = 0x42;
  cpu.mem[0] = STY_ZP;
  cpu.mem[1] = 0x20;
  sty_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x42, cpu.mem[0x20]);

  // Test STY Zero Page X
  cpu.Y = 0x55;
  cpu.X = 0x05;
  cpu.mem[0] = STY_ZPX;
  cpu.mem[1] = 0x20;
  sty_zeropage_x(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x55, cpu.mem[0x25]);

  // Test STY Absolute
  cpu.Y = 0x66;
  cpu.mem[0] = STY_ABS;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  sty_absolute(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x66, cpu.mem[0x1234]);

  // Test that STY doesn't affect flags
  u8 original_flags = cpu.P;
  cpu.Y = 0x00; // Zero value
  cpu.mem[0] = STY_ZP;
  cpu.mem[1] = 0x30;
  sty_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.mem[0x30]);
  TEST_ASSERT_EQUAL_HEX8(original_flags, cpu.P); // Flags unchanged

  cpu.Y = 0x80; // Negative value
  cpu.mem[0] = STY_ZP;
  cpu.mem[1] = 0x31;
  sty_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x80, cpu.mem[0x31]);
  TEST_ASSERT_EQUAL_HEX8(original_flags, cpu.P); // Flags unchanged
}

void test_transfer_instructions(void) {}

void test_branch_instructions(void) {}

void test_stack_instructions(void) {}

void test_and_instructions(void) {}

void test_ora_instructions(void) {}

void test_eor_instructions(void) {}

void test_cmp_instructions(void) {}

void test_adc_instructions(void) {}

void test_sbc_instructions(void) {}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_lda_instructions);
  RUN_TEST(test_ldx_instructions);
  RUN_TEST(test_ldy_instructions);
  RUN_TEST(test_sta_instructions);
  RUN_TEST(test_stx_instructions);
  RUN_TEST(test_sty_instructions);
  RUN_TEST(test_transfer_instructions);
  RUN_TEST(test_branch_instructions);
  RUN_TEST(test_stack_instructions);
  RUN_TEST(test_and_instructions);
  RUN_TEST(test_ora_instructions);
  RUN_TEST(test_eor_instructions);
  RUN_TEST(test_cmp_instructions);
  RUN_TEST(test_adc_instructions);
  RUN_TEST(test_sbc_instructions);
  return UNITY_END();
}
