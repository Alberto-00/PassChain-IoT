
void cryptoRun(){
  client.setCACert(test_root_ca);
  
  Serial.println("\nStarting connection to server...");
  Serial.println(client.remoteIP().toString());
  
  if (!client.connect(WiFi.gatewayIP(), port)){
    Serial.println("Connection failed!");
  }
  else {
    Serial.println("Connected to server!");
    client.println("CIAO DA ESP :)");

    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("headers received");
        break;
      }
    }
    // if there are incoming bytes available from the server, read them and print them:
    while (client.available()) {
      char c = client.read();
      Serial.write(c);
    }

    client.stop();
  }
}
