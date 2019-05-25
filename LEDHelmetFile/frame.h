#ifndef frame_h
#define frame_h

typedef struct frame {
  byte red[LEDSize];
  byte green[LEDSize];
  byte blue[LEDSize];
  byte selectedLEDs[LEDSize];
  int timeDelay;
} frame;



#endif