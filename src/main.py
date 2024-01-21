# DEBUG COMPILE TIME ONLY
print("Hello World!")

from config import *
from utils import *
from mole import *

from button import Button
from menu import Menu

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
    TEXT_FONT, # file_path
    size = 40   # font_size
)
normalFont = pygame.font.Font(
    TEXT_FONT,
    size = 25
)

# Images
startImage = pygame.image.load("static/Prinbles_Asset_UNDER/png/Buttons/Rect/PlayIcon/Default.png").convert_alpha()
resumeImage = pygame.image.load("static/Prinbles_Asset_UNDER/png/Buttons/Rect/PlayText/Default.png").convert_alpha()
timeImage = pygame.image.load("static/Prinbles_Asset_UNDER/png/Counter/Example.png").convert_alpha()

# Game buttons
startButton = Button(startImage, padding=(0,100))
resumeButton = Button(resumeImage, padding=(0,100))

# Game instances
'''Start Menu'''
startMenu = Menu([startButton])

'''Pause Menu'''
pauseMenu = Menu([resumeButton])

'''Moving Sprites'''
exampleSprites = pygame.sprite.Group()
frog = Mole([
    pygame.image.load("static/example-sprite/attack_1.png").convert_alpha(),
    pygame.image.load("static/example-sprite/attack_2.png").convert_alpha(),
    pygame.image.load("static/example-sprite/attack_3.png").convert_alpha(),
    pygame.image.load("static/example-sprite/attack_4.png").convert_alpha(),
    pygame.image.load("static/example-sprite/attack_5.png").convert_alpha(),
    pygame.image.load("static/example-sprite/attack_6.png").convert_alpha(),
    pygame.image.load("static/example-sprite/attack_7.png").convert_alpha(),
    pygame.image.load("static/example-sprite/attack_8.png").convert_alpha(),
    pygame.image.load("static/example-sprite/attack_9.png").convert_alpha(),
    pygame.image.load("static/example-sprite/attack_10.png").convert_alpha()
], (0,0))
exampleSprites.add(frog)


# Game clock
clock = pygame.time.Clock()
currentTime = 30
pausedTime = 0
timeImgTemplate = normalFont.render('60:60', True, TEXT_COLOR)

# Game loop
while isRunning:

    # set window background
    screen.fill(WINDOW_BACKGROUND)


    if not isStart:
        currentTime = 0
        pausedTime = pygame.time.get_ticks()
        pygame.draw.rect(screen, (255,255,255,100), ( SCREEN_WIDTH//2  - 450//2, SCREEN_HEIGHT//2 - 450//2 ,450,450), 0, 15)

        # get button toggle
        if startButton.draw(screen):
            isStart = True
            frog.animate()
    elif not pauseMenu.getIsDisplay():


        drawTextOnScreen(
            screen,
            "Press SPACE to pause",
            introFont,
            TEXT_COLOR,
            160,
            250)

        screen.blit(timeImage, (SCREEN_WIDTH - timeImage.get_width(),0))

        drawTextOnScreen(
            screen,
            convertGameTime2Minute(PLAY_TIME - currentTime),
            normalFont,
            TEXT_COLOR,
            SCREEN_WIDTH - timeImgTemplate.get_width() - 10,
            10)

        exampleSprites.draw(screen)
        exampleSprites.update()

        currentTime = pygame.time.get_ticks() - pausedTime

    else:
        frog.deanimate()
        pausedTime = pygame.time.get_ticks() - currentTime
        pauseMenuValues = pauseMenu.getButtonsToggle(screen, backgroundColor = (255,255,255), border = 0)

        # if resume is pressed
        if pauseMenuValues[0]:
            pauseMenu.setIsDisplay(False)
            frog.animate()


    for event in pygame.event.get():

        # If pressed any buttons
        if event.type == pygame.KEYDOWN:
            # If pressed PAUSE_KEY
            if event.key == PAUSE_KEY:
                pauseMenu.setIsDisplay(True)

        # If quit
        if event.type == pygame.QUIT:
            isRunning = False



    pygame.display.flip()
    clock.tick(FPS)


# Quit PyGame
pygame.quit()
