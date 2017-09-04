#pragma config(Sensor, S2,     snrRHS,         sensorSONAR)
#pragma config(Sensor, S3,     lghtSNS,        sensorLightActive)
#pragma config(Sensor, S4,     snrFRNT,        sensorSONAR)
#pragma config(Motor,  motorB,          mtrRHS,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          mtrLHS,        tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//CODE FOR ENGG282 - V1 - 18-07-17
///////////////////////////////////////////////////////////////////////////////////////////
int steps[150];
//Condition 1
void moveForward() {
	motor[mtrRHS] = 25;
	motor[mtrLHS] = 25;
	wait1Msec(100);
}
//Condition 2
void turnLeft() {
	motor[mtrRHS] = 25;
	motor[mtrLHS] = -25;
	wait1Msec(720);
	motor[mtrRHS] = 0;
	motor[mtrLHS] = 0;
}
//Condition 3
void turnRight() {
	motor[mtrRHS] = 25;
	motor[mtrLHS] = -25;
	wait1Msec(720);
	motor[mtrRHS] = 0;
	motor[mtrLHS] = 0;
}
//Condition 4
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
//Method to control the robot
void action(int i, int pos) {
	steps[pos] = i;
	if (i == 1){
		moveForward();
	}
	else if (i == 2) {
		turnRight();
	}
	else if (i == 3) {
		turnLeft();
	}
	else if (i == 4){
		wallGap();
	}
	else {
	//GO BACK THROUGH STEPS ARRAY - LIGHT HAS BEEN FOUND SO GO HOME TO START POS
		//returnToBase();
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
//tLight
int tSonarFront()
{
		// Variables for sonar reading and distance from front
		int sonarValue = SensorValue(snrFRNT);
		int distFromFront = 30;

		// If there is a range error - i.e sonar not receiving sonar signal back
		if (sonarValue == 255)
  	{
  		//moveForward
 		 	return 1;
 		}
		// The front wall is close, turn to the left of it, move back first
		else if (sonarValue < distFromFront)
		{
			//turnLeft();
		return 3;
		}
		// Move forward as normal
		else
		{
			//moveForward();
			return 1;
		}
}
int tSonarRight()
{
	int sonarValue = SensorValue(snrRHS);
	int distFromRight = 25;
	//If there is a range error - i.e sonar not receiving sonar signal back
	if (sonarValue == 255){
  	return 1;
  }
  // Turn needs to be made
  else if (sonarValue > distFromRight)
  {
  	//wallGap();
  	return 4;
  }
  /*
  //CORRECTION CODE
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
  		//moveForward();
  		return 1;

  	}
  	*/
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
task main()
{
	int pos = 0;
	while (true)
	{
		int x = tSonarFront();
		wait1Msec(200);
		int y = tSonarRight();
		//int z = tLight();
		//Modify this for three conditions
		if(x > y)
		{
			action(x, pos);
		}
		else
		{
			action(y, pos);
		}
		pos = pos + 1;
	}

}
// Concept 1: This
// Concept 2: Use curved edges to auto correct the robot
// Concept 3: bumper instead of sonar

/*
Different Conditions:
1. Wall is on the RHS - moveForward
2. Wall is on the RHS but there is a wall in front - turnLeft OR turnRight x3
3. No wall on RHS but turn right and there is a wall on the RHS - turnRight
4. No wall on RHS but turn right and still no wall on the RHS - wallGap
5. Reached the light - lightFound

The greater the number on these conditions = the step that takes precedence

Have the program work in that it stores all the steps by passing out int values from the methods
Then have an array of all the steps it take in the main program so that it can follow all these steps backwards again

*/
