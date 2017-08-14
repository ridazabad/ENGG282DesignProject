#pragma config(Sensor, S2,     snrRHS,         sensorSONAR)
#pragma config(Sensor, S3,     lghtSNS,        sensorLightActive)
#pragma config(Sensor, S4,     snrFRNT,        sensorSONAR)
#pragma config(Motor,  motorB,          mtrRHS,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          mtrLHS,        tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//CODE FOR ENGG282 - V1 - 18-07-17
void moveForward() {
	motor[mtrRHS] = 25;
	motor[mtrLHS] = 25;
	wait1Msec(100);
}

void turnRight() {
	motor[mtrRHS] = 25;
	motor[mtrLHS] = -25;
	wait1Msec(720);
	motor[mtrRHS] = 0;
	motor[mtrLHS] = 0;
}

void wallGap() {
	//Move forward for a lil bit
	motor[mtrRHS] = 25;
	motor[mtrLHS] = 25;
	wait1Msec(500);
	//RHS turn
	motor[mtrRHS] = -25;
	motor[mtrLHS] = 25;
	wait1Msec(720);
	//Move forward again slightly
	motor[mtrRHS] = 25;
	motor[mtrLHS] = 25;
	wait1Msec(1000);
}
//Turn method for collision with front wall
void turnLeft() {
	motor[mtrRHS] = 25;
	motor[mtrLHS] = -25;
	wait1Msec(720);
	motor[mtrRHS] = 0;
	motor[mtrLHS] = 0;
}

void tLight()
{
	// Variables for light value and whether the light is found
	int lightSensor = SensorValue(lghtSNS);
	bool lightFound = false;

	while(lightFound == false)
	{
		// Look for the light, if it is found, indicate it programatically
		if (lightSensor > 32){
			lightFound = true;
		}
	}
	//9 pivot values in a 90 degree range?
	//turn to the left looking for highest intensity
	//turn to the right looking for highest intensity
	//move towards the highest intensity
	while (lightFound) {
		//set zero
		//go forward for 200ms
		//check for light again
	}
}
void tSonarFront()
{
		// Variables for sonar reading and distance from front
		int sonarValue = SensorValue(snrFRNT);
		int distFromFront = 20;

		// If there is a range error - i.e sonar not receiving sonar signal back
		if (sonarValue == 255)
  	{
 		 	moveForward();
 		}
		// The front wall is close, turn to the left of it, move back first
		else if (sonarValue < distFromFront)
		{
			turnLeft();
			//wait1Msec(1000);
		}
		// Move forward as normal
		else
		{
			moveForward();
		}
}
void tSonarRight()
{
	int sonarValue = SensorValue(snrRHS);
	int distFromRight = 25;
	//If there is a range error - i.e sonar not receiving sonar signal back
	if (sonarValue == 255){
  	moveForward();
  }
  // Turn needs to be made
  else if (sonarValue > distFromRight)
  {
  	wallGap();
  }
  //If the sonar is returning a range within 16-24, then it is relatively close to the wall
  else if(sonarValue >= 20 && sonarValue <=24) {
  	// Too far away from the wall, set the RHS wheel to go slower so that it turns towards the wall
  	if(sonarValue > 22){
  		motor[mtrRHS] = 23;
  		motor[mtrLHS] = 25;
  		wait1Msec(200);
  	}
  	// Too close to the wall, set the LHS wheel to go slower so that it turns away from the wall
  	else if (sonarValue < 22){
  		motor[mtrRHS] = 25;
  		motor[mtrLHS] = 23;
  		wait1Msec(200);
  	}
  	// Else, all is well, continue moving forward on the path
  	else
  	{
  		moveForward();
  		//wait1Msec(300);
  	}
  }
}
task main()
{
	while (true)
	{
		// The robot should only move not forward because of 1 of 3 reasons
		// 1. It senses a wall in front, so will turn right so as to not run into it
		// 2. It does not sense a wall on the right, so turns right to find a wall
		// 3. It sees the light and moves towards it

		tSonarFront();
		tSonarRight();
	}

}
// Concept 1: This
// COncept 2: Use curved edges to auto correct the robot
// Concept 3: bumper instead of sonar
