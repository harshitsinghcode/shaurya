import numpy as np
import json
from convert_model import model_to_fdeep_json
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
X_train = np.random.randn(1000, 3)
y_train = (X_train.sum(axis=1) > 0).astype(int)

model = Sequential()
model.add(Dense(10, input_dim=3, activation='relu')) 
model.add(Dense(5, activation='relu'))                
model.add(Dense(1, activation='sigmoid'))            

model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])
model.fit(X_train, y_train, epochs=10, batch_size=32, verbose=0)

model.save('shaurya_brain.h5')
fdeep_json = model_to_fdeep_json(model)

with open('fdeep_model.json', 'w') as f:
    json.dump(fdeep_json, f, allow_nan=False, separators=(',', ':'))
print("[SUCCESS] Model converted to 'shaurya_brain.json'")