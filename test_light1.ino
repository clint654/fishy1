
#define IN_BUFFER_SIZE 100
#define CHAN_NUM 6

byte channel_pin[] = {3,5,6,9,10,11};
byte channel_brightness[] = {1,1,1,1,1,1};

int brightness =0;
 char input_buffer[IN_BUFFER_SIZE];
 char *ip = input_buffer;

void setup() {
  // put your setup code here, to run once:
  for (int i=0; i< CHAN_NUM; i++){
    pinMode(channel_pin[i], OUTPUT);
    analogWrite(channel_pin[i],channel_brightness[i]);
  }

  Serial.begin(115200);

}

void process_string(char * instr) {
 char buffer[100];
 int chan =-1;
 int b = 0;
 
  switch(instr[0]) {
    case '+':
      for (int i=0; i< CHAN_NUM; i++) {
        if (channel_brightness[i] < 255) channel_brightness[i]++;
        analogWrite(channel_pin[i],channel_brightness[i]);
      }
      sprintf(buffer,"Set Channel ALL +1\n",channel_brightness[0],channel_brightness[1],channel_brightness[2],channel_brightness[3],channel_brightness[4],channel_brightness[5]);      
      break;
      case '-':
      for (int i=0; i< CHAN_NUM; i++) {
        if (channel_brightness[i] > 0)  channel_brightness[i]--;
        analogWrite(channel_pin[i],channel_brightness[i]);
      }
      sprintf(buffer,"Set Channel ALL +1\n",channel_brightness[0],channel_brightness[1],channel_brightness[2],channel_brightness[3],channel_brightness[4],channel_brightness[5]);      
      break;
    case '?':  
      sprintf(buffer,"C %d %d %d %d %d %d\n",channel_brightness[0],channel_brightness[1],channel_brightness[2],channel_brightness[3],channel_brightness[4],channel_brightness[5]);      
      break;
    case 'l':
      sscanf(instr,"l %d %d",&chan,&b);
      sprintf(buffer,"Set Channel %d %d\n",chan,b);
      channel_brightness[chan] = b; 
      analogWrite(channel_pin[chan],channel_brightness[chan]);
    break;
    
      
      
    default:
      sprintf(buffer,"Unknown Command %s\n",instr);
  }
  Serial.print(buffer);
}

void loop() {
  // put your main code here, to run repeatedly:
 
 if (Serial.available()) {
    // read the most recent byte (which will be from 0 to 255):
    *ip = Serial.read();
    if (*ip == '\n') { //end of string
      ip++;
      *ip = 0;  
      process_string(input_buffer);
      ip = input_buffer;
    } else {
      ip++;
    }
 }

}




