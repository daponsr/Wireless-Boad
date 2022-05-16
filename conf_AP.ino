
#define DEBUG true

String sendData(String command, const int timeout, boolean debug){
  String response = "";
  Serial3.print(command);
  long int time = millis();
  while( (time+timeout) > millis()){
    while(Serial3.available()){
      char c = Serial3.read();
      response+=c;
    }  
  }
                
  if(debug){
    Serial.print(response);
    }
  return response;   
}


void creacio_AP(void){
  Serial.println("CREACIO AP");
  sendData("AT\r\n",500,DEBUG);            
  sendData("AT+RST\r\n",3000,DEBUG);    
  sendData("AT+CWMODE=3\r\n",3000,DEBUG);   
  sendData("AT+CWSAP=\"ESP_M12\",\"1234abcd\",1,4\r\n",10000,DEBUG);
  sendData("AT+CIPMUX=1\r\n",2000,DEBUG); 
  sendData("AT+CIPSERVER=1,80\r\n",2000,DEBUG);
  sendData("AT+CWDHCP_CUR=0,1\r\n",2000,DEBUG); 
  sendData("AT+CIFSR\r\n",2000,DEBUG);      
  sendData("AT+CWLIF\r\n",2000,DEBUG);    
  Serial.println("---------PREPARAT----------");
}


void conect_wifi_casa(void){
  Serial.println("CONNEXIO WIFI CASA");
  sendData("AT\r\n",2000,DEBUG);      
  sendData("AT+RESTORE\r\n",3000,DEBUG);      
  sendData("AT+CWMODE=1\r\n",3000,DEBUG);  
  sendData("AT+CWJAP=\"MOVISTAR_DBF2\",\"9F3B123885A645C67E77\"\r\n",10000,DEBUG);
  sendData("AT+CIPMUX=1\r\n",2000,DEBUG);   //habilitar connexions múltiples
  sendData("AT+CIPSERVER=1,80\r\n",2000,DEBUG);
  sendData("AT+CIFSR\r\n",2000,DEBUG);
  sendData("AT+CWLIF\r\n",2000,DEBUG);
  Serial.println("-------------PREPARAT-------------");
}
