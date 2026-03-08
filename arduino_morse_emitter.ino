/*
  Blink Morse

  Converts a text string into a textual Morse code representation
  and prints it to the Serial Monitor.

  Notes:
  - Each Morse symbol is encoded in 4-bit groups.
  - 0b1000 represents "dit".
  - 0b1110 represents "dah".
  - 0b0000 represents a space between words.
*/

/*
  Morse code lookup entry.

  Fields:
  - capital: ASCII code for the uppercase character.
  - regular: ASCII code for the lowercase character.
  - parts: number of used 4-bit groups in the data field.
  - data: Morse code binary representation stored in up to 16 bits.
*/
struct MorseCode {
  int capital;    // Capital character ASCII decimal symbol.
  int regular;    // Regular character ASCII decimal symbol.
  int parts;      // The amount of 4 bit parts each morse character has (for example 0b10001110 has two 4 bit parts).
  uint16_t data;  // Mores code character binary representation / 16 bits (four 4 bit parts).
};

/*
  Morse code dictionary.

  The trailing comment on each line contains:
  - the associated character,
  - the position in the table.
*/
MorseCode data[] = {
  {65, 97, 2, 0b10001110},          // A       0
  {66, 98, 4, 0b1110100010001000},  // B       1
  {69, 101, 1, 0b1000},             // E       4
  {70, 102, 4, 0b1000100011101000}, // F       5
  {71, 103, 3, 0b111011101000},     // G       6
  {67, 99, 4, 0b1110100011101000},  // C       2
  {68, 100, 3, 0b111010001000},     // D       3
  {72, 104, 4, 0b1000100010001000}, // H       7
  {73, 105, 2, 0b10001000},         // I       8
  {74, 106, 4, 0b1000111011101110}, // J       9
  {75, 107, 3, 0b111010001110},     // K       10
  {76, 108, 4, 0b1000111010001000}, // L       11
  {77, 109, 2, 0b11101110},         // M       12
  {78, 110, 2, 0b10001110},         // N       13
  {79, 111, 3, 0b111011101110},     // O       14
  {80, 112, 4, 0b1000111011101000}, // P       15
  {81, 113, 4, 0b1110111010001110}, // Q       16
  {82, 114, 3, 0b100011101000},     // R       17
  {83, 115, 3, 0b100010001000},     // S       18
  {84, 116, 1, 0b1110},             // T       19
  {85, 117, 3, 0b100010001110},     // U       20
  {86, 118, 4, 0b1000100010001110}, // V       21
  {87, 119, 3, 0b100011101110},     // W       22
  {88, 120, 4, 0b1110100010001110}, // X       23
  {89, 121, 4, 0b1110100011101110}, // Y       24
  {90, 122, 4, 0b1110111010001000}, // Z       25
  {32, 32, 4, 0b0000}               // SPACE   26
};

/*
  Returns a copy of the MorseCode record matching the provided ASCII code.

  The function searches both uppercase and lowercase ASCII values.
*/
MorseCode getCopyByIndex(int searchIndex) {
  const int dataSize = sizeof(data) / sizeof(data[0]);

  for (int i = 0; i < dataSize; i++) {
    if (searchIndex == data[i].regular || searchIndex == data[i].capital) {
      MorseCode recordCopy = data[i];
      return recordCopy;
    }
  }
}

// The setup function runs once when you press reset or power the board.
void setup() {
  const int dit_rate = 50;
  const char msg_display[] = "Hello world";
  int current_char = 0;

  delay(1000); // Initial startup delay.

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);

  // Iterate through the source text one character at a time.
  while (msg_display[current_char] != '\0') {
    MorseCode mrsChar = getCopyByIndex(msg_display[current_char]);

    // Process Morse code groups from the most significant used nibble to the least significant one.
    for (int i = mrsChar.parts - 1; i >= 0; i--) {
      if (mrsChar.data == 0b0000) { // Emit space between words.
        Serial.print("______");
        break; // End processing for the current space character.
      }

      // Extract the current 4-bit symbol.
      byte symb = (mrsChar.data >> (i * 4)) & 0x0F;

      // Translate the 4-bit symbol into its textual Morse form.
      switch (symb) {
        case 0b1000:
          Serial.print("dit");
          break; // End current symbol handling.
        case 0b1110:
          Serial.print("dah");
          break; // End current symbol handling.
        default:
          break; // Ignore unsupported symbols.
      }

      // Read the next character to decide whether to print symbol or character spacing.
      MorseCode nextChar = getCopyByIndex(msg_display[current_char + 1]); // Get next character.

      if (i == 0 && nextChar.data != 0b0000) { // If it is the last binary part of the current character and next character is not space, emit space between characters.
        Serial.print("___");
      } else { // Emit space between symbols.
        Serial.print("_");
      }
    }

    current_char++;
  }
}

// The loop function runs over and over again forever.
void loop() {
  // Loop code here.
}
