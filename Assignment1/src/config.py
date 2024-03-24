import pygame

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 650

WINDOW_TITLE = "ASSIGNMENT 1"
WINDOW_BACKGROUND = (0,30,0,155)

logo = [
  "█     █░ ▄▄▄      ▒███████▒ ",
  "▓█░ █ ░█░▒████▄    ▒ ▒ ▒ ▄▀░",
  "▒█░ █ ░█ ▒██  ▀█▄  ░ ▒ ▄▀▒░ ",
  "░█░ █ ░█ ░██▄▄▄▄██   ▄▀▒   ░",
  "░░██▒██▓  ▓█   ▓██▒▒███████▒",
  "░ ▓░▒ ▒   ▒▒   ▓▒█░░▒▒ ▓░▒░▒",
  "  ▒ ░ ░    ▒   ▒▒ ░░░▒ ▒ ░ ▒",
  "  ░   ░    ░   ▒   ░ ░ ░ ░ ░",
  "    ░          ░  ░  ░ ░    ",
  "                   ░        "
]

# Sounds
backgroundSoundPath = 'static/sound/swing.mp3'
backgroundSoundVolume = 0.3

# Set text font
INTRO_FONT = 'static/font/JetBrainsMonoNerdFontMono-Regular.ttf'
INTRO_FONT_SIZE = 20

BUTTON_FONT = 'static/font/BigBlueTermPlusNerdFont-Regular.ttf'
BUTTON_FONT_SIZE = 40
BUTTON_TEXT_COLOR = (219,243,162)

SLIDER_FONT = 'static/font/OpenDyslexicAltNerdFont-Bold.otf'
SLIDER_COLOR = (255,255,255)
SLIDER_FONT_SIZE = 20

TEXT_FONT = 'static/font/JetBrainsMonoNerdFontMono-Regular.ttf'
TEXT_COLOR = (255,255,255)
TEXT_FONT_SIZE = 25

# PLAY TIME IN TICK
FPS = 24
PLAY_TIME = 31

# Key binding
PAUSE_KEY = pygame.K_SPACE

# SOUND

SOUND_HIT = "static/sound/punch.mp3"
SOUND_DEAD  ="static/sound/dead.mp3"
SOUND_MISS  ="static/sound/miss.wav"

