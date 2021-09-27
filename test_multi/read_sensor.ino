void read_sensor() { // legge il sensore di pressione sul arduino master
  ValoreADC = analogRead(A0);
  PressioneBar = (ValoreADC - 97 ) * 0.0072763;
  PM = max(PressioneBar, PM);     // confronta la pressione istantanea con quella massima ed assegna a PM il valore piu alto
  PT = PM / 2;                    // pressione Target = pressione Massima /2
  if (digitalRead(button_C) == LOW) {          // se premuto azzera il valore di PT (target)
    PT = 0;
    PTprec = 0;
    PM = 0;
    PressioneBar = 0;
    Serial.println("PULSANTE UP");
  }

  if (PressioneBar != PMprec) {
    PMprec = PM;
    lcd.setCursor(3, 1);
    lcd.print("     ");
    lcd.setCursor(3, 1);
    lcd.print(PressioneBar);
    Serial.print("pressioneBar= ");
    Serial.println(PressioneBar);
    

  }
 if (PT > PTprec) {
    PTprec = PT;
    lcd.setCursor(16, 1);
    lcd.print("    ");
    lcd.setCursor(16, 1);
    lcd.print(PT);
    Serial.print("pT= ");
    Serial.println(PT);
  }
}
