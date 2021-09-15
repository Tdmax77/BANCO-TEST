void testo_richiesta_inserimento_Engine() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Select ENGINE: ");
  lcd.setCursor(0, 3);
  lcd.print(" -    ok    +       ");
}


void testo_richiesta_inserimento_offset() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("  Inserire valore   ");
  lcd.setCursor(0, 2);
  lcd.print("   ANGOLO  VOLANO     ");
  lcd.setCursor(0, 3);
  lcd.print(" -    ok    +       ");
}


void testo_richiesta_inserimento_Timing() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Insert Timing:   ");
  lcd.setCursor(0, 3);
  lcd.print(" -    ok    +       ");
}


void display_no_conn() {

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("   NO  CONNECTION    ");
  Serial.println("noconn");
}
