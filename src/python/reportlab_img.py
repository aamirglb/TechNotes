from reportlab.pdfgen import canvas
from reportlab.lib.pagesizes import A4, landscape
from reportlab.lib.styles import getSampleStyleSheet
from reportlab.platypus import Paragraph, Table, TableStyle, Image
from reportlab.lib.enums import TA_LEFT, TA_CENTER
from reportlab.lib import colors
from reportlab.lib.units import inch

a = Image("../../images/cpp/notation.png")
a.drawHeight = 1*inch
a.drawWidth = 2*inch
data=[['1','2'],['3','4'], [], [], []]
c = canvas.Canvas("Reportlabtest.pdf", pagesize=A4, bottomup=1)
table = Table(data, colWidths=200, rowHeights=50)
table.setStyle(TableStyle([
                           ('INNERGRID', (0,0), (-1,-1), 0.25, colors.black),
                           ('BOX', (0,0), (-1,-1), 0.25, colors.black),
                           ('BACKGROUND',(0,0),(-1,2),colors.lightgrey)
                           ]))
table.wrapOn(c, 200, 400)
table.drawOn(c,20,50)
c.save()