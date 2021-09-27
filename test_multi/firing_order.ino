void firing_order() {

  if (motore.cylinder > 10) {
    lcd.clear();
    lcd.setCursor(0, 0);
    for (byte i = 0; (i < 7) && (i < motore.cylinder); i++) {

      lcd.print(motore.e[i]);
      lcd.print(" ");
    }
    lcd.setCursor(0, 1);
    for (byte i = 7; (i < 14) && (i < motore.cylinder); i++) {

      lcd.print(motore.e[i]);
      lcd.print(" ");
    }
    lcd.setCursor(0, 2);
    for (byte i = 14; (i < 20) && (i < motore.cylinder); i++) {

      lcd.print(motore.e[i]);
      lcd.print(" ");
    }
  } else {

    lcd.clear();
    lcd.setCursor(0, 0);
    for (byte i = 0; (i < 7) && (i < motore.cylinder); i++) {

      lcd.print(motore.e[2 * i]);
      lcd.print(" ");
    }
    lcd.setCursor(0, 1);
    for (byte i = 7; (i < 14) && (i < motore.cylinder); i++) {

      lcd.print(motore.e[2 * i]);
      lcd.print(" ");
    }


  }
  delay (8000);
  lcd.clear();
  write_lcdBG_AA;

}
