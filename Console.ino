#include <MCUFRIEND_kbv.h>
#include <Wire.h>
#include "Console.h"

MCUFRIEND_kbv tft;
const int NUM_BUTTONS = 6;
const int btnPinArr[NUM_BUTTONS] = {22, 23, 24, 25, 26, 27};
byte btnArr[NUM_BUTTONS] = {0,0,0,0,0,0};
byte graphicsBuffer[32];
int graphicsBufferSize = 0;
byte spriteList[32][25];

void setup() {
  for(int i = 0; i < 6; i++){
    pinMode(btnPinArr[i], INPUT);
  }
  //Setup Display
  tft.reset();
  uint16_t ID = tft.readID();
  tft.begin(ID); 
  tft.setRotation(3);
  drawBootLogo();
  //Setup Communications With Cartridge
  Wire.begin(8);
  Wire.setClock(400000);
  Wire.onRequest(sendInputs);
  Wire.onReceive(getDrawData);
}

void loop() {
}

void drawBootLogo(){
  tft.fillScreen(WHITE);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.setCursor(80, 120);
  tft.print("Gameboy");
  tft.setTextSize(3);
  tft.setCursor(140, 180);
  tft.print("By: Levi Aviv");
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

uint16_t getColor(byte color_index){
  uint16_t color;
  switch(color_index){
    case 1:
      color = BLACK;
      break;
    case 2:
      color = NAVY;
      break;
    case 3:
      color = DARKGREEN;
      break;
    case 4:
      color = DARKCYAN;
      break;
    case 5:
      color = MAROON;
      break;
    case 6:
      color = PURPLE;
      break;
    case 7:
      color = OLIVE;
      break;
    case 8:
      color = LIGHTGREY;
      break;
    case 9:
      color = DARKGREY;
      break;
    case 10:
      color = BLUE;
      break;
    case 11:
      color = GREEN;
      break;
    case 12:
      color = CYAN;
      break;
    case 13:
      color = RED;
      break;
    case 14:
      color = MAGENTA;
      break;
    case 15:
      color = YELLOW;
      break;
    case 16:
      color = WHITE;
      break;
    case 17:
      color = ORANGE;
      break;
    case 18:
      color = GREENYELLOW;
      break;
    case 19:
      color = PINK;
      break;
  }
  return color;
}

void drawGraphicsBuffer(){
  int shape = graphicsBuffer[0];
  switch(shape){
    case 0:
      drawVLine();
      break;
    case 1:
      drawHLine();
      break;
    case 2:
      drawRect();
      break;
    case 3:
      fillRect();
      break;
    case 4:
      drawCircle();
      break;
    case 5:
      fillCircle();
      break;
    case 6:
      //Triangle
      break;
    case 7:
      tft.fillScreen(getColor(graphicsBuffer[1]));
      break;
    case 8:
      drawPixel();
      break;
    case 9:
      storeSprite();
      break;
    case 10:
      drawSprite();
      break;
    case 11:
      drawText();
      break;
  }
}

void getDrawData(){
  graphicsBufferSize = Wire.read();
  int i = 0;
  while(Wire.available()){
    graphicsBuffer[i++] = Wire.read();
  }
  drawGraphicsBuffer();
}

void drawVLine(){
  byte b1, b2;
  int x, y, length;
  int i = 1;
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  x = byte2int(b1, b2);
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  y = byte2int(b1, b2);
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  length = byte2int(b1, b2);
  tft.drawFastVLine(x, y, length, getColor(graphicsBuffer[i++]));
}

void drawHLine(){
  byte b1, b2;
  int x, y, length;
  int i = 1;
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  x = byte2int(b1, b2);
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  y = byte2int(b1, b2);
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  length = byte2int(b1, b2);
  tft.drawFastHLine(x, y, length, getColor(graphicsBuffer[i++]));
}

void drawRect(){
  byte b1, b2;
  int x, y, l, w;
  int i = 1;
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  x = byte2int(b1, b2);
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  y = byte2int(b1, b2);
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  l = byte2int(b1, b2);
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  w = byte2int(b1, b2);
  tft.drawRect(x, y, l, w, getColor(graphicsBuffer[i++]));
}

void fillRect(){
  byte b1, b2;
  int x, y, l, w;
  int i = 1;
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  x = byte2int(b1, b2);
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  y = byte2int(b1, b2);
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  l = byte2int(b1, b2);
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  w = byte2int(b1, b2);
  tft.fillRect(x, y, l, w, getColor(graphicsBuffer[i++]));
}

void drawCircle(){
  byte b1, b2;
  int x, y, r;
  int i = 1;
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  x = byte2int(b1, b2);
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  y = byte2int(b1, b2);
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  r = byte2int(b1, b2);
  tft.drawCircle(x, y, r, getColor(graphicsBuffer[i++]));
}

void fillCircle(){
  byte b1, b2;
  int x, y, r;
  int i = 1;
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  x = byte2int(b1, b2);
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  y = byte2int(b1, b2);
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  r = byte2int(b1, b2);
  tft.fillCircle(x, y, r, getColor(graphicsBuffer[i++]));
}

void drawPixel(){
  byte b1, b2;
  int x, y;
  int i = 1;
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  x = byte2int(b1, b2);
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  y = byte2int(b1, b2);
  tft.drawPixel(x, y, getColor(graphicsBuffer[i++]));
}

void storeSprite(){
  int i = 1;
  byte spriteIndex = graphicsBuffer[i++];
  for(int j = 0; j < 25; j++){
    spriteList[spriteIndex][j] = graphicsBuffer[i++];
  }
}

void drawSprite(){
  byte b1, b2, sprite_index, scaler, color_index;
  int x, y, cur_x, cur_y;
  uint16_t cur_color;
  int i = 1;
  sprite_index = graphicsBuffer[i++];
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  x = byte2int(b1, b2);
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  y = byte2int(b1, b2);
  scaler = graphicsBuffer[i++];
  color_index = 0;
  for(int y_pixel = 0; y_pixel < 5 * scaler; y_pixel += scaler){
    for(int x_pixel = 0; x_pixel < 5 * scaler; x_pixel += scaler){
      if(spriteList[sprite_index][color_index] > 0){
        cur_color = getColor(spriteList[sprite_index][color_index++]);
        for(int y_sub = 0; y_sub < scaler; y_sub++){
          for(int x_sub = 0; x_sub < scaler; x_sub++){
            cur_x = x + x_pixel + x_sub;
            cur_y = y + y_pixel + y_sub;
            if(tft.readPixel(cur_x, cur_y) != cur_color){
              tft.drawPixel(cur_x, cur_y, cur_color);
            }
          }
        }
      } else {
        color_index++;
      }
    }
  }
}

void drawText(){
  byte b1, b2;
  int x, y;
  int i = 1;
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  x = byte2int(b1, b2);
  b1 = graphicsBuffer[i++];
  b2 = graphicsBuffer[i++];
  y = byte2int(b1, b2);
  tft.setCursor(x, y);
  tft.setTextSize(graphicsBuffer[i++]);
  tft.setTextColor(getColor(graphicsBuffer[i++]));
  int text_index = 0;
  while(text_index < 25 && graphicsBuffer[i] != 0){
    Serial.println(graphicsBuffer[i]);
    tft.print((char)graphicsBuffer[i++]);
    text_index++;
  }
}