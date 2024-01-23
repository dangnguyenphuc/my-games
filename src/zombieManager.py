import pygame
import random
from mole import Mole
from sound import SoundManager
from config import *

class ZombieManager:
    def __init__(self, zombie_images, spawn_interval, hole_positions, despawn_interval):
        sound = SoundManager()
        self.zombies = pygame.sprite.Group()
        self.zombie_images = zombie_images
        self.spawn_interval = spawn_interval
        self.last_spawn_time = pygame.time.get_ticks()
        self.last_despawn_time = 0
        self.hole_positions = hole_positions
        self.despawn_interval = despawn_interval
        self.used_hole = [0]*6
        self.sound_manager = sound

    def spawn_zombie(self):
        available_holes = [i for i in range(6) if not self.used_hole[i]]
        if available_holes:
            selected_hole = random.choice(available_holes)
            self.used_hole[selected_hole] = 1
            zombie = Mole(self.zombie_images, self.hole_positions[selected_hole])
            zombie.hole = selected_hole
            zombie.animate()
            self.zombies.add(zombie)
            


    def despawn_zombies(self, current_time):
        if current_time - self.last_despawn_time > self.despawn_interval:
            if self.zombies:
                zombie = self.zombies.sprites()[0]
                self.used_hole[zombie.hole] = 0
                self.zombies.remove(zombie)
                self.last_despawn_time = current_time

    def update_zombies(self, speed=1):
        self.despawn_zombies(pygame.time.get_ticks())
        self.zombies.update(speed=0.1)

    def draw_zombies(self, screen):
        self.zombies.draw(screen)

    def manage_spawn(self, current_time):
        # Kiểm tra và quản lý việc spawn zombie
        if current_time - self.last_spawn_time > self.spawn_interval:
            self.spawn_zombie()
            self.last_spawn_time = current_time

    def check_on_click(self, click_pos, score):
        for zombie in self.zombies:
            if zombie.rect.collidepoint(click_pos):
                # Phát âm thanh khi click trúng zombie
                self.sound_manager.play_sound("hit")
                self.sound_manager.play_sound("dead")
                self.used_hole[zombie.hole] = 0
                self.zombies.remove(zombie)
                score.increase_score()
            else:
                self.sound_manager.play_sound("hit")
                score.increase_miss()
