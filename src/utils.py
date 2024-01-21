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
def drawTextOnScreen(surface, text, font, textColor, x, y):

    img = font.render(text, True, textColor)

    surface.blit(img, (x,y))

def convertGameTime2Minute(time):
    minute = (time // 1000) // 60
    second = (time // 1000) - 60 * minute
    return "{:02d}:{:02d}".format(minute, second)

