#include <SPI.h> //Inclui a biblioteca SPI.h
#include <Ethernet.h> //Inclui a biblioteca Ethernet.h

// Configurações para o Ethernet Shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x83, 0xEA }; // Entre com o valor do MAC

IPAddress ip(192,168,0,16); // Configure um IP válido 
byte gateway[] = { 192 , 168, 0, 1 }; //Entre com o IP do Computador onde a Câmera esta instalada
byte subnet[] = { 255, 255, 255, 0 }; //Entre com a Máskara de Subrede
EthernetServer server(80); //Inicializa a biblioteca EthernetServer com os valores de IP acima citados e configura a porta de acesso(80)

void setup()
{
  Ethernet.begin(mac, ip);// Inicializa o Server com o IP e Mac atribuido acima
}



void loop()
{
  EthernetClient client = server.available();// Verifica se tem alguém conectado

  if (client)
  {

    boolean currentLineIsBlank = true; // A requisição HTTP termina com uma linha em branco Indica o fim da linha
    String valPag;

    while (client.connected())
    {

      if (client.available())
      {

        char c = client.read(); //Variável para armazenar os caracteres que forem recebidos
        valPag.concat(c); // Pega os valor após o IP do navegador ex: 192.168.1.2/0001        

        //Compara o que foi recebido
        if(valPag.endsWith("0001")) //Se o que for pego após o IP for igual a 0001
        {
          Serial.println(valPag);
        }
        
        else if(valPag.endsWith("0010")) //Senão se o que for pego após o IP for igual a 0010
        {
          Serial.println(valPag);

        }
        
        else if(valPag.endsWith("0100")) //Senão se o que for pego após o IP for igual a 0100
        {
          Serial.println(valPag);      
        }
        //=========================================================================================================================

        if (c == '\n' && currentLineIsBlank)
        {
          //Inicia página HTML
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.print("<HTML> ");
          client.println("<BR><center></B></I></U><a href=\"http://www.labdegaragem.com\"> <img src=http://www.labdegaragem.com.br/logo.png></a></B></I></U></center>");
          //=========================================================================================================================
          
          client.print("<BR><BR>");

          //=========================================================================================================================      

          client.print("<BR><BR>");

          //=========================================================================================================================

          client.print(" <meta http-equiv=\"refresh\" content=\"5; url=http://192.168.1.2/\"> ");

          client.println("</HTML>");

          break;

        } //Fecha if (c == '\n' && currentLineIsBlank)
        
      } //Fecha if (client.available())
      
    } //Fecha While (client.connected())
    
    delay(3);// Espera um tempo para o navegador receber os dados
    client.stop(); // Fecha a conexão
    
  } //Fecha if(client)
  
} //Fecha loop





