void mostra_q() {


/* binA e binB sono gli intervalli di cambio dell'indice del vettore per visualizzare la label col cilindro
 *  nominalA e nominalB sono i timing 
 */
  Serial.print(F("funzioneA "));      
  auto binA = map(angstamp, motore.fire_spacing / 2.0 - motore.fire_spacing, 720 + motore.fire_spacing / 2.0 + motore.fire_spacing, 1, motore.index + 1 + 2);
  // +1 perchè devo farne uno piu dei cilindri, inoltre ne aggiungo 2 per aver lintevallo negativo prima dello zero
  Serial.println(binA);      
  Serial.print("funzioneB ");       
  auto binB = map(angstamp, motore.delta + motore.fire_spacing / 2.0 - motore.fire_spacing, motore.delta + 720 + motore.fire_spacing / 2.0 + motore.fire_spacing, 1, motore.index + 1 + 2);
  Serial.println(binB);      
  auto nominalB = -motore.fire_spacing + motore.delta + motore.fire_spacing * binB;
  auto nominalA = -motore.fire_spacing + motore.fire_spacing * binA;
  Serial.println(nominalA);

  if (abs(nominalA - angstamp) < range) {                                     // se A è nel range stampa 
    Serial.print("QUESTO LO STAMPO A ");
    Serial.println(motore.e[2 * (binA - 1)]);
    lcd.setCursor(12, 2);
    lcd.print(motore.e[2 * (binA - 1)]);
  } else if ((abs(nominalB - angstamp) < range) && (motore.cylinder > 10)) {  //se B è nel range ed ho un V (cyl > 10) stampa
    Serial.print("QUESTO LO STAMPO B ");
    Serial.println(motore.e[2 * (binB - 1) + 1]);
    lcd.setCursor(12, 2);
    lcd.print(motore.e[2 * (binB - 1) + 1]);
  } else {                                                                    // se non è nella condizione di visualizazione pulisce lo schermo
    lcd.setCursor(12, 2);
    lcd.print("       ");
  }
}
