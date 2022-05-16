int contador_lest_lectures = 0;

bool gestio_lectures(void*){
  contador_lest_lectures += 1;
  Serial.println(contador_lest_lectures); 
  if(ac_gps_1){
    Serial.println("##########DE CALIBRACIÓ");
    delay(1000);
    llegir_gps();
    Serial.println("------------------------------------FI CALIBRACIO");
    delay(1000);
    ac_gps_1 = false;
    contador_lest_lectures = 0;
  }
  if(contador_lest_lectures == 1){
    contador_lest_lectures = 0;
    Serial.println("GPS--");
    llegir_gps();
    info_gps = ";" + estat_gps + ";" + lati + ";" + lati_d + ";" + longi + ";" + longi_d;
    Serial.println("--GPS");
  }

  fer_lectures();
  informacio_a_enviar = info_accelerometre + info_gps + info_humedad + info_nivell + ";";
  enviar_wifi("0",informacio_a_enviar);
  
  return true;
}

void fer_lectures(void){
  Serial.println("LECTURA");
  ace_gir();  //crida a fer la lectura
  humedad();    //llegir humitat
  agua();

}
