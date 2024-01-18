# DEBUG COMPILE TIME ONLY
print("Hello World!")

from config import *
from utils import *

from button import Button

pygame.init()

'''GAME STATES'''
isPaused = False


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
    size = 30
)

# Images
startImage = pygame.image.load("static/Prinbles_Asset_UNDER/png/Buttons/Rect/PlayIcon/Default.png").convert_alpha()
resumeImage = pygame.image.load("static/Prinbles_Asset_UNDER/png/Buttons/Rect/PlayText/Default.png").convert_alpha()
timeImage = pygame.image.load("static/Prinbles_Asset_UNDER/png/Counter/Example.png").convert_alpha()

# Game buttons
startButton = Button(startImage, 1, padding=(0,100))
resumeButton = Button(resumeImage, 1, padding=(0,100))



# Game clock
clock = pygame.time.Clock()
currentTime = 30
pausedTime = 0
timeImgTemplate = normalFont.render('60:60', True, TEXT_COLOR)

# Game loop
isRunning = True
isStart = False
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
    elif not isPaused:


        drawTextOnScreen(screen, "Press SPACE to pause", introFont, TEXT_COLOR, 160, 250)
        drawTextOnScreen(screen, convertGameTime2Minute(PLAY_TIME - currentTime), normalFont, TEXT_COLOR,
                                SCREEN_WIDTH - timeImgTemplate.get_width(),0)

        currentTime = pygame.time.get_ticks() - pausedTime

    else:
        pausedTime = pygame.time.get_ticks() - currentTime
        pygame.draw.rect(screen, (255,255,255,100), ( SCREEN_WIDTH//2  - 450//2, SCREEN_HEIGHT//2 - 450//2 ,450,450), 0, 15)

        # display buttons
        if resumeButton.draw(screen):
            isPaused = False

    for event in pygame.event.get():

        # If pressed any button
        if event.type == pygame.KEYDOWN:
            # If pressed PAUSE_KEY
            if event.key == PAUSE_KEY:
                isPaused = True
        # If quit
        if event.type == pygame.QUIT:
            isRunning = False



    pygame.display.update()
    clock.tick(FPS)


# Quit PyGame
pygame.quit()
