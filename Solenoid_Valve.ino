//set pin numbers
const int solenoid_pin =2; //const won't change
const int button_pin =4;

//variable will change
 int button_statusCheck = 0;  //variable for reading the pushbutton status

void setup() {
  Serial.begin(9600);
  pinMode(solenoid_pin , OUTPUT);//initialize the LED pin as an output
  pinMode(button_pin,INPUT); //initialize the bp pin as an output
}
void loop() {
  //read the state of the pushbutton value
  button_statusCheck = digitalRead(button_pin); 
  if (button_statusCheck == HIGH){     //check if the pushbutton is pressed
    //if it is , the butttonStatus is high
   digitalWrite(solenoid_pin, LOW);  
   Serial.println("ON"); //turn LED on
   }
    else{        
//if it is , the bu tttonStatus is low
      digitalWrite(solenoid_pin, HIGH);  //turn LED off
      Serial.println("OFF");
       }
 }  
