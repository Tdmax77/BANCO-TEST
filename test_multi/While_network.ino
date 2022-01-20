void While_network() {
  while ( network.available() ) {                             // if network is up  ... I need at least one slave active for to keep active the network, otherwise no network will be available
    if (mostraangolo == 1) {                                  // after a lost connection it need to refresh display also if value is not changed
      lcd.setCursor(8, 1);
      lcd.print(angstamp);
      mostraangolo = 0;                                     // reset value
    }

    byte cnt (0);                                             // reset counter
    RF24NetworkHeader header;                                // declare the address of this node: every packet sent from slaves to header will be readed from this node (00, the master)
    network.read(header, &payload, sizeof(payload));         // read the packet netwotk sent for this node
    size_t node_id = header.from_node;                       // create a variable node_id that stores the source of the packet ( who is sending it to me? COMP1 with 01 , COMP2 with 02 and so on..
    if ((payload.OffsetReq == 5) && (payload.VO = 9999) && (y == 1)) {     // if Offset is request i start the Offset task
      testo_richiesta_inserimento_offset();                                // ask for offset
      while (digitalRead(button_B) == HIGH )                             // insert value and wait for OK button pressed
      {
        //lcd.clear();
        PROCEDURA_OFFSET();
        //read_serialmonitor();// Offset procedure
      }
      payload.OffsetReq = 0;                                                // reset the Offset request
      if (motore.cw == 1) {
        payload.VO = var;
      }
      else {
        payload.VO = 720 - var;
      }



      // assign offset value to payload
      RF24NetworkHeader header5(05);                                        // define encoder network address
      network.write(header5, &payload, sizeof(payload));                    // send payload to encoder
      y = 0;
      delay(100);                                                           // little delay
      tempo = millis();                                                     // set variable for y status
      //     y = 0;                                                                // put y to 0
      lcd.clear();
      write_lcdBG_AA();
    } else {
      write_lcdBG_AA();
    }
  }
}
