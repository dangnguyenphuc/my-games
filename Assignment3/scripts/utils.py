import os

import pygame
from scripts.config import *

BASE_IMG_PATH = 'data/images/'

def calculate_distance(pos1, pos2):
    return abs(pos1[0] - pos2[0]) + abs(pos1[1] - pos2[1])

def myFunc(e):
    return e.split('.')[0]

def load_image(path, scale = 1):
    img = pygame.transform.scale_by(pygame.image.load(BASE_IMG_PATH + path).convert(), scale)
    img.set_colorkey((0, 0, 0))
    return img

def load_images(path, scale = 1):
    images = []
    for img_name in sorted(os.listdir(BASE_IMG_PATH + path)):
        images.append(load_image(path + '/' + img_name, scale = scale))
    return images

class Animation:
    def __init__(self, images, img_dur=5, loop=True):
        self.images = images
        self.loop = loop
        self.img_duration = img_dur
        self.done = False
        self.frame = 0

    def copy(self):
        return Animation(self.images, self.img_duration, self.loop)

    def update(self):
        if self.loop:
            self.frame = (self.frame + 1) % (self.img_duration * len(self.images))
        else:
            self.frame = min(self.frame + 1, self.img_duration * len(self.images) - 1)
            if self.frame >= self.img_duration * len(self.images) - 1:
                self.done = True

    def img(self):
        return self.images[int(self.frame / self.img_duration)]

class Timer:
    def __init__(self, time):
        self.time = time*FPS
        self.currentTime = time*FPS

    def reset(self):
        self.currentTime = self.time

    def run(self):
        self.currentTime -= 1

    def getFlag(self):
        self.run()
        if self.currentTime <= 0:
            self.reset()
            return True
        return False
