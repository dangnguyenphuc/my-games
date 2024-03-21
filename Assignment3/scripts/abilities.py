import pygame

class Ability:
  def __init__(self, game, a_type, pos, frame=0):
    self.game = game
    self.type = a_type
    self.animation = self.game.assets['abilities/' + a_type].copy()
    self.animation.frame = frame
    self.pos = pos

  def rect(self):
    img = self.animation.img()
    return pygame.Rect(self.pos[0], self.pos[1], img.get_width(), img.get_height())

  def update(self):
    kill = False
    if self.animation.done:
      kill = True
    self.animation.update()
    return kill


  def render(self, surf, offset=(0, 0)):
    img = self.animation.img()
    surf.blit(img, (self.pos[0] - offset[0] - img.get_width() // 2, self.pos[1] - offset[1] - img.get_height() // 2))

class Slash(Ability):
  def __init__(self, game, pos, frame=2):
    super().__init__(game, "slash", pos, frame)

class Boom(Ability):
  def __init__(self, game, pos, frame=5):
    super().__init__(game, "boom", pos, frame)