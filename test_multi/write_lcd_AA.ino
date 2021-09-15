void write_lcd_AA() {     // scrive i dati sul display solo se cambiano di valore

  if (PressioneBar != PMprec) {
    PMprec = PM;
    lcd.setCursor(3, 1);
    lcd.print("     ");
    lcd.setCursor(3, 1);
    lcd.print(PressioneBar);

  }
  if (PT >= PTprec) {
    PTprec = PT;
    lcd.setCursor(12, 1);
    lcd.print("       ");
    lcd.setCursor(12, 1);
    lcd.print(PT);
  }
}
