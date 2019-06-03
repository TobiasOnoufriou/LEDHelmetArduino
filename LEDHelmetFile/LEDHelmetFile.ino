 #include <SD.h>
#include <SPI.h>
#include <FastLED.h>

#define LEDSize 100

byte cs = 53;
File myFile;
String buffers;
int frameAmount;
CRGB leds[144];


typedef struct frame {
  byte red[LEDSize];
  byte green[LEDSize];
  byte blue[LEDSize];
  byte selectedLEDs[LEDSize];
  int timeDelay;
} frame;

frame Frames[10];
void showAnimation()
{
  for(int cF = 0; cF < frameAmount; cF++){
    Serial.println(cF);
    for(int i = 0; i < LEDSize; i++){
      if(Frames[cF].selectedLEDs[i] == 1){
        Serial.println(i);
        Serial.println(Frames[cF].red[i]);
        leds[i] = CRGB(Frames[cF].red[i],Frames[cF].green[i],Frames[cF].blue[i]);
        FastLED.show();
      }
      
    }
   
    delay(1500);
     FastLED.clear();
  }
}

void assignValues(File& myFile) {
  byte incriment = 0;
  byte currentFrame = -1;
  //byte incriment = 0;
  char delim[] = "() ";
  //frame Frames[frameAmount];
  while (myFile.available()) {
    buffers = myFile.readStringUntil('\n');
    char *ptr = strtok(buffers.c_str(), delim);
    for (int i = 0; ptr[i] != '\0'; i++) {
      if (ptr[i] == '[') {
        currentFrame++;
        //Serial.println(ptr[i+1]);
        ptr = strtok(NULL, delim);
        incriment = 0;
        
      } else {
          byte r,g,b,selected;
          int tempTimeDelay;
          char* val[1];
          //%[^,]
          if(sscanf(ptr, "%d,%d,%d,%d", &selected, &r, &g, &b) != 1){
          
            Frames[currentFrame].red[incriment] = (byte)r;
            Frames[currentFrame].green[incriment] = (byte)g;
            Frames[currentFrame].blue[incriment] = (byte)b;
            Frames[currentFrame].selectedLEDs[incriment] = (byte)selected; //This is set to true.
            //Serial.println(Frames[currentFrame].selectedLEDs[incriment]);
            incriment++;
          }
          /*if(sscanf(ptr, "Delay:%d",&tempTimeDelay)){
            Serial.println(tempTimeDelay);
          }*/
          ptr = strtok(NULL, delim);
          
        }
      }
    }
    
  }

void readFrames(File& myFile) {
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
  char myFileName[] = "NEW2.txt";
  FastLED.addLeds<WS2812B, 7, GRB>(leds, 144);
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

  
  readFrames(myFile);
  assignValues(myFile);
}

void loop() {
  // put your main code here, to run repeatedly:
  showAnimation();

  

}
