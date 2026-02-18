# C:\Users\Admin\shaurya\train_model.py
import numpy as np
import json
from convert_model import model_to_fdeep_json
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
# NEW (Correct, assuming convert_model.py is in the same folder)
# from convert_model import convert_model_to_json
# 1. Generate Fake HFT Data (Features: Last 3 Price Changes)
# 1000 samples, 3 features each (Delta 1, Delta 2, Delta 3)
X_train = np.random.randn(1000, 3)
# Target: 1 (Buy) if the sum of changes is positive, else 0 (Sell)
y_train = (X_train.sum(axis=1) > 0).astype(int)

# 2. Build the Neural Network
model = Sequential()
model.add(Dense(10, input_dim=3, activation='relu'))  # Hidden Layer
model.add(Dense(5, activation='relu'))                # Hidden Layer
model.add(Dense(1, activation='sigmoid'))             # Output Layer

model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])
model.fit(X_train, y_train, epochs=10, batch_size=32, verbose=0)

# 3. Save & Convert for C++
model.save('shaurya_brain.h5')
# NEW CODE
# 1. Convert the model to a dictionary
fdeep_json = model_to_fdeep_json(model)

# 2. Save the dictionary to a file manually
with open('fdeep_model.json', 'w') as f:
    json.dump(fdeep_json, f, allow_nan=False, separators=(',', ':'))
print("[SUCCESS] Model converted to 'shaurya_brain.json'")