import processing.serial.*;
 
Serial myPort;        // A porta serial
int xPos = 1;         // posição horizontal do gráfico
float height_old = 0;
float height_new = 0;
float inByte = 0;
int BPM = 0;
int beat_old = 0;
float[] beats = new float[500];  // para calcular o BPM médio
int beatIndex;
float threshold = 620.0;  // Limite para o cálculo BPM
boolean belowThreshold = true;
PFont font;
 
void setup () {
  // tamanho da janela
  size(1000, 400);        
 
  // Lista de portas seriais disponíveis
  println(Serial.list());
  // Abra qualquer porta que você está usando.
  myPort = new Serial(this, Serial.list()[2], 9600);
  // não gere um serialEvent () a menos que você obtenha um caractere de nova linha:
  myPort.bufferUntil('\n');
  // definir fundo inicial:
  background(0xff);
  font = createFont("Ariel", 12, true);
}
 
 
void draw () {
     // Mapeie e desenhe a linha para o novo ponto de dados
     inByte = map(inByte, 0, 1023, 0, height);
     height_new = height - inByte; 
     line(xPos - 1, height_old, xPos, height_new);
     height_old = height_new;
    
      // na borda, voltar ao início
      if (xPos >= width) {
        xPos = 0;
        background(0xff);
      } 
      else {
        // posição horizontal:
        xPos++;
      }
      
      // mostrar BPM periodicamente
      if (millis() % 128 == 0){
        fill(0xFF);
        rect(0, 0, 200, 20);
        fill(0x00);
        text("BPM: " + inByte, 15, 10);
      }
}
  
void serialEvent (Serial myPort) 
{
  // obter string ASCII:
  String inString = myPort.readStringUntil('\n');
 
  if (inString != null) 
  {
    inString = trim(inString);
 
    // Se a detecção de derivações for verdadeira, notificar usando linha azul
    if (inString.equals("!")) 
    { 
      stroke(0, 0, 0xff); // azul
      inByte = 512;  // intervalo ADC
    }
    // Se os dados estiverem ok, deixe-os passar
    else 
    {
      stroke(0xff, 0, 0); //Set stroke to red ( R, G, B)
      inByte = float(inString); 
      
      // verificação de cálculo de BPM
      if (inByte > threshold && belowThreshold == true)
      {
        calculateBPM();
        belowThreshold = false;
      }
      else if(inByte < threshold)
      {
        belowThreshold = true;
      }
    }
  }
}
  
void calculateBPM () 
{  
  int beat_new = millis();    // tempo atual em milésimos
  int diff = beat_new - beat_old;    // tempo entre cada sístole
  float currentBPM = 60000 / diff;    // recorrer a BPM
  beats[beatIndex] = currentBPM;  // média BPM
  float total = 0.0;
  for (int i = 0; i < 500; i++){
    total += beats[i];
  }
  BPM = int(total / 500);
  beat_old = beat_new;
  beatIndex = (beatIndex + 1) % 500;  
}