void write_lcdBG_AA() {  // scrive il "background" che non viene mai aggiornato (non serve e così non flashano le scritte
  lcd.setCursor(0, 0);
  lista();
  lcd.setCursor(12, 0);
  lcd.print(F("T= "));
  lcd.setCursor(15, 0);
  lcd.print(timing_float);
  lcd.setCursor(0, 1);
  lcd.print(F("P= "));
  lcd.setCursor(12, 1);
  lcd.print(F("Pt= "));
  lcd.setCursor(0, 2);
  lcd.print(F("Ang= "));
  lcd.setCursor(0, 3);
  lcd.print(F("f.o.   -   rst    - "));

}
