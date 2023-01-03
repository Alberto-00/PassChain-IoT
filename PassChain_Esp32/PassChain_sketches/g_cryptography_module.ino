
bool encrypt(char *text, char *encrypted){
  while(true){ 
    // Encryption
    generate_iv();
    
    mbedtls_gcm_init(&aes);
    mbedtls_gcm_setkey(&aes, MBEDTLS_CIPHER_ID_AES, (const unsigned char*) key, strlen(key) * 8);
    
    if(mbedtls_gcm_starts(&aes, MBEDTLS_GCM_ENCRYPT, (const unsigned char*) iv, strlen(iv), NULL, NULL) != 0)  
      return false;
      
    if(mbedtls_gcm_update(&aes, strlen(text), (const unsigned char*) text, (unsigned char*) encrypted) != 0)
      return false;
      
    if(mbedtls_gcm_finish(&aes, (unsigned char*) tag, 16) != 0)
      return false;
      
    mbedtls_gcm_free(&aes);

    char decrypted[256] = {0};
    decrypt(encrypted, decrypted, iv);

    if(strcmp(tag, tag2) == 0)
      return true;
  }
}


bool decrypt(char *encrypted, char *decrypted, char *iv){
  mbedtls_gcm_init(&aes);
  mbedtls_gcm_setkey(&aes, MBEDTLS_CIPHER_ID_AES, (const unsigned char*) key, strlen(key) * 8);
  
  if(mbedtls_gcm_starts(&aes, MBEDTLS_GCM_DECRYPT, (const unsigned char*) iv, strlen(iv), NULL, NULL) != 0)
    return false;
    
  if(mbedtls_gcm_update(&aes, strlen(encrypted), (const unsigned char*) encrypted, (unsigned char*) decrypted) != 0)
    return false;
    
  if(mbedtls_gcm_finish(&aes, (unsigned char*) tag2, 16) != 0)
    return false;

  mbedtls_gcm_free(&aes);
  return true;
}


char *generate_iv(){
  char pad_iv[6] = {""};
  
  uint32_t num = esp_random();
  uint32_t num2 = esp_random();
  
  sprintf(iv, "%u", num);
  sprintf(pad_iv, "%u", num2);
    
  for(int i = 0, j = 0; i < 12; i++){
    if(strcmp(&iv[i], "") == 0){
      iv[i] = pad_iv[j];
      j++;
     }
  }
  return iv;
}
