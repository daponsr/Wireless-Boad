void espera_connec_disp(int num_esp){   //num es son els dispositius que s'esperen
  Serial.println("Esperant acció per part del PC");
  int cont_disp = 0;
  char mirat_disp = 0;
  String acu_disp = "";
  String llista_i[10] = {"nan","nan","nan","nan","nan","nan","nan","nan","nan","nan"};    //amb l'identificador
  String llista_d[10] = {"non","non","non","non","non","non","non","non","non","non"};    //amb la direcció
  while(cont_disp < num_esp){
    if(Serial3.available()>0){
      mirat_disp = Serial3.read();
      if(mirat_disp == 43){ //si trobem el simbol "+"
        acu_disp = "+"; //per començar amb el "+"
            // +IPD,2,2:PC o  +IPD,2,2:MV     es busquen els identificadors
        while(mirat_disp != 58){  //quedem aquí fins trobar ":"
          if(Serial3.available()>0){
            mirat_disp = Serial3.read();
            acu_disp += mirat_disp;
          }
        }
        
        llista_d[cont_disp] = acu_disp[5];  //guardem el numero
        Serial.print("Nombre disp: ");
        Serial.println(llista_d[cont_disp]);
        digitalWrite(49, HIGH);
        acu_disp = "";
        
        while(mirat_disp != 45){            //esperem a trobar un "-"
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

void enviar_wifi(String dire_1, String a_enviar){   //dire_1 és la direcció (1,2,4,5)
  Serial.println("ENTRAT A ENVIAR");
  String aux_per_enviar = "";
  char mirat_per_enviar = 0;
  String aux_per_enviar_2 = "";
  int longitut_aux = a_enviar.length();
  boolean correcte_tot = true;
  Serial3.print("AT+CIPSEND=" + dire_1 + "," + String(a_enviar.length()) + "\r\n");
  Serial.println("ESPERANT K");
  while(mirat_per_enviar != 75){  //esperem a rebre una K
    if(Serial3.available()>0){
      mirat_per_enviar = Serial3.read();
    }
    Serial.write(mirat_per_enviar);
    if(mirat_per_enviar == 82){   //si es troba una R vol dir error
      Serial.println("ERROR - DIRECCIÓ NO CORRECTE");
      digitalWrite(49, LOW);
      espera_connec_disp(1);
      mirat_per_enviar = 75;
      correcte_tot = false;
    }
  }
  Serial.println("ESPERANT salt de linia");
  while(Serial3.read() != 10);  //esperem a rebre una SALT DE LINIA
  if(correcte_tot){
    Serial.println("tot correcte");
    Serial3.print(a_enviar);
    while(Serial3.read() != 75);  //esperem a rebre una K
    while(Serial3.read() != 10);  //esperem a rebre una SALT DE LINIA
    Serial.print("ENVIAT: ");
    Serial.println(a_enviar);
  }
}
