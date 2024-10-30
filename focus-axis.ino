
void setup() {
  pinMode(6, OUTPUT); //step
  pinMode(5, OUTPUT); //direction
  pinMode(7, OUTPUT); //camera shutter
  pinMode(19, INPUT); //enable switch
  
  pinMode(10, OUTPUT); //step for turntable/rotary
  pinMode(9, OUTPUT); //direction for turntable/rotary
 

}

void moveRotary(int disR, int dircR) {
  if (dircR == 1 ) {digitalWrite(9, HIGH);} //sets which direction motor will turn
      else {digitalWrite(9, LOW);} 
    
   for(int x=0; x <= disR; x++) {   //one set of steps. Delays drive motor speeds, which are slow for this axis
      digitalWrite(10, HIGH);
      delay(4);              
      digitalWrite(10, LOW);   
      delay(4);  
   } 
}


void moveFrame(int dis, int dirc) {
  if (dirc == 1 ) {digitalWrite(5, HIGH);} //sets which direction motor will turn
      else {digitalWrite(5, LOW);}
    
   for(int x=0; x <= dis-1; x++) {      //one set of steps for focus axis. "for" loop runs until enough steps have occurred between two focus points.
      digitalWrite(6, HIGH);
      delay(1);              
      digitalWrite(6, LOW);   
      delay(1);  
   } 
}
void takeFrame(int cameraDelay) {
    delay(400);  //delay for settling/vibration
    
    digitalWrite(7, LOW);  //take a picture
        delay(55);  
        digitalWrite(7, HIGH);
        delay(55);  
        digitalWrite(7, LOW);
        
    delay(cameraDelay);  //delay for frame timing
}

void moveTotal(int travel, int dir, int distance, int cameraDelay) { 
  /* this function is one way of automating the process: it will call for a total distance,
  but stop at take a picture at each defined interval between. */
  
  for(int x=0; x<=travel;) {
      moveFrame(distance, dir);
      takeFrame(cameraDelay);
      x=x+distance;
     if (digitalRead(19)==LOW) { break; }
 }

}


void loop() {
  /* camera variables
    distance = distance (steps) between frames
    dir = 0=back, 1 = forward
    cameraDelay = time to wait after triggering the camera
    travel = total distance (steps) to cover while taking images
    
    moveTotal(travel, dir, distance, cameraDelay)
    moveFrame(distance, dir)
    
    note: moveframe and movetotal will run one loop even if distance set is 0.
  */
          //if (digitalRead(19)==HIGH) {moveRotary(5, 1);} //800 = 360degrees. Enable just this lineto continuously rotate the turntable axis
          
          
          // enable this section to automate a process with rotation
          /*       
            if (digitalRead(19)==HIGH) {moveRotary(5, 1); //800 = 360d
              delay(500);              
                  if (digitalRead(19)==HIGH) {moveTotal(1480,   1  ,   20,       300); //25 seems like min?
              delay(100);              
               //  if (digitalRead(19)==HIGH) {moveRotary(1, 1);}
              delay(2);              
                  if (digitalRead(19)==HIGH) {moveFrame(1500,   0); // 1600 = 360d = 1/8"
                
          }}}
          */ 

            //enable next two lines for a slow focus, no picture taking. I use this to determine settling times and determine area in focus.
                //if (digitalRead(19)==HIGH) {moveFrame(5,   1); // 1600 = 360d = 1/8"
                //delay(5000);   }           
            
            //enable next line to move-image-move-etc until switch is turned off
              if (digitalRead(19)==HIGH) {moveTotal(1,   1  ,   12,       900);}

}


