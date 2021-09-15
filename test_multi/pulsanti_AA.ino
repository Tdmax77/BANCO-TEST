void pulsanti_AA() {
  if (digitalRead(button_C) == LOW) {          // se premuto azzera il valore di PT (target)
    PT = 0;
    PTprec = 0;
    PM = 0;
    PressioneBar = 0;
    Serial.println("PULSANTE UP");
  }
}
