// Copyright 2006-2016 Coppelia Robotics GmbH. All rights reserved.
// marc@coppeliarobotics.com
// www.coppeliarobotics.com
//----------------------------------------------------------------------------------------------------
// THIS FILE IS DISTRIBUTED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
// WARRANTY. THE USER WILL USE IT AT HIS/HER OWN RISK. THE ORIGINAL
// AUTHORS AND COPPELIA ROBOTICS GMBH WILL NOT BE LIABLE FOR DATA LOSS,
// DAMAGES, LOSS OF PROFITS OR ANY OTHER KIND OF LOSS WHILE USING OR
// MISUSING THIS SOFTWARE.
//
// You are free to use/modify/distribute this file for whatever purpose!
//----------------------------------------------------------------------------------------------------
//
// This file was automatically created for V-REP release V3.3.0 on February 19th 2016
//----------------------------------------------------------------------------------------------------
// Make sure to have the server side running in V-REP!
// Start the server from a child script with following command:
// simExtRemoteApiStart(portNumber) -- starts a remote API server service on the specified port
//----------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "flie.h"
//----------------------------------------------------------------------------------------------------
extern "C"
{
    #include "extApi.h"
}
//----------------------------------------------------------------------------------------------------
// calcular a posicao no vetor de imagem, para um pixel em "linha,coluna". Inicio embaixo a esquerda,
// uma linha por vez, até o topo a direita. Canal 0=R,1=G,2=B
int getposition(int linha, int coluna, int canal, int resolucaoX, int resolucaoY)
{
	if((linha < (resolucaoX))&&(coluna < (resolucaoY)))
	return(linha * ((resolucaoX - 1)*3) + coluna*3 + canal);
	else
	return(0);
}
//----------------------------------------------------------------------------------------------------
int getpos(int lin, int col, int canal)
{
 	return(getposition(lin, col, canal, 128, 128));
}
//----------------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	configFuzzy();
	int portNb=0;
	int leftMotorHandle;
	int rightMotorHandle;
	int sensorHandle[6];
	float distanceSensor[6];
	int count=0;

	if(argc >= 5)
	{
		portNb=atoi(argv[1]);
		leftMotorHandle=atoi(argv[2]);
		rightMotorHandle=atoi(argv[3]);
		sensorHandle[0]=atoi(argv[4]);
		sensorHandle[1]=atoi(argv[5]);
		sensorHandle[2]=atoi(argv[6]);
		sensorHandle[3]=atoi(argv[7]);
		sensorHandle[4]=atoi(argv[8]);
		sensorHandle[5]=atoi(argv[9]);
	}
	else
	{
		printf("Indicate following arguments: 'portNumber leftMotorHandle rightMotorHandle sensorHandle[1..6]'!\n");
		extApi_sleepMs(5000);
		return 0;
	}

	int clientID=simxStart((simxChar*)"127.0.0.1",portNb,true,true,2000,5);

    if(clientID != -1)
	{

		for(int i = 0; i < 6; i++)
        {
            simxReadProximitySensor(clientID, sensorHandle[i], NULL, NULL, NULL, NULL, simx_opmode_streaming);
        }

		int driveBackStartTime = -99000;
		float motorSpeeds[2];

		while(simxGetConnectionId(clientID) != -1)
		{
		    int passive;
		    int resolution[2];
		    simxUChar* image;

		    simxGetObjectHandle(clientID,"ePuck_camera#0",&passive,simx_opmode_blocking);
		    simxGetVisionSensorImage(clientID,passive,resolution,&image,0,simx_opmode_streaming);

	            if(simxGetVisionSensorImage(clientID,passive,resolution,&image,0,simx_opmode_buffer) == 0)
	            {
	                printf("Resolution: %d x %d Data:image[1][1](RGB) = %d,%d,%d\n",
                           resolution[0], resolution[1], image[0], image[1], image[2]);
	                printf("Data:(canto inferior direito) image[][](RGB) -> image[%d]=%d,image[%d]=%d,image[%d]=%d\n",
                           127*3+0, image[127*3+0],127*3+1, image[127*3+1], 127*3+2, image[127*3+2]);
	                printf("Data:(canto inferior direito) image[][](RGB) -> %d,%d,%d\n", image[getpos(0,127,0)],
                           image[getpos(0,127, 1)], image[getpos(0,127,2)]);
	                printf("Data:(canto superior esquerdo) image[][](RGB)-> image[%d]=%d,image[%d]=%d,image[%d]=%d\n",
                           resolution[0]*3*(resolution[1]-1)+0, image[resolution[0]*3*(resolution[1]-1)+0],
                           resolution[0]*3*(resolution[1]-1)+1, image[resolution[0]*3*(resolution[1]-1)+1],
                           resolution[0]*3*(resolution[1]-1)+2, image[resolution[0]*3*(resolution[1]-1)+2]);
	                printf("Data:(canto superior direito) image[][](RGB) -> image[%d]=%d,image[%d]=%d,image[%d]=%d\n",
                           128*3*128-3, image[128*3*128-3], 128*3*128-2, image[128*3*128-2], 128*3*128-1, image[128*3*128-1]);
	                printf("Data:(canto superior direito) image[][](RGB) -> %d,%d,%d\n",
                           image[getpos(127,127,0)], image[getpos(127,127, 1)], image[getpos(127,127,2)]);
                }

            for(int i = 0; i < 6; i++)
            {
                float distanceAxis[4];
                distanceSensor[i] = 40.0;

                simxReadProximitySensor(clientID, sensorHandle[i], NULL, &(distanceAxis[0]), NULL,
                                        NULL, simx_opmode_buffer);
                float distance = pow(distanceAxis[0],2) + pow(distanceAxis[1],2) + pow(distanceAxis[2],2);

                distance = sqrt(distance);
                distanceSensor[i] = distance;

                if(distanceSensor[i] > 0.040)
                {
                    distanceSensor[i] = 40.0;
                }
                else
                {
                    distanceSensor[i] = distanceSensor[i]*1000;
                }
            }

            float distLeft, distCenter, distRight;

            distLeft = distanceSensor[1];
            distCenter = (distanceSensor[2] + distanceSensor[3])/2;
            distRight = distanceSensor[4];

            std::cout << endl <<"Distance Sensor Left: " << distLeft << endl;
            std::cout <<"Distance Sensor Center: " << distCenter << endl;
            std::cout <<"Distance Sensor Right: " << distRight << endl;

            for(int i = 0; i < 6; i++)
            {
                std::cout << "Distance Sensor " << i << " valor: " << distanceSensor[i] << endl;
            }
            std::cout << endl;

            motorSpeeds[0] = leftMotorInference(distLeft,distCenter,distRight);
            motorSpeeds[1] = rightMotorInference(distLeft,distCenter,distRight);

            simxSetJointTargetVelocity(clientID,leftMotorHandle,motorSpeeds[0],simx_opmode_oneshot);
            simxSetJointTargetVelocity(clientID,rightMotorHandle,motorSpeeds[1],simx_opmode_oneshot);

            // extApi_sleepMs(50);
	    }
	    simxFinish(clientID);
 	}
	return(0);
}
//----------------------------------------------------------------------------------------------------
