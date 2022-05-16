


  //fin programa SERVOMOTOR
//__________________________________________________________________________
float h1 = 0.0;
float h2 = 0.0;
void humedad (){
  // Leemos la humedad relativa
  h1 = dht1.readHumidity();   //pin 29
  h2 = dht2.readHumidity();   //pin 31
  info_humedad = ";" + String(h1) + ";" + String(h2);
  Serial.println("HUMITAT 1: " + String(h1));
  Serial.println("HUMITAT 2: " + String(h2));
}
//__________________________________________________________________________
int nivell_box = 0;
int nivell_mot = 0;
void agua(){
  //SENSOR DE AGUA 
  nivell_box = analogRead(AGUABOX);
  Serial.println("NIVELL 1:" + String(nivell_box));
  nivell_mot = analogRead(AGUAMOTOR);
  Serial.println("NIVELL 2:" + String(nivell_mot));
  info_nivell = ";" + String(nivell_box) + ";" + String(nivell_mot);
}
//__________________________________________________________________________

void ace_gir(){
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  info_accelerometre =  ";" + String(a.acceleration.x) + ";" + String(a.acceleration.y) + ";" + String(a.acceleration.z) + ";" + String(g.gyro.x) + ";" + String(g.gyro.y) + ";" + String(g.gyro.z) + ";" + String(temp.temperature);
}
//__________________________________________________________________________
/*
//MOTOR DRIVER
void driver(){
  if(Serial.available() > 0) //Detecta si hay alguna entrada por serial
   {
      iSpeed = Serial.parseInt();
      Serial.println(iSpeed);
    if (iSpeed >= 0) {
     analogWrite(pinPwm, iSpeed);
    digitalWrite(pinDir, LOW);
   }
  
}
}
*/
//__________________________________________________________________________
