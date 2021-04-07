#include <Arduino.h>

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h> 
#include "Adafruit_GrayOLED.h"

//-----------------DISPLAY-----------------//
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_SUPPLY_nEN 16
#define OLED_SDA 0
#define OLED_SCL 4
#define SCREEN_WIDTH 128 // OLED display Breite, in pixels
#define SCREEN_HEIGHT 64 // OLED display Höhe, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//-----------------BUTTONS-----------------//
int Back = T7; // IO27
int Select = T6; // IO14
int Menu = T5; // IO12

//------------MENUE-VARIABLEN-------------//
boolean cloudMenu = true;
int color1;
int color2;
int wahl = 6;

int Menustate;
int Selectstate;
int Backstate;

boolean menustatebool = true;
boolean backstatebool = true;
boolean selectstatebool = true;
boolean Menubutton = false;
boolean Backbutton = false;
boolean Selectebutton = false;
//---------------VOID---------------------//
void menu();


void setup() {
  //--------------DISPLAYBEGIN----------//
  pinMode(OLED_SUPPLY_nEN, OUTPUT);
  digitalWrite(OLED_SUPPLY_nEN, LOW);
  Wire.begin(OLED_SDA, OLED_SCL);
  

  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false);
  display.dim(0);
  delay(100);
  display.clearDisplay();

  pinMode(Back, INPUT);
  pinMode(Select, INPUT);
  pinMode(Menu, INPUT);

}

void loop() {
  display.clearDisplay();
//---------------CLOUD------------------//
  if(cloudMenu == true){
    menu();
  }


}

void menu(){
//-------------BUTTONREAD--------------//
  
  Menustate += touchRead(T5);
  Selectstate += touchRead(T6);
  Backstate += touchRead(T7);

  //Menustate += touchRead(T5);
  //Selectstate += touchRead(T6);
  //Backstate += touchRead(T7);

  //Menustate += touchRead(T5);
  //Selectstate += touchRead(T6);
  //Backstate += touchRead(T7);

  Menustate = Menustate / 3;
  Selectstate = Selectstate / 3;
  Backstate = Backstate / 3;
  

  

  if(Menustate < 20){
    if(menustatebool == true){
      Menubutton = true;
      menustatebool = false;
    }
  }
  else{
    menustatebool = true;
    Menubutton = false;
  }

  if(Backstate < 20){
    if(backstatebool == true){
      Backbutton = true;
      backstatebool = false;
    }
  }
  else{
    backstatebool = true;
    Backbutton = false;
  }

  if(Selectstate < 20){
    if(selectstatebool == true){
      Selectebutton = true;
      selectstatebool = false;
    }
  }
  else{
    selectstatebool = true;
    Selectebutton = false;
  }

//--------------SOMTHING--------------//
if(wahl == 6 && Menubutton == true){
  wahl = 28;
}
else if(wahl == 28 && Menubutton == true){
  wahl  = 6;
}

  if(wahl == 6){
    color1 = BLACK;
    color2 = WHITE;
  }
  else if(wahl == 28){
    color1 = WHITE;
    color2 = BLACK;
  }
//--------------DISPLAYMENU--------------//
  display.drawRect(8, 6, 110, 20, WHITE);
  display.drawRect(8, 28, 110, 20, WHITE);

  display.fillRect(8, wahl, 110, 20, WHITE);

  display.setTextSize(2);
  display.setTextColor(color1);
  display.setCursor(10, 9);
  display.print("NEW GAME"); 

  display.setTextSize(2);
  display.setTextColor(color2);
  display.setCursor(10, 31);
  display.print("DOWNLOAD"); 

  display.display();

//-------------AUSWAHL---------------//
if(Selectebutton == true){
  display.clearDisplay();
  if(wahl = 6){//----------NEWGAME-------//
    //DINGS
  }
  else if(wahl = 28){//----------CLOUDGAME-------//
    //DONGS
  }

  cloudMenu = false;
}
}