import keras
from keras.preprocessing.image import ImageDataGenerator
from keras.applications.mobilenet import preprocess_input

model = keras.models.load_model('C:/Users/Dev4rishi/PycharmProjects/PlantDL/venv/model_updated.h5', compile=True)
eval_datagen= ImageDataGenerator(preprocessing_function=preprocess_input)
eval_generator= eval_datagen.flow_from_directory('D:/plantdisease/Validation',target_size=(224, 224), color_mode='rgb', batch_size=100, class_mode='categorical', shuffle=True )

scores = keras.Model.evaluate_generator(model, eval_generator,steps=100)

print("Accuracy = {}%".format(scores[1]*100))