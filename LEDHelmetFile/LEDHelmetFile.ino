#include <SD.h>
#include <SPI.h>


#define LEDSize 10


int cs = 10;
File myFile;
String data;
String buffers;
int lines;
int frames;

typedef struct{
  int red[LEDSize][LEDSize];
  int green[LEDSize][LEDSize];
  int blue[LEDSize][LEDSize];
  boolean selectedLEDs[LEDSize][LEDSize];
  int timeDelay;
}frame;

void assignValues(File& myFile, int frameSize){
  int listLength = 1;
  int currentFrame = -1;
  int curChar;
  frame Frames[frameSize];
  char delim[] = "()";
  char subDelim = ",";
  
    while(myFile.available()){
      buffers = myFile.readStringUntil('\n');
      char *ptr = strtok(buffers.c_str(), delim);
      for(int i = 0; ptr[i] != '\0'; i++){
        if(ptr[i] == '['){
          currentFrame++;
          Serial.println(ptr[i+1]);
        }else{
        for(int n = 0; n < 3; n++){
            if(i == 0){
              Serial.println(ptr);
              ptr = strtok(NULL, delim);
            }else if(i >= 1 ){
             
          }
        }
      }
    }
  }
}

int readFrames(File& myFile, int& frameAmount){
  String tempBuffer;
  tempBuffer = myFile.readStringUntil('>');
  char delim[] = "<>";
  char* line = strtok(tempBuffer.c_str(),delim );
  while(myFile.available()){ 
    while(line != NULL){
      frameAmount = atoi(line);
      Serial.println(frameAmount);
      break;
    }
    break;
  }
}
void setup() {
  // put your setup code here, to run once:
  char myFileName[] = "NEW.txt";

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
  //char temp[10];
  int frameAmount;
  readFrames(myFile, frameAmount);
  
  assignValues(myFile,frameAmount);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
