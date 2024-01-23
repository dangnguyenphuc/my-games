import pygame

class Cursor:
  def __init__(self, sprite, size=None, padding=(0,0)):
    self.sprite = sprite
    self.currentImage = 0
    self.image = self.sprite[self.currentImage]

    self.x = 0
    self.y = 0

    if size:
      self.width = size[0]
      self.height = size[1]
    else:
      self.width = self.image.get_width()
      self.height = self.image.get_height()

    self.rectangle = self.image.get_rect()
    self.padding = padding
    self.isAnimate = False

  def draw(self, surface):
    surface.blit(self.image, (self.x  - self.padding[0], self.y - self.padding[1]))

  def update(self, speed = 1):

    position = pygame.mouse.get_pos()
    self.x = position[0]
    self.y = position[1]
    self.rectangle = pygame.rect.Rect(self.x, self.y, self.width, self.height)

    mouse_presses = pygame.mouse.get_pressed()
    if mouse_presses[0]:
      self.isAnimate = True

    if self.isAnimate:
      self.currentImage += speed
      if self.currentImage >= len(self.sprite):
        self.currentImage = 0
        self.isAnimate = False

      self.image = self.sprite[int(self.currentImage)]
