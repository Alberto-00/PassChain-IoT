
void fingerprint_setup(){
  while (!Serial);
  delay(100);
  
  finger.begin(57600);
  delay(5);
 
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(5, 47);
    tft.print("Fingerprint don't");
    tft.setCursor(5, 80);
    tft.print("detect.");
    tft.setCursor(5, 122);
    tft.print("Turn off the power."); 
    while (1) { delay(1); }
  }
}


/* Match Phase - start*/
uint8_t fingerprint_match(){
  finger.getTemplateCount();

  if (finger.templateCount == 0)
    return 0;

  return getFingerprintID();
}


uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();

  switch (p) {
    case FINGERPRINT_OK:
      break;
      
    case FINGERPRINT_NOFINGER:
      return 0;
      
    case FINGERPRINT_PACKETRECIEVEERR:
      return 0;
      
    case FINGERPRINT_IMAGEFAIL:
      return 0;
      
    default:
      return 0;
  }

  // OK success!
  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      break;
      
    case FINGERPRINT_IMAGEMESS:
      return 0;
      
    case FINGERPRINT_PACKETRECIEVEERR:
      return 0;
      
    case FINGERPRINT_FEATUREFAIL:
      return 0;
      
    case FINGERPRINT_INVALIDIMAGE:
      return 0;
      
    default:
      return 0;
  }

  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {} 
  
  else if (p == FINGERPRINT_PACKETRECIEVEERR) 
    return 0;
    
  else if (p == FINGERPRINT_NOTFOUND)
    return 0;
    
  else
    return 0;

  return finger.fingerID;
}
/* Match Phase - end*/


/* Enroll Phase - start */
bool fingerprint_enroll(uint8_t id){
  for(int i = 0; i < 3; i++){
    tft.fillRect(0,25,240,110,TFT_BLACK);
    tft.setCursor(5, 47);
    tft.print("Ready to enroll!");
    tft.setCursor(5, 87);
    tft.print("Steps ("); 
    tft.print(steps_enroll); 
    tft.print("/6).");
    
    delay(400);
    tft.print("."); delay(400);
    tft.print("."); delay(400);
  }

  if (id == 0)  /* ID #0 not allowed, try again! */ 
    return false;

  while (!getFingerprintEnroll(id));
  return true;
}


uint8_t getFingerprintEnroll(uint8_t id){
  int p = -1;
  int count = 0;

  tft.fillRect(0,25,240,110,TFT_BLACK);
  tft.setCursor(5, 47);
  tft.print("Place finger.");
  
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    
    switch (p) {
      case FINGERPRINT_OK:
        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(5, 47);
        tft.print("Not leave");
        break;
        
      case FINGERPRINT_NOFINGER:
        if(count < 4){
          tft.print(".");
          count++;
        }
        else{
          count = 0;
          tft.fillRect(0,25,240,110,TFT_BLACK);
          tft.setCursor(5, 47);
          tft.print("Place finger.");
        }
        break;
      
      case FINGERPRINT_PACKETRECIEVEERR:
        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(5, 47);
        tft.print("Communication error");
        delay(2000);
        break;
        
      case FINGERPRINT_IMAGEFAIL:
        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(5, 47);
        tft.print("Imaging error");
        delay(2000);
        break;
        
      default:
        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(5, 47);
        tft.print("Unknown error");
        delay(2000);
        break;
    }
  }

  // OK success!
  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      tft.fillRect(0,25,240,110,TFT_BLACK);
      tft.setCursor(5, 47);
      tft.print("Not leave");
      break;
      
    case FINGERPRINT_IMAGEMESS:
      tft.fillRect(0,25,240,110,TFT_BLACK);
      tft.setCursor(5, 47);
      tft.print("Image too messy");
      delay(2000);
      return p;
      
    case FINGERPRINT_PACKETRECIEVEERR:
      tft.fillRect(0,25,240,110,TFT_BLACK);
      tft.setCursor(5, 47);
      tft.print("Communication error");
      delay(2000);
      return p;
      
    case FINGERPRINT_FEATUREFAIL:
      tft.fillRect(0,25,240,110,TFT_BLACK);
      tft.setCursor(5, 47);
      tft.print("Finger not");
      tft.setCursor(5, 74);
      tft.println("found");
      delay(2000);
      return p;
      
    case FINGERPRINT_INVALIDIMAGE:
      tft.fillRect(0,25,240,110,TFT_BLACK);
      tft.setCursor(5, 47);
      tft.print("Invalid image");
      delay(2000);
      return p;
      
    default:
      tft.fillRect(0,25,240,110,TFT_BLACK);
      tft.setCursor(5, 47);
      tft.print("Unknown error");
      delay(2000);
      return p;
  }

  tft.fillRect(0,25,240,110,TFT_BLACK);
  tft.setCursor(5, 47);
  tft.print("Remove finger");
  delay(2500);
  
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }

  p = -1;
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    
    switch (p) {
      case FINGERPRINT_OK:
        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(5, 47);
        tft.print("Not leave");
        break;
        
      case FINGERPRINT_NOFINGER:
        if(count < 4){
          tft.print(".");
          count++;
        }
        else{
          count = 0;
          tft.fillRect(0,25,240,110,TFT_BLACK);
          tft.setCursor(5, 47);
          tft.print("Place same finger");
          tft.setCursor(5, 74);
          tft.print("again.");
        }
        break;
      
      case FINGERPRINT_PACKETRECIEVEERR:
        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(5, 47);
        tft.print("Communication error");
        fingerprint_delete(id);
        delay(2000);
        break;
        
      case FINGERPRINT_IMAGEFAIL:
        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(5, 47);
        tft.print("Imaging error");
        delay(2000);
        break;
        
      default:
        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(5, 47);
        tft.print("Unknown error");
        delay(2000);
        break;
    }
  }

  // OK success!
  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      tft.fillRect(0,25,240,110,TFT_BLACK);
      tft.setCursor(5, 47);
      tft.print("Not leave");
      break;
      
    case FINGERPRINT_IMAGEMESS:
      tft.fillRect(0,25,240,110,TFT_BLACK);
      tft.setCursor(5, 47);
      tft.print("Image too messy");
      delay(2000);
      return p;
      
    case FINGERPRINT_PACKETRECIEVEERR:
      tft.fillRect(0,25,240,110,TFT_BLACK);
      tft.setCursor(5, 47);
      tft.print("Communication error");
      delay(2000);
      return p;
      
    case FINGERPRINT_FEATUREFAIL:
      tft.fillRect(0,25,240,110,TFT_BLACK);
      tft.setCursor(5, 47);
      tft.print("Finger not");
      tft.setCursor(5, 74);
      tft.println("found");
      delay(2000);
      return p;
      
    case FINGERPRINT_INVALIDIMAGE:
      tft.fillRect(0,25,240,110,TFT_BLACK);
      tft.setCursor(5, 47);
      tft.print("Invalid image");
      delay(2000);
      return p;
      
    default:
      tft.fillRect(0,25,240,110,TFT_BLACK);
      tft.setCursor(5, 47);
      tft.print("Unknown error");
      delay(2000);
      return p;
  }

  // OK converted!
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    tft.fillRect(0,25,240,110,TFT_BLACK);
    tft.setCursor(5, 47);
    tft.print("Not leave");
  } 
  else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    tft.fillRect(0,25,240,110,TFT_BLACK);
    tft.setCursor(5, 47);
    tft.print("Communication error");
    delay(2000);
    return p;
  } 
  else if (p == FINGERPRINT_ENROLLMISMATCH) {
    tft.fillRect(0,25,240,110,TFT_BLACK);
    tft.setCursor(5, 47);
    tft.print("Fingerprints did't");
    tft.setCursor(5, 74);
    tft.print("match!");
    delay(2000);
    return p;
  } 
  else {
    tft.fillRect(0,25,240,110,TFT_BLACK);
    tft.setCursor(5, 47);
    tft.print("Unknown error");
    delay(2000);
    return p;
  }

  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    tft.fillRect(0,25,240,110,TFT_BLACK);
    tft.setCursor(5, 47);
    tft.print("Store Fingerprint.");
    tft.setCursor(5, 74);
    tft.print("Leave.");
    delay(3000);
  } 
  else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    tft.fillRect(0,25,240,110,TFT_BLACK);
    tft.setCursor(5, 47);
    tft.print("Communication error");
    delay(2000);
    return p;
  } 
  else if (p == FINGERPRINT_BADLOCATION) {
    tft.fillRect(0,25,240,110,TFT_BLACK);
    tft.setCursor(5, 47);
    tft.print("Impossible store");
    tft.setCursor(5, 74);
    tft.print("in that location");
    delay(2000);
    return p;
  } 
  else if (p == FINGERPRINT_FLASHERR) {
    tft.fillRect(0,25,240,110,TFT_BLACK);
    tft.setCursor(5, 47);
    tft.print("Error writing");
    tft.setCursor(5, 74);
    tft.print("to flash");
    delay(2000);
    return p;
  } 
  else {
    tft.fillRect(0,25,240,110,TFT_BLACK);
    tft.setCursor(5, 47);
    tft.print("Unknown error");
    delay(2000);
    return p;
  }

  tft.fillRect(0,25,240,110,TFT_BLACK);
  return true;
}
/* Enroll Phase - end */


/* Delete Phase - start */
bool fingerprint_delete(uint8_t id){
  if (id == 0) // ID #0 not allowed, try again!
     return false;
     
  return deleteFingerprint(id);
}


void fingerprint_deleteAll(){
  for(int i = 0; i < 3; i++){
    tft.fillRect(0,25,240,110,TFT_BLACK);
    tft.setCursor(5, 47);
    tft.print("Ready to enroll!");
    tft.setCursor(5, 87);
    tft.print("Please follow");
    tft.setCursor(5, 111);
    tft.print("the instructions.");
    
    delay(400);
    tft.print("."); delay(400);
    tft.print("."); delay(400);
    tft.print("."); delay(400);
  }
  
  finger.emptyDatabase();
  
  tft.fillRect(0,25,240,110,TFT_BLACK);
  tft.setCursor(30, 60);
  tft.print("Database empty!");
  tft_logo.pushImage(90, 75, 52, 52, success);
  delay(3000);
}


bool deleteFingerprint(uint8_t id) {
  uint8_t p = -1;

  p = finger.deleteModel(id);

  if (p == FINGERPRINT_OK) 
    return true;
  
  else if (p == FINGERPRINT_PACKETRECIEVEERR) 
    return false;
  
  else if (p == FINGERPRINT_BADLOCATION) 
    return false;
  
  else if (p == FINGERPRINT_FLASHERR)
    return false;
  
  else 
    return false;

  return false;
}
/* Delete Phase - end */
