#include <wire.h>
#include <LiquidCrystal_I2c.h>

//lcd
LiquidCrystal_I2c lcd(0x27, 16, 2);

//pin sensor ultra sonic kiri
const int trigKiri = 2;
const int echoKiri = 3;

//pin sensor ultra sonic depan


//pin sensor ultra sonic kanan
const int trigKanan = 6;
const int echoKanan = 7;


//buzzer

//led
const int ledpin = 9;

// Jarak maksimal deteksi rintangan (dalam centimeter)
const int jarakAman = 60;

// status mengecek mode tersesat
bool sedangTersesat = false;

// Variabel penampung waktu membatasi pengiriman data serial
unsigned long waktuLamaKirim = 0;


void setup() {

//sensor ultra sonic (depan,kiri dan kanan)

//Sensor ultra sonic (kiri)
pinMode(trigKiri,OUTPUT);
pinMode(echoKiri,INPUT); 

// sensor ultra sonic (kanan)
pinMode (trigKanan,OUTPUT);
pinMode (echoKanan,INPUT);



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
      // jalankan logika sensor ultrra sonic
      if (sedangtersesat == false) {
        // baca jarak dari sensor
        long jarakKiri = bacaJarak(trigKiri,echoKiri);
        long jarakKanan = bacaJarak(trigKanan,echoKanan);

        // cari jarak terdekat dari ke 3 arah
        long JarakTerdekat = JarakDepan;
        if (JarakKiri < JarakTerdekat) jarakTerdekat = JarakKiri;
        if (JarakKanan < JarakTerdekat) jarakTerdekat = JarakKanan;

        // batasi pengiriman serial setiap (5 detik)
        if (millis() - waktuLamaKirim >= 500) {
          serial.println(JarakTerdekat);
          waktuLamaKirim = millis();
          }
          
        }
