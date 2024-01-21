# This is button class

import pygame

from config import *

class Button:
    def __init__(self, image, scale = 1, xy = None, padding=None, background = None):
        width = image.get_width()
        height = image.get_height()
        self.image = pygame.transform.scale(image, (int(width*scale), int(height*scale)))
        self.rectangle = self.image.get_rect()

        if background:
            bgWidth = background.get_width()
            bgHeight = background.get_height()
            self.background = pygame.transform.scale(background, (int(bgWidth*scale), int(bgHeight*scale)))

        if xy:
            self.rectangle.topleft = (xy[0],xy[1])
        elif padding:
            self.rectangle.topleft = (SCREEN_WIDTH//2 - width//2 - padding[0], SCREEN_HEIGHT//2 - height//2 - padding[1])
        else:
            self.rectangle.topleft = (0,0)
        self.clicked = False

    def draw(self, surface):
        action = False

        mousePosition = pygame.mouse.get_pos()

        if self.rectangle.collidepoint(mousePosition):
            if pygame.mouse.get_pressed()[0] == 1 and self.clicked== False:
                self.clicked = True
                action = True

        if pygame.mouse.get_pressed()[0] == 0:
            self.clicked = False

        if self.background:
            surface.blit(self.image, (self.rectangle.x, self.rectangle.y))
        surface.blit(self.image, (self.rectangle.x, self.rectangle.y))
        return action

