import os

from PIL import Image, ImageOps

import keras

from keras.applications.mobilenet import preprocess_input
import numpy as np

model = keras.models.load_model('C:/Users/Dev4rishi/PycharmProjects/PlantDL/venv/model_updated.h5', compile=True)
data = np.ndarray(shape=(1, 224, 224, 3), dtype=np.float32)
directory = r'C:/Users/Dev4rishi/Downloads/IMG-1459.jpg'
for filename in os.listdir(directory):
    print(os.path.join(directory, filename))
    image = Image.open(os.path.join(directory, filename))
    size = (224, 224)
    image = ImageOps.fit(image, size, Image.ANTIALIAS)
    image_array = np.asarray(image)
    normalized_image_array = preprocess_input(image_array)
    data[0] = normalized_image_array
    prediction = list(model.predict(data))
    print(prediction)
    mx = 0
    pos = 0
    i = 0
    for i, j in enumerate(prediction[0]):

        if j > mx:
            mx = j
            pos = i

    labels = ['Mango Diseased', 'Mango healthy', 'Pepper Bell Bacterial Spot', 'Pepper Bell Healthy',
              'Potato Early Blight', 'Potato Healthy', 'Potato Late Blight', 'Tomato Target Spot',
              'Tomato Mosaic Virus', 'Tomato Yellow Leaf Curl Virus', 'Tomato Bacterial Spot', 'Tomato Early Blight',
              "Tomato Healthy", 'Tomato Late Blight', 'Tomato Leaf Mold', 'Tomato Septoria Leaf Spot',
              'Tomato Spider Mites']
    print(labels[pos])
