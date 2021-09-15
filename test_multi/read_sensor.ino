void read_sensor() { // legge il sensore di pressione sul arduino master
  ValoreADC = analogRead(A0);
  PressioneBar = (ValoreADC - 97 ) * 0.0072763;
  PM = max(PressioneBar, PM);     // confronta la pressione istantanea con quella massima ed assegna a PM il valore piu alto
  PT = PM / 2;                    // pressione Target = pressione Massima /2
}
