

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
Adafruit_MPU6050 mpu;


#include <arduino-timer.h>
auto timer = timer_create_default();

//////////////////


//_________________________________________________________________________

// Humidity Sensor
#include <DHT.h>
#define DHTBOX 29
#define DHTMOTOR 31
#define DHTTYPE DHT11
 // Inicializamos el sensor DHT11
DHT dht1(DHTBOX, DHTTYPE);
DHT dht2(DHTMOTOR, DHTTYPE);
//__________________________________________________________________________

//Water Level
int AGUABOX = 0;
int AGUAMOTOR = 1; 
//__________________________________________________________________________

//SERVO
#include <Servo.h>
Servo myservo;  // crea el objeto servo
int pinServo = 27;
int pos = 0;    // posicion del servo
//__________________________________________________________________________

//DRIVER MOTOR 
const int pinPwm = 3;
const int pinDir = 2;

boolean activador = false;

//__________________________________________________________________________
//__________________________________________________________________________

/////////////////


String estat_gps = "V";
String lati = "non";
String lati_d = "non";
String longi = "non";
String longi_d = "non";
boolean habilitador1 = true;    
boolean activador2 = false;
////
String info_accelerometre = "";
String info_humedad = "";
String info_nivell = "";
String info_gps = "";
String informacio_a_enviar = "";


////


int valor_1 = 0;  //pel motor
int valor_2 = 0;  //pel servo
boolean ac_gps_1 = true;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
  Serial3.begin(115200);

  Serial.println("------------------------------------------------------------------------");

  pinMode(49, OUTPUT);
  pinMode(47, OUTPUT);
  digitalWrite(49, LOW);
  digitalWrite(47, LOW);
  
  confi_acc();
  dht1.begin();
  dht2.begin();
  llegir_gps();
  creacio_AP(); 
  digitalWrite(47, HIGH);
  espera_connec_disp(1);
  enviar_wifi("0", "PROVA");
  Serial.println("ENVIAT");
  
  pinMode(pinPwm, OUTPUT);

  myservo.attach(pinServo);

  
  pinMode(AGUABOX, INPUT);
  pinMode(AGUAMOTOR,INPUT);
  timer.every(1000, gestio_lectures);
 
  ac_gps_1 = true;
}
String a_enviar = "";
char mirat_instant = 0;
void loop() {
  timer.tick();
  if(Serial3.available()>0){
    mirat_instant = Serial3.read();
    if(mirat_instant == 36){
      llegir_PWM_wifi();
    }
  }  
  
}
