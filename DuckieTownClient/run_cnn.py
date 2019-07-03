from keras.layers import Dense, Conv2D, MaxPooling2D, Flatten, Dropout
from keras.utils import np_utils
from keras.models import Sequential
from keras.models import model_from_json
import keras
import vrep
import numpy as np 
import cv2 
json_file = open('model.json', 'r')      
loaded_model_json = json_file.read()
json_file.close()
loaded_model = model_from_json(loaded_model_json)
loaded_model.load_weights("model.h5")
print("Loaded model from disk")

loaded_model.compile(optimizer = 'adam', loss = 'categorical_crossentropy', metrics = ['accuracy'])

print('Program started')
vrep.simxFinish(-1) # just in case, close all opened connections
clientID=vrep.simxStart('127.0.0.1',19997,True,True,5000,5)

if(clientID != -1):
    print('Connected to remote API server')

    res,v0=vrep.simxGetObjectHandle(clientID,'ePuck_camera#0',vrep.simx_opmode_oneshot_wait)
    _,leftMotorID = vrep.simxGetObjectHandle(clientID,'ePuck_leftJoint#0',vrep.simx_opmode_oneshot_wait)
    _,rightMotorID = vrep.simxGetObjectHandle(clientID,'ePuck_rightJoint#0',vrep.simx_opmode_oneshot_wait)

    err,resolution,image = vrep.simxGetVisionSensorImage(clientID, v0, 1, vrep.simx_opmode_streaming)

    while(vrep.simxGetConnectionId(clientID) != -1):
        err,resolution,image = vrep.simxGetVisionSensorImage(clientID, v0, 1, vrep.simx_opmode_buffer)
        if(err == vrep.simx_return_ok):
            image = np.array(image, dtype = np.uint8)
            image = np.reshape(image, (1, 128*128))
            image = image[0:1,0:128*64]
            image = np.array(image, dtype=float)/255
            image = np.reshape(image, (1, 64, 128, 1))
            prediction = loaded_model.predict_classes(image)
            print(prediction)
            # image = np.reshape(image, (64, 128, 1))
            # image = np.flip(image, 0)
            # image = cv2.resize(image, (128*4, 64*4))
            # cv2.imshow("img", image)
            # cv2.waitKey(1)
            if(prediction == 2):
                vrep.simxSetJointTargetVelocity(clientID, leftMotorID, 3.14/2.0, vrep.simx_opmode_oneshot)		
                vrep.simxSetJointTargetVelocity(clientID, rightMotorID, 3.14/4.0, vrep.simx_opmode_oneshot)
            elif(prediction == 1):
                vrep.simxSetJointTargetVelocity(clientID, leftMotorID, 3.14/4.0, vrep.simx_opmode_oneshot)		
                vrep.simxSetJointTargetVelocity(clientID, rightMotorID, 3.14/2.0, vrep.simx_opmode_oneshot)
            else:
                vrep.simxSetJointTargetVelocity(clientID, leftMotorID, 3.14/2.0, vrep.simx_opmode_oneshot)		
                vrep.simxSetJointTargetVelocity(clientID, rightMotorID, 3.14/2.0, vrep.simx_opmode_oneshot)

