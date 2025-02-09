
class Common {
  public:
  virtual void on(){}
  virtual void OFF(){}
  virtual Common* getNextState(){}
  virtual void setNextState(Common*){}
  virtual void encodeLEDCOlor(){}
};
class LED{
  private:
  int pin,pin7 = 7,pin6 = 2;
  public: 
  LED(int p){
    pinMode(p, OUTPUT);
    pinMode(pin7, OUTPUT);
    pinMode(pin6, OUTPUT);
     pin = p;    
  }
  void on(){
    digitalWrite(pin,HIGH);
  }
  void off(){
    printf("Turning Off");
    digitalWrite(pin,LOW);
  }
  void encode(int pin7val,int pin6val){
       switch (pin7val) {
        case 0:
            digitalWrite(7, LOW);
            break;
        case 1:
            digitalWrite(7, HIGH);
            break;
        default:
            Serial.println("Invalid value for pin 7");
            break;
    }

    switch (pin6val) {
        case 0:
            digitalWrite(2, LOW);
            break;
        case 1:
            digitalWrite(2, HIGH);
            break;
        default:
            Serial.println("Invalid value for pin 6");
            break;
    }

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
  void encodeLEDCOlor(){
    obj.encode(0, 1);
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
   void encodeLEDCOlor(){
    obj.encode(1, 0);
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
   void encodeLEDCOlor(){
    obj.encode(1, 1);
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

  class Control{
    private:
    int i = 1;
    
    public:
    Control(){}
    bool holdThreadUntil(int val){
      Serial.println("Loop stopped");
            bool runLoop = false;
            int command;
            while(true){
              if (Serial.available() > 0) {
                command = Serial.parseInt();  // Read integer command
               }
              if(command == val){
                runLoop = true;
                return runLoop;
                break;
                }

           
        }

    }

  };
  
State var = State();
Common* obj = var.get_first_state();

Control ctrl = Control();

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
           runLoop = ctrl.holdThreadUntil(1);
        }
    else{runLoop = true;}
  }
   if (runLoop) {
  obj ->on();
  obj ->encodeLEDCOlor();
  digitalWrite(10,HIGH);
  delay(30);
  digitalWrite(10,LOW);
  obj -> OFF();  
  obj = obj ->getNextState(); 
  }
}



   
  
