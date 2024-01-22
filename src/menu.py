# this is MENU class
from button import Button
from config import *
import pygame

class Menu:
    def __init__(self, buttons ,menuBackground=None, size = (500,500), xy = None):

        self.menuBackground = menuBackground
        self.size = size
        if xy:
            self.x = xy[0]
            self.y = xy[1]

        else:

            #center align
            self.x = SCREEN_WIDTH // 2 - size[0] // 2
            self.y = SCREEN_HEIGHT // 2 - size[1] // 2

        self.isDisplay = False
        self.buttonsValue = [False] * len(buttons)
        self.buttons = buttons


    # draw buttons, also get buttons value
    def getButtonsToggle(self, surface, backgroundColor = None, border = 0):
        if self.isDisplay:

            # draw background
            if self.menuBackground:
                surface.blit(self.menuBackground, (self.x, self.y))
            elif backgroundColor:
                pygame.draw.rect(surface, backgroundColor, (self.x, self.y, self.size[0], self.size[1]) , border)

            for i in range(len(self.buttons)):
                self.buttonsValue[i] = self.buttons[i].draw(surface)

        return self.buttonsValue

    def setButtonValue2False(self, buttonIndex = None, value=False):
        if buttonIndex:
            self.buttonsValue[buttonIndex] = value
        else:
            self.buttonsValue = [value] * len(self.buttons)

    def setIsDisplay(self, value):
        self.isDisplay = value

    def getIsDisplay(self):
        return self.isDisplay
