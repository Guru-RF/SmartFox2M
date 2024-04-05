#include "si5351.h"
#include "Wire.h"

Si5351 si5351;

//#define PLLB_FREQ    87250000000ULL
#define PLLB_FREQ      87274800000ULL
//                     14545000000ULL

void setup()
{
  delay(2000);
  Serial.println("Enable I2C bus");
  Wire.begin(1);    // I2C bus address = 1
  delay(3000);
  si5351.reset();
  Serial.println("Reset SI5351");
  si5351.init(SI5351_CRYSTAL_LOAD_8PF,0,0);
  si5351.set_vcxo(PLLB_FREQ, 61); //0->232 (deviation)
  si5351.set_ms_source(SI5351_CLK0, SI5351_PLLB);
  si5351.set_freq_manual(14545800000ULL, PLLB_FREQ, SI5351_CLK0);
  si5351.drive_strength(SI5351_CLK0, SI5351_DRIVE_2MA);
  
  si5351.update_status();
  delay(500);

}

void loop()
{

  si5351.update_status();
  Serial.print("  SYS_INIT: ");
  Serial.print(si5351.dev_status.SYS_INIT);
  Serial.print("  LOL_A: ");
  Serial.print(si5351.dev_status.LOL_A);
  Serial.print("  LOL_B: ");
  Serial.print(si5351.dev_status.LOL_B);
  Serial.print("  LOS: ");
  Serial.print(si5351.dev_status.LOS);
  Serial.print("  REVID: ");
  Serial.println(si5351.dev_status.REVID);

  si5351.output_enable(SI5351_CLK0, 1);
  delay(100);
  for (int i=0; i<5; i++)  {
    Serial.println("Ring");
    tone(15, 425, 1000);
    delay(1000);
    tone(15, 0, 3000);
    delay(3000);
  }
  for (int i=0; i<5; i++)  {
    Serial.println("Busy");
    tone(15, 425, 500);
    delay(500);
    tone(15,0,500);
    delay(500);
  }
  //425/167,0/167
  for (int i=0; i<5; i++)  {
    Serial.println("Busy");
    tone(15, 425, 167);
    delay(167);
    tone(15,0,167);
    delay(167);
  }
  si5351.output_enable(SI5351_CLK0, 0);

  delay(20000);
  
  
}
