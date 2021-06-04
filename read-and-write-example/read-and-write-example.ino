#include <EEPROM.h>

#define MAX_STRING_LENGTH 20

struct { 
    char mySSID[MAX_STRING_LENGTH] = "";
    char myPW[MAX_STRING_LENGTH] = "";
  } settings;


  
void setup() {
  Serial.begin(115200); //start the serial output
  Serial.println();
  Serial.println("Starting up");


  //load eeprom data (sizeof(settings) bytes) from flash memory into ram
  EEPROM.begin(sizeof(settings));
  Serial.println("EEPROM size: " + String(sizeof(settings)) + " bytes");
}

void loop() {


//---------------------------------------------------------------------------------------
//
//    READ DATA FROM EEPROM
//
//----------------------------------------------------------------------------------------
  Serial.println("Reading old data from EEPROM:");
  //read data from EEPROM :
  unsigned int addr = 0;
  //---------------------------------------------------------------------------------------
  //using get()
  //---------------------------------------------------------------------------------------
  EEPROM.get(addr, settings); //read data from array in ram and cast it to settings
  Serial.println("Using EEPROM.get:");
  Serial.println("mySSID: " + String(settings.mySSID) + ",\t\tmyPW: " + String(settings.myPW));

  //reset strings to "" for testing:
  strncpy(settings.mySSID, "", MAX_STRING_LENGTH);
  strncpy(settings.myPW, "", MAX_STRING_LENGTH);
  
  //---------------------------------------------------------------------------------------
  //using read()
  //---------------------------------------------------------------------------------------
  for(int i=0; i<MAX_STRING_LENGTH; ++i){
    settings.mySSID[i] = EEPROM.read(addr + i); //read individual byte from ram at (addr + i) and copy it to settings.mySSID[i]
  }
  addr += MAX_STRING_LENGTH;
  for(int i=0; i<MAX_STRING_LENGTH; ++i){
    settings.myPW[i] = EEPROM.read(addr + i); //read individual byte from ram at (addr + i) and copy it to settings.myPW[i]
  }
  Serial.println("Using EEPROM.read:");
  Serial.println("mySSID: " + String(settings.mySSID) + ",\t\tmyPW: " + String(settings.myPW));



//---------------------------------------------------------------------------------------
//
//    CHANGE DATA FOR TESTING
//
//----------------------------------------------------------------------------------------
  //set new data for testing:
  strncpy(settings.mySSID, "my-WiFi-SSID2", MAX_STRING_LENGTH);
  strncpy(settings.myPW, "superSecretPW2", MAX_STRING_LENGTH);



//---------------------------------------------------------------------------------------
//
//    WRITE DATA TO EEPROM
//
//----------------------------------------------------------------------------------------
  //write data to EEPROM
  addr=0;
  //---------------------------------------------------------------------------------------
  //using put()
  //---------------------------------------------------------------------------------------
  EEPROM.put(addr, settings); //write data to array in ram 
  EEPROM.commit();  //write data from ram to flash memory. Do nothing if there are no changes to EEPROM data in ram

  
  addr=0;
  //---------------------------------------------------------------------------------------
  //using write()
  //---------------------------------------------------------------------------------------
  for(int i=0; i<MAX_STRING_LENGTH; ++i){
    EEPROM.write(addr + i, settings.mySSID[i]); //write individual byte from settings.mySSID[i] to ram at (addr + i)
  }
  addr += MAX_STRING_LENGTH;
  for(int i=0; i<MAX_STRING_LENGTH; ++i){
    EEPROM.write(addr + i, settings.myPW[i]); //write individual byte from settings.myPW[i] to ram at (addr + i)
  }
  EEPROM.commit();  //write data from ram to flash memory. Do nothing if there are no changes to EEPROM data in ram

  
  delay(5000);
}
