#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "main.h"

const char* ssid = "SSID DA REDE"; const char* password = "PASSWORD";

//CASO OCORRA PROBLEMAS COM A PORTA 80, UTILIZE OUTRA (EX:8082,8089) E A CHAMADA DA URL FICARÁ IP:PORTA(EX: 192.168.0.15:8082) 
WiFiServer server(80); 
 
uint8_t txdata[2];

bool ledcom=0;

uint8_t comando; 

void setup() {

Serial.begin(9600); 

    delay(10); 
  
    Serial.print("Iniciando comunicação ssid..."); 
    Serial.print(ssid); 
  
    WiFi.begin(ssid, password); 
  
    pinMode(BUILTIN_LED,OUTPUT);

    //ENQUANTO STATUS FOR DIFERENTE DE CONECTADO
    while (WiFi.status() != WL_CONNECTED) { 
      delay(500); 
      Serial.print("."); 
    }

    Serial.println("Conectado!!!");

    server.begin(); //INICIA O SERVIDOR PARA RECEBER DADOS NA PORTA DEFINIDA EM "WiFiServer server(porta);"
    Serial.println("Servidor iniciado"); 
    
    Serial.print("IP para se conectar ao NodeMCU: "); 
    Serial.print("http://"); 
    Serial.println(WiFi.localIP()); 

    
}

/*
* Envia e Recebe dados da porta serial 0, comunicando com o Arduino
* uses UART0, which is mapped to pins GPIO1 (TX) and GPIO3 (RX). 
*/
void comunicaarduino(){
    uint8_t readbyte;
    
    //envia mensagem para arduino
    txdata[0] = comando;
    Serial.write(txdata[0]);

    //espera resposta do arduino 
    if (Serial.available() ) {
      readbyte = Serial.read();
      if (readbyte == txdata[0]){
          //pisca led falando que comunicacao esta OK
        ledcom = !ledcom;
        digitalWrite(LED_BUILTIN, ledcom); 
      }
    }

}

void loop() {
    WiFiClient client = server.available(); //VERIFICA SE ALGUM CLIENTE ESTÁ CONECTADO NO SERVIDOR

    if (!client) { //SE NÃO EXISTIR CLIENTE CONECTADO, FAZ
      return; //REEXECUTA O PROCESSO ATÉ QUE ALGUM CLIENTE SE CONECTE AO SERVIDOR
    }
  
    while(client.available() == 0){ //ENQUANTO CLIENTE ESTIVER CONECTADO
        delay(1); //INTERVALO DE 1 MILISEGUNDO
    }

    //Pagina HTML - Inicio
    String req = client.readStringUntil('\r'); //FAZ A LEITURA DA PRIMEIRA LINHA DA REQUISIÇÃO
    client.flush(); //AGUARDA ATÉ QUE TODOS OS DADOS DE SAÍDA SEJAM ENVIADOS AO CLIENTE
    
    client.println("HTTP/1.1 200 OK"); 
    client.println("Content-Type: text/html"); 
    client.println("");
    client.println("<!DOCTYPE HTML>"); 
    client.println("<html>"); 
    client.println("<h1><center>Teste Renato Fernandes!</center></h1>"); 
    client.println("<center><font size='5'>Exemplo Controlando LED !</center>"); 
    client.println("<p><center><a href=\"BTDireita\"><button>DIREITA</button></a></p>"); 
    client.println("<p><a href=\"BTEsquerda\"><button>ESQUERDA</button></a></p>"); 
    client.println("<p><a href=\"BTDescer\"><button>DESCER</button></a></p>"); 
    client.println("<p><a href=\"BTSubir\"><button>SUBIR</button></a></p>"); 
    client.println("</html>"); 
    client.flush();
    //FECHA A TAG "html"

    //verifica se algum botao foi pressionado 
    if (req.indexOf("BTDireita") !=-1)
      comando = (uint8_t) CMD_DIR;
    else if (req.indexOf("BTEsquerda") !=-1)
      comando = (uint8_t)  CMD_ESQ;
    else if (req.indexOf("BTDescer") !=-1)
      comando = (uint8_t) CMD_CIMA;
    else if (req.indexOf("BTSubir") !=-1)
      comando = (uint8_t) CMD_BAIXO;
    else
      comando = (uint8_t) CMD_NENHUM;
        
    client.stop();

    //Comunicacao com Arduino 
    comunicaarduino();

    delay(100);


}