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
//byte ip[] = { 192, 168, 0, 16 };

//ENDEREÇO IP DO COMPUTADOR ONDE ESTA O BD
byte servidor[] = { 192, 168, 0, 33 };

//EthernetClient cliente;
EthernetClient enviocliente, respostacliente;

IPAddress ip(192, 168, 0, 16); // Configure um IP válido
byte gateway[] = { 192 , 168, 0, 1 };
byte subnet[] = { 255, 255, 255, 0 }; //Entre com a Máskara de Subrede
EthernetServer server(80);

void setup() {
  Serial.begin(9600); //inicia a serial
  SPI.begin(); //inicia SPI bus
  mfrc522.PCD_Init(); //inicia MFRC522
  Ethernet.begin(mac, ip);

  pinMode(BUZZER, OUTPUT);
  tone(BUZZER, 1500);
  delay(100);
  noTone(BUZZER);
  delay(100);
  tone(BUZZER, 1500);
  delay(100);
  noTone(BUZZER);
  delay(100);
  tone(BUZZER, 1500);
  delay(100);
  noTone(BUZZER);
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    Serial.println("Aguardando novos cartoes;");
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    Serial.println("Selecionando um dos cartoes;");
    return;
  }
  //captura cartao
  String cartao = "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    cartao.concat(String(mfrc522.uid.uidByte[i]));
  }
  //Mostra UID na serial
  Serial.print("UID da tag :");
  Serial.println(cartao);
  
  //leria cartao da serial
  //if(Serial.available()){
  //String cartao = leStringSerial();
  
  if (enviocliente.connect(servidor, PORTA)) {
    Serial.println("conectado");
    enviocliente.print("GET /bikeuniversitaria/controledeacesso.php?");
    enviocliente.print("cartao=\"");
    enviocliente.print(cartao);
    enviocliente.println("\"");
    Serial.println("cartao enviado para o servidor");
    // ===== OK ======
    /*tone(BUZZER, 1500);
      delay(300);
      noTone(BUZZER);
      delay(3000);*/

  } else {
    Serial.println("falha na conexao com o servidor");
    //===== ACCESS DENIED ========
    /*tone(BUZZER, 1500);
    delay(200);
    noTone(BUZZER);
    tone(BUZZER, 1500);
    delay(200);
    noTone(BUZZER);*/
  }
  Serial.flush();
  enviocliente.stop();

  // Verifica se tem alguém conectado
  while(!(respostacliente = server.available())); 
  
  if (respostacliente)
  {
    String valPag;

    while (respostacliente.connected())
    {

      if (respostacliente.available())
      {

        char c; //Variável para armazenar os caracteres que forem recebidos

        while (c != '\n') {
          c = respostacliente.read();
          valPag.concat(c); // Pega os valor após o IP do navegador ex: 192.168.1.2/0001
        }
        Serial.println(valPag);
        //continue;
        //=========================================================================================================================

        if (c == '\n')
        {
          //Inicia página HTML
          respostacliente.println("HTTP/1.1 200 OK");
          respostacliente.println("Content-Type: text/html");
          respostacliente.println();
          respostacliente.print("<HTML> ");
          respostacliente.println("<BR><center></B></I></U>Arduino Ethernet Shield</B></I></U></center>");
          //client.print(" <meta http-equiv=\"refresh\" content=\"5; url=http://192.168.1.2/\"> ");

          respostacliente.println("</HTML>");
          
          respostacliente.stop();
          break;

        } //Fecha if (c == '\n' && currentLineIsBlank)

      } //Fecha if (client.available())

    } //Fecha While (client.connected())

    //delay(3);// Espera um tempo para o navegador receber os dados
    //client.stop(); // Fecha a conexão

  } else{
    Serial.println("Aguardando conexao");
  }


}

/**
   Função que lê uma string da Serial
   e retorna-a
*/
String leStringSerial() {
  String conteudo = "";
  char caractere;

  // Enquanto receber algo pela serial
  while (Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n') {
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

