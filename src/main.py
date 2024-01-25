# DEBUG COMPILE TIME ONLY
print("Hello World!")

from config import *
from utils import *

from sound import SoundManager
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
pauseImage = pygame.font.Font(BUTTON_FONT,size = 70).render('PAUSE', True, BUTTON_TEXT_COLOR)
completeImage = pygame.font.Font(BUTTON_FONT,size = 50).render('HOORAY !!!', True, (0,0,0))
scoreImage = pygame.font.Font(BUTTON_FONT,size = 25).render('SCORE: ', True, (0,0,0))
missImage = pygame.font.Font(BUTTON_FONT,size = 25).render('MISS: ', True, (0,0,0))
startImage = buttonFont.render('PLAY', True, BUTTON_TEXT_COLOR)
optionsImage = buttonFont.render('OPTS', True, BUTTON_TEXT_COLOR)
quitImage = buttonFont.render('QUIT', True, BUTTON_TEXT_COLOR)
soundImage = normalFont.render("Sound", True, (0,0,0))
timeTextImage = normalFont.render("Time", True, (0,0,0))
modeTextImage = normalFont.render("Mode", True, (0,0,0))
timeImage = pygame.image.load("static/image/Prinbles_Asset_UNDER/png/Counter/Example.png").convert_alpha()
background_image = pygame.image.load("static/image/background/background.png")
backImage = pygame.image.load("static/image/Prinbles_Asset_UNDER/png/Icon/ArrowLeft-Thin.png").convert_alpha()
buttonBackgroundImage = pygame.image.load("static/image/Prinbles_Asset_UNDER/png/Button/Rect/Default.png").convert_alpha()
menuBackgroundImage = pygame.image.load("static/image/Prinbles_Asset_UNDER/png/Level/Button/Dummy.png").convert_alpha()
optsImage = pygame.image.load("static/image/Prinbles_Asset_UNDER/png/Icon/Levels.png").convert_alpha()
sliderBackgroundImage = pygame.image.load("static/image/Prinbles_Asset_UNDER/png/Load/Magazine/Dummy.png").convert_alpha()
squareButtonImage = pygame.image.load("static/image/Prinbles_Asset_UNDER/png/Button/Square/Default.png").convert_alpha()
homeImage = pygame.image.load("static/image/Prinbles_Asset_UNDER/png/Buttons/Square/Home/Default.png").convert_alpha()
resumeImage = pygame.image.load("static/image/Prinbles_Asset_UNDER/png/Buttons/Square/Play/Default.png").convert_alpha()
repeatImage = pygame.image.load("static/image/Prinbles_Asset_UNDER/png/Buttons/Square/Repeat/Default.png").convert_alpha()
timeImgTemplate = normalFont.render('60:60', True, TEXT_COLOR)
logoImageTemplate = introFont.render(logo[0], True, TEXT_COLOR)
background_image = pygame.image.load("static/image/background/background.png")

# Image Positions
pauseImagePosition = (SCREEN_WIDTH//2 - pauseImage.get_width()//2,
                        SCREEN_HEIGHT//2 - pauseImage.get_height()//2 - 40)
soundImagePosition = (SCREEN_WIDTH//2 - soundImage.get_width() - 65 ,
                        SCREEN_HEIGHT//2 - 5 )
timeTextImagePosition = (SCREEN_WIDTH//2 - soundImage.get_width() - 65 ,
                        SCREEN_HEIGHT//2 + 45 )
modeTextImagePosition = (SCREEN_WIDTH//2 - soundImage.get_width() - 65 ,
                        SCREEN_HEIGHT//2 + 95 )
completeImagePosition = (SCREEN_WIDTH//2 - completeImage.get_width() // 2 ,
                        SCREEN_HEIGHT//2 - completeImage.get_height() // 2 - 50)
scoreImagePosition = (SCREEN_WIDTH//2 - scoreImage.get_width() // 2 ,
                        SCREEN_HEIGHT//2 - scoreImage.get_height() // 2 )
missImagePosition = (SCREEN_WIDTH//2 - missImage.get_width() // 2 ,
                        SCREEN_HEIGHT//2 - missImage.get_height() // 2 + 50 )

# Modified Images
optsImageMod = fillImageColor(optsImage, (219,244,162, 100))
sliderBackgroundImage = sliderBackgroundImage.subsurface(3, 3, sliderBackgroundImage.get_width()-3, sliderBackgroundImage.get_height()-3)

# menuBackgroundImage = menuBackgroundImage.subsurface(25, 25, menuBackgroundImage.get_width()-45, menuBackgroundImage.get_height()-30)

menuBackgroundImagePause = pygame.transform.scale(menuBackgroundImage, (menuBackgroundImage.get_width()*5, menuBackgroundImage.get_width()*4))
menuBackgroundImageOpt = pygame.transform.scale(menuBackgroundImage, (menuBackgroundImage.get_width()*5, menuBackgroundImage.get_width()*3))
menuBackgroundImageComplete = pygame.transform.scale(menuBackgroundImage, (menuBackgroundImage.get_width()*5, menuBackgroundImage.get_height()*4))

# Game buttons
## '''Start Menu Buttons'''
startButton = Button(startImage, padding=(0,-BUTTON_FONT_SIZE*0), background=buttonBackgroundImage)
optionsButton = Button(optionsImage, padding=(0,-BUTTON_FONT_SIZE*2.5), background=buttonBackgroundImage)
quitButton = Button(quitImage, padding=(0,-BUTTON_FONT_SIZE*5), background=buttonBackgroundImage)

homeButtonPause = Button(homeImage, padding=(-150,-75))
optsButtonPause = Button(optsImageMod, padding=(-50,-75), background=squareButtonImage)
repeatButtonPause = Button(repeatImage, padding=(50,-75))
resumeButtonPause = Button(resumeImage, padding=(150,-75))

homeButtonComplete = Button(homeImage, padding=(-50,-140))
repeatButtonComplete = Button(repeatImage, padding=(50,-140))

backButton = Button(backImage, padding=(160,60))

# Sliders
soundSlider = Slider(
    position=(SCREEN_WIDTH // 2 - 15, SCREEN_HEIGHT//2),
    size = (120,30),
    initValue = 0.5,
    minValue = 0,
    maxValue = 101,
    containerBackground = sliderBackgroundImage,
    padding = (14,10)
)

timeSlider = Slider(
    position=(SCREEN_WIDTH // 2 - 15, SCREEN_HEIGHT//2 + 50),
    size = (120,30),
    initValue = 0.4,
    minValue = 10,
    maxValue = 61,
    containerBackground = sliderBackgroundImage,
    padding = (14,10)
)

modeSlider = Slider(
    position=(SCREEN_WIDTH // 2 - 15, SCREEN_HEIGHT//2 + 100),
    size = (120,30),
    initValue = 0.5,
    minValue = 1,
    maxValue = 4,
    containerBackground = sliderBackgroundImage,
    padding = (14,10)
)

# Game instances
'''Start Menu'''
startMenu = Menu([startButton, optionsButton, quitButton])

'''Pause Menu'''
pauseMenu = Menu(
    [resumeButtonPause, repeatButtonPause, optsButtonPause, homeButtonPause],
    images = [pauseImage],
    imagesPosition = [pauseImagePosition],
    menuBackground = menuBackgroundImagePause,
    size = (400,250))

'''Opts Menu'''
optionsMenu = Menu(
    [backButton],
    sliders = [soundSlider, timeSlider, modeSlider],
    images = [soundImage, timeTextImage, modeTextImage],
    imagesPosition = [soundImagePosition, timeTextImagePosition, modeTextImagePosition],
    menuBackground = menuBackgroundImageOpt,
    size = (300,250)
)

# '''Complete Menu'''
completeMenu = Menu(
    [repeatButtonComplete, homeButtonComplete],
    images = [completeImage, scoreImage, missImage],
    imagesPosition = [completeImagePosition, scoreImagePosition, missImagePosition],
    menuBackground = menuBackgroundImageComplete,
)

'''Moving Sprites'''
zombieMoving = load_frames_from_sprite_sheet('static/image/zombie/Zombie.png', size=(32,32), rowIndex=0, numberOfCol=8, scale=3)
zombieDie = load_frames_from_sprite_sheet('static/image/zombie/Zombie.png', size=(32,32), rowIndex=5, numberOfCol=8, scale=3)
zombieBeingSmashed = load_frames_from_sprite_sheet('static/image/zombie/Zombie.png', size=(32,32), rowIndex=3, numberOfCol=13, scale=3)
zombieSpawn = zombieDie[::-1]

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

# sounds
pygame.mixer.music.load(backgroundSoundPath)
pygame.mixer.music.set_volume(backgroundSoundVolume)
pygame.mixer.music.play(-1)

sound = SoundManager()


zombie_imgs = zombieSpawn + zombieMoving + zombieDie
death_imgs = zombieBeingSmashed

holes_pos = [(120,550), (380, 550), (630, 550), (170, 470), (380, 470), (590, 470)]
zombies_manager = ZombieManager(
        zombie_imgs,
        death_imgs,
        spawn_interval=2,
        hole_positions=holes_pos,
        despawn_interval=3,
        loopFrames=(len(zombieSpawn), len(zombieSpawn) + len(zombieMoving)))

'''GAME STATES'''
previosState = None
gameState = GameState.IS_START
startMenu.setIsDisplay(True)

# Game loop
while gameState:
    mouse = 0
    mousePosition = pygame.mouse.get_pos()

    for event in pygame.event.get():

        # If pressed any buttons
        if gameState == GameState.IS_PLAY:
            if event.type == pygame.KEYDOWN:

                # If pressed PAUSE_KEY
                if event.key == PAUSE_KEY:
                    pauseMenu.setIsDisplay(True)
                    pygame.mouse.set_visible(True)
                    previosState = gameState
                    gameState = GameState.IS_PAUSE

        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            mouse = 1


        # If quit
        if event.type == pygame.QUIT:
            previosState = gameState
            gameState = GameState.IS_EXIT


    # Handle Options Menu
    if gameState ==  GameState.OPEN_OPTS:
        optValue = optionsMenu.draw(screen, mousePosition, mouse, backgroundColor = (10,220,10), border = 0, sliderFont = sliderFont)

        if optValue["buttons"][0]:
            if previosState == GameState.IS_PAUSE:
                optionsMenu.setIsDisplay(False)
                previosState = gameState
                gameState =  GameState.IS_PAUSE

            if previosState == GameState.IS_START:
                optionsMenu.setIsDisplay(False)
                startMenu.setIsDisplay(True)
                previosState = gameState
                gameState =  GameState.IS_START

        pygame.mixer.music.set_volume(optValue["sliders"][0]/100)

        if playTimer.time != optValue["sliders"][1]:
            playTimer.removeAndSetOtherTime(optValue["sliders"][1])
            score.reset_miss()
            score.reset_score()
            zombies_manager.reset()

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
            previosState = gameState
            gameState =  GameState.IS_PLAY

            pygame.mouse.set_visible(False)

        if startMenuButtonValues[1]:
            startMenu.setIsDisplay(False)
            optionsMenu.setIsDisplay(True)
            previosState = gameState
            gameState =  GameState.OPEN_OPTS

            pygame.mouse.set_visible(True)

        if startMenuButtonValues[2]:
            previosState = gameState
            gameState = GameState.IS_EXIT

    elif gameState ==  GameState.IS_PLAY:

        screen.blit(background_image, (0, 0))

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

        zombies_manager.manage_spawn()
        zombies_manager.update_zombies(mousePosition, mouse, sound, score, speed = 1)
        zombies_manager.draw_zombies(screen)


        cursor.update(mousePosition, mouse, sound, score,speed = 1)
        cursor.draw(screen)

        playTimer.runTimer()

        if playTimer.getFlag():
            completeMenu.setIsDisplay(True)
            scoreImage = pygame.font.Font(BUTTON_FONT,size = 25).render('SCORE: ' + str(score.score), True, (0,0,0))
            missImage = pygame.font.Font(BUTTON_FONT,size = 25).render('MISS: ' + str(score.miss), True, (0,0,0))
            completeMenu.setImage(scoreImage, 1)
            completeMenu.setImage(missImage, 2)

            playTimer.resetTimer()
            score.reset_miss()
            score.reset_score()
            zombies_manager.reset()

            previosState = gameState
            gameState = GameState.IS_COMPLETE

            pygame.mouse.set_visible(True)

    elif gameState == GameState.IS_PAUSE:

        pauseMenuButtonValues = pauseMenu.draw(screen, mousePosition, mouse, backgroundColor = (255,255,255), border = 0)['buttons']

        # print(pauseMenuButtonValues)
        # if resume is pressed
        if pauseMenuButtonValues[0]:
            pauseMenu.setIsDisplay(False)
            previosState = gameState
            gameState =  GameState.IS_PLAY
            pygame.mouse.set_visible(False)

        # if replay
        if pauseMenuButtonValues[1]:
            pauseMenu.setIsDisplay(False)
            playTimer.resetTimer()
            score.reset_miss()
            score.reset_score()
            zombies_manager.reset()
            previosState = gameState
            gameState =  GameState.IS_PLAY
            pygame.mouse.set_visible(False)

        if pauseMenuButtonValues[2]:
            optionsMenu.setIsDisplay(True)
            previosState = gameState
            gameState =  GameState.OPEN_OPTS
            pygame.mouse.set_visible(True)

        if pauseMenuButtonValues[3]:
            pauseMenu.setIsDisplay(False)
            startMenu.setIsDisplay(True)
            playTimer.resetTimer()
            score.reset_miss()
            score.reset_score()
            zombies_manager.reset()
            previosState = gameState
            gameState =  GameState.IS_START
            pygame.mouse.set_visible(True)

    elif gameState == GameState.IS_COMPLETE:

        completeMenuButtonValues = completeMenu.draw(screen, mousePosition, mouse)['buttons']

        # if replay
        if completeMenuButtonValues[0]:
            completeMenu.setIsDisplay(False)
            previosState = gameState
            gameState =  GameState.IS_PLAY
            pygame.mouse.set_visible(False)


        if completeMenuButtonValues[1]:
            completeMenu.setIsDisplay(False)
            previosState = gameState
            startMenu.setIsDisplay(True)
            gameState =  GameState.IS_START
            pygame.mouse.set_visible(True)

        zombies_manager.reset()
        playTimer.resetTimer()
        score.reset_score()
        score.reset_miss()


    pygame.display.update()
    clock.tick(FPS)


# Quit PyGame
pygame.mixer.music.stop()
pygame.quit()