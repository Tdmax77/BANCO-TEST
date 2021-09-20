void calcolo_array() {
/*
  if (motore.cylinder > 10) {
    for ( byte i = 1; i < motore.cylinder + 1; i++) {                    // per tutti i cilindri verifico se sono pari o dispari
      double mod = fmod(i, 2);
      //  Serial.print("mod = ");
      //  Serial.print(mod);

      if (mod == 1.0)  {                                          // 1 3 5  sui cilindri dispari aggiungo il delta tra le bancate (50°)
        scoppio = ((i - 1) / 2) * motore.fire_spacing  /*- timing_float*//*;
        Serial.print(" cilindro = A");
        cyl = motore.e[i - 1] - 10;                              // devo modificare a senconda dell'engine mettendo il array corretto
        Serial.print(cyl);

      }
      else {                                                      // 2 4 6  cilindri pari
        scoppio = (i / 2 * motore.fire_spacing ) - motore.fire_spacing + 50/*- timing_float*//*;
        Serial.print(" cilindro = B");
        cyl = motore.e[i - 1] - 20;                       // devo modificare a senconda dell'engine mettendo il array corretto
        Serial.print(cyl);

      }
      Serial.print(" scoppio= ");
      Serial.println(scoppio);
      motore.n[i - 1] = scoppio;
      motore.h[i - 1] = scoppio + range;
      motore.l[i - 1] = scoppio - range;
    }
  }
  else  // se motore linea quindi cilindri minori di 10
  {
    for ( byte i = 1; i < motore.cylinder + 1; i++) {
      // scoppio = ((i - 1) / 2) * motore.fire_spacing  /*- timing_float*//*;
      scoppio = (i - 1) * motore.fire_spacing  /*- timing_float*//*;
      Serial.print(" cilindro = A");
      cyl = motore.e[i - 1] - 10;                              // devo modificare a senconda dell'engine mettendo il array corretto
      Serial.print(cyl);
      Serial.print(" scoppio= ");
      Serial.println(scoppio);
      motore.n[i - 1] = scoppio;
      motore.h[i - 1] = scoppio + range;
      motore.l[i - 1] = scoppio - range;
    }
  }

  for ( byte i = 1; i < motore.cylinder + 1; i++) {
    
/*    Serial.print("superiore ");
    Serial.print(motore.h[i - 1]);
    Serial.print("   nominale ");
    Serial.print(motore.n[i - 1]);
    Serial.print("   inferiore ");
    Serial.print(motore.l[i - 1]);
 Serial.println();
 *//*
  }
  Serial.println("scritti tutti");
  */
}
