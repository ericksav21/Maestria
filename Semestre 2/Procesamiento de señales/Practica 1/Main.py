#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np
import math, sys, os
import glob, re
from math import *
import matplotlib.image as mpimg
import matplotlib.cm as cm
import cv2
from keras import layers, models

#path_data = "/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Procesamiento de señales/Tarea 10/dataset/"
path_data = "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Procesamiento de señales/Practica 1/dataset/"
input_dir = path_data.replace("/dataset/", "/input/")
out_dir = path_data.replace("/dataset/", "/output/")

def get_train_sets():
    files_in = sorted(glob.glob(os.path.join(input_dir, "*.jpg")))
    files_out = sorted(glob.glob(os.path.join(out_dir, "*.jpg")))
    train_x = []
    train_y = []
    for file in files_in:
        img_in = cv2.imread(file)
        train_x.append(img_in)
    for file in files_out:
        img_out = cv2.imread(file)
        train_y.append(img_out)

    return train_x, train_y

def main():
    model = models.Sequential()
    model.add(layers.Conv2D(4, (3, 3), activation = 'linear', padding = 'same', input_shape = (64, 64, 1)))
    model.add(layers.Conv2D(3, (3, 3), activation = 'linear', padding = 'same'))
    model.add(layers.Conv2D(1, (3, 3), activation = 'linear', padding = 'same'))
    model.summary()

    model1 = models.Sequential()
    model1.add(layers.Conv2D(4, (3, 3), activation = 'linear', padding = 'same', input_shape = (64, 64, 1)))
    model1.add(layers.Conv2D(3, (3, 3), activation = 'linear', padding = 'same'))
    model1.add(layers.Flatten())
    model1.add(layers.Dense(64 * 64, activation = 'linear'))
    #model1.summary()

    train_x, train_y = get_train_sets()
    model.compile(optimizer = 'rmsprop', loss = 'mse', metrics = ['mae'])
    model.fit(train_x, train_y, epochs = 10, batch_size = 64)

if __name__ == '__main__':
    main()
