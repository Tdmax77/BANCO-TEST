void write_lcdBG_AA() {  // scrive il "background" che non viene mai aggiornato (non serve e così non flashano le scritte
  lcd.setCursor(0, 0);
  lista();
  lcd.setCursor(12, 0);
  lcd.print("T= ");
  lcd.setCursor(15, 0);
  lcd.print(timing_float);
  lcd.setCursor(0, 1);
  lcd.print("P= ");
  lcd.setCursor(8, 1);
  lcd.print("Pt= ");
  lcd.setCursor(0, 2);
  lcd.print("Ang= ");
  lcd.setCursor(0, 3);
  lcd.print("  -    -   rst    - ");

}
