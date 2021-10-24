from reportlab.lib import colors
from reportlab.pdfgen import canvas
from reportlab.lib.pagesizes import letter, A4
from typing import Tuple
from reportlab.lib.units import inch

lyrics = [
    'well she hit Net Solutions',
    'and she registered her own .com site now',
    'and filled it up with yahoo profile pics',
    'she snarfed in one night now',
    'and she made 50 million when Huge Hefner',
    'bought up the rights now',
    'and she\'ll have fun fun fun',
    'til her Daddy takes the keyboard away',
]

def bezier2(canvas):
    from reportlab.lib.colors import yellow, green, red, black
    from reportlab.lib.units import inch
    # make a sequence of control points
    xd,yd = 5.5*inch/2, 3*inch/2
    xc,yc = xd,yd
    dxdy = [(0,0.33), (0.33,0.33), (0.75,1), (0.875,0.875),
            (0.875,0.875), (1,0.75), (0.33,0.33), (0.33,0)]

    pointlist = []

    for xoffset in (1,-1):
        yoffset = xoffset
        for (dx,dy) in dxdy:
            px = xc + xd*xoffset*dx
            py = yc + yd*yoffset*dy
            pointlist.append((px,py))
        yoffset = -xoffset
        for (dy,dx) in dxdy:
            px = xc + xd*xoffset*dx
            py = yc + yd*yoffset*dy
            pointlist.append((px,py))

    # draw tangent lines and curves
    canvas.setLineWidth(inch*0.1)

    while pointlist:
        [(x1,y1),(x2,y2),(x3,y3),(x4,y4)] = pointlist[:4]
        del pointlist[:4]

        canvas.setLineWidth(inch*0.1)
        canvas.setStrokeColor(green)
        canvas.line(x1,y1,x2,y2)
        canvas.setStrokeColor(red)
        canvas.line(x3,y3,x4,y4)
        # finally draw the curve
        canvas.setStrokeColor(black)
        canvas.bezier(x1,y1, x2,y2, x3,y3, x4,y4)

def bezier(canvas):
    from reportlab.lib.colors import yellow, green, red, black
    i = inch
    d = i/4

    # define the bezier curve control points
    x1,y1, x2,y2, x3,y3, x4,y4 = d,1.5*i, 1.5*i,d, 3*i,d, 5.5*i-d,3*i-d

    # draw a figure enclosing the control points
    canvas.setFillColor(yellow)
    p = canvas.beginPath()
    p.moveTo(x1,y1)
    for (x,y) in [(x2,y2), (x3,y3), (x4,y4)]:
        p.lineTo(x,y)
    canvas.drawPath(p, fill=1, stroke=0)

    # draw the tangent lines
    canvas.setLineWidth(inch*0.1)
    canvas.setStrokeColor(green)
    canvas.line(x1,y1,x2,y2)
    canvas.setStrokeColor(red)
    canvas.line(x3,y3,x4,y4)

    # finally draw the curve
    canvas.setStrokeColor(black)
    canvas.bezier(x1,y1, x2,y2, x3,y3, x4,y4)

def pencil(canvas, text="No.2"):
    from reportlab.lib.colors import yellow, red, black,white
    from reportlab.lib.units import inch
    u = inch/10.0
    canvas.setStrokeColor(black)
    canvas.setLineWidth(4)
    # draw erasor
    canvas.setFillColor(red)
    canvas.circle(30*u, 5*u, 5*u, stroke=1, fill=1)
    # draw all else but the tip (mainly rectangles with different fills)
    canvas.setFillColor(yellow)
    canvas.rect(10*u,0,20*u,10*u, stroke=1, fill=1)
    canvas.setFillColor(black)
    canvas.rect(23*u,0,8*u,10*u,fill=1)
    canvas.roundRect(14*u, 3.5*u, 8*u, 3*u, 1.5*u, stroke=1, fill=1)
    canvas.setFillColor(white)
    canvas.rect(25*u,u,1.2*u,8*u, fill=1,stroke=0)
    canvas.rect(27.5*u,u,1.2*u,8*u, fill=1, stroke=0)
    canvas.setFont("Times-Roman", 3*u)
    canvas.drawCentredString(18*u, 4*u, text)

    # now draw the tip
    penciltip(canvas,debug=0)

    # draw broken lines across the body.
    canvas.setDash([10,5,16,10],0)
    canvas.line(11*u,2.5*u,22*u,2.5*u)
    canvas.line(22*u,7.5*u,12*u,7.5*u)

def penciltip(c:canvas.Canvas, debug:int=1):
    from reportlab.lib.colors import tan, black, green
    u = inch/10.0
    c.setLineWidth(4)
    if debug:
        c.scale(2.8, 2.8)
        c.setLineWidth(1)
    c.setStrokeColor(black)
    c.setFillColor(tan)
    p = c.beginPath()
    p.moveTo(10*u, 0)
    p.lineTo(0, 5*u)
    p.lineTo(10*u, 10*u)
    p.curveTo(11.5*u, 10*u, 11.5*u, 7.5*u, 10*u, 7.5*u)
    p.curveTo(12*u,7.5*u, 11*u,2.5*u, 9.7*u,2.5*u)
    p.curveTo(10.5*u,2.5*u, 11*u,0, 10*u,0)
    c.drawPath(p, stroke=1, fill=1)
    c.setFillColor(black)
    p = c.beginPath()
    p.moveTo(0,5*u)
    p.lineTo(4*u,3*u)
    p.lineTo(5*u,4.5*u)
    p.lineTo(3*u,6.5*u)
    c.drawPath(p, stroke=1, fill=1)
    if debug:
        c.setStrokeColor(green) # put in a frame of reference
        c.grid([0,5*u,10*u,15*u], [0,5*u,10*u])

def joins(c: canvas.Canvas):
    c.setLineWidth(5)
    star(c, "Default: mitered join", "0: pointed", xcenter=1*inch)
    c.setLineJoin(1)
    star(c, "Round join", "1: rounded")
    c.setLineJoin(2)
    star(c, "Bevelled join", "2: square", xcenter=4.5*inch)

def star(c: canvas.Canvas, title:str="Title Here", aka:str="Comment here",
        xcenter:float=None, ycenter:float=None, nvertices:int=5):
    from math import pi
    radius=inch/3.0
    if xcenter is None:
        xcenter=2.75*inch
    if ycenter is None:
        ycenter = 1.5*inch

    c.drawCentredString(xcenter, ycenter+1.3*radius, title)
    c.drawCentredString(xcenter, ycenter-1.4*radius, aka)
    p = c.beginPath()
    p.moveTo(xcenter, ycenter+radius)
    from math import pi, cos, sin
    angle = (2*pi)*2/5.0
    startangle = pi/2.0

    for vertex in range(nvertices-1):
        nextanle = angle*(vertex+1)+startangle
        x = xcenter + radius*cos(nextanle)
        y = ycenter + radius*sin(nextanle)
        p.lineTo(x, y)

    if nvertices == 5:
        p.close()
    c.drawPath(p)

def charspace(c: canvas.Canvas):
    textobject = c.beginText()
    textobject.setTextOrigin(3, 2.5*inch)
    textobject.setFont('Helvetica-Oblique', 10)
    charspace = 0
    for line in lyrics:
        textobject.setCharSpace(charspace)
        textobject.textLine('%s: %s'%(charspace, line))
        charspace = charspace+0.5
    textobject.setFillGray(0.4)
    textobject.textLines('''
    With many apologies to the Beach Boys
    and anyone else who finds this objectionable
    ''')
    c.drawText(textobject)

def cursormoves2(c: canvas.Canvas):
    textobject = c.beginText()
    textobject.setTextOrigin(inch, 2.5*inch)
    textobject.setFont('Helvetica-Oblique', 14)
    for line in lyrics:
        textobject.textLine(line)
    textobject.setFillGray(0.4)
    textobject.textLines('''
    With many apologies to the Beach Boys
    and anyone else who finds this objectionable
    ''')
    c.drawText(textobject)


def cursormoves1(c: canvas.Canvas):
    textobject = c.beginText()
    textobject.setTextOrigin(2, 2.5*inch)
    textobject.setFont('Helvetica-Oblique', 14)
    for line in lyrics:
        textobject.textOut(line)
        textobject.moveCursor(14, 14)
    textobject.setFillColorRGB(0.4, 0, 1)
    textobject.textLines('''
    With many apologies to the Beach Boys
    and anyone else who finds this objectionable
    ''')
    c.drawText(textobject)

def fonts(c: canvas.Canvas):
    text = 'Now is the time for all good men to...'
    x = 1.8*inch
    y = 2.7*inch
    for font in c.getAvailableFonts():
        c.setFont(font, 10)
        c.drawString(x, y, text)
        c.setFont('Helvetica', 10)
        c.drawRightString(x-10, y, font+':')
        y = y-13

def textsize(c: canvas.Canvas):
    from reportlab.lib.colors import magenta, red
    c.setFont('Times-Roman', 20)
    c.setFillColor(red)
    c.drawCentredString(2.75*inch, 2.5*inch, 'Font size examples')
    c.setFillColor(magenta)
    size = 7
    y = 2.3*inch
    x = 1.3*inch
    for line in lyrics:
        c.setFont('Helvetica', size)
        c.drawRightString(x, y, "%s points: " % size)
        c.drawString(x, y, line)
        y = y-size*1.2
        size = size+1.5

def spumoni2(c: canvas.Canvas):
    from reportlab.lib.colors import pink, green, brown, white, black
    spumoni(c)
    p = c.beginPath()
    xcenter = 2.75*inch
    radius = 0.45*inch
    p.moveTo(xcenter-radius, 1.5*inch)
    p.lineTo(xcenter+radius, 1.5*inch)
    p.lineTo(xcenter, 0)
    c.setFillColor(brown)
    c.setStrokeColor(black)
    c.drawPath(p, fill=1)
    y = 1.5*inch
    for color in (pink, green, brown):
        c.setFillColor(color)
        c.circle(xcenter, y, radius, fill=1)
        y = y+radius

def spumoni(c: canvas.Canvas):
    from reportlab.lib.colors import pink, green, brown, white
    x = 0
    dx = 0.4 * inch
    for i in range(4):
        for color in (pink, green, brown):
            c.setFillColor(color)
            c.rect(x, 0, dx, 3*inch, stroke=0, fill=1)
            x = x + dx
    c.setFillColor(white)
    c.setStrokeColor(white)
    c.setFont('Helvetica-Bold', 85)
    c.drawCentredString(2.75*inch, 1.3*inch, 'SPUMONI')

def colorsCMYK(canvas: canvas.Canvas):
    from reportlab.lib.colors import CMYKColor, PCMYKColor
    black = CMYKColor(0,0,0,1)
    cyan = PCMYKColor(100,0,0,0)
    y=x=0
    dy=inch*3/4.0
    dx=inch*5.5/5
    w=h=dy/2
    rdx=(dx-w)/2
    rdy=h/5.0
    texty=h+2*rdy
    canvas.setFont('Helvetica', 10)
    y=y+dy
    x=0

    for cmyk in [(1,0,0,0), (0,1,0,0), (0,0,1,0), (0,0,0,1), (0,0,0,0)]:
        c,m,y1,k = cmyk
        canvas.setFillColorCMYK(c,m,y1,k)
        canvas.rect(x+rdx, y+rdy, w, h, fill=1)
        canvas.setFillColor(black)
        canvas.drawCentredString(x+dx/2, y+texty, "c%s m%s y%s k%s"%cmyk)
        x = x+dx

def alpha(c: canvas.Canvas):
    from reportlab.graphics.shapes import Rect
    from reportlab.lib.colors import Color, black, blue, red
    red50transparent = Color(100, 0, 0, alpha=0.5)
    c.setFillColor(black)
    c.setFont('Helvetica', 10)
    c.drawString(25, 180, 'solid')
    c.setFillColor(blue)
    c.rect(25, 25, 100, 100, fill=True, stroke=False)

    c.setFillColor(red)
    c.rect(100, 75, 100, 100, fill=True, stroke=False)

    c.setFillColor(black)
    c.drawString(255, 180, 'transparent')
    c.setFillColor(blue)
    c.rect(255, 25, 100, 100, fill=True, stroke=False)
    c.setFillColor(red50transparent)
    c.rect(300, 75, 100, 100, fill=True, stroke=False)

def colorsRGB(c: canvas.Canvas):
    from reportlab.lib import colors

    black = colors.black
    y = x = 0
    dy = inch * 3/4.0
    dx = inch * 5.5/5
    w = h = dy/2
    rdx = (dx - w)/2
    rdy = h/5.0
    texty = h+2*rdy
    c.setFont('Helvetica', 10)

    cnt = 0
    for [namedcolor, name] in (
        [colors.lavenderblush, 'lavenderblush'],
        [colors.lawngreen, 'lawngreen'],
        [colors.lemonchiffon, 'lemonchiffon'],
        [colors.lightblue, 'lightblue'],
        [colors.lightcoral, 'lightcoral'],
        [colors.aliceblue, 'aliceblue'],
        [colors.antiquewhite, 'antiquewhite'],
        [colors.aqua, 'aqua'],
        [colors.aquamarine, 'aquamarine'],
        [colors.azure, 'azure'],
        [colors.beige, 'beige'],
        [colors.bisque, 'bisque'],
        [colors.black, 'black'],
        [colors.blanchedalmond, 'blanchedalmond'],
        [colors.blue, 'blue'],
        [colors.blueviolet, 'blueviolet'],
        [colors.brown, 'brown'],
        [colors.burlywood, 'burlywood'],
        [colors.cadetblue, 'cadetblue'],
        [colors.chocolate, 'chocolate'],
        [colors.coral, 'coral'],
        [colors.cornflower, 'cornflower'],
        [colors.cornflowerblue, 'cornflowerblue'],
        [colors.cornsilk, 'cornsilk'],
        [colors.crimson, 'crimson'],
        [colors.cyan, 'cyan'],
        [colors.darkblue, 'darkblue'],
        [colors.darkcyan, 'darkcyan'],
        [colors.darkgoldenrod, 'darkgoldenrod'],
        [colors.darkgray, 'darkgray'],
        [colors.darkgreen, 'darkgreen'],
        [colors.darkgrey, 'darkgrey'],
        [colors.darkkhaki, 'darkkhaki'],
        [colors.darkmagenta, 'darkmagenta'],
        [colors.darkolivegreen, 'darkolivegreen'],
        [colors.darkorange, 'darkorange']):

        c.setFillColor(namedcolor)
        c.rect(x+rdx, y+rdy, w, h, fill=1)
        c.setFillColor(black)
        c.drawCentredString(x+dx/2, y+texty, name)
        x = x+dx

        cnt += 1
        if cnt == 5:
            y = y+dy
            x = 0
            cnt = 0
    y = y+dy
    x = 0

    for rgb in [(1,0,0), (0,1,0), (0,0,1), (0.5,0.3,0.1), (0.4,0.5,0.3)]:
        r,g,b = rgb
        c.setFillColorRGB(r, g, b)
        c.rect(x+rdx, y+rdy, w, h, fill=1)
        c.setFillColor(black)
        c.drawCentredString(x+dx/2, y+texty, "r%s g%s b%s"%rgb)
        x = x+dx
    y = y+dy
    x = 0

    for gray in (0.0, 0.25, 0.5, 0.75, 1.0):
        c.setFillGray(gray)
        c.rect(x+rdx, y+rdy, w, h, fill=1)
        c.setFillColor(black)
        c.drawCentredString(x+dx/2, y+texty, "gray: %s"%gray)
        x = x+dx

def variousshapes(canvas):
    from reportlab.lib.units import inch
    inch = int(inch)
    canvas.setStrokeGray(0.5)
    canvas.grid(range(0,int(11*inch/2),int(inch/2)), range(0,int(7*inch/2),int(inch/2)))
    canvas.setLineWidth(4)
    canvas.setStrokeColorRGB(0, 0.2, 0.7)
    canvas.setFillColorRGB(1, 0.6, 0.8)

    p = canvas.beginPath()
    p.rect(0.5*inch, 0.5*inch, 0.5*inch, 2*inch)
    p.circle(2.75*inch, 1.5*inch, 0.3*inch)
    p.ellipse(3.5*inch, 0.5*inch, 1.2*inch, 2*inch)
    canvas.drawPath(p, fill=1, stroke=1)

c = canvas.Canvas('colors.pdf', pagesize=A4)
c.translate(2*inch, 1*inch)
colorsRGB(c)
c.showPage()
alpha(c)
c.showPage()
colorsCMYK(c)
c.showPage()
spumoni(c)
c.translate(0, 4*inch)
spumoni2(c)
c.showPage()
c.translate(0.5*inch, 0)
textsize(c)
c.showPage()
fonts(c)
c.showPage()
cursormoves2(c)

c.showPage()
cursormoves1(c)

c.showPage()
charspace(c)
c.showPage()
star(c)
c.showPage()
joins(c)
c.showPage()
penciltip(c)
c.showPage()
c.translate(0.3*inch, 0.3*inch)
pencil(c)
c.showPage()
bezier(c)
c.showPage()
bezier2(c)
c.showPage()
c.translate(0.3*inch, 0.3*inch)
variousshapes(c)
c.save()