//funció per enviar la informació
#define DEBUG true

String sendData(String command, const int timeout, boolean debug){
  String response = "";
  Serial3.print(command);//enviar el comandament
  long int time = millis();
  while( (time+timeout) > millis()){  //esperar el temps
    while(Serial3.available()){
      char c = Serial3.read(); // llegir el que es troba dins els temps de TIMEOUT
      response+=c;
    }  
  }
                
  if(debug){
    Serial.print(response); //mostra la resposta
    }
  return response;          //retorna en format string el que es RESPON el ESP
}


void creacio_AP(void){
  Serial.println("CREACIO AP");
  sendData("AT\r\n",500,DEBUG);            //comandament de prova
  sendData("AT+RST\r\n",3000,DEBUG);        //fer un RST
  sendData("AT+CWMODE=3\r\n",3000,DEBUG);   //posar en mode 1 (client)
  sendData("AT+CWSAP=\"ESP_M12\",\"1234abcd\",1,4\r\n",10000,DEBUG); //ES POSA EL 10000 perque tarda en connectar-se al wifi
  sendData("AT+CIPMUX=1\r\n",2000,DEBUG);   //habilitar connexions múltiples
  sendData("AT+CIPSERVER=1,80\r\n",2000,DEBUG); //iniciar un servidor al port 80
  sendData("AT+CWDHCP_CUR=0,1\r\n",2000,DEBUG); //PER HABILITAR QUE ES PUGUIN CONECTAR
  sendData("AT+CIFSR\r\n",2000,DEBUG);          //consultar la IP
  sendData("AT+CWLIF\r\n",2000,DEBUG);          //consultar la IP
  Serial.println("---------PREPARAT----------");
}


void conect_wifi_casa(void){
  Serial.println("CONNEXIO WIFI CASA");
  sendData("AT\r\n",2000,DEBUG);            //comandament de prova
  sendData("AT+RESTORE\r\n",3000,DEBUG);        //fer un RST
  sendData("AT+CWMODE=1\r\n",3000,DEBUG);   //posar en mode 1 (client)
  sendData("AT+CWJAP=\"MOVISTAR_DBF2\",\"9F3B123885A645C67E77\"\r\n",10000,DEBUG); //ES POSA EL 10000 perque tarda en connectar-se al wifi
  sendData("AT+CIPMUX=1\r\n",2000,DEBUG);   //habilitar connexions múltiples
  sendData("AT+CIPSERVER=1,80\r\n",2000,DEBUG); //iniciar un servidor al port 80
  sendData("AT+CIFSR\r\n",2000,DEBUG);          //consultar la IP
  sendData("AT+CWLIF\r\n",2000,DEBUG);           //mirar quehi ha conectat
  Serial.println("-------------PREPARAT-------------");
}
