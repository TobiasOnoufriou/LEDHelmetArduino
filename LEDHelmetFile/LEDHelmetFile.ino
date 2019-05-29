#include <SD.h>
#include <SPI.h>
#include <FastLED.h>

#define LEDSize 101

int cs = 53;
File myFile;
String buffers;
CRGB leds[LEDSize];

typedef struct frame {
  byte red[LEDSize];
  byte green[LEDSize];
  byte blue[LEDSize];
  byte selectedLEDs[LEDSize];
  int timeDelay;
} frame;

bool checked = false;
void assignValues(File& myFile, int frameSize, frame Frames[]);
void showAnimation(frame Frames[]);
void readFrames(File& myFile, int& frameAmount);


void setup() {
  char myFileName[] = "NEW.txt";
  FastLED.addLeds<WS2812B, 7, RGB>(leds, LEDSize);
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
  frame Frames[frameAmount];
  assignValues(myFile, frameAmount);

  //showAnimation(Frames);
}


void showAnimation(frame Frames[]){
     for(int cF = 0; cF <= 2; cF++){
      for(int i = 0; i < LEDSize; i++){
      //Serial.println(Frames[cF].selectedLEDs[i]);
      if(Frames[cF].selectedLEDs[i] == 1){
        leds[i] = CRGB(Frames[cF].red[i],Frames[cF].green[i],Frames[cF].blue[i]);
        FastLED.show();
      }
    }
  }
}


void assignValues(File& myFile, int frameSize) {
  byte incriment = 0;
  byte currentFrame = -1;
  frame Frames[frameSize];
  
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
          char* val[6];
          if(sscanf(ptr, "%*[^,],%d,%d,%d", val, &r, &g, &b ) != 1){
            Frames[currentFrame].red[incriment] = (byte)r;
            Frames[currentFrame].green[incriment] = (byte)g;
            Frames[currentFrame].blue[incriment] = (byte)b;
         
            //Serial.println(Frames[currentFrame].blue[incriment]);
            Serial.println(val[0]);
            if(val[0] == 't'){
              Frames[currentFrame].selectedLEDs[incriment] = 1;
            }else{
              Frames[currentFrame].selectedLEDs[incriment] = 0;
            }
            incriment++;
          }
          
          Serial.println(ptr);
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


void loop() {
  // put your main code here, to run repeatedly:
 
  
}
