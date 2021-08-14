import pygame
import sys

pygame.init()
bgcolor = (200, 200, 200)
surf = pygame.display.set_mode((400, 400))

circle_color = (255, 0, 0)
x, y = 200, 300
circle_rad = 25

pygame.display.set_caption("Window")

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_UP:
                y -= 10
            elif event.key == pygame.K_DOWN:
                y += 10
            elif event.key == pygame.K_RIGHT:
                x += 10
            elif event.key == pygame.K_LEFT:
                x -= 10
        
        circle_pos = (x, y)
        surf.fill(bgcolor)
        pygame.draw.circle(surf, circle_color, circle_pos, circle_rad)
        pygame.display.flip()