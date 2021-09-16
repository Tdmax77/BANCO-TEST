
void mostra_array(){
for ( byte i = 1; i < motore.cylinder + 1; i++) {

    Serial.print("superiore ");
    Serial.print(motore.h[i - 1]);
    Serial.print("   nominale ");
    Serial.print(motore.n[i - 1]);
    Serial.print("   inferiore ");
    Serial.print(motore.l[i - 1]);
    Serial.println();
  }
}
