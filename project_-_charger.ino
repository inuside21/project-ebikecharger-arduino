#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 4); 
int ctr = 0;

// coinslot
int PIN_IN   = 10;
int switchState = 0;
int pulseCount = 0;
int prevState = 1;
int MaxElapsedTime = 500;
unsigned long StartTime = millis();
int ctrs = 0;
int convertCount = 60;

// button
int btn1 = 11; // charger 1
int btn2 = 12; // charger 2
int btnStop = 13; // stop

// charge
bool isCharging = false;
int chargingPort = 0;
int remainingTime = 0;

// Relay
int out1 = 9;
int out2 = 8;
int out3 = 7;
int out4 = 6;
int out5 = 5;
int out6 = 4;
int out7 = 3;
int out8 = 2;


// ============================
// Start
// ============================
void setup() {

  Serial.begin(9600);
  // init lcd
  lcd.begin(16, 4); //initialize the lcd
  lcd.backlight(); //open the backlight 

  // coinslot
  pinMode(PIN_IN, INPUT_PULLUP);

  // relay
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);
  pinMode(out5, OUTPUT);
  pinMode(out6, OUTPUT);
  pinMode(out7, OUTPUT);
  pinMode(out8, OUTPUT);

  digitalWrite(out1, HIGH);
  digitalWrite(out2, HIGH);
  digitalWrite(out3, HIGH);
  digitalWrite(out4, HIGH);
  digitalWrite(out5, HIGH);
  digitalWrite(out6, HIGH);
  digitalWrite(out7, HIGH);
  digitalWrite(out8, HIGH);

  // button
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);

  // display
  lcd.clear();
  lcd.setCursor(0, 0);        
  lcd.print("E-Bike Charger"); 
  lcd.setCursor(0, 1);        
  lcd.print("Starting..."); 
  delay(3000);
}


// ============================
// Loop
// ============================
void loop() {
  // display
  if (ctrs <= 0)
  {
    lcd.clear();
    lcd.setCursor(0, 0);        
    lcd.print("E-Bike Charger");
    lcd.setCursor(0, 1);    
    lcd.print("Insert coin..."); 
  }
  
  // input
  switchState = digitalRead(PIN_IN);
  int btnState1 = digitalRead(btn1);
  int btnState2 = digitalRead(btn2);

  // coinslot
  if (!switchState && !isCharging)
  {
    ctrs += 1;
    delay(100);
    Serial.println(ctrs);

    lcd.clear();
    lcd.setCursor(0, 0);        
    lcd.print("E-Bike Charger");
    lcd.setCursor(0, 1);    
    lcd.print("Balance: " + String(ctrs)); 
  }

  // check
  if (ctrs > 0)
  {
    // display
    if (!isCharging)
    {
      
    }
    else
    {
      if (chargingPort == 1)
      {
        lcd.clear();
        lcd.setCursor(0, 0);        
        lcd.print("E-Bike Charger");
        lcd.setCursor(0, 1);    
        lcd.print("Charging Port: #1"); 
        lcd.setCursor(0, 2);    
        lcd.print("Remaining Time:"); 
        lcd.setCursor(0, 3);    
        lcd.print(String(remainingTime) + " seconds");
        delay(1000);
        remainingTime -= 1;
      }

      if (chargingPort == 2)
      {
        lcd.clear();
        lcd.setCursor(0, 0);        
        lcd.print("E-Bike Charger");
        lcd.setCursor(0, 1);    
        lcd.print("Charging Port: #2"); 
        lcd.setCursor(0, 2);    
        lcd.print("Remaining Time:"); 
        lcd.setCursor(0, 3);    
        lcd.print(String(remainingTime) + " seconds");
        delay(1000);
        remainingTime -= 1;
      }
    }

    // button
    if (!btnState1 && !isCharging)
    {
      remainingTime = convertCount * ctrs;
      chargingPort = 1;
      isCharging = true;
      digitalWrite(out1, LOW);
      digitalWrite(out2, LOW);
    }

    // button
    if (!btnState2 && !isCharging)
    {
      remainingTime = convertCount * ctrs;
      chargingPort = 2;
      isCharging = true;
      digitalWrite(out3, LOW);
      digitalWrite(out4, LOW);
    }

    // remaining
    if (remainingTime <= 0 && isCharging)
    {
      ctrs = 0;
      isCharging = false;
      digitalWrite(out1, HIGH);
      digitalWrite(out2, HIGH);
      digitalWrite(out3, HIGH);
      digitalWrite(out4, HIGH);
      digitalWrite(out5, HIGH);
      digitalWrite(out6, HIGH);
      digitalWrite(out7, HIGH);
      digitalWrite(out8, HIGH);
    }
  }
}
