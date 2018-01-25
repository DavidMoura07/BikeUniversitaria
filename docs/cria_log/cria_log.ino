#include <SPI.h>
#include <Ethernet.h>
#include <String.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

//pinos usados no cristal liquid
int rs = A0;
int e = A1;
int d4 = A2;
int d5 = A3;
int d6 = A4;
int d7 = A5;

//leds
int ledverde = 5;
int ledvermelho = 6;

//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

//pinos do RFID
#define SS_PIN 9 //SDA
#define RST_PIN 8

//buzzer
#define BUZZER 7

//variaveis para pag html do arduino
String readString;
int Pin = 6;
EthernetServer server(80);
EthernetClient client;

MFRC522 mfrc522(SS_PIN, RST_PIN);

//NAO MEXA A MENOS QUE TENHA CERTEZA DO QUE ESTA FAZENDO
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

//RODE O EXEMPLO DhcpAddressPrinter E COLOQUE O IP EXIBIDO AQUI CONFORME O MODELO ABAIXO
byte ip[] = { 192, 168, 0, 16 };

//ENDEREÇO IP DO COMPUTADOR ONDE ESTA O BD 
byte servidor[] = { 192, 168, 0, 33 };

EthernetClient cliente;


void setup() {  
  Serial.begin(9600); //inicia a serial
  SPI.begin(); //inicia SPI bus
  mfrc522.PCD_Init(); //inicia MFRC522
  Ethernet.begin(mac, ip);

  lcd.begin(16, 2); //Inicia o LCD com dimensões 16x2(Colunas x Linhas)

  pinMode(ledverde, OUTPUT);
  pinMode(ledvermelho, OUTPUT);
  //Ascendendo os leds para teste
  digitalWrite(ledverde, HIGH);
  digitalWrite(ledvermelho, HIGH);
  //apito de inicialização "pi pi pi" 
  pinMode(BUZZER,OUTPUT);
  tone(BUZZER,1500);   
  delay(100); 
  noTone(BUZZER);
  delay(100);
  tone(BUZZER,1500);   
  delay(100); 
  noTone(BUZZER);
  delay(100);
  tone(BUZZER,1500);   
  delay(100); 
  noTone(BUZZER);
  //fim apito

  //apagando os leds
  digitalWrite(ledverde, LOW);
  digitalWrite(ledvermelho, LOW);
}

void loop() {
  // aguardando novo cartao
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Selecionando um cartao
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     conteudo.concat(String(mfrc522.uid.uidByte[i]));  
  }
  Serial.println(conteudo);
  tone(BUZZER,1500);   
  delay(100); 
  noTone(BUZZER);
  //if(Serial.available()){
    //String cartao = leStringSerial();
    //verifica se exite conexao com o servido na porta 80
    if (cliente.connect(servidor, 80)) {
      Serial.println("conectado");
      //chama a pagina controledeacesso.php que esta no servidor atraves da segiunte url /bikeuniversitaria/controledeacesso.php?cartao="IDdoCARTAO"
      cliente.print("GET /bikeuniversitaria/controledeacesso.php?");
      cliente.print("cartao=\"");
      //cliente.print(cartao);
      cliente.print(conteudo);
      cliente.println("\"");
      //fim da url

      //aguardando resposta do servidor
      client = server.available();
      if (client) {
        while (client.connected()) {
          if (client.available()) {
            char c = client.read();
      
            if (readString.length() < 100) {
              readString += c;             
            }
     
            if (c == '\n') {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: text/html");
              client.println();
               
              client.println("<HTML>");
              client.println("<BODY>");
              client.println("<H1>Acende LED</H1>");
              client.println("<hr />");
              client.println("<br />");
               
              client.println("<a href=\"/?ledon\">Ligar o led</a>");
              client.println("<a href=\"/?ledoff\">Desligar o led</a><br />");   
               
              client.println("</BODY>");
              client.println("</HTML>");
               
              delay(1);
              client.stop();
               
              if(readString.indexOf("?ledon") > 0)
              {
                digitalWrite(Pin, HIGH);
              }
              else {
                if(readString.indexOf("?ledoff") > 0)
                {
                  digitalWrite(Pin, LOW);
                }
              }
              readString="";    
            }
          }
        }
      }
      //fim contato servidor-arduino
      
      //ascende o led verde caso ocorra a conexao
      digitalWrite(ledverde,HIGH);
      
      //apita duas vezes indicando sucesso
      tone(BUZZER,1500);   
      delay(100); 
      noTone(BUZZER);
      tone(BUZZER,1500);   
      delay(100); 
      noTone(BUZZER);
      delay(100);
      
      //apaga o led
      digitalWrite(ledverde,LOW);
    } else {
      Serial.println("falha na conexao");
      //acende led vermelho
      digitalWrite(ledvermelho, HIGH);
      
      tone(BUZZER,1500);   
      delay(300); 
      noTone(BUZZER);
      delay(300);
      
      //apaga led vermelho
      digitalWrite(ledvermelho, LOW);
      
    }
    Serial.flush();
  //}
  cliente.stop();
}

/**
 * Função que lê uma string da Serial
 * e retorna-a (nao usada neste programa)
 */
String leStringSerial(){
  String conteudo = "";
  char caractere;
  
  // Enquanto receber algo pela serial
  while(Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
    
  Serial.print("Recebi: ");
  Serial.println(conteudo);
    
  return conteudo;
}

