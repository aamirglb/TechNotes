class Settings:
    '''A class to store all settings for the game'''

    def __init__(self):
        self.screen_width = 1200
        self.screen_height = 800
        self.bg_color = (230, 230, 230)
        self.ship_speed = 1.5
        self.ship_limit = 3

        # bullet settings
        self.bullet_speed = 1.5
        self.bullet_width = 3
        self.bullet_height = 15
        self.bullet_color = (60, 60, 60)
        self.bullets_allowed = 10

        self.alien_speed = 0.2
        self.fleet_drop_speed = 10
        self.fleet_direction = 1

        self.speedup_scale = 1.1

        self.initalize_dynamic_settings()

    def initalize_dynamic_settings(self):
        self.ship_speed = float(1.5)
        self.bullet_speed = 3.0
        self.alien_speed = 1.0

        self.fleet_direction = 1

    def increase_speed(self):
        self.ship_speed *= self.speedup_scale
        self.bullet_speed *= self.speedup_scale
        self.alien_speed *= self.speedup_scale