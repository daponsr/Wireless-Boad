void llegir_PWM_wifi_1(void){
  if(Serial3.available()>0){
    mirat_instant = Serial3.read();
    if(mirat_instant == 36){  //es troba un "$" (inici d'informació del PWM
      llegir_PWM_wifi();
    }
  }
}
void llegir_PWM_wifi(void){
  char aux_PWM = 36;
  int index = 1;
  String acu_1 = "";
  String s_1 = "";
  String s_2 = "";
  
  while(aux_PWM != 35){   //mentre no es trobi un "#"
    while(Serial3.available()<=0);
    aux_PWM = Serial3.read(); //llegim
    if(aux_PWM == 59){                //si es troba un ";"
        if(index == 1){
          s_1 = acu_1;
          valor_1 = conv_str_int(s_1);
          analogWrite(pinPwm, valor_1);   //escriure el valor rebut (0-255) com PWM de 8 bits pel dirver del motor
          Serial.print(valor_1);
          Serial.print(";");
          index = 0;
        }
        else{
          s_2 = acu_1;
          valor_2 = conv_str_int(s_2);
          myservo.write(valor_2);
          
          Serial.println("--****************************************************************************************");
          index = 1;
          activador2 = false; //es desactiva l'activador
        }
        acu_1 = "";
      }
      else{
        acu_1 = acu_1 + aux_PWM;
      }
  }
}
int conv_str_int(String entrat){
  int index = 0;
  int aux;
  char mirat;
  while(index < entrat.length()){
    mirat = entrat[index];                        //mirem el valor de l'index 1
    aux = aux*10 + int(mirat-48);    //fem la suma
    index += 1;
  }
  return aux;
}
