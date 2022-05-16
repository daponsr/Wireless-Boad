void espera_connec_disp(int num_esp){
  Serial.println("Esperant acció per part del PC");
  int cont_disp = 0;
  char mirat_disp = 0;
  String acu_disp = "";
  String llista_i[10] = {"nan","nan","nan","nan","nan","nan","nan","nan","nan","nan"};
  String llista_d[10] = {"non","non","non","non","non","non","non","non","non","non"};
  while(cont_disp < num_esp){
    if(Serial3.available()>0){
      mirat_disp = Serial3.read();
      if(mirat_disp == 43){ //symbor "+"
        acu_disp = "+"; //to start
            // +IPD,2,2:PC o  +IPD,2,2:MV
        while(mirat_disp != 58){
          if(Serial3.available()>0){
            mirat_disp = Serial3.read();
            acu_disp += mirat_disp;
          }
        }
        
        llista_d[cont_disp] = acu_disp[5];
        Serial.print("Nombre disp: ");
        Serial.println(llista_d[cont_disp]);
        digitalWrite(49, HIGH);
        acu_disp = "";
        
        while(mirat_disp != 45){
          if(Serial3.available()>0){
            mirat_disp = Serial3.read();
            if(mirat_disp != 45){
              acu_disp += mirat_disp;
            }
          }
        }
        llista_i[cont_disp] = acu_disp;
        Serial.print("Identificador: ");
        Serial.println(llista_i[cont_disp]);
        cont_disp += 1;
      }
    }
  }
  //enviem una resposta de confirmació
  Serial.println("FINI");
}

void enviar_wifi(String dire_1, String a_enviar){
  Serial.println("ENTRAT A ENVIAR");
  String aux_per_enviar = "";
  char mirat_per_enviar = 0;
  String aux_per_enviar_2 = "";
  int longitut_aux = a_enviar.length();
  boolean correcte_tot = true;
  Serial3.print("AT+CIPSEND=" + dire_1 + "," + String(a_enviar.length()) + "\r\n");
  Serial.println("ESPERANT K");
  while(mirat_per_enviar != 75){
    if(Serial3.available()>0){
      mirat_per_enviar = Serial3.read();
    }
    Serial.write(mirat_per_enviar);
    if(mirat_per_enviar == 82){
      Serial.println("ERROR - DIRECCIÓ NO CORRECTE");
      digitalWrite(49, LOW);
      espera_connec_disp(1);
      mirat_per_enviar = 75;
      correcte_tot = false;
    }
  }
  Serial.println("ESPERANT salt de linia");
  while(Serial3.read() != 10);
  if(correcte_tot){
    Serial.println("tot correcte");
    Serial3.print(a_enviar);
    while(Serial3.read() != 75); 
    while(Serial3.read() != 10); 
    Serial.print("ENVIAT: ");
    Serial.println(a_enviar);
  }
}
