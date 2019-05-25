#include <SD.h>
#include <SPI.h>
#include <FastLED.h>

#define LEDSize 100

int cs = 53;
File myFile;
String buffers;


typedef struct frame {
  byte red[LEDSize];
  byte green[LEDSize];
  byte blue[LEDSize];
  byte selectedLEDs[LEDSize];
  int timeDelay;
} frame;


void assignValues(File& myFile, int frameSize) {
  byte incriment = 0;
  byte currentFrame = -1;
  frame Frames[frameSize];
  //byte incriment = 0;
  char delim[] = "() ";
  while (myFile.available()) {
    buffers = myFile.readStringUntil('\n');
    char *ptr = strtok(buffers.c_str(), delim);
    for (int i = 0; ptr[i] != '\0'; i++) {
      if (ptr[i] == '[') {
        currentFrame++;
        Serial.println(ptr[i+1]);
        ptr = strtok(NULL, delim);
        incriment = 0;
        
      } else {
          byte r,g,b;
          char* val[1];
          if(sscanf(ptr, "%[^,],%d,%d,%d", val, &r, &g, &b) != 1){
            /*Serial.println(r);
            Serial.println(g);
            Serial.println(b);*/
            Frames[currentFrame].red[incriment] = (byte)r;
            Frames[currentFrame].green[incriment] = (byte)g;
            Frames[currentFrame].blue[incriment] = (byte)b;
            if(val[0] == 't'){
              Frames[currentFrame].selectedLEDs[incriment] = (byte)1;
            }else{
              Frames[currentFrame].selectedLEDs[incriment] = (byte)0;
            }
           
          }
          incriment++;
          //Serial.println(ptr);
          ptr = strtok(NULL, delim);
          
        }
      }
    }
  }

void readFrames(File& myFile, int& frameAmount) {
  String tempBuffer;
  tempBuffer = myFile.readStringUntil('>');
  char delim[] = "<>";
  char* line = strtok(tempBuffer.c_str(), delim );
  while (myFile.available()) {
    while (line != NULL) {
      frameAmount = atoi(line);
      Serial.println(frameAmount);
      break;
    }
    break;
  }
}
void setup() {
  char myFileName[] = "NEW.txt";

  Serial.begin(9600);
  while (!Serial) {

  }
  Serial.println("Connecting to SD card...");
  pinMode(cs, OUTPUT);
  digitalWrite(10,HIGH);
  pinMode(SS, OUTPUT);
  if (!SD.begin(cs)) {
    Serial.println("SD did not initalize");
  }
  myFile = SD.open(myFileName, FILE_READ);
  if (!myFile) {
    Serial.println("Could not open file");
    while (1);
  }

  int frameAmount;
  readFrames(myFile, frameAmount);
  assignValues(myFile, frameAmount);
}
void read
void loop() {
  // put your main code here, to run repeatedly:

}
