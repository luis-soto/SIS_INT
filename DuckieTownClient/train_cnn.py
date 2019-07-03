from keras.layers import Dense, Conv2D, MaxPooling2D, Flatten, Dropout, BatchNormalization, Activation
from keras.utils import np_utils
from keras.models import Sequential
from keras.models import model_from_json
from keras import backend
import keras
import numpy as np 
import pandas as pd

X = pd.read_csv('data_image.csv')     
Y = pd.read_csv('data_command.csv')
X_validate = pd.read_csv('data_image_validate.csv')    
Y_validate = pd.read_csv('data_command_validate.csv') 

X = np.array(X)
Y = np.array(Y)
X_validate = np.array(X_validate)
Y_validate = np.array(Y_validate)

X = X.reshape(X.shape[0], 64, 128, 1) 
X_validate = X_validate.reshape(X_validate.shape[0], 64, 128, 1) 
  
y = np_utils.to_categorical(Y)
y_validate = np_utils.to_categorical(Y_validate)

x = X/255
x_validate = X_validate/255

model = Sequential()
model.add(Conv2D(32, kernel_size=(3, 3), activation='relu', input_shape=(64,128,1)))
model.add(Conv2D(64, (3, 3), activation='relu'))
model.add(MaxPooling2D(pool_size=(2, 2)))
model.add(Dropout(0.25))
model.add(Flatten())
model.add(Dense(128, activation='relu'))
model.add(Dropout(0.5))
model.add(Dense(y.shape[1], activation='softmax'))

model.summary()

model.compile(optimizer = keras.optimizers.Adadelta(), loss = keras.losses.categorical_crossentropy, metrics = ['accuracy'])
model.fit(x, y, validation_data = (x_validate, y_validate), epochs = 5, batch_size = 128)

model_json = model.to_json()
with open("model.json", "w") as json_file:
    json_file.write(model_json)
model.save_weights("model.h5")
print("Saved model to disk")
