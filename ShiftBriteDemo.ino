#include "typedefs.h"

#define clockpin 13 // CI
#define enablepin 10 // EI
#define latchpin 9 // LI
#define datapin 11 // DI

#define NumLEDs 3

int LEDChannels[NumLEDs][3] = {0};
int SB_CommandMode;
int SB_RedCommand;
int SB_GreenCommand;
int SB_BlueCommand;

RgbColor laserCannonRGB;
HsvColor laserCannonHsv = {
  170, 255 ,255};

void setup()
{
  Serial.begin(9600);
  pinMode(datapin, OUTPUT);
  pinMode(latchpin, OUTPUT);
  pinMode(enablepin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  SPCR = (1<<SPE)|(1<<MSTR)|(0<<SPR1)|(0<<SPR0);
  digitalWrite(latchpin, LOW);
  digitalWrite(enablepin, LOW);

  laserCannonRGB = HsvToRgb(laserCannonHsv);
  Serial.print("H=");
  Serial.print(laserCannonHsv.h);
  Serial.print("  S=");
  Serial.print(laserCannonHsv.s);
  Serial.print("  V=");
  Serial.println(laserCannonHsv.v);

  Serial.print("R=");
  Serial.print(laserCannonRGB.r);
  Serial.print("  G=");
  Serial.print(laserCannonRGB.g);
  Serial.print("  B=");
  Serial.println(laserCannonRGB.b);
}

void SetLEDbarPosition(int barPosition)
{
  int shiftBrite;
  int positionCenter;
  int positionDelta;
  int shiftBriteIntensity;

  for (shiftBrite = 0; shiftBrite<NumLEDs; shiftBrite++)
  {
    positionCenter = 256 / (NumLEDs+1) * (shiftBrite +1);
    positionDelta = positionCenter - barPosition;
    shiftBriteIntensity = (256 / (NumLEDs + 1)) - abs(positionDelta);

    if(shiftBriteIntensity >0) laserCannonHsv.v = shiftBriteIntensity * (NumLEDs +1);
    else laserCannonHsv.v = 0;

    laserCannonRGB = HsvToRgb(laserCannonHsv);

    LEDChannels[shiftBrite][0] = laserCannonRGB.r;
    LEDChannels[shiftBrite][1] = laserCannonRGB.g;
    LEDChannels[shiftBrite][2] = laserCannonRGB.b;
  }
  WriteLEDArray();
  delay(1);
}

void loop()
{
  int i;
  int color;

  for (color = 0; color <= 300; color +=10)
  {
    laserCannonHsv.h = color;
    for (i=0; i<550; i+=2)
    {
      SetLEDbarPosition(i);
    }
  }
}

