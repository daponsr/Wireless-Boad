void llegir_gps(void){
  habilitador1 = true;     
  Serial.println("ENTRAT a la mesura del GPS");
  while(habilitador1 == true){
    llegir_PWM_wifi_1();
    trobar_com();
  }
}

void trobar_com(void){    
  char act = 0;
  String acu = "";
  if(Serial2.available()>0){
        act = Serial2.read();
        //Serial.write(act);
        if(act == 36 ){ //un $
          acu = "";
          while(act != 44 ) {

            acu += act;     
            while(Serial2.available()<=0);
            act = Serial2.read();
          }
          if(acu == "$GNRMC"){
            Serial.println("¬¬¬¬¬¬¬¬¬¬¬¬BO");
            while(act != 10){
              acu += act;
              while(Serial2.available()<=0);
              act = Serial2.read();
              Serial.write(act);
            }
            desc_string_gps(acu);
            habilitador1 = false;
          }
          else if(acu == "$PMTK010" |acu == "$PMTK011"){
            Serial.println("&&&&&&&&&&&&&&DOLENT");
            acu = "";
            act = 0;
            estat_gps = "NOP";
            habilitador1 = false;
          }
        }
      }
}


void desc_string_gps(String a_mir){   
  //Serial.println("DESXIIIIIIIIIF");
  int cont1 = 0;  //comptador
  int index_c = 0;
  String mir_act = "";
  String form_act = ""; 
  while(cont1 <= 6){
    mir_act = a_mir[index_c];
    if(mir_act == ","){
      if(cont1 == 2){       //estat
        estat_gps = form_act;
        //Serial.print("Estat: ");
        //Serial.println(estat_gps);
      }
      else if(cont1 == 3){  //lati
        if(estat_gps == "A"){
          lati = form_act;
        }
        //Serial.print("Lati: ");
        //Serial.println(lati);
      }
      else if(cont1 == 4){  //lati_d
        if(estat_gps == "A"){
          lati_d = form_act;
        }

      }
      else if(cont1 == 5){  //longi
        if(estat_gps == "A"){
          longi = form_act;
        }
      }
      else if(cont1 == 6){                 
        if(estat_gps == "A"){
          longi_d = form_act;
        }
        //Serial.print("Longi D: ");
        //Serial.println(longi_d);
      }
      cont1 += 1;
      //Serial.print("Comptador: ");
      //Serial.println(cont1);
      form_act = "";
    }
    else{
      form_act += mir_act;
      //Serial.println(form_act);
    }
    
    if(index_c < a_mir.length()){
      index_c += 1;
    }
  }
}
