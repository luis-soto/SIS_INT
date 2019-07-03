import vrep
import matplotlib.pyplot as plt
import time
import numpy as np
import keyboard
import cv2

print('Program started')

vrep.simxFinish(-1)
clientID=vrep.simxStart('127.0.0.1',19997,True,True,5000,5)

if(clientID != -1):
    print('Connected to remote API server')

    res,v0=vrep.simxGetObjectHandle(clientID, 'ePuck_camera#0', vrep.simx_opmode_oneshot_wait)
    _,leftMotorID = vrep.simxGetObjectHandle(clientID, 'ePuck_leftJoint#0', vrep.simx_opmode_oneshot_wait)
    _,rightMotorID = vrep.simxGetObjectHandle(clientID, 'ePuck_rightJoint#0', vrep.simx_opmode_oneshot_wait)

    while True: # Pressionar tecla "q" para iniciar a captura de dados
        if keyboard.is_pressed('q'): 
            time.sleep(0.5)
            break

    err,resolution,image = vrep.simxGetVisionSensorImage(clientID, v0, 1, vrep.simx_opmode_streaming)

    while(vrep.simxGetConnectionId(clientID) != -1):
        err,resolution,image = vrep.simxGetVisionSensorImage(clientID, v0, 1, vrep.simx_opmode_buffer)
        if(err == vrep.simx_return_ok):
            image = np.array(image, dtype = np.uint8)
            image = np.reshape(image, (1, 128*128))
            image = image[0:1,0:128*64]     # Somente a metade inferior da imagem é selecionada
            image = np.reshape(image, (1, 128*64))
            if(keyboard.is_pressed('q')):   # Programa é encerrado caso a tecla "q" seja pressionada
                break
            elif(keyboard.is_pressed('d')): # Carrinho vira a direita caso a tecla "d" seja pressionada
                vrep.simxSetJointTargetVelocity(clientID, leftMotorID, 3.14/2.0, vrep.simx_opmode_oneshot)		
                vrep.simxSetJointTargetVelocity(clientID, rightMotorID, 3.14/4.0, vrep.simx_opmode_oneshot)
                button = 2
            elif(keyboard.is_pressed('a')): # Carrinho vira a esquerda caso a tecla "a" seja pressionada
                vrep.simxSetJointTargetVelocity(clientID, leftMotorID, 3.14/4.0, vrep.simx_opmode_oneshot)		
                vrep.simxSetJointTargetVelocity(clientID, rightMotorID, 3.14/2.0, vrep.simx_opmode_oneshot)
                button = 1
            else:
                vrep.simxSetJointTargetVelocity(clientID, leftMotorID, 3.14/2.0, vrep.simx_opmode_oneshot)		
                vrep.simxSetJointTargetVelocity(clientID, rightMotorID, 3.14/2.0, vrep.simx_opmode_oneshot)
                button = 0
            with open("data_image.csv","a") as data_image:      # Dados da imagem são salvos no arquivo data_image.csv
                np.savetxt(data_image, image, delimiter=",", fmt='%i')
            with open("data_command.csv","a") as data_command:  # Comando é salvo no arquivo data_command.csv
                data_command.write(str(button))
                data_command.write('\n')
            # image = np.reshape(image,(64,128))
            # image = np.flip(image,0)
            # resized = cv2.resize(image, (64*4,128*2))
            # cv2.imshow("Camera", resized)
            # cv2.waitKey(1)

else:
    print('Failed connecting to remote API server')
print('Program ended')
