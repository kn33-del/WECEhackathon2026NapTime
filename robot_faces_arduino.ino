#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte backSlash[8] = {
  B00000, B10000, B01000, B00100, B00010, B00001, B00000, B00000
};
byte forwardSlash[8] = {
  B00000, B00001, B00010, B00100, B01000, B10000, B00000, B00000
};
byte heart[8] = {
  B00000, B01010, B11111, B11111, B01110, B00100, B00000, B00000
};

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, backSlash);
  lcd.createChar(1, forwardSlash);
  lcd.createChar(2, heart);
}

void loop() {
  // --- Frame 1: Standard Happy ---
  // Eye span: 8 chars (cols 4 to 11). Midpoint is between col 7 & 8.
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("(O    O)"); 
  lcd.setCursor(6, 1);
  lcd.print("____");    // 4 chars wide (cols 6,7,8,9) - Perfectly centered
  delay(1500);

  // --- Frame 2: Quick Blink ---
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("(-    -)"); 
  lcd.setCursor(6, 1);
  lcd.print("____");
  delay(200); 

  // --- Frame 3: Cute Smile ---
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("(^    ^)"); 
  lcd.setCursor(6, 1);
  lcd.write(byte(0));   // Custom \ 
  lcd.print("__");      // Center of mouth
  lcd.write(byte(1));   // Custom /
  delay(2000);

  // --- Frame 4: Anime Squint ---
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("(>    <)"); 
  lcd.setCursor(6, 1);
  lcd.write(byte(0)); 
  lcd.print("____");    // Slightly wider smile for the big expression
  lcd.write(byte(1));
  delay(2000);

  // --- Frame 5: Heart Blink ---
  // To keep the heart centered in an 8-char span:
  // ( - <3 - ) is 10 chars. Let's start at col 3.
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("(-  ");
  lcd.write(byte(2)); 
  lcd.print("  -)");
  lcd.setCursor(7, 1);
  lcd.print("ww");      // Centered 2-char mouth
  delay(1500);
}