#include <wire.h>
#include <LiquidCrystal_I2c.h>

//lcd
LiquidCrystal_I2c lcd(0x27, 16, 2);

//pin sensor ultra sonic kiri
const int trigKiri = 2;
const int echoKiri = 3;

//pin sensor ultra sonic depan
const int trigDepan = 4;
const int echoDepan = 5;


//pin sensor ultra sonic kanan
const int trigKanan = 6;
const int echoKanan = 7;


//buzzer
const int buzzer = 8;

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

// sensor ultra sonic (depan)
pinMode(trigDepan,OUTPUT);
pinMode(echoDepan,INPUT); 

// sensor ultra sonic (kanan)
pinMode (trigKanan,OUTPUT);
pinMode (echoKanan,INPUT);

//buzzer
pinMode(buzzer, OUTPUT);

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
          //BUNYI BUZZER & LED BERDASARKAN JARAK SENSOR 
          if(jarakTerdekat > 0 && jarakTerdekat <= jarakAman){

            //Skenario 1:SANGAT BAHAYA (30 cm) Bunyi Panjang
            if(jarakTerdekat <=30){
              digitalWrite(buzzer, HIGH);
              digitalWrite(ledPin, HIGH);
              delay(10);
            }
           //Skenario 2: PERINGATAN(31 cm sampai 60 cm) Bunyi Putus Putus
            else {
              int jedaBunyi = map(jarakTerdekat, 31, jarakAman, 30, 300);
              if (jedaBunyi < 30) jedaBunyi = 30;

              digitalWrite(buzzer, HIGH);
              digitalWrite(ledPin, HIGH);
              delay(50);

              digitalWrite(buzzer, LOW);
              digitalWrite(ledPin, LOW);
              delay(jedaBunyi); 
            }
            
          } else {
            //Skenario 3: AMAN (> 60cm )Semua fungsi deteksi mati 
             digitalWrite(buzzer, LOW);
              digitalWrite(ledPin, LOW);
              delay(20); 
          }
         }  
       }
       
         //Fungsi khusus menghitung jarak sensor HC-SR04
         long bacaJarak(int trigPin, int echoPin) {
          digitalWrite(trigPin, LOW);
          delayMicroseconds(2);
          digitalWrite(trigPin, HIGH);
          delayMicroseconds(10);
          digitalWrite(trigPin, LOW);

          long durasi = pulseIn(echoPin, HIGH, 20000);
          long cm = durasi * 0.034 / 2;

          if (cm == 0 || cm > 200) return 200;
          return cm;          
        }
