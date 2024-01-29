import pygame
from config import *
class SoundManager:
    def __init__(self):
        pygame.mixer.init()
        self.sound_effects = {}
        self.load_sound("hit", SOUND_HIT)
        self.load_sound("dead", SOUND_DEAD)
        self.load_sound("miss", SOUND_MISS)

    def load_sound(self, sound_name, file_path):
        sound = pygame.mixer.Sound(file_path)
        self.sound_effects[sound_name] = sound

    def play_sound(self, sound_name):
        if sound_name in self.sound_effects:
            self.sound_effects[sound_name].play()
        else:
            print(f"Sound '{sound_name}' not found.")