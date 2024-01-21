import pygame

class Mole(pygame.sprite.Sprite):
  def __init__(self, images ,position):
    super().__init__()
    self.isAnimate = False
    self.sprite = images
    self.currentSprite = 0
    self.image = self.sprite[self.currentSprite]
    self.rect = self.image.get_rect()
    self.rect.topleft = position

  def animate(self):
    self.isAnimate = True

  def deanimate(self):
    self.isAnimate = False

  def update(self):
    if self.isAnimate:
      self.currentSprite += 1

      if self.currentSprite >= len(self.sprite):
        self.currentSprite = 0

      self.image = self.sprite[self.currentSprite]