class Counter {

private:

  int count;  

public:

  Counter(int value){
    count = value;
  }

  ~Counter(){
    // destructor  
  }
  
  void inc(){
    count++;  
  }
  
  int getValue(){
    return count;
  }

};

int a = 1;
Counter c(10);
Counter* c1;
Counter* c3;

int co = 0;

void setup(){
   int x1 = 3;
   int x2 = 4;
   
   Serial.begin(9600); 
   c1 = new Counter(20);
   c3 = new Counter(30);

   Serial.println((unsigned long) &a);
   Serial.println((unsigned long) &c);
   Serial.println((unsigned long) &c1);

   Serial.println((unsigned long) &x1);
   Serial.println((unsigned long) &x2);

   Serial.println((unsigned long) c1);
   Serial.println((unsigned long) c3);
}


void loop(){
/*
  c.inc();
  Serial.println(c.getValue());
  
  c1->inc();
  Serial.println(c1->getValue());

  Counter* c3 = new Counter(micros());
  Serial.println(c3->getValue());
  // delete c3;

  Counter c2(10);
  c2.inc();

  delay(10);
*/  
  
}
