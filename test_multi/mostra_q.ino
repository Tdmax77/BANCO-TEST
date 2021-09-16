void mostra_q() {
  //h = motore.e []
  Serial.println("sono nel mostra_q");  //DEBUG
/*
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
  */
  Serial.print(F("funzioneA "));      //DEBUG
  auto binA = map(angstamp, motore.fire_spacing/2.0-120, 720 + motore.fire_spacing/2.0 + 120, 1, motore.index + 1 + 2);
  Serial.println(binA);      //DEBUG
  Serial.print("funzioneB ");      //DEBUG
  auto binB = map(angstamp, 50 + motore.fire_spacing/2.0 - 120, 770 + motore.fire_spacing/2.0 + 120, 1, motore.index + 1 + 2);
  Serial.println(binB);      //DEBUG

  // Questo andra' salvato in array invece che calcolato, se c'e' memoria disponibile
  auto nominalA = -120 + motore.fire_spacing*binA;
  Serial.println(nominalA);
  if (abs(nominalA - angstamp) < range) {
    Serial.print("QUESTO LO STAMPO A ");
    Serial.println(motore.e[2*(binA-1)]);
    
  }
  auto nominalB = -120 + 50 + motore.fire_spacing*binB;
  Serial.println(nominalB);
  if (abs(nominalB - angstamp) < range) {
    Serial.print("QUESTO LO STAMPO B ");
    Serial.println(motore.e[2*(binB-1)+1]);
  }
/* 
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
  if (h < 1) h = motore.cylinder;
  if (h > motore.cylinder) h = 1;
  Serial.println("esco da_q");       //DEBUG
  */
}
