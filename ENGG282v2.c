#pragma config(Sensor, S2,     snrRHS,         sensorSONAR)
#pragma config(Sensor, S3,     lghtSNS,        sensorLightActive)
#pragma config(Sensor, S4,     snrFRNT,        sensorSONAR)
#pragma config(Motor,  motorB,          mtrRHS,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          mtrLHS,        tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//CODE FOR ENGG282 - Concept 2
task main()
{
	while (true)
	{
		motor[mtrRHS] = 30;
	  motor[mtrLHS] = 30;
	  wait1Msec(2000);
	  motor[mtrRHS] = 0;
	  motor[mtrLHS] = 0;
	  wait1Msec(3000);
	}

}
