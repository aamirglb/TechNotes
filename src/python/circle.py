import turtle as t

t.bgcolor('black')
t.color('cyan')
# t.speed(11)
# t.shape('turtle')
t.hideturtle()
t.showturtle()

def square(length):
    for i in range(4):
        t.fd(length)
        t.left(90)

def gui_example():
    t.setup(300, 200)
    t.screensize(300, 200)
    t.setworldcoordinates(0, 0, 300, 200)
    t.color('white')
    t.penup()
    t.setpos(100, 0)
    t.pendown()
    t.setpos(100, 100)
    t.penup()
    t.setpos(200, 0)
    t.pendown()
    t.setpos(200, 200)
    t.onscreenclick(shapedrawer)

def shapedrawer(x, y):
    t.penup()
    t.setpos(x, y)
    t.begin_fill()
    if x < 100:
        t.color('green')
        square(10)
    elif 100 < x <= 200:
        t.color('red')
        t.circle(10)
    else:
        t.color('blue')
        square(10)
    t.end_fill()

def test2_drawfib():
    t.speed(0)
    drawfib(15, 15)

def test_drawfib():
    start_points = [[-300, 250], [-150, 250],
    [-300, 110], [-80, 110],
    [-300, -150], [50, -150]]

    n = 0
    for start_point in start_points:
        x, y = start_point
        n += 1
        t.penup()
        t.setpos(x, y)
        t.pendown()
        drawfib(n, 30)

def drawfib(n, len_ang):
    
    t.forward(2*len_ang)
    if n == 0:
        pass
    elif n == 1:
        pass
    else:
        t.left(len_ang)
        drawfib(n-1, len_ang)
        t.right(2*len_ang)
        drawfib(n-2, len_ang)
        t.left(len_ang)
    t.backward(2*len_ang)

def fill_shape():
    t.begin_fill()
    t.fd(150)
    t.seth(45)
    t.fd(150)
    t.seth(90)
    t.fd(150)
    t.color('blue')
    t.end_fill()

def draw_spiral():
    colors = ['blue', 'green', 'purple', 'cyan', 'magenta', 'violet']
    t.speed(10)
    for i in range(45):
        t.color(colors[i % 6])
        t.pendown()
        t.fd(2+i*5)
        t.left(45)
        t.width(i)
        t.penup()

def complex_circle():
    for angle in range(0, 360, 15):
        t.setheading(angle)
        t.circle(100)

def draw_circles():
    t.speed(0)
    for i in range(10):
        r = 100 - (i*10)
        t.circle(r)
        t.circle(-r)

def draw_servay():
    side1 = 200
    side2 = side1 * 0.1
    for i in range(10):
        if i % 2 == 0:
            t.fd(side1)
            t.lt(90)
            t.fd(side2)
            t.lt(90)
        else:
            t.fd(side1)
            t.rt(90)
            t.fd(side2)
            t.rt(90)

def draw_star():
    length = 200
    for i in range(5):
        t.forward(length)
        t.left(144)

def draw_square():
    count = 0
    length = 100
    while length > 0:
        t.forward(length)
        t.left(90)
        count += 1
        length -= 10
        

def draw_circle():
    # draw circle
    for i in range(360):
        t.forward(3)
        t.left(1)

if __name__ == '__main__':
    # draw_servay()
    # draw_star()
    # t.reset()
    # t.rt(90)
    # draw_circles()
    # complex_circle()
    # draw_spiral()
    # fill_shape()
    # test_drawfib()
    # test2_drawfib()
    gui_example()
    t.mainloop()
    # t.exitonclick()