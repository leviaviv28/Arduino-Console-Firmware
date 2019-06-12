#include <MCUFRIEND_kbv.h>
#include <Wire.h>
#include <I2C_Anything.h>
#include "Console.h"

MCUFRIEND_kbv tft;

const int NUM_BUTTONS = 6;
const int btnPinArr[NUM_BUTTONS] = {22, 23, 24, 25, 26, 27};
byte btnArr[NUM_BUTTONS] = {0,0,0,0,0,0};
byte graphicsBuffer[32];
int graphicsBufferSize = 0;

void setup() {
  for(int i = 0; i < 6; i++){
    pinMode(btnPinArr[i], INPUT);
  }
  //Setup Display
  tft.reset();
  uint16_t ID = tft.readID();
  tft.begin(ID); 
  tft.setRotation(4);
  tft.fillScreen(BLACK);

  //Setup Communications With Cartridge
  Wire.begin(8);
  Wire.setClock(400000);
  Wire.onRequest(sendInputs);
  Wire.onReceive(getDrawData);
  Serial.begin(9600);
}

void loop() {
}

int byte2int(byte intp1, byte intp2) {
  int convInt = intp1;
  convInt |= (intp2 << 8);
  return convInt;
}

void sendInputs(){
  for(int i = 0; i < NUM_BUTTONS; i++){
    btnArr[i] = digitalRead(btnPinArr[i]);
    Wire.write(btnArr[i]);
  }
}

void drawGraphicsBuffer(){
  byte b1, b2;
  int shape, x0, y0, x1, y1, x2, y2, w, h, r, length;
  uint16_t color;
  int i = 0;
  while(i < graphicsBufferSize){
    shape = graphicsBuffer[i++];
    color = tft.color565(graphicsBuffer[i++], graphicsBuffer[i++], graphicsBuffer[i++]);
    switch(shape){
      case 0:
        x0 = byte2int(graphicsBuffer[i++], graphicsBuffer[i++]);
        y0 = byte2int(graphicsBuffer[i++], graphicsBuffer[i++]);
        length = byte2int(graphicsBuffer[i++], graphicsBuffer[i++]);
        tft.drawFastVLine(x0, y0, length, color);
        break;
      case 1:
        x0 = graphicsBuffer[i++];
        y0 = graphicsBuffer[i++];
        length = graphicsBuffer[i++];
        tft.drawFastVLine(x0, y0, length, color);
        break;
      case 2:
        b1 = graphicsBuffer[i++];
        b2 = graphicsBuffer[i++];
        x0 = byte2int(b1, b2);
        b1 = graphicsBuffer[i++];
        b2 = graphicsBuffer[i++];
        y0 = byte2int(b1, b2);
        b1 = graphicsBuffer[i++];
        b2 = graphicsBuffer[i++];
        h = byte2int(b1, b2);
        b1 = graphicsBuffer[i++];
        b2 = graphicsBuffer[i++];
        w = byte2int(b1, b2);
        tft.drawRect(x0, y0, w, h, color);
        break;
      case 3:
        b1 = graphicsBuffer[i++];
        b2 = graphicsBuffer[i++];
        x0 = byte2int(b1, b2);
        b1 = graphicsBuffer[i++];
        b2 = graphicsBuffer[i++];
        y0 = byte2int(b1, b2);
        b1 = graphicsBuffer[i++];
        b2 = graphicsBuffer[i++];
        h = byte2int(b1, b2);
        b1 = graphicsBuffer[i++];
        b2 = graphicsBuffer[i++];
        w = byte2int(b1, b2);
        tft.fillRect(x0, y0, w, h, color);
        break;
      case 4:
        b1 = graphicsBuffer[i++];
        b2 = graphicsBuffer[i++];
        x0 = byte2int(b1, b2);
        b1 = graphicsBuffer[i++];
        b2 = graphicsBuffer[i++];
        y0 = byte2int(b1, b2);
        b1 = graphicsBuffer[i++];
        b2 = graphicsBuffer[i++];
        r = byte2int(b1, b2);
        tft.drawCircle(x0, y0, r, color);
        break;
      case 5:
        b1 = graphicsBuffer[i++];
        b2 = graphicsBuffer[i++];
        x0 = byte2int(b1, b2);
        b1 = graphicsBuffer[i++];
        b2 = graphicsBuffer[i++];
        y0 = byte2int(b1, b2);
        b1 = graphicsBuffer[i++];
        b2 = graphicsBuffer[i++];
        r = byte2int(b1, b2);
        tft.fillCircle(x0, y0, r, color);
        break;
      case 6:
        b1 = graphicsBuffer[i++];
        b2 = graphicsBuffer[i++];
        x0 = byte2int(b1, b2);
        b1 = graphicsBuffer[i++];
        b2 = graphicsBuffer[i++];
        y0 = byte2int(b1, b2);
        b1 = graphicsBuffer[i++];
        b2 = graphicsBuffer[i++];
        x1 = byte2int(b1, b2);
        b1 = graphicsBuffer[i++];
        b2 = graphicsBuffer[i++];
        y1 = byte2int(b1, b2);
        b1 = graphicsBuffer[i++];
        b2 = graphicsBuffer[i++];
        x2 = byte2int(b1, b2);
        b1 = graphicsBuffer[i++];
        b2 = graphicsBuffer[i++];
        y2 = byte2int(b1, b2);
        tft.drawTriangle(x0, y0, x1, y1, x2, y2, color);
        break;
      case 7:
        tft.fillScreen(color);
    }
  }
  graphicsBufferSize = 0;
}

void getDrawData(){
  graphicsBufferSize = Wire.read();
  int i = 0;
  while(Wire.available()){
    graphicsBuffer[i++] = Wire.read();
  }
  drawGraphicsBuffer();
}
