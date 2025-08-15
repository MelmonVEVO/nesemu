#include "opcode.h"
#include "unity.h"

CPU cpu;

void setUp(void) {
  cpu.P = 0b00100000;
  cpu.A = 0;
  cpu.X = 0;
  cpu.Y = 0;
  cpu.S = 0xFF;
  cpu.PC = 0;
  for (int i = 0; i < 0x10000; i++) {
    cpu.mem[i] = 0;
  }
}

void tearDown(void) {
  // Clean up if needed
}

static void test_lda_immediate(void) {
  cpu.mem[0] = LDA_IMM;
  cpu.mem[1] = 0x42;
  lda_immediate(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x42, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_lda_zeropage(void) {
  cpu.mem[0] = LDA_ZP;
  cpu.mem[1] = 0x20;
  cpu.mem[0x20] = 0x55;
  lda_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x55, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_lda_zeropage_x(void) {
  cpu.mem[0] = LDA_ZPX;
  cpu.mem[1] = 0x20;
  cpu.X = 0x05;
  cpu.mem[0x25] = 0x66;
  lda_zeropage_x(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x66, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_lda_absolute(void) {
  cpu.mem[0] = LDA_ABS;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.mem[0x1234] = 0x77;
  lda_absolute(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x77, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_lda_absolute_x(void) {
  cpu.mem[0] = LDA_ABSX;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.X = 0x02;
  cpu.mem[0x1236] = 0x08;
  lda_absolute_x(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x08, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_lda_absolute_y(void) {
  cpu.mem[0] = LDA_ABSY;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.Y = 0x03;
  cpu.mem[0x1237] = 0x19;
  lda_absolute_y(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x19, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_lda_indirect_x(void) {
  cpu.mem[0] = LDA_INDX;
  cpu.mem[1] = 0x20;
  cpu.X = 0x05;
  cpu.mem[0x25] = 0x34;
  cpu.mem[0x26] = 0x12;
  cpu.mem[0x1234] = 0x2A;
  lda_indirect_x(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x2A, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_lda_indirect_y(void) {
  cpu.mem[0] = LDA_INDY;
  cpu.mem[1] = 0x20;
  cpu.Y = 0x05;
  cpu.mem[0x20] = 0x34;
  cpu.mem[0x21] = 0x12;
  cpu.mem[0x1239] = 0x3B;
  lda_indirect_y(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x3B, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_lda_zero_flag(void) {
  cpu.mem[0] = LDA_IMM;
  cpu.mem[1] = 0x00;
  lda_immediate(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.A);
  TEST_ASSERT_TRUE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_lda_negative_flag(void) {
  cpu.mem[0] = LDA_IMM;
  cpu.mem[1] = 0x80;
  lda_immediate(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x80, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_TRUE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_ldx_immediate(void) {
  cpu.mem[0] = LDX_IMM;
  cpu.mem[1] = 0x42;
  ldx_immediate(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x42, cpu.X);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_ldx_zeropage(void) {
  cpu.mem[0] = LDX_ZP;
  cpu.mem[1] = 0x20;
  cpu.mem[0x20] = 0x55;
  ldx_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x55, cpu.X);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_ldx_zeropage_y(void) {
  cpu.mem[0] = LDX_ZPY;
  cpu.mem[1] = 0x20;
  cpu.Y = 0x05;
  cpu.mem[0x25] = 0x66;
  ldx_zeropage_y(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x66, cpu.X);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_ldx_absolute(void) {
  cpu.mem[0] = LDX_ABS;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.mem[0x1234] = 0x77;
  ldx_absolute(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x77, cpu.X);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_ldx_absolute_y(void) {
  cpu.mem[0] = LDX_ABSY;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.Y = 0x02;
  cpu.mem[0x1236] = 0x08;
  ldx_absolute_y(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x08, cpu.X);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_ldx_zero_flag(void) {
  cpu.mem[0] = LDX_IMM;
  cpu.mem[1] = 0x00;
  ldx_immediate(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.X);
  TEST_ASSERT_TRUE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_ldx_negative_flag(void) {
  cpu.mem[0] = LDX_IMM;
  cpu.mem[1] = 0x80;
  ldx_immediate(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x80, cpu.X);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_TRUE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_ldy_immediate(void) {
  cpu.mem[0] = LDY_IMM;
  cpu.mem[1] = 0x42;
  ldy_immediate(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x42, cpu.Y);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_ldy_zeropage(void) {
  cpu.mem[0] = LDY_ZP;
  cpu.mem[1] = 0x20;
  cpu.mem[0x20] = 0x55;
  ldy_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x55, cpu.Y);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_ldy_zeropage_x(void) {
  cpu.mem[0] = LDY_ZPX;
  cpu.mem[1] = 0x20;
  cpu.X = 0x05;
  cpu.mem[0x25] = 0x66;
  ldy_zeropage_x(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x66, cpu.Y);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_ldy_absolute(void) {
  cpu.mem[0] = LDY_ABS;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.mem[0x1234] = 0x77;
  ldy_absolute(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x77, cpu.Y);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_ldy_absolute_x(void) {
  cpu.mem[0] = LDY_ABSX;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.X = 0x02;
  cpu.mem[0x1236] = 0x08;
  ldy_absolute_x(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x08, cpu.Y);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_ldy_zero_flag(void) {
  cpu.mem[0] = LDY_IMM;
  cpu.mem[1] = 0x00;
  ldy_immediate(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.Y);
  TEST_ASSERT_TRUE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_ldy_negative_flag(void) {
  cpu.mem[0] = LDY_IMM;
  cpu.mem[1] = 0x80;
  ldy_immediate(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x80, cpu.Y);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_TRUE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_sta_zeropage(void) {
  TEST_IGNORE();
  cpu.A = 0x42;
  cpu.mem[0] = STA_ZP;
  cpu.mem[1] = 0x20;
  sta_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x42, cpu.mem[0x20]);
}

static void test_sta_zeropage_x(void) {
  TEST_IGNORE();
  cpu.A = 0x55;
  cpu.X = 0x05;
  cpu.mem[0] = STA_ZPX;
  cpu.mem[1] = 0x20;
  sta_zeropage_x(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x55, cpu.mem[0x25]);
}

static void test_sta_absolute(void) {
  TEST_IGNORE();
  cpu.A = 0x66;
  cpu.mem[0] = STA_ABS;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  sta_absolute(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x66, cpu.mem[0x1234]);
}

static void test_sta_absolute_x(void) {
  TEST_IGNORE();
  cpu.A = 0x77;
  cpu.X = 0x02;
  cpu.mem[0] = STA_ABSX;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  sta_absolute_x(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x77, cpu.mem[0x1236]);
}

static void test_sta_absolute_y(void) {
  TEST_IGNORE();
  cpu.A = 0x88;
  cpu.Y = 0x03;
  cpu.mem[0] = STA_ABSY;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  sta_absolute_y(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x88, cpu.mem[0x1237]);
}

static void test_sta_indirect_x(void) {
  TEST_IGNORE();
  cpu.A = 0x99;
  cpu.X = 0x05;
  cpu.mem[0] = STA_INDX;
  cpu.mem[1] = 0x20;
  cpu.mem[0x25] = 0x34;
  cpu.mem[0x26] = 0x12;
  sta_indirect_x(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x99, cpu.mem[0x1234]);
}

static void test_sta_indirect_y(void) {
  TEST_IGNORE();
  cpu.A = 0xAA;
  cpu.Y = 0x05;
  cpu.mem[0] = STA_INDY;
  cpu.mem[1] = 0x20;
  cpu.mem[0x20] = 0x34;
  cpu.mem[0x21] = 0x12;
  sta_indirect_y(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0xAA, cpu.mem[0x1239]);
}

static void test_sta_flags_unchanged_zero(void) {
  TEST_IGNORE();
  u8 original_flags = cpu.P;
  cpu.A = 0x00;
  cpu.mem[0] = STA_ZP;
  cpu.mem[1] = 0x30;
  sta_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.mem[0x30]);
  TEST_ASSERT_EQUAL_HEX8(original_flags, cpu.P);
}

static void test_sta_flags_unchanged_negative(void) {
  TEST_IGNORE();
  u8 original_flags = cpu.P;
  cpu.A = 0x80;
  cpu.mem[0] = STA_ZP;
  cpu.mem[1] = 0x31;
  sta_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x80, cpu.mem[0x31]);
  TEST_ASSERT_EQUAL_HEX8(original_flags, cpu.P);
}

static void test_stx_zeropage(void) {
  TEST_IGNORE();
  cpu.X = 0x42;
  cpu.mem[0] = STX_ZP;
  cpu.mem[1] = 0x20;
  stx_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x42, cpu.mem[0x20]);
}

static void test_stx_zeropage_y(void) {
  TEST_IGNORE();
  cpu.X = 0x55;
  cpu.Y = 0x05;
  cpu.mem[0] = STX_ZPY;
  cpu.mem[1] = 0x20;
  stx_zeropage_y(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x55, cpu.mem[0x25]);
}

static void test_stx_absolute(void) {
  TEST_IGNORE();
  cpu.X = 0x66;
  cpu.mem[0] = STX_ABS;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  stx_absolute(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x66, cpu.mem[0x1234]);
}

static void test_stx_flags_unchanged_zero(void) {
  TEST_IGNORE();
  u8 original_flags = cpu.P;
  cpu.X = 0x00; // Zero value
  cpu.mem[0] = STX_ZP;
  cpu.mem[1] = 0x30;
  stx_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.mem[0x30]);
  TEST_ASSERT_EQUAL_HEX8(original_flags, cpu.P);
}

static void test_stx_flags_unchanged_negative(void) {
  TEST_IGNORE();
  u8 original_flags = cpu.P;
  cpu.X = 0x80; // Negative value
  cpu.mem[0] = STX_ZP;
  cpu.mem[1] = 0x31;
  stx_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x80, cpu.mem[0x31]);
  TEST_ASSERT_EQUAL_HEX8(original_flags, cpu.P);
}

static void test_sty_zeropage(void) {
  TEST_IGNORE();
  cpu.Y = 0x42;
  cpu.mem[0] = STY_ZP;
  cpu.mem[1] = 0x20;
  sty_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x42, cpu.mem[0x20]);
}

static void test_sty_zeropage_x(void) {
  TEST_IGNORE();
  cpu.Y = 0x55;
  cpu.X = 0x05;
  cpu.mem[0] = STY_ZPX;
  cpu.mem[1] = 0x20;
  sty_zeropage_x(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x55, cpu.mem[0x25]);
}

static void test_sty_absolute(void) {
  TEST_IGNORE();
  cpu.Y = 0x66;
  cpu.mem[0] = STY_ABS;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  sty_absolute(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x66, cpu.mem[0x1234]);
}

static void test_sty_flags_unchanged_zero(void) {
  TEST_IGNORE();
  u8 original_flags = cpu.P;
  cpu.Y = 0x00; // Zero value
  cpu.mem[0] = STY_ZP;
  cpu.mem[1] = 0x30;
  sty_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.mem[0x30]);
  TEST_ASSERT_EQUAL_HEX8(original_flags, cpu.P);
}

static void test_sty_flags_unchanged_negative(void) {
  TEST_IGNORE();
  u8 original_flags = cpu.P;
  cpu.Y = 0x80; // Negative value
  cpu.mem[0] = STY_ZP;
  cpu.mem[1] = 0x31;
  sty_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x80, cpu.mem[0x31]);
  TEST_ASSERT_EQUAL_HEX8(original_flags, cpu.P);
}

static void test_tax_basic(void) {
  TEST_IGNORE();
  cpu.A = 0x42; cpu.X = 0x00; tax(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x42, cpu.X);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}
static void test_tax_zero_flag(void) {
  TEST_IGNORE();
  cpu.A = 0x00; tax(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.X);
  TEST_ASSERT_TRUE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}
static void test_tax_negative_flag(void) {
  TEST_IGNORE();
  cpu.A = 0x80; tax(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x80, cpu.X);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_TRUE(get_flag(&cpu, FLAG_NEGATIVE));
}
static void test_tay_basic(void) {
  TEST_IGNORE();
  cpu.A = 0x55; cpu.Y = 0x00; tay(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x55, cpu.Y);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}
static void test_tay_zero_flag(void) {
  TEST_IGNORE();
  cpu.A = 0x00; tay(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.Y);
  TEST_ASSERT_TRUE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}
static void test_tay_negative_flag(void) {
  TEST_IGNORE();
  cpu.A = 0xFF; tay(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0xFF, cpu.Y);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_TRUE(get_flag(&cpu, FLAG_NEGATIVE));
}
static void test_txa_basic(void) {
  TEST_IGNORE();
  cpu.X = 0x33; cpu.A = 0x00; txa(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x33, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}
static void test_txa_zero_flag(void) {
  TEST_IGNORE();
  cpu.X = 0x00; txa(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.A);
  TEST_ASSERT_TRUE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}
static void test_txa_negative_flag(void) {
  TEST_IGNORE();
  cpu.X = 0x90; txa(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x90, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_TRUE(get_flag(&cpu, FLAG_NEGATIVE));
}
static void test_tya_basic(void) {
  TEST_IGNORE();
  cpu.Y = 0x77; cpu.A = 0x00; tya(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x77, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}
static void test_tya_zero_flag(void) {
  TEST_IGNORE();
  cpu.Y = 0x00; tya(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.A);
  TEST_ASSERT_TRUE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}
static void test_tya_negative_flag(void) {
  TEST_IGNORE();
  cpu.Y = 0xA0; tya(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0xA0, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_TRUE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_branch_instructions(void) {
  TEST_IGNORE();
  // Test BCC - Branch if Carry Clear (should branch)
  cpu.PC = 0x1000;
  set_flag(&cpu, FLAG_CARRY, 0); // Clear carry flag
  cpu.mem[0x1000] = BCC_REL;
  cpu.mem[0x1001] = 0x10; // Branch forward 16 bytes
  bcc(&cpu);
  cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1012, cpu.PC); // 0x1000 + 2 + 0x10

  // Test BCC - Branch if Carry Clear (should not branch)
  cpu.PC = 0x1000;
  set_flag(&cpu, FLAG_CARRY, 1); // Set carry flag
  cpu.mem[0x1000] = BCC_REL;
  cpu.mem[0x1001] = 0x10;
  bcc(&cpu);
  cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1002, cpu.PC); // PC should advance by 2 only

  // Test BCS - Branch if Carry Set (should branch)
  cpu.PC = 0x1000;
  set_flag(&cpu, FLAG_CARRY, 1); // Set carry flag
  cpu.mem[0x1000] = BCS_REL;
  cpu.mem[0x1001] = 0x08; // Branch forward 8 bytes
  bcs(&cpu);
  cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x100A, cpu.PC); // 0x1000 + 2 + 0x08

  // Test BCS - Branch if Carry Set (should not branch)
  cpu.PC = 0x1000;
  set_flag(&cpu, FLAG_CARRY, 0); // Clear carry flag
  cpu.mem[0x1000] = BCS_REL;
  cpu.mem[0x1001] = 0x08;
  bcs(&cpu);
  cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1002, cpu.PC); // PC should advance by 2 only

  // Test BEQ - Branch if Equal (should branch)
  cpu.PC = 0x1000;
  set_flag(&cpu, FLAG_ZERO, 1); // Set zero flag
  cpu.mem[0x1000] = BEQ_REL;
  cpu.mem[0x1001] = 0x05; // Branch forward 5 bytes
  beq(&cpu);
  cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1007, cpu.PC); // 0x1000 + 2 + 0x05

  // Test BEQ - Branch if Equal (should not branch)
  cpu.PC = 0x1000;
  set_flag(&cpu, FLAG_ZERO, 0); // Clear zero flag
  cpu.mem[0x1000] = BEQ_REL;
  cpu.mem[0x1001] = 0x05;
  beq(&cpu);
  cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1002, cpu.PC); // PC should advance by 2 only

  // Test BNE - Branch if Not Equal (should branch)
  cpu.PC = 0x1000;
  set_flag(&cpu, FLAG_ZERO, 0); // Clear zero flag
  cpu.mem[0x1000] = BNE_REL;
  cpu.mem[0x1001] = 0x0C; // Branch forward 12 bytes
  bne(&cpu);
  cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x100E, cpu.PC); // 0x1000 + 2 + 0x0C

  // Test BNE - Branch if Not Equal (should not branch)
  cpu.PC = 0x1000;
  set_flag(&cpu, FLAG_ZERO, 1); // Set zero flag
  cpu.mem[0x1000] = BNE_REL;
  cpu.mem[0x1001] = 0x0C;
  bne(&cpu);
  cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1002, cpu.PC); // PC should advance by 2 only

  // Test BMI - Branch if Minus (should branch)
  cpu.PC = 0x1000;
  set_flag(&cpu, FLAG_NEGATIVE, 1); // Set negative flag
  cpu.mem[0x1000] = BMI_REL;
  cpu.mem[0x1001] = 0x07; // Branch forward 7 bytes
  bmi(&cpu);
  cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1009, cpu.PC); // 0x1000 + 2 + 0x07

  // Test BMI - Branch if Minus (should not branch)
  cpu.PC = 0x1000;
  set_flag(&cpu, FLAG_NEGATIVE, 0); // Clear negative flag
  cpu.mem[0x1000] = BMI_REL;
  cpu.mem[0x1001] = 0x07;
  bmi(&cpu);
  cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1002, cpu.PC); // PC should advance by 2 only

  // Test BPL - Branch if Positive (should branch)
  cpu.PC = 0x1000;
  set_flag(&cpu, FLAG_NEGATIVE, 0); // Clear negative flag
  cpu.mem[0x1000] = BPL_REL;
  cpu.mem[0x1001] = 0x0A; // Branch forward 10 bytes
  bpl(&cpu);
  cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x100C, cpu.PC); // 0x1000 + 2 + 0x0A

  // Test BPL - Branch if Positive (should not branch)
  cpu.PC = 0x1000;
  set_flag(&cpu, FLAG_NEGATIVE, 1); // Set negative flag
  cpu.mem[0x1000] = BPL_REL;
  cpu.mem[0x1001] = 0x0A;
  bpl(&cpu);
  cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1002, cpu.PC); // PC should advance by 2 only

  // Test BVC - Branch if Overflow Clear (should branch)
  cpu.PC = 0x1000;
  set_flag(&cpu, FLAG_OVERFLOW, 0); // Clear overflow flag
  cpu.mem[0x1000] = BVC_REL;
  cpu.mem[0x1001] = 0x06; // Branch forward 6 bytes
  bvc(&cpu);
  cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1008, cpu.PC); // 0x1000 + 2 + 0x06

  // Test BVC - Branch if Overflow Clear (should not branch)
  cpu.PC = 0x1000;
  set_flag(&cpu, FLAG_OVERFLOW, 1); // Set overflow flag
  cpu.mem[0x1000] = BVC_REL;
  cpu.mem[0x1001] = 0x06;
  bvc(&cpu);
  cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1002, cpu.PC); // PC should advance by 2 only

  // Test BVS - Branch if Overflow Set (should branch)
  cpu.PC = 0x1000;
  set_flag(&cpu, FLAG_OVERFLOW, 1); // Set overflow flag
  cpu.mem[0x1000] = BVS_REL;
  cpu.mem[0x1001] = 0x04; // Branch forward 4 bytes
  bvs(&cpu);
  cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1006, cpu.PC); // 0x1000 + 2 + 0x04

  // Test BVS - Branch if Overflow Set (should not branch)
  cpu.PC = 0x1000;
  set_flag(&cpu, FLAG_OVERFLOW, 0); // Clear overflow flag
  cpu.mem[0x1000] = BVS_REL;
  cpu.mem[0x1001] = 0x04;
  bvs(&cpu);
  cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1002, cpu.PC); // PC should advance by 2 only

  // Test backward branch with negative offset
  cpu.PC = 0x1010;
  set_flag(&cpu, FLAG_ZERO, 1); // Set zero flag for BEQ
  cpu.mem[0x1010] = BEQ_REL;
  cpu.mem[0x1011] = 0xF0; // -16 in two's complement
  beq(&cpu);
  cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1002, cpu.PC); // 0x1010 + 2 + (-16) = 0x1002
}

static void test_stack_instructions(void) {
  TEST_IGNORE();
  // Test PHA - Push Accumulator
  cpu.A = 0x42;
  cpu.S = 0xFF; // Reset stack pointer
  pha(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0xFE, cpu.S);           // Stack pointer decremented
  TEST_ASSERT_EQUAL_HEX8(0x42, cpu.mem[0x01FF]); // Value pushed to stack

  // Test PHA multiple times
  cpu.A = 0x33;
  pha(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0xFD, cpu.S);
  TEST_ASSERT_EQUAL_HEX8(0x33, cpu.mem[0x01FE]);

  // Test PLA - Pull Accumulator
  cpu.A = 0x00; // Clear accumulator
  pla(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x33, cpu.A); // Should get last pushed value
  TEST_ASSERT_EQUAL_HEX8(0xFE, cpu.S); // Stack pointer incremented
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test PLA again
  cpu.A = 0x00;
  pla(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x42, cpu.A); // Should get first pushed value
  TEST_ASSERT_EQUAL_HEX8(0xFF, cpu.S); // Stack pointer back to original

  // Test PLA with zero value
  cpu.A = 0x00;
  cpu.S = 0xFE;
  cpu.mem[0x01FF] = 0x00; // Put zero on stack
  pla(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.A);
  TEST_ASSERT_EQUAL_HEX8(FLAG_ZERO, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test PLA with negative value
  cpu.A = 0x00;
  cpu.S = 0xFE;
  cpu.mem[0x01FF] = 0x80; // Put negative value on stack
  pla(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x80, cpu.A);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(FLAG_NEGATIVE, get_flag(&cpu, FLAG_NEGATIVE));

  // Test PHP - Push Processor Status
  cpu.S = 0xFF;
  cpu.P = 0b11010011; // Set some flags
  php(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0xFE, cpu.S); // Stack pointer decremented
  // PHP should push P with break flag set
  TEST_ASSERT_EQUAL_HEX8(0b11110011,
                         cpu.mem[0x01FF]); // Break flag should be set

  // Test PLP - Pull Processor Status
  cpu.P = 0x00; // Clear all flags
  cpu.S = 0xFE;
  cpu.mem[0x01FF] = 0b10100101; // Some flag pattern
  plp(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0xFF, cpu.S); // Stack pointer incremented
  // PLP should ignore break flag and bit 5
  TEST_ASSERT_EQUAL_HEX8(0b10100101 & ~FLAG_BREAK, cpu.P & ~FLAG_BREAK);
  TEST_ASSERT_EQUAL_HEX8(0b00100000, cpu.P & 0b00100000); // Bit 5 should be set

  // Test stack wraparound behavior
  cpu.S = 0x00; // Stack at bottom
  cpu.A = 0x99;
  pha(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0xFF, cpu.S);           // Should wrap to 0xFF
  TEST_ASSERT_EQUAL_HEX8(0x99, cpu.mem[0x0100]); // Should store at 0x0100

  cpu.A = 0x00;
  cpu.S = 0xFF; // Stack at top
  pla(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.S); // Should wrap to 0x00
  TEST_ASSERT_EQUAL_HEX8(0x99, cpu.A); // Should pull the value we just pushed

  // Test that PHA doesn't affect flags
  u8 original_flags = cpu.P;
  cpu.A = 0x00; // Zero value
  pha(&cpu);
  TEST_ASSERT_EQUAL_HEX8(original_flags, cpu.P); // Flags should be unchanged

  cpu.A = 0x80; // Negative value
  pha(&cpu);
  TEST_ASSERT_EQUAL_HEX8(original_flags, cpu.P); // Flags should be unchanged
}

// --- Modularized Branch Tests ---
static void test_bcc_branches(void) {
  TEST_IGNORE();
  cpu.PC = 0x1000; set_flag(&cpu, FLAG_CARRY, 0);
  cpu.mem[0x1000] = BCC_REL; cpu.mem[0x1001] = 0x10; bcc(&cpu); cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1012, cpu.PC);
}
static void test_bcc_no_branch(void) {
  TEST_IGNORE();
  cpu.PC = 0x1000; set_flag(&cpu, FLAG_CARRY, 1);
  cpu.mem[0x1000] = BCC_REL; cpu.mem[0x1001] = 0x10; bcc(&cpu); cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1002, cpu.PC);
}
static void test_bcs_branches(void) {
  TEST_IGNORE();
  cpu.PC = 0x1000; set_flag(&cpu, FLAG_CARRY, 1);
  cpu.mem[0x1000] = BCS_REL; cpu.mem[0x1001] = 0x08; bcs(&cpu); cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x100A, cpu.PC);
}
static void test_bcs_no_branch(void) {
  TEST_IGNORE();
  cpu.PC = 0x1000; set_flag(&cpu, FLAG_CARRY, 0);
  cpu.mem[0x1000] = BCS_REL; cpu.mem[0x1001] = 0x08; bcs(&cpu); cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1002, cpu.PC);
}
static void test_beq_branches(void) {
  TEST_IGNORE();
  cpu.PC = 0x1000; set_flag(&cpu, FLAG_ZERO, 1);
  cpu.mem[0x1000] = BEQ_REL; cpu.mem[0x1001] = 0x0A; beq(&cpu); cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x100C, cpu.PC);
}
static void test_beq_no_branch(void) {
  TEST_IGNORE();
  cpu.PC = 0x1000; set_flag(&cpu, FLAG_ZERO, 0);
  cpu.mem[0x1000] = BEQ_REL; cpu.mem[0x1001] = 0x0A; beq(&cpu); cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1002, cpu.PC);
}
static void test_bmi_branches(void) {
  TEST_IGNORE();
  cpu.PC = 0x1000; set_flag(&cpu, FLAG_NEGATIVE, 1);
  cpu.mem[0x1000] = BMI_REL; cpu.mem[0x1001] = 0x04; bmi(&cpu); cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1006, cpu.PC);
}
static void test_bmi_no_branch(void) {
  TEST_IGNORE();
  cpu.PC = 0x1000; set_flag(&cpu, FLAG_NEGATIVE, 0);
  cpu.mem[0x1000] = BMI_REL; cpu.mem[0x1001] = 0x04; bmi(&cpu); cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1002, cpu.PC);
}
static void test_bne_branches(void) {
  TEST_IGNORE();
  cpu.PC = 0x1000; set_flag(&cpu, FLAG_ZERO, 0);
  cpu.mem[0x1000] = BNE_REL; cpu.mem[0x1001] = 0x0C; bne(&cpu); cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x100E, cpu.PC);
}
static void test_bne_no_branch(void) {
  TEST_IGNORE();
  cpu.PC = 0x1000; set_flag(&cpu, FLAG_ZERO, 1);
  cpu.mem[0x1000] = BNE_REL; cpu.mem[0x1001] = 0x0C; bne(&cpu); cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1002, cpu.PC);
}
static void test_bpl_branches(void) {
  TEST_IGNORE();
  cpu.PC = 0x1000; set_flag(&cpu, FLAG_NEGATIVE, 0);
  cpu.mem[0x1000] = BPL_REL; cpu.mem[0x1001] = 0x0A; bpl(&cpu); cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x100C, cpu.PC);
}
static void test_bpl_no_branch(void) {
  TEST_IGNORE();
  cpu.PC = 0x1000; set_flag(&cpu, FLAG_NEGATIVE, 1);
  cpu.mem[0x1000] = BPL_REL; cpu.mem[0x1001] = 0x0A; bpl(&cpu); cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1002, cpu.PC);
}
static void test_bvc_branches(void) {
  TEST_IGNORE();
  cpu.PC = 0x1000; set_flag(&cpu, FLAG_OVERFLOW, 0);
  cpu.mem[0x1000] = BVC_REL; cpu.mem[0x1001] = 0x06; bvc(&cpu); cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1008, cpu.PC);
}
static void test_bvc_no_branch(void) {
  TEST_IGNORE();
  cpu.PC = 0x1000; set_flag(&cpu, FLAG_OVERFLOW, 1);
  cpu.mem[0x1000] = BVC_REL; cpu.mem[0x1001] = 0x06; bvc(&cpu); cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1002, cpu.PC);
}
static void test_bvs_branches(void) {
  TEST_IGNORE();
  cpu.PC = 0x1000; set_flag(&cpu, FLAG_OVERFLOW, 1);
  cpu.mem[0x1000] = BVS_REL; cpu.mem[0x1001] = 0x04; bvs(&cpu); cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1006, cpu.PC);
}
static void test_bvs_no_branch(void) {
  TEST_IGNORE();
  cpu.PC = 0x1000; set_flag(&cpu, FLAG_OVERFLOW, 0);
  cpu.mem[0x1000] = BVS_REL; cpu.mem[0x1001] = 0x04; bvs(&cpu); cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1002, cpu.PC);
}
static void test_beq_backward_branch(void) {
  TEST_IGNORE();
  cpu.PC = 0x1010; set_flag(&cpu, FLAG_ZERO, 1);
  cpu.mem[0x1010] = BEQ_REL; cpu.mem[0x1011] = 0xF0; beq(&cpu); cpu.PC += 2;
  TEST_ASSERT_EQUAL_HEX16(0x1002, cpu.PC);
}

// --- Modularized Stack Tests ---
static void test_pha_push_basic(void) {
  TEST_IGNORE();
  cpu.A = 0x42; cpu.S = 0xFF; pha(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0xFE, cpu.S);
  TEST_ASSERT_EQUAL_HEX8(0x42, cpu.mem[0x01FF]);
}
static void test_pha_multiple(void) {
  TEST_IGNORE();
  cpu.A = 0x42; cpu.S = 0xFF; pha(&cpu);
  cpu.A = 0x33; pha(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0xFD, cpu.S);
  TEST_ASSERT_EQUAL_HEX8(0x33, cpu.mem[0x01FE]);
}
static void test_pla_basic(void) {
  TEST_IGNORE();
  cpu.A = 0x42; cpu.S = 0xFF; pha(&cpu);
  cpu.A = 0x33; pha(&cpu);
  cpu.A = 0x00; pla(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x33, cpu.A);
  TEST_ASSERT_EQUAL_HEX8(0xFE, cpu.S);
}
static void test_pla_zero_sets_flag(void) {
  TEST_IGNORE();
  cpu.A = 0x00; cpu.S = 0xFE; cpu.mem[0x01FF] = 0x00; pla(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.A);
  TEST_ASSERT_TRUE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));
}
static void test_pla_negative_sets_flag(void) {
  TEST_IGNORE();
  cpu.A = 0x00; cpu.S = 0xFE; cpu.mem[0x01FF] = 0x80; pla(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x80, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_TRUE(get_flag(&cpu, FLAG_NEGATIVE));
}
static void test_php_push_sets_break_bit(void) {
  TEST_IGNORE();
  cpu.S = 0xFF; cpu.P = 0b11010011; php(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0xFE, cpu.S);
  TEST_ASSERT_EQUAL_HEX8(0b11110011, cpu.mem[0x01FF]);
}
static void test_plp_pull_status_masks_break_and_sets_bit5(void) {
  TEST_IGNORE();
  cpu.P = 0x00; cpu.S = 0xFE; cpu.mem[0x01FF] = 0b10100101; plp(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0xFF, cpu.S);
  TEST_ASSERT_EQUAL_HEX8(0b10100101 & ~FLAG_BREAK, cpu.P & ~FLAG_BREAK);
  TEST_ASSERT_EQUAL_HEX8(0b00100000, cpu.P & 0b00100000);
}
static void test_stack_wraparound_push_pull(void) {
  TEST_IGNORE();
  cpu.S = 0x00; cpu.A = 0x99; pha(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0xFF, cpu.S);
  TEST_ASSERT_EQUAL_HEX8(0x99, cpu.mem[0x0100]);
  cpu.A = 0x00; cpu.S = 0xFF; pla(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.S);
  TEST_ASSERT_EQUAL_HEX8(0x99, cpu.A);
}
static void test_pha_does_not_affect_flags(void) {
  TEST_IGNORE();
  u8 original_flags = cpu.P; cpu.A = 0x00; pha(&cpu);
  TEST_ASSERT_EQUAL_HEX8(original_flags, cpu.P);
  cpu.A = 0x80; pha(&cpu);
  TEST_ASSERT_EQUAL_HEX8(original_flags, cpu.P);
}

static void test_and_instructions(void) { TEST_IGNORE(); }

static void test_ora_instructions(void) { TEST_IGNORE(); }

static void test_eor_instructions(void) { TEST_IGNORE(); }

static void test_cmp_instructions(void) { TEST_IGNORE(); }

static void test_adc_instructions(void) { TEST_IGNORE(); }

static void test_sbc_instructions(void) { TEST_IGNORE(); }

int main(void) {
  UNITY_BEGIN();
  // -- LDA --
  RUN_TEST(test_lda_immediate);
  RUN_TEST(test_lda_zeropage);
  RUN_TEST(test_lda_zeropage_x);
  RUN_TEST(test_lda_absolute);
  RUN_TEST(test_lda_absolute_x);
  RUN_TEST(test_lda_absolute_y);
  RUN_TEST(test_lda_indirect_x);
  RUN_TEST(test_lda_indirect_y);
  RUN_TEST(test_lda_zero_flag);
  RUN_TEST(test_lda_negative_flag);

  // -- LDX --
  RUN_TEST(test_ldx_immediate);
  RUN_TEST(test_ldx_zeropage);
  RUN_TEST(test_ldx_zeropage_y);
  RUN_TEST(test_ldx_absolute);
  RUN_TEST(test_ldx_absolute_y);
  RUN_TEST(test_ldx_zero_flag);
  RUN_TEST(test_ldx_negative_flag);

  // -- LDY --
  RUN_TEST(test_ldy_immediate);
  RUN_TEST(test_ldy_zeropage);
  RUN_TEST(test_ldy_zeropage_x);
  RUN_TEST(test_ldy_absolute);
  RUN_TEST(test_ldy_absolute_x);
  RUN_TEST(test_ldy_zero_flag);
  RUN_TEST(test_ldy_negative_flag);

  // -- STA/STX/STY --
  RUN_TEST(test_sta_zeropage);
  RUN_TEST(test_sta_zeropage_x);
  RUN_TEST(test_sta_absolute);
  RUN_TEST(test_sta_absolute_x);
  RUN_TEST(test_sta_absolute_y);
  RUN_TEST(test_sta_indirect_x);
  RUN_TEST(test_sta_indirect_y);
  RUN_TEST(test_sta_flags_unchanged_zero);
  RUN_TEST(test_sta_flags_unchanged_negative);

  RUN_TEST(test_stx_zeropage);
  RUN_TEST(test_stx_zeropage_y);
  RUN_TEST(test_stx_absolute);
  RUN_TEST(test_stx_flags_unchanged_zero);
  RUN_TEST(test_stx_flags_unchanged_negative);

  RUN_TEST(test_sty_zeropage);
  RUN_TEST(test_sty_zeropage_x);
  RUN_TEST(test_sty_absolute);
  RUN_TEST(test_sty_flags_unchanged_zero);
  RUN_TEST(test_sty_flags_unchanged_negative);

  // -- Transfers --
  RUN_TEST(test_tax_basic);
  RUN_TEST(test_tax_zero_flag);
  RUN_TEST(test_tax_negative_flag);
  RUN_TEST(test_tay_basic);
  RUN_TEST(test_tay_zero_flag);
  RUN_TEST(test_tay_negative_flag);
  RUN_TEST(test_txa_basic);
  RUN_TEST(test_txa_zero_flag);
  RUN_TEST(test_txa_negative_flag);
  RUN_TEST(test_tya_basic);
  RUN_TEST(test_tya_zero_flag);
  RUN_TEST(test_tya_negative_flag);

  // -- Branches --
  RUN_TEST(test_bcc_branches);
  RUN_TEST(test_bcc_no_branch);
  RUN_TEST(test_bcs_branches);
  RUN_TEST(test_bcs_no_branch);
  RUN_TEST(test_beq_branches);
  RUN_TEST(test_beq_no_branch);
  RUN_TEST(test_bmi_branches);
  RUN_TEST(test_bmi_no_branch);
  RUN_TEST(test_bne_branches);
  RUN_TEST(test_bne_no_branch);
  RUN_TEST(test_bpl_branches);
  RUN_TEST(test_bpl_no_branch);
  RUN_TEST(test_bvc_branches);
  RUN_TEST(test_bvc_no_branch);
  RUN_TEST(test_bvs_branches);
  RUN_TEST(test_bvs_no_branch);
  RUN_TEST(test_beq_backward_branch);

  // -- Stack --
  RUN_TEST(test_pha_push_basic);
  RUN_TEST(test_pha_multiple);
  RUN_TEST(test_pla_basic);
  RUN_TEST(test_pla_zero_sets_flag);
  RUN_TEST(test_pla_negative_sets_flag);
  RUN_TEST(test_php_push_sets_break_bit);
  RUN_TEST(test_plp_pull_status_masks_break_and_sets_bit5);
  RUN_TEST(test_stack_wraparound_push_pull);
  RUN_TEST(test_pha_does_not_affect_flags);
  RUN_TEST(test_and_instructions);
  RUN_TEST(test_ora_instructions);
  RUN_TEST(test_eor_instructions);
  RUN_TEST(test_cmp_instructions);
  RUN_TEST(test_adc_instructions);
  RUN_TEST(test_sbc_instructions);
  return UNITY_END();
}
