import pygame

class Mole(pygame.sprite.Sprite):
  def __init__(self, images ,position, deathFrames=None):
    super().__init__()
    self.isAnimate = False
    self.sprite = images
    self.currentSprite = 0
    self.image = self.sprite[self.currentSprite]
    self.rect = self.image.get_rect()
    self.rect.center = position
    self.hole = -1
    self.deathFrames = deathFrames
    self.isDeath = False

  def animate(self):
    self.isAnimate = True

  def deanimate(self):
    self.isAnimate = False

  def update(self, mousePosition, mouse, speed = 1):
    # if self.isAnimate:

      if self.isDeath:
        self.currentSprite += speed
        if self.currentSprite >= len(self.deathFrames):
          self.currentSprite = 0
          self.isDeath = False

        self.image = self.deathFrames[int(self.currentSprite)]

      else:
        self.currentSprite += speed

        if self.currentSprite >= len(self.sprite):
          self.currentSprite = 0

        self.image = self.sprite[int(self.currentSprite)]
        self.rect = self.image.get_rect()

        if self.rect.collidepoint(mousePosition) and mouse[0]:
          self.isDeath = True
          self.currentSprite = 0
