WEB_ARDUINO_MCU
Este projeto usa a placa NodeMCU (ESP8266) para comunicacao wifi com o arduino
Este projeto é o codigo do Servidor Web rodando no NodeMCU.
Basicamente existe tres 4 botoes na web que pode ser usado para controle de um carrinho usando o arduino.

O NodeMCU deve ser ligado ao arduino pela UART0 do NodeMCU (Pinos GPIO2-TX e GPIO3-RX) 
Este codigo esta enviando somente 1 byte com o comando (1 a 4) para o Arduino e recebe o mesmo comando de volta como resposta.

Atencao: Alem deste codigo deve ser feito um codigo no arduino para comunicar com esta placa.


O codigo foi obtido no seguinte link da internet: 
https://randomnerdtutorials.com/esp8266-nodemcu-http-get-post-arduino/
e os videos no youtube de @EletronworldBr 



