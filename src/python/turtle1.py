import turtle as t

t.bgcolor('black')
t.color('cyan')

width = 200
t.forward(width)
t.left(90)
t.forward(width)
t.left(135)
c = ((width**2) + (width**2)) ** 0.5
t.forward(c)
t.exitonclick()