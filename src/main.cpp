#include "Arduino.h"
#include "ESP8266WiFi.h"

const char* ssid = "Rede udi"; const char* password = "1j4b7i2g$4";
//const char* ssid = "SALA3N320"; const char* password = "1j4b7i2g$3";

//CASO OCORRA PROBLEMAS COM A PORTA 80, UTILIZE OUTRA (EX:8082,8089) E A CHAMADA DA URL FICARÁ IP:PORTA(EX: 192.168.0.15:8082) 
WiFiServer server(80); 
 
void setup() {
Serial.begin(9600); 
    delay(10); 
  
    Serial.print("Conectando a "); 
    Serial.print(ssid); 
  
    WiFi.begin(ssid, password); 
  
    while (WiFi.status() != WL_CONNECTED) { //ENQUANTO STATUS FOR DIFERENTE DE CONECTADO
      delay(500); //INTERVALO DE 500 MILISEGUNDOS
      Serial.print("."); //ESCREVE O CARACTER NA SERIAL
    }

    Serial.print("Conectado a rede sem fio "); //ESCREVE O TEXTO NA SERIAL
    Serial.println(ssid); //ESCREVE O NOME DA REDE NA SERIAL

    server.begin(); //INICIA O SERVIDOR PARA RECEBER DADOS NA PORTA DEFINIDA EM "WiFiServer server(porta);"
    Serial.println("Servidor iniciado"); //ESCREVE O TEXTO NA SERIAL
    
    Serial.print("IP para se conectar ao NodeMCU: "); //ESCREVE O TEXTO NA SERIAL
    Serial.print("http://"); //ESCREVE O TEXTO NA SERIAL
    Serial.println(WiFi.localIP()); //ESCREVE NA SERIAL O IP RECEBIDO DENTRO DA REDE SEM FIO (O IP NESSA PRÁTICA É RECEBIDO DE FORMA AUTOMÁTICA)
}


void loop() {
    WiFiClient client = server.available(); //VERIFICA SE ALGUM CLIENTE ESTÁ CONECTADO NO SERVIDOR

    if (!client) { //SE NÃO EXISTIR CLIENTE CONECTADO, FAZ
      return; //REEXECUTA O PROCESSO ATÉ QUE ALGUM CLIENTE SE CONECTE AO SERVIDOR
    }
  
    while(client.available() == 0){ //ENQUANTO CLIENTE ESTIVER CONECTADO
        delay(1); //INTERVALO DE 1 MILISEGUNDO
    }

    String req = client.readStringUntil('\r'); //FAZ A LEITURA DA PRIMEIRA LINHA DA REQUISIÇÃO
    client.flush(); //AGUARDA ATÉ QUE TODOS OS DADOS DE SAÍDA SEJAM ENVIADOS AO CLIENTE
    

    client.println("HTTP/1.1 200 OK"); //ESCREVE PARA O CLIENTE A VERSÃO DO HTTP
    client.println("Content-Type: text/html"); //ESCREVE PARA O CLIENTE O TIPO DE CONTEÚDO(texto/html)
    client.println("");
    client.println("<!DOCTYPE HTML>"); //INFORMA AO NAVEGADOR A ESPECIFICAÇÃO DO HTML
    client.println("<html>"); //ABRE A TAG "html"
    client.println("<h1><center>Teste Renato Fernandes!</center></h1>"); 
    client.println("<center><font size='5'>Exemplo Controlando LED !</center>"); 
    client.println("<p><a href=\"BTDireita\"><button>DIREITA</button></a></p>"); 
    client.println("<p><a href=\"BTEsquerda\"><button>ESQUERDA</button></a></p>"); 
    client.println("<p><a href=\"BTDescer\"><button>DESCER</button></a></p>"); 
    client.println("<p><a href=\"BTSubir\"><button>SUBIR</button></a></p>"); 
    client.println("</html>"); //FECHA A TAG "html"
    client.flush();

    if (req.indexOf("BTDireita") !=-1){
      Serial.println("Mover Direita");
    }
    else if (req.indexOf("BTEsquerda") !=-1){
      Serial.println("Mover Esquerda");
    }
    else if (req.indexOf("BTDescer") !=-1){
      Serial.println("Mover Baixo");
    }
    else if (req.indexOf("BTSubir") !=-1){
      Serial.println("Mover Cima");
    }
        
    delay(1); //INTERVALO DE 1 MILISEGUNDO
    client.stop();
}