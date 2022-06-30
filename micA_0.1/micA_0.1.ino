#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

//читаємо термінал
int waiting_time = 10;
int waiting_time_out = 50;
bool bY = 0;

volatile uint32_t debounce;
volatile uint32_t debounce2;
String inString;


bool buttL;        //кнопкаL
bool buttR;        //кнопкаR



#define PINL 3   // входной контакт Neopixel
#define PINR 4   // входной контакт Neopixel
#define NUMPIXELS 4 // количество неопикселей в ринге

Adafruit_NeoPixel pixelsL = Adafruit_NeoPixel(NUMPIXELS, PINL, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixelsR = Adafruit_NeoPixel(NUMPIXELS, PINR, NEO_GRB + NEO_KHZ800);

byte redColor, greenColor, blueColor;



void setup() {

  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(3, OUTPUT);
  

  pinMode(8, INPUT );//кнопка
  pinMode(7, INPUT);//кнопка
   
  pixelsL.begin(); // Инициализирует библиотеку NeoPixel.
  pixelsR.begin(); // Инициализирует библиотеку NeoPixel.
  
  Serial.begin (9600); // Задаем скорость обмена com-порта 9600
  
  Serial.println(F("|setup|"));
  Serial.print(F("|NUMPIXELS : "));
  Serial.print(NUMPIXELS);
  Serial.print(F("|"));
  Serial.println(F("")); 
  
  Serial.print(F("| Red | "));
  Serial.print(F("| Green | "));
  Serial.print(F("| Blue |  "));
  Serial.println(F(""));
 

}

void loop() { 


   /////////////////// //читаємо термінал
if (Serial.available() > 0) { 
 
  char inChar = Serial.read();
  inString += inChar;
  debounce = millis();
  } 
  
  if (millis() - debounce >= waiting_time && inString != "") { 
    debounce = millis();
    waiting_time_out = inString.toInt();

    if (waiting_time_out == 0) waiting_time_out = 1;

    Serial.println("___________________________________________________");
    Serial.print("Result times : ");
    Serial.println("");
    

    Serial.println("___________________________________________________");
    Serial.print("next time = ");
    Serial.print(waiting_time_out);
    Serial.println(" m.c.");
    Serial.println("___________________________________________________");
    inString = "";
    
    
  }

     if (millis() - debounce2 >= waiting_time_out) { 
     debounce2 = millis();
     bY = !bY;
     analogWrite(10, waiting_time_out);
     analogWrite(3, waiting_time_out);
     analogWrite(9, 200);
     analogWrite(6, 200);
     
    
  }




  

  buttL = !digitalRead(8);
  buttR = !digitalRead(7);


  
  setColor();
  
}

// setColor()
// выбирает случайные значения для RGB

void setColor(){
  
  
  
  redColor = random(0, 255);
  greenColor = random(0,255);
  blueColor = random(0, 255);

   if (buttR == 0 || buttL == 0) {
  for (int i = 0 ; i < NUMPIXELS; i++ ) {      
  
    // пикселей. Цвет принимает значения RGB, от 0,0,0 до 255,255,255.
   
    
    
    
      if (buttR == 0 ) {
      pixelsR.setPixelColor(i, pixelsR.Color(redColor, greenColor, blueColor)); // Умеренно ярко-зеленый цвет.
     pixelsR.show(); // Это отправляет обновленный цвет пикселя на аппаратное обеспечение.

  }
  
    if (buttL == 0 ) {
      pixelsL.setPixelColor(i, pixelsL.Color(redColor, greenColor, blueColor)); // Умеренно ярко-зеленый цвет.
     pixelsL.show(); // Это отправляет обновленный цвет пикселя на аппаратное обеспечение.

  }
   
   
 

      delay(150);
  }

    Serial.print(F("  "));Serial.print(redColor);
    Serial.print(F("       "));Serial.print(greenColor);
    Serial.print(F("      "));Serial.print(blueColor);
    Serial.println(F(""));
  
   }

  

    
    

   


   
  

}
