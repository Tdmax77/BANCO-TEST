void display_angolo() {
  if (payload.num_sent != valoreangolocorrettoPrev)     // refresh display only if angle changes
  {
    valoreangolocorrettoPrev = payload.num_sent;        // read angle value
    angprint = payload.num_sent;                       //convert from long to float

    if (motore.cw == 1) {
      angstamp = angprint / 100;                         // add the comma
    } else {
      angstamp = ((72000 - angprint) /*- 72000*/) / 100;
    }


    lcd.setCursor(5, 2);
    lcd.print(angstamp);
    /*    Serial.print(" cw =");
        Serial.print(angstamp);
        Serial.print("    ccw =");
        Serial.println(((72000 - angprint)-72000)/100);
    */
  }
}
