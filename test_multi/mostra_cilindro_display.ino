void mostra_cilindro_display() {

  if (motore.cylinder > 10) {
    for ( byte i = 1; i < motore.cylinder + 1; i++) {                    // per tutti i cilindri verifico se sono pari o dispari
      double mod = fmod(i, 2);
      Serial.print(F("mod = "));
      Serial.print(mod);

      if (mod == 1.0)  {                                          // 1 3 5  sui cilindri dispari aggiungo il delta tra le bancate (50°)
        scoppio = ((i - 1) / 2) * motore.fire_spacing  /*- timing_float*/;
        Serial.print(" cilindro = A");
        cyl = motore.e[i - 1] - 10;                              // devo modificare a senconda dell'engine mettendo il array corretto
        Serial.print(cyl);
        lcd.setCursor(9, 2);
        lcd.print(" A");
        lcd.setCursor(12, 2);
        lcd.print(cyl);
        q= (2*angstamp/motore.fire_spacing)+1;
        Serial.print(F("q ="));
        Serial.println(q);
        
      }
      else {                                                      // 2 4 6  cilindri pari
        scoppio = (i / 2 * motore.fire_spacing ) - motore.fire_spacing + (motore.delta/100)/*- timing_float*/;
        Serial.print(" cilindro = B");
        cyl = motore.e[i - 1] - 20;                       // devo modificare a senconda dell'engine mettendo il array corretto
        Serial.print(cyl);
        lcd.setCursor(9, 2);
        lcd.print(F(" B"));
        lcd.setCursor(12, 2);
        lcd.print(cyl);
      }
      Serial.print(F(" scoppio= "));
      Serial.println(scoppio);
    }
  }
  else  // se motore linea quindi cilindri minori di 10
  {
    for ( byte i = 1; i < motore.cylinder + 1; i++) {
      scoppio = (i - 1) * motore.fire_spacing  /*- timing_float*/;
      Serial.print(F(" cilindro = A"));
      cyl = motore.e[i - 1] - 10;                              // devo modificare a senconda dell'engine mettendo il array corretto
      Serial.print(cyl);
      Serial.print(F(" scoppio= "));
      Serial.println(scoppio);
    }
  }

  Serial.println(F("scritti tutti"));
}
