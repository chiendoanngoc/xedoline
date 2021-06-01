#define MOTOR1_0 6 // phai
#define MOTOR1_1 7 // phai
#define MOTOR2_0 8 // trai
#define MOTOR2_1 9 // trai

unsigned int sensor[3];
int error = 0;
int countReadSensor = 0;
int tmp_err = 0;

void setup() {
  pinMode(MOTOR1_0,OUTPUT);
  Serial.begin(9600);
}

void motor_forward(){
  analogWrite(10,250);    //Left Motor Speed
  analogWrite(5,250);     //Right Motor Speed
  digitalWrite(MOTOR1_0,LOW);
  digitalWrite(MOTOR1_1,HIGH);
  digitalWrite(MOTOR2_0,LOW);
  digitalWrite(MOTOR2_1,HIGH);
}

void motor_stop(){
  digitalWrite(MOTOR1_0,LOW);
  digitalWrite(MOTOR1_1,LOW);
  digitalWrite(MOTOR2_0,LOW);
  digitalWrite(MOTOR2_1,LOW);
}

void turn_right(){
  analogWrite(10,80);   //Left Motor Speed
  digitalWrite(MOTOR2_0,LOW);
  digitalWrite(MOTOR2_1,HIGH);
  digitalWrite(MOTOR1_0,LOW);
  digitalWrite(MOTOR1_1,LOW);
}

void turn_right_slow(){
  analogWrite(10,60);   //Left Motor Speed
  digitalWrite(MOTOR2_0,LOW);
  digitalWrite(MOTOR2_1,HIGH);
  digitalWrite(MOTOR1_0,LOW);
  digitalWrite(MOTOR1_1,LOW);
}

void turn_left(){
  analogWrite(5,80);  //Right Motor Speed
  digitalWrite(MOTOR1_0,LOW);
  digitalWrite(MOTOR1_1,HIGH);
  digitalWrite(MOTOR2_0,LOW);
  digitalWrite(MOTOR2_1,LOW);
}

void turn_left_slow(){
  analogWrite(5,60);  //Right Motor Speed
  digitalWrite(MOTOR1_0,LOW);
  digitalWrite(MOTOR1_1,HIGH);
  digitalWrite(MOTOR2_0,LOW);
  digitalWrite(MOTOR2_1,LOW);
}

void read_sensor_values()
{
  sensor[0]=digitalRead(2); //trai
  sensor[1]=digitalRead(3); //giua
  sensor[2]=digitalRead(11); //phai - tim
  
  if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1))
  error=2;
  else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==1))
  error=1;
  else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==0))
  error=0;
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0))
  error=-1;
  else if((sensor[0]==1)&&(sensor[1]==0)&&(sensor[2]==0))
  error=-2;
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1))
  error=10;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0))
    if(error==-2) error=-3;
    else if(error == 2) error=3;
    else if (error == 1) error = 2;
    else if (error == -1) error = -2;
    else if (error == 0) error = 0;
}

void loop() {

  read_sensor_values();
  if (countReadSensor < 3){
    tmp_err += error;
    countReadSensor++;
  } else {
      error = tmp_err / 3;
      tmp_err = 0;
      countReadSensor = 0;
      if (error == 0)
        motor_forward();
      else if (error == 1)
        turn_right_slow();
      else if (error == -1)
        turn_left_slow();
      else if (error == 3){
        motor_stop();
        turn_right();
      }
      else if (error == -3){
        motor_stop();
        turn_left();
      }
      else if (error == 2)
        turn_right();
      else if (error == -2)
        turn_left();
      else if (error == 10)
        motor_forward();
      else
        motor_stop();
    }
}
