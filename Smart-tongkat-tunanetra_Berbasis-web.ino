#include <wire.h>
#include <LiquidCrystal_I2c.h>

//lcd
LiquidCrystal_I2c lcd(0x27, 16, 2);

//pin sensor ultra sonic kiri



//pin sensor ultra sonic depan


//pin sensor ultra sonic kanan


//buzzer

//led
const int ledpin = 9;


//status mengecek mode tersesat
bool sedangTersesat = false;


void setup() {

//sensor ultra sonic (depan,kiri dan kanan)




//buzzer

//led pin
pinMode(ledpin, OUTPUT);

//Inisial lcd
lcd.init();
lcd.backlight();

//serial begin
Serial.begin(19200);

//tampilan text lcd
lcd.setCursor(0, 0);
lcd.print("MAAF...     (._.)");
lcd.setCursor(0, 1);
lcd.print("SAYA TUNANETRA  ");
}

void loop() {
//interupsi Serial Monitor (Jika diketik angka 4 dari Web)
  if (Serial.available() > 0) {
    char dataMasuk = Serial.read();
    
    if (dataMasuk == '4') {
      sedangTersesat = true;
      
      // Matikan buzzer sementara agar tidak mengganggu proses interupsi
      digitalWrite(buzzer, LOW); 
      digitalWrite(ledPin, LOW);
      
      // Mengubah tampilan LCD menjadi SEDANG TERSESAT
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SEDANG TERSESAT ");
      lcd.setCursor(0, 1);
      lcd.print("TOLONG...  (T_T)");

      //Lampu LED Kedip-Kedip jika diketik angka 4
      for (int i = 0; i < 5; i++) {
        digitalWrite(ledPin, HIGH); 
        delay(500); 
        digitalWrite(ledPin, LOW);  
        delay(500); 

     // Selesai kedip, kembalikan ke tulisan semula
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("MAAF...    (._.)");
      lcd.setCursor(0, 1);
      lcd.print("SAYA TUNANETRA  ");
      
      //membersihkan sisa data serial yang menumpuk selama proses kedipan
      while(Serial.available() > 0) {
        Serial.read();
      }
      
      sedangTersesat = false;                
      }
}
