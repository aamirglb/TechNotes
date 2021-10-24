from reportlab.pdfgen import canvas
from reportlab.lib.pagesizes import letter
from typing import Tuple


def translate(c: canvas.Canvas, pos: Tuple[float]):
    from reportlab.lib.units import cm
    c.translate(pos[0]*cm, pos[1]*cm)
    coords(c)

def coords(c: canvas.Canvas):
    from reportlab.lib.units import inch
    from reportlab.lib.colors import pink, black, red, blue, green
    c.setStrokeColor(pink)
    c.grid([inch, 2*inch, 3*inch, 4*inch],
            [0.5*inch, inch, 1.5*inch, 2*inch, 2.5*inch])
    c.setStrokeColor(black)
    c.setFont('Times-Roman', 20)
    c.drawString(0, 0, '(0, 0) the Origin')
    c.drawString(2.5*inch, inch, '(2.5, 1) in inches')
    c.drawString(4*inch, 2.5*inch, '(4, 2.5)')
    c.setFillColor(red)
    c.rect(0, 2*inch, 0.2*inch, 0.3*inch, fill=1)
    c.setFillColor(green)
    c.circle(4.5*inch, 0.4*inch, 0.2*inch, fill=1)

c = canvas.Canvas('coords.pdf', pagesize=letter)
translate(c, (2, .3))
c.scale(.5, .5)
translate(c, (2, 20))
c.scale(2.5, 2.5)
translate(c, (2, 3.5))
c.showPage()
#c.scale(-1, -1)
translate(c, (2, 0.3))
c.scale(-1, -1)
translate(c, (4, .3))
c.save()