'''
@funtion drawText: renders text in (x,y) coordinate.
@params:
    - surface: Surface to be drawn
    - text(String): String to be rendered.
    - font(pygame.font.Font): font to be used.
    - textColor((R,G,B)): color to be applied for text
    - x(int): horizontal coordinate.
    - y(int): vertical coordinate.
'''
import pygame

def drawTextOnScreen(surface, text, font, textColor, x, y):

    img = font.render(text, True, textColor)

    surface.blit(img, (x,y))

def convertGameTime2Minute(time):
    minute = (time // 1000) // 60
    second = (time // 1000) - 60 * minute
    return "{:02d}:{:02d}".format(minute, second)

def load_sprite_sheet(file_path, rows, cols, scale=1):
    sheet = pygame.image.load(file_path).convert_alpha()
    sheet_rect = sheet.get_rect()
    frame_width = sheet_rect.width // cols
    frame_height = sheet_rect.height // rows

    scaled_frames = []
    for row in range(rows):
        for col in range(cols):
            frame_rect = pygame.Rect(col * frame_width, row * frame_height, frame_width, frame_height)
            frame = sheet.subsurface(frame_rect)
            scaled_frame = pygame.transform.scale(frame, (int(frame_width * scale), int(frame_height * scale)))
            scaled_frames.append(scaled_frame)

    return scaled_frames

