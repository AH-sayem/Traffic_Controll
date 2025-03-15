#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <Servo.h>
#define SS_PIN 10
#define RST_PIN 9
int card_pin = 6;
int ring_pin = 7;
Servo servo;
int pos = 90;
int IRSensor1 = 4;
int IRSensor2 = 2;
#define card "A3 C7 3A 14"

#define tag "D3 48 69 28"

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

byte card_ID[4]; //card UID size 4byte
byte Name1[4]={0xD3,0x48,0x69,0x28};//first UID card D3 48 69 28
byte Name2[4]={0xA3,0xC7,0x3A,0x14};//second UID card A3 C7 3A 14

//if you want the arduino to detect the cards only once
int NumbCard[2];//this array content the number of cards. in my case i have just two cards.
int j=0;        

int const RedLed=6;
int const GreenLed=5;
int const Buzzer=8;

String Name;//user name
long Number;//user number
int n ;//The number of card you want to detect (optional)  


void setup() 
{
  servo.attach(3);
  //lcd.begin();
  lcd.begin(16, 2);  // Corrected
  lcd.backlight();
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  lcd.setCursor(2, 0);
  lcd.print(" Automatic ");
  lcd.setCursor(0, 1);
  lcd.print("Toll Collection");
  servo.write(pos);
  
  pinMode(card_pin,OUTPUT);
  pinMode(ring_pin,OUTPUT); 
  pinMode(IRSensor1, INPUT);
  pinMode(IRSensor2, INPUT);


  // ************************************excell***********************

  Serial.println("CLEARSHEET");                 // clears starting at row 1
  Serial.println("LABEL,Date,Time,Name,Number");// make four columns (Date,Time,[Name:"user name"]line 48 & 52,[Number:"user number"]line 49 & 53)

  pinMode(RedLed,OUTPUT);
  pinMode(GreenLed,OUTPUT);
  pinMode(Buzzer,OUTPUT);

//**********************************end excell *****************************

}


void loop() {

int sensorStatus1 = digitalRead(IRSensor1);
int sensorStatus2 = digitalRead(IRSensor2);
if (sensorStatus1 == 0) // Check if the pin high or not
  { 
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Car Detected");
  }

  {

    // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

     //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;

  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));

//***********************************excell start ****************************************

     card_ID[i]=mfrc522.uid.uidByte[i];

       if(card_ID[i]==Name1[i]){
       Name="SAYEM";//user name
       Number=1901152;//user number
       j=0;//first number in the NumbCard array : NumbCard[j]
      }
      else if(card_ID[i]==Name2[i]){
       Name="ANOY_ZISAN";//user name
       Number=1234567;//user number
       j=1;//Second number in the NumbCard array : NumbCard[j]
      }
      else{
          digitalWrite(GreenLed,LOW);
          digitalWrite(RedLed,HIGH);
          goto cont;//go directly to line 85
     }


// ***********************************excell end ************************************
  }

  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();

if (sensorStatus2 == 0){
  if (content.substring(1) == tag) 
  {
    // Serial.println("Authorized access to this card");
    // Serial.println();
    // lcd.clear();
    // lcd.setCursor(3,0);
    // lcd.print("Bill Paid!");
    // lcd.setCursor(4,1);
    // lcd.print("Welcome!");
    // digitalWrite(6,HIGH);\
    // delay(3000);
    // digitalWrite(6,LOW);
    // for (pos = 90; pos <= 180; pos += 1) { 
    // servo.write(pos);              
    // delay(15);
    // } 
    // delay(5000);
    // for (pos = 180; pos >= 90; pos -= 1) {
    //   servo.write(pos);  
    //   delay(15);                       
    // }
    // lcd.clear();
    // lcd.setCursor(2, 0);
    // lcd.print(" Automatic ");
    // lcd.setCursor(0, 1);
    // lcd.print("Toll Collection");


    Serial.println("Authorized access to this tag");
    Serial.println();
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Not Enough");
    lcd.setCursor(5,1);
    lcd.print("Fund!");
    digitalWrite(7,HIGH);
    delay(3000);
    digitalWrite(7,LOW);
    lcd.clear();
    delay(1000);
    lcd.setCursor(2, 0);
    lcd.print(" Automatic ");
    lcd.setCursor(0, 1);
    lcd.print("Toll Collection");


    }
   
    }
  else if(content.substring(1) == card)
  {
    // Serial.println("Authorized access to this tag");
    // Serial.println();
    // lcd.clear();
    // lcd.setCursor(3,0);
    // lcd.print("Not Enough");
    // lcd.setCursor(5,1);
    // lcd.print("Fund!");
    // digitalWrite(7,HIGH);
    // delay(3000);
    // digitalWrite(7,LOW);
    // lcd.clear();
    // delay(1000);
    // lcd.setCursor(2, 0);
    // lcd.print(" Automatic ");
    // lcd.setCursor(0, 1);
    // lcd.print("Toll Collection");

    Serial.println("Authorized access to this card");
    Serial.println();
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Bill Paid!");
    lcd.setCursor(4,1);
    lcd.print("Welcome!");
    digitalWrite(6,HIGH);\
    delay(3000);
    digitalWrite(6,LOW);
    for (pos = 90; pos <= 180; pos += 1) { 
    servo.write(pos);              
    delay(15);
    } 
    delay(5000);
    for (pos = 180; pos >= 90; pos -= 1) {
      servo.write(pos);  
      delay(15);                       
    }
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print(" Automatic ");
    lcd.setCursor(0, 1);
    lcd.print("Toll Collection");


  }


else if(content.substring(1) == tag)
  {
    Serial.println("Authorized access to this tag");
    Serial.println();
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Not Enough");
    lcd.setCursor(5,1);
    lcd.print("Fund!");
    digitalWrite(7,HIGH);
    delay(3000);
    digitalWrite(7,LOW);
    lcd.clear();
    delay(1000);
    lcd.setCursor(2, 0);
    lcd.print(" Automatic ");
    lcd.setCursor(0, 1);
    lcd.print("Toll Collection");

    // Serial.println("Authorized access to this card");
    // Serial.println();
    // lcd.clear();
    // lcd.setCursor(3,0);
    // lcd.print("Bill Paid!");
    // lcd.setCursor(4,1);
    // lcd.print("Welcome!");
    // digitalWrite(6,HIGH);\
    // delay(3000);
    // digitalWrite(6,LOW);
    // for (pos = 90; pos <= 180; pos += 1) { 
    // servo.write(pos);              
    // delay(15);
    // } 
    // delay(5000);
    // for (pos = 180; pos >= 90; pos -= 1) {
    //   servo.write(pos);  
    //   delay(15);                       
    // }
    // lcd.clear();
    // lcd.setCursor(2, 0);
    // lcd.print(" Automatic ");
    // lcd.setCursor(0, 1);
    // lcd.print("Toll Collection");


  }


 else   
 {
    Serial.println(" Access denied");
    delay(2000);
  }


  }



// ********************************excell ******************************************

      if(NumbCard[j] == 1){//to check if the card already detect
      NumbCard[j] = 1;//put 1 in the NumbCard array : NumbCard[j]={1,1} to let the arduino know if the card was detecting 
      n++;//(optional)
      Serial.print("DATA,DATE,TIME," + Name);//send the Name to excel
      Serial.print(",");
      Serial.println(Number); //send the Number to excel
      digitalWrite(GreenLed,HIGH);
      digitalWrite(RedLed,LOW);
      digitalWrite(Buzzer,HIGH);
      delay(30);
      digitalWrite(Buzzer,LOW);
      Serial.println("SAVEWORKBOOKAS,Names/WorkNames");
      }
      else{
      NumbCard[j] = 1;//put 1 in the NumbCard array : NumbCard[j]={1,1} to let the arduino know if the card was detecting 
      n++;//(optional)
      Serial.print("DATA,DATE,TIME," + Name);//send the Name to excel
      Serial.print(",");
      Serial.println(Number); //send the Number to excel
      digitalWrite(GreenLed,HIGH);
      digitalWrite(RedLed,LOW);
      digitalWrite(Buzzer,HIGH);
      delay(30);
      digitalWrite(Buzzer,LOW);
      Serial.println("SAVEWORKBOOKAS,Names/WorkNames");
      }
      delay(1000);




// ********************************end excell ****************************************



//************************************excell****************************************

cont:
delay(2000);
digitalWrite(GreenLed,LOW);
digitalWrite(RedLed,LOW);


//************************************excell**************************************

}







