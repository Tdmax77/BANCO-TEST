void PROCEDURA_OFFSET() { // mi restituisce un valore var che ho inserito come offset

  readButtonState();  //Lettura stato buttons con controllo antirimbalzo

  if (buttonUpState == HIGH || buttonDownState == HIGH) {
    if ((repeatEnable == HIGH && ((millis() - timerPauseRepeat) > time_pause)) || repeatEnable == LOW) {
      if ((millis() - timerButtonPushed) > time_add_10) {
        if ((millis() - timerButtonPushed) > time_add_100) {
          if (buttonUpState == HIGH) var = var + 100;
          if (buttonDownState == HIGH) var = var - 100;
        } else {
          byte resto = 0;
          if (buttonUpState == HIGH) resto = 10 - (var % 10);
          if (buttonDownState == HIGH) resto = (var % 10);
          if (resto == 0) {
            if (buttonUpState == HIGH) var = var + 10;
            if (buttonDownState == HIGH) var = var - 10;
          } else {
            if (buttonUpState == HIGH) var = var + resto;
            if (buttonDownState == HIGH) var = var - resto;
          }
        }
      } else {
        if (buttonUpState == HIGH) var++;
        if (buttonDownState == HIGH) var--;
      }
      timerPauseRepeat = millis();
      repeatEnable = HIGH;
      if (var > varMax) var = varMax;
      if (var < varMin) var = varMin;
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Ins. valore indice: ");
      lcd.setCursor(4, 2);
      lcd.print(var);
      lcd.setCursor(10, 2);
      lcd.print("Gradi");
      lcd.setCursor(0,3);
      lcd.print(" -    ok    +       ");
      delay(200);
    }
  } else {
    timerButtonPushed = millis();
    timerPauseRepeat = millis();
    repeatEnable = LOW;
  }
  
}
