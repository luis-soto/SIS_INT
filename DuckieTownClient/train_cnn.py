from keras.layers import Dense, Conv2D, MaxPooling2D, Flatten, Dropout
from keras.utils import np_utils
from keras.models import Sequential
from keras.models import model_from_json
import keras
import numpy as np 
import pandas as pd

X = pd.read_csv('data_image.csv')    
Y = pd.read_csv('data_command.csv')

X = np.array(X)
Y = np.array(Y)

X = X.reshape(X.shape[0], 64, 128, 1) 
print(X.shape)

y = np_utils.to_categorical(Y)
print(Y.shape)

x = X/255

model = Sequential()
model.add(Conv2D(8, (5, 5), activation = 'relu', input_shape = (64,128,1)))
model.add(MaxPooling2D(pool_size = (2,2)))
model.add(Flatten())
model.add(Dense(y.shape[1], activation = 'softmax', name = 'predict'))

model.summary()

model.compile(optimizer = 'adam', loss = 'categorical_crossentropy', metrics = ['accuracy'])
model.fit(x, y, epochs = 10)

model_json = model.to_json()
with open("model.json", "w") as json_file:
    json_file.write(model_json)
model.save_weights("model.h5")
print("Saved model to disk")
