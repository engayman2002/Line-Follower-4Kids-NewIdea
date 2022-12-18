// Line Follower Project ( Ayman Mohamed Elashry )

// -------------- Motors Objects

// Front Right Motor
#define FRMot1 3
#define FRMot2 4

// Front Left Motor
#define FLMot1 7
#define FLMot2 6

// Back Right Motor
#define BRMot1 9
#define BRMot2 8

// Back Left Motor
#define BLMot1 11
#define BLMot2 12

//--------------------- IRs Objects

// Right IRs
#define IRI 41
#define IRO 40

// Left IRs
#define ILI 35
#define ILO 30

// Main IR
#define IM 23

// Upper IR
#define IU 22

// ---------------- Values For Speed

// Analog Write For The Highest Speed Of Your Motors
byte high=170;

// Analog Write For The Medium Speed Of Your Motors
byte med=110;

// Analog Write For The Lowest Speed Of Your Motors
byte low=80;

// Note This Information depends on IRs Reading
/* For The Black Line
* Black = 1 ---- b=1
* White = 0 ---- w=0
*/

/* For The White Line
* Black = 0 ---- b=0
* White = 1 ---- w=1
*/

// IRs Black and White Values
// Default Color For The Line is "" Black "" depends on your IRs

byte b=1;
byte w=0;

// Variable of the Equation
short x=0;
byte y=0,z=0;

void setup() {
// -------------------------------IRs Pins
// Right IRs
pinMode(IRI,INPUT);
pinMode(IRO,INPUT);

// 2 IR on The Line
pinMode(IM,INPUT);
pinMode(IU,INPUT);

// Left IRs
pinMode(ILI,INPUT);
pinMode(ILO,INPUT);

// ----------------------------- Motors_Pins

// Front Right Motor
pinMode(FRMot1,OUTPUT);
pinMode(FRMot2,OUTPUT);

// Front Left Motor
pinMode(FLMot1,OUTPUT);
pinMode(FLMot2,OUTPUT);

// Back Right Motor
pinMode(BRMot1,OUTPUT);
pinMode(BRMot2,OUTPUT);

// Back Left Motor
pinMode(BLMot1,OUTPUT);
pinMode(BLMot2,OUTPUT);

// ------------------------------ Before Starting Your Road

delay(1000);
}
// ---------------------- End Setup Function

//--------------------------------------- Motors Status ------------------------------ 

// -------------------- Front Right Motor Status
void R1Mot(byte f,byte r)
{
analogWrite(FRMot1,f);
analogWrite(FRMot2,r);
}

// ------------------------- Front Left Motor Status
void L1Mot(byte f,byte r)
{

analogWrite(FLMot1,f);
analogWrite(FLMot2,r);
}

// -------------------- Back Right Motor Status
void R2Mot(byte f,byte r)
{
analogWrite(BRMot1,f);
analogWrite(BRMot2,r);
}

// ------------------------- Back Left Motor Status
void L2Mot(byte f,byte r)
{
analogWrite(BLMot1,f);
analogWrite(BLMot2,r);
}

// Function for Stopping All Motors
void stopMot()

{
R1Mot(0,0);
L1Mot(0,0);
R2Mot(0,0);
L2Mot(0,0);
}

// --------------------------------------- End Motors Status ---------------------------------------

// ----------------------------------Directions of The Car ---------------------------------------
/*
R1Mot(,);
L1Mot(,);

R2Mot(,);
L2Mot(,);
*/

// Forward Case
void Forward(byte val)
{
R1Mot(val,0);
L1Mot(val,0);
R2Mot(val,0);
L2Mot(val,0);
}
void avoid(byte val)
{
R1Mot(val,0);
L1Mot(val,0);
R2Mot(val,0);
L2Mot(val,0);
while(1)
{
if( ( digitalRead(IM)==b ) || (
(digitalRead(ILO)==w) &&
(digitalRead(ILI)==w) &&
(digitalRead(IRI)==w) &&
(digitalRead(IRO)==w) ) )
{
stopMot();
break;
}
}
}

// Right Case
void Right(byte val)
{
R1Mot(0,val);
L1Mot(val,0);
R2Mot(0,val);
L2Mot(val,0);
}

// Left Cases
void Left(byte val)
{

R1Mot(val,0);
L1Mot(0,val);
R2Mot(val,0);
L2Mot(0,val);
}

// Special Right Cases
void specRight(byte val)
{
// Two Left Forward
R1Mot(0,val/2);
L1Mot(val/2,0);
R2Mot(0,val/2);
L2Mot(val,0);
while(1){if((digitalRead(IM)==b) ||
(digitalRead(ILI)==b) ||
(digitalRead(ILO)==b) ){stopMot();
break;}}
}

// Special Left Cases
void specLeft(byte val)

{
// Two Right Forward
R1Mot(val/2,0);
L1Mot(0,val/2);
R2Mot(val,0);
L2Mot(0,val/2);
while(1){if( (digitalRead(IM)==b) ||
(digitalRead(IRI)==b) ||
(digitalRead(IRO)==b) ){stopMot();
break;}}
}

void loop() {

x=digitalRead(ILO)*10000+digitalRead(ILI)*1000+digitalRead(IM)*100+digitalRead(IRI)*10+digitalRead(IRO);
switch(x)
{
// Cases
// Forward Cases
case 0 : // 00000

case 100: // 00100
case 11111 : // 11111
Forward( digitalRead(IU)==b ? high
: med );
break;

// Forward to avoid IRs Fast Reading
case 11011 : // 11011
avoid(med);
break;

// Right Cases
case 1: // 00001
case 10: // 00010
Right(med);
break;

// Left Cases
case 1000 : // 01000
case 10000 : // 10000
Left(med);

break;

// Mini Right Cases
case 10010 : // 10010
case 1011 : // 01011
case 10011: // 10011
case 101 : // 00101 ( Think About it Again )
case 1111 : // 01111
case 10110 : // 10110
case 110 : // 00110
case 10111 : // 10111
Right(low);
break;

// Mini Left Cases
case 1001 : // 01001
case 11001: // 11001
case 11010: // 11010
case 10100 : // 10100 ( Think About it Again )
case 11110 : // 11110

case 1100 : // 01100
case 1101 : // 01101
case 11101 : // 11101
Left(low);
break;

// Spec Right Cases
case 11 : // 00011
specRight(255);
break;

// Spec Left Cases
case 11000: // 11000
specLeft(255);
break;

// Mini Forward
/*
---------------------------------------
------ Done Fake Forward
---------------------------------------

------

* ( Without Thinking Again )
* 01110 -- 10001 -- 10101 -- 01010
* ( Fake Line Go Forward With
The Smallest Speed because it is a
danger region )00111 -- 11100
*
---------------------------------------

-
* ( With Thinking Again )
* Still Testing For Better
Function ( )
*
---------------------------------------

-
*/
default:
Forward(low);
}

}
// This Equation only for The Black Line depends on IRs Reading

//x=digitalRead(ILO)*10000+digitalRead(ILI)*1000+digitalRead(IM)*100+digitalRead(IRI)*10+digitalRead(IRO);

// For White Line This is The Equation depends on IRs Reading
//x=(!digitalRead(ILO))*10000+(!digitalRead(ILI))*1000+(!digitalRead(IM))*100+(!digitalRead(IRI))*10+(!digitalRead(IRO));

/*
If you want using Analog Reading Use
This Sol and editing this ( == ) into
the requried comparison mark

// Left Sensors
analogRead(ILO)==b ? x=10000*1 :
x=10000*0;
analogRead(ILI)==b ? x+=1000*1 :

x+=1000*0;

// Main Sensor
analogRead(IM)==b ? x+=100*1 :
x+=100*0;

// Right Sensors
analogRead(IRI)==b ? x+=10*1 :
x+=10*0;
analogRead(IRO)==b ? x+=1*1 : x+=1*0;
*/
