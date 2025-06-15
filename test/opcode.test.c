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

static void test_lda_instructions(void) {
  // Test LDA Immediate
  cpu.mem[0] = LDA_IMM;
  cpu.mem[1] = 0x42;
  lda_immediate(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x42, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Zero Page
  cpu.mem[0] = LDA_ZP;
  cpu.mem[1] = 0x20;
  cpu.mem[0x20] = 0x55;
  lda_zeropage(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x55, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Zero Page X
  cpu.mem[0] = LDA_ZPX;
  cpu.mem[1] = 0x20;
  cpu.X = 0x05;
  cpu.mem[0x25] = 0x66;
  lda_zeropage_x(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x66, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Absolute
  cpu.mem[0] = LDA_ABS;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.mem[0x1234] = 0x77;
  lda_absolute(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x77, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Absolute X
  cpu.mem[0] = LDA_ABSX;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.X = 0x02;
  cpu.mem[0x1236] = 0x88;
  lda_absolute_x(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x88, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Absolute Y
  cpu.mem[0] = LDA_ABSY;
  cpu.mem[1] = 0x34;
  cpu.mem[2] = 0x12;
  cpu.Y = 0x03;
  cpu.mem[0x1237] = 0x99;
  lda_absolute_y(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x99, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Indirect X
  cpu.mem[0] = LDA_INDX;
  cpu.mem[1] = 0x20;
  cpu.X = 0x05;
  cpu.mem[0x25] = 0x34;
  cpu.mem[0x26] = 0x12;
  cpu.mem[0x1234] = 0xAA;
  lda_indirect_x(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0xAA, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Indirect Y
  cpu.mem[0] = LDA_INDY;
  cpu.mem[1] = 0x20;
  cpu.Y = 0x05;
  cpu.mem[0x20] = 0x34;
  cpu.mem[0x21] = 0x12;
  cpu.mem[0x1239] = 0xBB;
  lda_indirect_y(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0xBB, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Zero Flag
  cpu.mem[0] = LDA_IMM;
  cpu.mem[1] = 0x00;
  lda_immediate(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.A);
  TEST_ASSERT_TRUE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_NEGATIVE));

  // Test LDA Negative Flag
  cpu.mem[0] = LDA_IMM;
  cpu.mem[1] = 0x80;
  lda_immediate(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x80, cpu.A);
  TEST_ASSERT_FALSE(get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_TRUE(get_flag(&cpu, FLAG_NEGATIVE));
}

static void test_ldx_instructions(void) {
  TEST_IGNORE();
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

static void test_ldy_instructions(void) {
  TEST_IGNORE();
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

static void test_sta_instructions(void) {
  TEST_IGNORE();
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

static void test_stx_instructions(void) {
  TEST_IGNORE();
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

static void test_sty_instructions(void) {
  TEST_IGNORE();
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

static void test_transfer_instructions(void) {
  TEST_IGNORE();
  // Test TAX - Transfer Accumulator to X
  cpu.A = 0x42;
  cpu.X = 0x00; // Clear X to verify transfer
  tax(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x42, cpu.X);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test TAX with zero value
  cpu.A = 0x00;
  tax(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.X);
  TEST_ASSERT_EQUAL_HEX8(FLAG_ZERO, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test TAX with negative value
  cpu.A = 0x80;
  tax(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x80, cpu.X);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(FLAG_NEGATIVE, get_flag(&cpu, FLAG_NEGATIVE));

  // Test TAY - Transfer Accumulator to Y
  cpu.A = 0x55;
  cpu.Y = 0x00; // Clear Y to verify transfer
  tay(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x55, cpu.Y);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test TAY with zero value
  cpu.A = 0x00;
  tay(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.Y);
  TEST_ASSERT_EQUAL_HEX8(FLAG_ZERO, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test TAY with negative value
  cpu.A = 0xFF;
  tay(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0xFF, cpu.Y);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(FLAG_NEGATIVE, get_flag(&cpu, FLAG_NEGATIVE));

  // Test TXA - Transfer X to Accumulator
  cpu.X = 0x33;
  cpu.A = 0x00; // Clear A to verify transfer
  txa(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x33, cpu.A);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test TXA with zero value
  cpu.X = 0x00;
  txa(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.A);
  TEST_ASSERT_EQUAL_HEX8(FLAG_ZERO, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test TXA with negative value
  cpu.X = 0x90;
  txa(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x90, cpu.A);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(FLAG_NEGATIVE, get_flag(&cpu, FLAG_NEGATIVE));

  // Test TYA - Transfer Y to Accumulator
  cpu.Y = 0x77;
  cpu.A = 0x00; // Clear A to verify transfer
  tya(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x77, cpu.A);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test TYA with zero value
  cpu.Y = 0x00;
  tya(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0x00, cpu.A);
  TEST_ASSERT_EQUAL_HEX8(FLAG_ZERO, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_NEGATIVE));

  // Test TYA with negative value
  cpu.Y = 0xA0;
  tya(&cpu);
  TEST_ASSERT_EQUAL_HEX8(0xA0, cpu.A);
  TEST_ASSERT_EQUAL_HEX8(0, get_flag(&cpu, FLAG_ZERO));
  TEST_ASSERT_EQUAL_HEX8(FLAG_NEGATIVE, get_flag(&cpu, FLAG_NEGATIVE));
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

static void test_and_instructions(void) { TEST_IGNORE(); }

static void test_ora_instructions(void) { TEST_IGNORE(); }

static void test_eor_instructions(void) { TEST_IGNORE(); }

static void test_cmp_instructions(void) { TEST_IGNORE(); }

static void test_adc_instructions(void) { TEST_IGNORE(); }

static void test_sbc_instructions(void) { TEST_IGNORE(); }

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
