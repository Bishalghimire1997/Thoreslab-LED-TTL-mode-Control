
class Common {
  public:
  virtual void on(){}
  virtual void OFF(){}
  virtual Common* getNextState(){}
  virtual void setNextState(Common*){}
};
class LED{
  private:
  int pin;
  public: 
  LED(int p){
     pinMode(p, OUTPUT);
     pin = p;    
  }
  void on(){
    digitalWrite(pin,HIGH);
  }
  void off(){
    printf("Turning Off");
    digitalWrite(pin,LOW);
  }
};

class Blue : public Common {
  private:
  LED obj = LED(12);
  Common* next_state ; 
  public:
  Blue(){}
   void on() override{
    obj.on();
  }
  void OFF() override{
    obj.off();
  }
   void setNextState(Common* val) {
     next_state = val;    
  }
  Common* getNextState() {
    return next_state;
  }
};

class Green: public Common {
  private:
  LED obj = LED(13); 
  Common* next_state;
  
  public:
   void on() override {
    obj.on();
  }
  void OFF() override{
    obj.off();
  }
  void setNextState(Common* val) {
     next_state = val;    
  }
  Common* getNextState() {
    return next_state;
  }
  };
  
class Red:public Common{
  private:
  LED obj = LED(11) ;
  Common* next_state;  
  public:
  Red(){}
   void on()  override {
    obj.on();
  }
  void OFF() override {
    obj.off();
  }
  void setNextState(Common* val) {
     next_state = val;
    
  }
  Common* getNextState() {
    return next_state;
  }
};

class State {
  private:
  Common* red;
  Common* blue;
  Common* green;

  public:
  State(){
     red = new Red();
     blue = new Blue();
     green = new Green();

     red ->setNextState(blue);
     green ->setNextState(red);
     blue -> setNextState(green);
  }
     Common* get_first_state(){
      return blue;
     }  
  };
  
State var = State();
Common* obj = var.get_first_state();
bool runLoop = false;
void setup(){
  Serial.begin(9600);
  pinMode(10, OUTPUT);
}
void loop() {  

  if (Serial.available() > 0) {
         int command = Serial.parseInt();  // Read integer command
        
        if (command == 1) {
            runLoop = true;
            Serial.println("Loop started");
        } else if (command == 0) {
           Serial.println("Loop stopped");
            runLoop = false;
            obj -> OFF(); 
            obj = var.get_first_state();
            digitalWrite(10,LOW);
            while(true){
              if (Serial.available() > 0) {
               command = Serial.parseInt();  // Read integer command

            }
            if(command == 1){
              runLoop = true;
              break;}

           
        }
    
     
    }
    else{runLoop = true;}
  }
   if (runLoop) {
  obj ->on();
  digitalWrite(10,HIGH);
  delay(30);
  digitalWrite(10,LOW);
  obj -> OFF();  
  obj = obj ->getNextState(); 
  }
}



   
  
