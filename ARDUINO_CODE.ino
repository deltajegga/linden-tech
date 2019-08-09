volatile int  flow_frequency;  // Measures flow meter pulses
unsigned int  l_hour;          // Calculated litres/hour                      
unsigned char flowmeter = 2;  // Flow Meter Pin number
unsigned long currentTime;
unsigned long cloopTime;

void flow ()                  // Interruot function
{ 
   flow_frequency++;
} 

void setup()
{  pinMode(3 , OUTPUT);
   digitalWrite(3 , LOW);
   pinMode(flowmeter, INPUT);
   Serial.begin(9600); 
   attachInterrupt(0, flow, RISING); // Setup Interrupt 
                                     // see http://arduino.cc/en/Reference/attachInterrupt
   sei();                            // Enable interrupts  
   currentTime = millis();
   cloopTime = currentTime;
} 

void loop ()    
{
   currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {     
      cloopTime = currentTime;              // Updates cloopTime
     float liter_per_minute = flow_frequency * 0.0117951447;
      flow_frequency = 0;                   // Reset Counter
      Serial.println(liter_per_minute);           // Print litres/hour
      if(liter_per_minute>0.09){
        digitalWrite(3 , LOW);
      }
      else{
        digitalWrite(3 , HIGH);
      }
     
   }
}
