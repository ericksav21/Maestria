from keras.datasets import mnist
from keras.utils import to_categorical
from keras import layers
from keras import models

(train_images, train_labels), (test_images, test_labels) = mnist.load_data()
num_pixels = train_images.shape[1] * train_images.shape[2]
train_images = train_images.reshape(train_images.shape[0], num_pixels)
train_images = train_images.astype('float32') / 255.0

test_images = test_images.reshape(test_images.shape[0], num_pixels)
test_images = test_images.astype('float32') / 255.0

train_labels = to_categorical(train_labels)
test_labels = to_categorical(test_labels)

val_images = test_images[0 : 5000, :]
val_labels = test_labels[0 : 5000, :]
test_images = test_images[5000 : -1, :]
test_labels = test_labels[5000 : -1, :]

model = models.Sequential()
model.add(layers.Dense(num_pixels, activation = 'relu', input_dim = num_pixels))
model.add(layers.Dense(50, activation = 'relu'))
#model.add(layers.Dense(50, activation = 'relu'))
model.add(layers.Dense(10, activation = 'softmax'))

#model.summary()
model.compile(optimizer = 'rmsprop', loss = 'categorical_crossentropy', metrics = ['accuracy'])
model.fit(train_images, train_labels, epochs = 20, batch_size = 64, validation_data = (val_images, val_labels))
score = model.evaluate(test_images, test_labels, verbose = 0)
print("Error: %.2f%%" % (100.0 - score[1] * 100))
