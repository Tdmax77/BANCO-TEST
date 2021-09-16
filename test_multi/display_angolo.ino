void display_angolo() {
  if (payload.num_sent != valoreangolocorrettoPrev)     // refresh display only if angle changes
  {
    valoreangolocorrettoPrev = payload.num_sent;        // read angle value
    angprint = payload.num_sent;                       //convert from long to float
    angstamp = angprint / 100;                         // add the comma
    // lcd.setCursor(5, 2);
    //lcd.print("      ");
   lcd.setCursor(5, 2);
   lcd.print(angstamp);
    Serial.println(angstamp);
  }
}
