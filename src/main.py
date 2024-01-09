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
font = pygame.font.Font(
    TEXT_FONT, # file_path
    size = 40   # font_size
)

# Images
resumeImage = pygame.image.load("static/Prinbles_Asset_UNDER/png/Buttons/Rect/PlayText/Default.png").convert_alpha()



# Game instances
resumeButton = Button(resumeImage, 1, padding=(0,100))

# Game loop
isRunning = True 
while isRunning:
    
    # set window background
    screen.fill(WINDOW_BACKGROUND)
    
    if not isPaused:
        drawTextOnScreen(screen, "Press SPACE to pause", font, TEXT_COLOR, 160, 250)
    else:
        
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

# Quit PyGame
pygame.quit()
