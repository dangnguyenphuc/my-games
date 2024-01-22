# DEBUG COMPILE TIME ONLY
print("Hello World!")

from config import *
from utils import *

from mole import Mole
from button import Button
from menu import Menu
from cursor import Cursor

pygame.init()

'''MENU VALUES'''
startMenuValues = None
pauseMenuValues = None

'''GAME STATES'''
isStart = False
isRunning = True

'''
init a window screen that has:
    width = SCREEN_WIDTH
    height = SCREEN_HEIGHT
'''
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))

# Set title
pygame.display.set_caption(WINDOW_TITLE)

# Set text font
introFont = pygame.font.Font(
    INTRO_FONT, # file_path
    size = INTRO_FONT_SIZE   # font_size
)
buttonFont = pygame.font.Font(
    BUTTON_FONT,
    size = BUTTON_FONT_SIZE
)

normalFont = pygame.font.Font(
    TEXT_FONT,
    size = TEXT_FONT_SIZE
)

# Images
startImage = buttonFont.render('PLAY', True, BUTTON_TEXT_COLOR)
optionsImage = buttonFont.render('OPTS', True, BUTTON_TEXT_COLOR)
quitImage = buttonFont.render('QUIT', True, BUTTON_TEXT_COLOR)
resumeImage = pygame.image.load("static/image/Prinbles_Asset_UNDER/png/Buttons/Rect/PlayText/Default.png").convert_alpha()
timeImage = pygame.image.load("static/image/Prinbles_Asset_UNDER/png/Counter/Example.png").convert_alpha()
buttonBackgroundImage = pygame.image.load("static/image/Prinbles_Asset_UNDER/png/Button/Rect/Default.png").convert_alpha()

# Game buttons
startButton = Button(startImage, padding=(0,-BUTTON_FONT_SIZE*0), background=buttonBackgroundImage)
optionsButton = Button(optionsImage, padding=(0,-BUTTON_FONT_SIZE*2.5), background=buttonBackgroundImage)
quitButton = Button(quitImage, padding=(0,-BUTTON_FONT_SIZE*5), background=buttonBackgroundImage)
resumeButton = Button(resumeImage, padding=(0,100))

# Game instances
'''Start Menu'''
startMenu = Menu([startButton, optionsButton, quitButton])

'''Pause Menu'''
pauseMenu = Menu([resumeButton])

'''Moving Sprites'''
exampleSprites = pygame.sprite.Group()
frog = Mole([
    pygame.image.load("static/image/example-sprite/attack_1.png").convert_alpha(),
    pygame.image.load("static/image/example-sprite/attack_2.png").convert_alpha(),
    pygame.image.load("static/image/example-sprite/attack_3.png").convert_alpha(),
    pygame.image.load("static/image/example-sprite/attack_4.png").convert_alpha(),
    pygame.image.load("static/image/example-sprite/attack_5.png").convert_alpha(),
    pygame.image.load("static/image/example-sprite/attack_6.png").convert_alpha(),
    pygame.image.load("static/image/example-sprite/attack_7.png").convert_alpha(),
    pygame.image.load("static/image/example-sprite/attack_8.png").convert_alpha(),
    pygame.image.load("static/image/example-sprite/attack_9.png").convert_alpha(),
    pygame.image.load("static/image/example-sprite/attack_10.png").convert_alpha()
], (0,0))
exampleSprites.add(frog)

'''Cursor'''
pygame.mouse.set_cursor(pygame.SYSTEM_CURSOR_HAND)
pygame.mouse.set_visible(True)


hammer = pygame.image.load("static/image/cursor/hammer.png").convert_alpha()
cursor = Cursor([
    hammer,
    pygame.transform.rotate(hammer.copy(), 10),
    pygame.transform.rotate(hammer.copy(), 20),
    pygame.transform.rotate(hammer.copy(), 30),
    pygame.transform.rotate(hammer.copy(), 40),
    pygame.transform.rotate(hammer.copy(), 50)

], padding=(16,25))

# Game clock
clock = pygame.time.Clock()
currentTime = 30
pausedTime = 0


timeImgTemplate = normalFont.render('60:60', True, TEXT_COLOR)
logoImageTemplate = introFont.render(logo[0], True, TEXT_COLOR)
# Game loop
startMenu.setIsDisplay(True)
while isRunning:

    # set window background
    screen.fill(WINDOW_BACKGROUND)


    if startMenu.getIsDisplay():
        currentTime = 0
        pausedTime = pygame.time.get_ticks()

        for i in range(len(logo)):
            drawTextOnScreen(
            screen,
            logo[i],
            introFont,
            TEXT_COLOR,
            SCREEN_WIDTH//2 - logoImageTemplate.get_width()//2 ,
            SCREEN_HEIGHT//2 - logoImageTemplate.get_height()//2 - 250 +INTRO_FONT_SIZE*i)

        startMenuValues = startMenu.getButtonsToggle(screen)

        # if play is pressed
        if startMenuValues[0]:
            startMenu.setIsDisplay(False)

        if startMenuValues[1]:
            pass

        if startMenuValues[-1]:
            isRunning = False
    elif not pauseMenu.getIsDisplay():
        frog.animate()


        screen.blit(timeImage, (SCREEN_WIDTH - timeImage.get_width(),0))

        drawTextOnScreen(
            screen,
            convertGameTime2Minute(PLAY_TIME - currentTime),
            normalFont,
            TEXT_COLOR,
            SCREEN_WIDTH - timeImgTemplate.get_width() - 10,
            10)

        exampleSprites.draw(screen)
        exampleSprites.update(0.25)

        cursor.update(speed = 0.5)
        cursor.draw(screen)

        currentTime = pygame.time.get_ticks() - pausedTime

    else:
        frog.deanimate()
        pausedTime = pygame.time.get_ticks() - currentTime
        pauseMenuValues = pauseMenu.getButtonsToggle(screen, backgroundColor = (255,255,255), border = 0)

        # if resume is pressed
        if pauseMenuValues[0]:
            pauseMenu.setIsDisplay(False)


    for event in pygame.event.get():

        # If pressed any buttons
        if event.type == pygame.KEYDOWN:
            # If pressed PAUSE_KEY
            if event.key == PAUSE_KEY:
                pauseMenu.setIsDisplay(True)
                pygame.mouse.set_visible(True)

        # If quit
        if event.type == pygame.QUIT:
            isRunning = False



    pygame.display.flip()
    clock.tick(FPS)


# Quit PyGame
pygame.quit()
