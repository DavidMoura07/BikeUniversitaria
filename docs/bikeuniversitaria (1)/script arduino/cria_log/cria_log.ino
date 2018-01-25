#include <SPI.h>
#include <Ethernet.h>
#include <String.h>
#include <MFRC522.h>

#define SS_PIN 9
#define RST_PIN 8
#define BUZZER 7
#define PORTA 8081

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
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
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
  //if(Serial.available()){
    //String cartao = leStringSerial();
    if (cliente.connect(servidor, PORTA)) {
      Serial.println("conectado");
      cliente.print("GET /bikeuniversitaria/controledeacesso.php?");
      cliente.print("cartao=\"");
      //cliente.print(cartao);
      cliente.print(conteudo);
      cliente.println("\"");
      tone(BUZZER,1500);   
      delay(300); 
      noTone(BUZZER);
      delay(500);
    } else {
      Serial.println("falha na conexao");
      tone(BUZZER,1500);   
      delay(200); 
      noTone(BUZZER);
      tone(BUZZER,1500);   
      delay(200); 
      noTone(BUZZER);
    }
    Serial.flush();
  //}
  cliente.stop();
}

/**
 * Função que lê uma string da Serial
 * e retorna-a
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

