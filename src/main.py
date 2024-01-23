# DEBUG COMPILE TIME ONLY
print("Hello World!")

from config import *
from utils import *

from gamestate import GameState
from mole import Mole
from button import Button
from menu import Menu
from cursor import Cursor
from zombieManager import ZombieManager
from score import ScoreManager
from slider import Slider

pygame.init()


# FONTS
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

sliderFont = pygame.font.Font(
    SLIDER_FONT,
    size = SLIDER_FONT_SIZE
)

'''MENU VALUES'''
startMenuButtonValues = None
pauseMenuButtonValues = None

'''
init a window screen that has:
    width = SCREEN_WIDTH
    height = SCREEN_HEIGHT
'''
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))

# Set title
pygame.display.set_caption(WINDOW_TITLE)

# Images
startImage = buttonFont.render('PLAY', True, BUTTON_TEXT_COLOR)
optionsImage = buttonFont.render('OPTS', True, BUTTON_TEXT_COLOR)
quitImage = buttonFont.render('QUIT', True, BUTTON_TEXT_COLOR)
soundImage = normalFont.render("Sound", True, BUTTON_TEXT_COLOR)
soundImagePosition = (SCREEN_WIDTH//2 - soundImage.get_width() - 50 ,
                        SCREEN_HEIGHT//2 - 5 )

timeImage = pygame.image.load("static/image/Prinbles_Asset_UNDER/png/Counter/Example.png").convert_alpha()
background_image = pygame.image.load("static/image/background/background.png")
backImage = pygame.image.load("static/image/Prinbles_Asset_UNDER/png/Icon/ArrowLeft-Thin.png").convert_alpha()
buttonBackgroundImage = pygame.image.load("static/image/Prinbles_Asset_UNDER/png/Button/Rect/Default.png").convert_alpha()

sliderBackgroundImage = pygame.image.load("static/image/Prinbles_Asset_UNDER/png/Load/Magazine/Dummy.png")
sliderBackgroundImage = sliderBackgroundImage.subsurface(3, 3, sliderBackgroundImage.get_width()-3, sliderBackgroundImage.get_height()-3)

homeImage = pygame.image.load("static/image/Prinbles_Asset_UNDER/png/Buttons/Square/Home/Default.png").convert_alpha()
resumeImage = pygame.image.load("static/image/Prinbles_Asset_UNDER/png/Buttons/Square/Play/Default.png").convert_alpha()
repeatImage = pygame.image.load("static/image/Prinbles_Asset_UNDER/png/Buttons/Square/Repeat/Default.png").convert_alpha()

timeImgTemplate = normalFont.render('60:60', True, TEXT_COLOR)
logoImageTemplate = introFont.render(logo[0], True, TEXT_COLOR)
background_image = pygame.image.load("static/image/background/background.png")

# Game buttons
startButton = Button(startImage, padding=(0,-BUTTON_FONT_SIZE*0), background=buttonBackgroundImage)
optionsButton = Button(optionsImage, padding=(0,-BUTTON_FONT_SIZE*2.5), background=buttonBackgroundImage)
quitButton = Button(quitImage, padding=(0,-BUTTON_FONT_SIZE*5), background=buttonBackgroundImage)

homeButton = Button(homeImage, padding=(-100,0))
repeatButton = Button(repeatImage, padding=(0,0))
resumeButton = Button(resumeImage, padding=(100,0))
backButton = Button(backImage, padding=(125,90))

# Sliders
soundSlider = Slider(
    position=(SCREEN_WIDTH // 2 - 15, SCREEN_HEIGHT//2),
    size = (100,30),
    initValue = 0.5,
    minValue = 0,
    maxValue = 200,
    containerBackground = sliderBackgroundImage,
    padding = (14,10)
)

# Game instances
'''Start Menu'''
startMenu = Menu([startButton, optionsButton, quitButton])

'''Pause Menu'''
pauseMenu = Menu([resumeButton, repeatButton, homeButton], size = (300,100))

'''Opts Menu'''
optionsMenu = Menu(
    [backButton],
    sliders = [soundSlider],
    images = [soundImage],
    imagesPosition = [soundImagePosition],
    size = (300,250)
)

'''Moving Sprites'''
zombie = load_sprite_sheet('static/image/zombie/zombie.png', rows=5, cols=5, scale=1)


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

], padding=(16,45))
mouse = None
mousePosition = None


# Game clock
clock = pygame.time.Clock()
playTimer = Timer(PLAY_TIME)


# Score manager
score = ScoreManager()

holes_pos = [(110,550), (370, 550), (620, 550), (160, 470), (370, 470), (580, 470)]
zombies_manager = ZombieManager(zombie, 2000, holes_pos, 3000)

# sounds
pygame.mixer.music.load(backgroundSoundPath)
pygame.mixer.music.set_volume(backgroundSoundVolume)
pygame.mixer.music.play(-1)


zombie_imgs = [
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
]

death_imgs = load_sprite_sheet("static/image/zombie/zombie.png", 5,5)
frog = Mole(zombie_imgs, (40,40), deathFrames=death_imgs)

exampleSprites = pygame.sprite.Group()
exampleSprites.add(frog)


'''GAME STATES'''
gameState = GameState.IS_START


# Game loop
startMenu.setIsDisplay(True)
while gameState:
    # get mouse pressed and mouse positions
    mouse = pygame.mouse.get_pressed()
    mousePosition = pygame.mouse.get_pos()

    # Handle Options Menu
    if gameState ==  GameState.OPEN_OPTS:
        optValue = optionsMenu.draw(screen, mousePosition, mouse, backgroundColor = (10,220,10), border = 0, sliderFont = sliderFont)

        if optValue["buttons"][0]:
            optionsMenu.setIsDisplay(False)
            startMenu.setIsDisplay(True)
            gameState =  GameState.IS_START

        pygame.mixer.music.set_volume(optValue["sliders"][0]/100)

    elif gameState ==  GameState.IS_START:

        # set window background
        screen.fill(WINDOW_BACKGROUND)

        for i in range(len(logo)):
            drawTextOnScreen(
            screen,
            logo[i],
            introFont,
            (255-i*25, 255, 255-i*25),
            SCREEN_WIDTH//2 - logoImageTemplate.get_width()//2 ,
            SCREEN_HEIGHT//2 - logoImageTemplate.get_height()//2 - 250 +INTRO_FONT_SIZE*i)


        startMenuButtonValues = startMenu.draw(screen, mousePosition, mouse)['buttons']

        # if play is pressed
        if startMenuButtonValues[0]:
            startMenu.setIsDisplay(False)
            playTimer.resetTimer()
            gameState =  GameState.IS_PLAY

        if startMenuButtonValues[1]:
            startMenu.setIsDisplay(False)
            optionsMenu.setIsDisplay(True)
            gameState =  GameState.OPEN_OPTS

        if startMenuButtonValues[2]:
            isRunning = False
            gameState = GameState.IS_EXIT

    elif gameState ==  GameState.IS_PLAY:

        screen.blit(background_image, (0, 0))
        zombies_manager.manage_spawn(playTimer.currentTime)
        zombies_manager.update_zombies()
        zombies_manager.draw_zombies(screen)

        screen.blit(timeImage, (SCREEN_WIDTH - timeImage.get_width(),0))

        drawTextOnScreen(
            screen,
            "SCORE: " + str(score.score),
            introFont,
            TEXT_COLOR,
            150,
            20)

        drawTextOnScreen(
            screen,
            "MISS: " + str(score.miss),
            introFont,
            TEXT_COLOR,
            400,
            20)

        drawTextOnScreen(
            screen,
            convertGameTime2Minute(playTimer.currentTime),
            normalFont,
            TEXT_COLOR,
            SCREEN_WIDTH - timeImgTemplate.get_width() - 10,
            10)

        cursor.update(mousePosition, mouse,speed = 0.6)
        cursor.draw(screen)

        playTimer.runTimer()

        if playTimer.getFlag():
            gameState = GameState.IS_COMPLETE

    elif gameState == GameState.IS_PAUSE:

        pauseMenuButtonValues = pauseMenu.draw(screen, mousePosition, mouse, backgroundColor = (255,255,255), border = 0)['buttons']

        # print(pauseMenuButtonValues)
        # if resume is pressed
        if pauseMenuButtonValues[0]:
            pauseMenu.setIsDisplay(False)
            gameState =  GameState.IS_PLAY

        # if replay
        if pauseMenuButtonValues[1]:
            pauseMenu.setIsDisplay(False)
            playTimer.resetTimer()
            gameState =  GameState.IS_PLAY

        if pauseMenuButtonValues[2]:
            pauseMenu.setIsDisplay(False)
            startMenu.setIsDisplay(True)
            playTimer.resetTimer()
            gameState =  GameState.IS_START

    elif gameState == GameState.IS_COMPLETE:
        playTimer.resetTimer()
        pass

    for event in pygame.event.get():

        # If pressed any buttons
        if gameState == GameState.IS_PLAY:
            if event.type == pygame.KEYDOWN:

                # If pressed PAUSE_KEY
                if event.key == PAUSE_KEY:
                    pauseMenu.setIsDisplay(True)
                    pygame.mouse.set_visible(True)
                    gameState = GameState.IS_PAUSE

        # If click left mouse
        # if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
        #     click_pos = pygame.mouse.get_pos()
        zombies_manager.check_on_click(mousePosition, mouse, score)

        # If quit
        if event.type == pygame.QUIT:
            gameState = GameState.IS_EXIT

    exampleSprites.draw(screen)
    exampleSprites.update(mousePosition, mouse, 0.1)

    pygame.display.flip()
    clock.tick(FPS)


# Quit PyGame
pygame.mixer.music.stop()
pygame.quit()