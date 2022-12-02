
int EthernetSend(WOLFSSL* ssl, char* msg, int sz, void* ctx) {
  int sent = 0;
  sent = client.write((byte*)msg, sz);
  return sent;
}

int EthernetReceive(WOLFSSL* ssl, char* reply, int sz, void* ctx) {
  int ret = 0;

  while (client.available() > 0 && ret < sz) {
    reply[ret++] = client.read();
  }

  return ret;
}

void cryptoRun() {
  while(true){
  int err = 0;
  int input = 0;
  char errBuf[80];
  char reply[80];
  int replySz = 0;
  const char* cipherName;

  /* Listen for incoming client requests. */
  while(!client){
    client = server.available();
    /*if (!client) {
      Serial.println("NON FUNZIONA !! !!! !!! !!! !!!");
      break;
    }*/
  }
  

  if (client.connected()) {

    Serial.println("Client connected");

    ssl = wolfSSL_new(ctx);
    if (ssl == NULL) {
      Serial.println("Unable to allocate SSL object");
      return;
    }
    Serial.println("Sono qui1");

    err = wolfSSL_accept(ssl);
    if (err != WOLFSSL_SUCCESS) {
      Serial.println("Sono qui3");
      err = wolfSSL_get_error(ssl, 0);
      wolfSSL_ERR_error_string(err, errBuf);
      Serial.print("TLS Accept Error: ");
      Serial.println(errBuf);
    }
    Serial.println("Sono qui2");

    Serial.print("SSL version is ");
    Serial.println(wolfSSL_get_version(ssl));
    
    cipherName = wolfSSL_get_cipher(ssl);
    Serial.print("SSL cipher suite is ");
    Serial.println(cipherName);

    Serial.print("Server Read: ");
    /* wait for data */
    while (!client.available()) {}
    /* read data */
    while (wolfSSL_pending(ssl)) {
      input = wolfSSL_read(ssl, reply, sizeof(reply) - 1);
      if (input < 0) {
        err = wolfSSL_get_error(ssl, 0);
        wolfSSL_ERR_error_string(err, errBuf);
        Serial.print("TLS Read Error: ");
        Serial.println(errBuf);
        break;
      } else if (input > 0) {
        replySz = input;
        reply[input] = '\0';
        Serial.print(reply);
      } else {
        Serial.println();
      }
    }

    /* echo data */
    if ((wolfSSL_write(ssl, reply, replySz)) != replySz) {
      err = wolfSSL_get_error(ssl, 0);
      wolfSSL_ERR_error_string(err, errBuf);
      Serial.print("TLS Write Error: ");
      Serial.println(errBuf);
    }
    
    wolfSSL_shutdown(ssl);
    wolfSSL_free(ssl);
  }

  client.stop();
  Serial.println("Connection complete");
  }
}
