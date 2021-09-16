void mostra_q() {
  Serial.println("sono nel mostra_q");  //DEBUG
  float inf = motore.l[h - 1];                  //  impostto dinamicamente il  limite inferiore della finestra di visualizzazione
  float sup = motore.h[h - 1];                  //  impostto dinamicamente il  limite superiore della finestra di visualizzazione
  Serial.print("h= ");      //DEBUG
  Serial.println(h);      //DEBUG
  Serial.print("inf= ");      //DEBUG
  Serial.println(inf);      //DEBUG
  Serial.print("sup= ");      //DEBUG
  Serial.println(sup);      //DEBUG
  Serial.print("angolo ");      //DEBUG
  Serial.println(angstamp);      //DEBUG


  if ((angstamp >= inf  ) && ( angstamp <= sup )) {
    Serial.println("sono nel if");       //DEBUG
    if (motore.cylinder > 10) {             // se il motre è un V
      double mod = fmod(h, 2);              // definisco i cilindri pari e dispari
      if (mod == 1.0) {                     // se sono pari
        Serial.println("sono nel if mod 1");
        cyl = motore.e[h - 1] - 10;
        lcd.setCursor(12, 2);
        lcd.print(" A");
        lcd.setCursor(14, 2);
        lcd.print(cyl);
      } else {                              // se sono dispari
        Serial.println("sono nel if mod 0");
        cyl = motore.e[h - 1] - 20;
        lcd.setCursor(12, 2);
        lcd.print(" B");
        lcd.setCursor(14, 2);
        lcd.print(cyl);
      }
    } else {                                // se il motore ha meno di 10 cilindri ovvero è un linea
      cyl = motore.e[h - 1] - 10;
      lcd.setCursor(12, 2);
      lcd.print(" A");
      lcd.setCursor(14, 2);
      lcd.print(cyl);
    }
  } else {                                  // se non è nella condizione di visualizazione pulisce lo schermo
    lcd.setCursor(12, 2);
    lcd.print("       ");
  };

  
  if (angstamp == inf) {                    // condizione per modificare la finestra passando al cilindro prima
    h--;
  };
  if (angstamp == sup) {                    // condizione per modificare la finestra passando al cilindro dopo 
    h++;
  };
  Serial.println("esco da_q");       //DEBUG
}
