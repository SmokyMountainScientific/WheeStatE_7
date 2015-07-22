//  analogRead tab, 
//  Energia sketch
//  StellarisWheeStat5_4a
//  June 23, 2014 -JSS

//////////////// Read voltage pin ///////////
void readVolts() {
 

  int inVolt = 0;                 // voltage read
  for (int i =0; i<=15; ++i){  
    inVolt += analogRead(Vread_pin);
  }
  mVread = inVolt/16;
  mVread = mVread*vcc/4096;
  mVread = (-vcc/2)+mVread;        // sign changed for WheeStat7
  Serial.print(mVread);  
  Serial.print(",");
  }

//////////////////// Read current pin //////////////
void readCurrent(boolean printI) {
  unsigned int iRead = 0;                 // current read
  for (int i =0; i<=15; ++i){  
    iRead += analogRead(Iread_pin);
   }

  mVi = iRead/16;
  if (gotLims == false){
    iMax = mVi-2048;
    iMin = mVi-2048;
    gotLims = true;
  }
  if(mVi >= iMax+2048) {
   iMax = mVi-2048; 
  }
  if(mVi <= iMin+2048) {
    iMin = mVi-2048;
  }

 // float cor1 = 0.4253*amplif + 1.2866;
  mVi = mVi*vcc/4096 + corr;    // Vout
// float offset = (res6/res5 +1)*dOff*vcc/330;
 float offset = (dOff)*vcc/330;  // was 330
  mVi = mVi-offset;
    // check for problem with digital pot by commenting out next three lines
  mVi = res5/res6*mVi/res4;
  float off2 = (165-dOff)*vcc/330/res4;
  mVi = (mVi -off2)*1000;  // JS-problem with digitization of floats fixed by 1000 fold increase. 

//  mVi = 1000* mVi;  // put in with problem check
    // end of test for digital pot function
  if (printI == true) {
    Serial.print(mVi);  
    Serial.print(",");
  }
}

