#include "opcode.h"
#include "unity.h"
#include <string.h>

CPU cpu;

void setUp(void) {
  // Initialize CPU state
  memset(&cpu, 0, sizeof(CPU));
  cpu.S = 0xFF; // Initialize stack pointer
}

void tearDown(void) {
  // Clean up if needed
}

void test_lda_instructions(void) {
  // Test LDA Immediate
  cpu.mem[0] = LDA_IMM;
  cpu.mem[1] = 0x42;
  lda_immediate(&cpu);
  TEST_ASSERT_EQUAL(0x42, cpu.A);
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Zero Page
  cpu.mem[0] = LDA_ZP;
  cpu.mem[1] = 0x20;
  cpu.mem[0x20] = 0x55;
  lda_zeropage(&cpu);
  TEST_ASSERT_EQUAL(0x55, cpu.A);
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Zero Page X
  cpu.mem[0] = LDA_ZPX;
  cpu.mem[1] = 0x20;
  cpu.X = 0x05;
  cpu.mem[0x25] = 0x66;
  lda_zeropage_x(&cpu);
  TEST_ASSERT_EQUAL(0x66, cpu.A);
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Absolute
  cpu.mem[0] = LDA_ABS;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.mem[0x1234] = 0x77;
  lda_absolute(&cpu);
  TEST_ASSERT_EQUAL(0x77, cpu.A);
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Absolute X
  cpu.mem[0] = LDA_ABSX;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.X = 0x02;
  cpu.mem[0x1236] = 0x88;
  lda_absolute_x(&cpu);
  TEST_ASSERT_EQUAL(0x88, cpu.A);
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Absolute Y
  cpu.mem[0] = LDA_ABSY;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.Y = 0x03;
  cpu.mem[0x1237] = 0x99;
  lda_absolute_y(&cpu);
  TEST_ASSERT_EQUAL(0x99, cpu.A);
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Indirect X
  cpu.mem[0] = LDA_INDX;
  cpu.mem[1] = 0x20;
  cpu.X = 0x05;
  cpu.mem[0x25] = 0x34;
  cpu.mem[0x26] = 0x12;
  cpu.mem[0x1234] = 0xAA;
  lda_indirect_x(&cpu);
  TEST_ASSERT_EQUAL(0xAA, cpu.A);
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Indirect Y
  cpu.mem[0] = LDA_INDY;
  cpu.mem[1] = 0x20;
  cpu.Y = 0x05;
  cpu.mem[0x20] = 0x34;
  cpu.mem[0x21] = 0x12;
  cpu.mem[0x1239] = 0xBB;
  lda_indirect_y(&cpu);
  TEST_ASSERT_EQUAL(0xBB, cpu.A);
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Zero Flag
  cpu.mem[0] = LDA_IMM;
  cpu.mem[1] = 0x00;
  lda_immediate(&cpu);
  TEST_ASSERT_EQUAL(0x00, cpu.A);
  TEST_ASSERT_EQUAL(1, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Negative Flag
  cpu.mem[0] = LDA_IMM;
  cpu.mem[1] = 0x80;
  lda_immediate(&cpu);
  TEST_ASSERT_EQUAL(0x80, cpu.A);
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(1, get_flag(&cpu, FLAG_NEGATIVE));
}

void test_ldx_instructions(void) {
  // Test LDX Immediate
  cpu.mem[0] = LDX_IMM;
  cpu.mem[1] = 0x42;
  ldx_immediate(&cpu);
  TEST_ASSERT_EQUAL(0x42, cpu.X);
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDX Zero Page
  cpu.mem[0] = LDX_ZP;
  cpu.mem[1] = 0x20;
  cpu.mem[0x20] = 0x55;
  ldx_zeropage(&cpu);
  TEST_ASSERT_EQUAL(0x55, cpu.X);
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDX Zero Page Y
  cpu.mem[0] = LDX_ZPY;
  cpu.mem[1] = 0x20;
  cpu.Y = 0x05;
  cpu.mem[0x25] = 0x66;
  ldx_zeropage_y(&cpu);
  TEST_ASSERT_EQUAL(0x66, cpu.X);
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDX Absolute
  cpu.mem[0] = LDX_ABS;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.mem[0x1234] = 0x77;
  ldx_absolute(&cpu);
  TEST_ASSERT_EQUAL(0x77, cpu.X);
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDX Absolute Y
  cpu.mem[0] = LDX_ABSY;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.Y = 0x02;
  cpu.mem[0x1236] = 0x88;
  ldx_absolute_y(&cpu);
  TEST_ASSERT_EQUAL(0x88, cpu.X);
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDX Zero Flag
  cpu.mem[0] = LDX_IMM;
  cpu.mem[1] = 0x00;
  ldx_immediate(&cpu);
  TEST_ASSERT_EQUAL(0x00, cpu.X);
  TEST_ASSERT_EQUAL(1, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDX Negative Flag
  cpu.mem[0] = LDX_IMM;
  cpu.mem[1] = 0x80;
  ldx_immediate(&cpu);
  TEST_ASSERT_EQUAL(0x80, cpu.X);
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(1, get_flag(&cpu, FLAG_NEGATIVE));
}

void test_ldy_instructions(void) {
  // Test LDY Immediate
  cpu.mem[0] = LDY_IMM;
  cpu.mem[1] = 0x42;
  ldy_immediate(&cpu);
  TEST_ASSERT_EQUAL(0x42, cpu.Y);
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDY Zero Page
  cpu.mem[0] = LDY_ZP;
  cpu.mem[1] = 0x20;
  cpu.mem[0x20] = 0x55;
  ldy_zeropage(&cpu);
  TEST_ASSERT_EQUAL(0x55, cpu.Y);
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDY Zero Page X
  cpu.mem[0] = LDY_ZPX;
  cpu.mem[1] = 0x20;
  cpu.X = 0x05;
  cpu.mem[0x25] = 0x66;
  ldy_zeropage_x(&cpu);
  TEST_ASSERT_EQUAL(0x66, cpu.Y);
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDY Absolute
  cpu.mem[0] = LDY_ABS;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.mem[0x1234] = 0x77;
  ldy_absolute(&cpu);
  TEST_ASSERT_EQUAL(0x77, cpu.Y);
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDY Absolute X
  cpu.mem[0] = LDY_ABSX;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.X = 0x02;
  cpu.mem[0x1236] = 0x88;
  ldy_absolute_x(&cpu);
  TEST_ASSERT_EQUAL(0x88, cpu.Y);
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDY Zero Flag
  cpu.mem[0] = LDY_IMM;
  cpu.mem[1] = 0x00;
  ldy_immediate(&cpu);
  TEST_ASSERT_EQUAL(0x00, cpu.Y);
  TEST_ASSERT_EQUAL(1, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDY Negative Flag
  cpu.mem[0] = LDY_IMM;
  cpu.mem[1] = 0x80;
  ldy_immediate(&cpu);
  TEST_ASSERT_EQUAL(0x80, cpu.Y);
  TEST_ASSERT_EQUAL(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL(1, get_flag(&cpu, FLAG_NEGATIVE));
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_lda_instructions);
  RUN_TEST(test_ldx_instructions);
  RUN_TEST(test_ldy_instructions);
  return UNITY_END();
}
