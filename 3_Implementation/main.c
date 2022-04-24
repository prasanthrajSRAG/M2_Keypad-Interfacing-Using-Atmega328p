#include <avr/io.h>

/*
 * a b c d e f g
 */
#define SET(P, B) (P|=(1 << B))
#define CLEAR(P, B) (P&=(~(1 << B)))

uint8_t mapping[] = {0b1111110, 0b0110000, 0b1101101, 0b1111001, 0b0110011, 0b1011011, 0b1011111, 0b1110000, 0b1111111, 0b1110011, 0};
const int mapping_size = sizeof(mapping) / sizeof(mapping[0]);

int keypad[4][3] = {
  {1, 2, 3},
  {4, 5, 6},
  {7, 8, 9},
  {0, 0, 0}
};

int main() {
  DDRC = 0xff;
  DDRD = 0xff;
  DDRB = 0x00;
  PORTD = 0xff;
  while (1) {
    for (int i = 0; i < 4; i++) {
      SET(PORTD, i);
      int val = PINB;
      int c1 = (val & 0b100) ? 1 : 0;
      int c2 = (val & 0b010) ? 1 : 0;
      int c3 = (val & 0b001) ? 1 : 0;
      if (c1)
        PORTC = mapping[keypad[i][0]];
      else if (c2)
        PORTC = mapping[keypad[i][1]];
      else if (c3)
        PORTC = mapping[keypad[i][2]];
      else
        PORTC = 0;
      PORTD = 0;
    }
  }
}