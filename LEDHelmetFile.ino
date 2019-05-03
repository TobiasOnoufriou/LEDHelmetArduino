#include <SD.h>
#include <SPI.h>


#define LEDSize 10;


int cs = 10;
File myFile;
String data;
String buffers;
int lines;

typedef struct{
  int red[10][10];
  int green[10][10];
  int blue[10][10];
  boolean selectedLEDs[10][10];
  int timeDelay;
}frame;

void assignValues(File& myFile){
  int listLength = 1;
  int curChar;
  char delim[] = "()";
  while(myFile.available()){
    buffers = myFile.readStringUntil('\n');
    char *ptr = strtok(buffers.c_str(), delim);
    while(ptr != NULL){
      Serial.println(ptr);
      ptr = strtok(NULL, delim);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  char myFileName[] = "WORKING.txt";

  Serial.begin(9600);
  while(!Serial){
    
  }
  Serial.println("Connecting to SD card...");
  pinMode(cs, OUTPUT);
  pinMode(SS, OUTPUT);
  if(!SD.begin(cs)){
    Serial.println("SD did not initalize");
  }
  myFile = SD.open(myFileName, FILE_READ);
  if(!myFile){
    Serial.println("Could not open file");
    while(1);
  }
  assignValues(myFile);
}

void loop() {
  // put your main code here, to run repeatedly:

}
