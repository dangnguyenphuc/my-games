import math
import random

import pygame

from scripts.particle import Particle
from scripts.spark import Spark
from scripts.abilities import Slash, Boom, Ability

class PhysicsEntity:
    def __init__(self, game, e_type, pos, size):
        self.game = game
        self.type = e_type
        self.pos = list(pos)
        self.size = size
        self.velocity = [0, 0]
        self.collisions = {'up': False, 'down': False, 'right': False, 'left': False}

        self.action = ''
        self.anim_offset = (-3, -3)
        self.flip = False
        self.set_action('idle')

        self.last_movement = [0, 0]

    def rect(self):
        return pygame.Rect(self.pos[0], self.pos[1], self.size[0], self.size[1])

    def set_action(self, action):
        if action != self.action:
            self.action = action
            self.animation = self.game.assets[self.type + '/' + self.action].copy()

    def update(self, tilemap, movement=(0, 0)):
        self.collisions = {'up': False, 'down': False, 'right': False, 'left': False}

        frame_movement = (movement[0] + self.velocity[0], movement[1] + self.velocity[1])

        self.pos[0] += frame_movement[0]
        entity_rect = self.rect()
        for rect in tilemap.physics_rects_around(self.pos):
            if entity_rect.colliderect(rect):
                if frame_movement[0] > 0:
                    entity_rect.right = rect.left
                    self.collisions['right'] = True
                if frame_movement[0] < 0:
                    entity_rect.left = rect.right
                    self.collisions['left'] = True
                self.pos[0] = entity_rect.x

        self.pos[1] += frame_movement[1]
        entity_rect = self.rect()
        for rect in tilemap.physics_rects_around(self.pos):
            if entity_rect.colliderect(rect):
                if frame_movement[1] > 0:
                    entity_rect.bottom = rect.top
                    self.collisions['down'] = True
                if frame_movement[1] < 0:
                    entity_rect.top = rect.bottom
                    self.collisions['up'] = True
                self.pos[1] = entity_rect.y

        if movement[0] > 0:
            self.flip = False
        if movement[0] < 0:
            self.flip = True

        self.last_movement = movement

        self.velocity[1] = min(5, self.velocity[1] + 0.1)

        if self.collisions['down'] or self.collisions['up']:
            self.velocity[1] = 0

        self.animation.update()

    def render(self, surf, offset=(0, 0)):
        surf.blit(pygame.transform.flip(self.animation.img(), self.flip, False), (self.pos[0] - offset[0] + self.anim_offset[0], self.pos[1] - offset[1] + self.anim_offset[1]))

class Enemy(PhysicsEntity):
    def __init__(self, game, pos, size):
        super().__init__(game, 'enemy', pos, size)

        self.walking = 0
        self.isDead = False

    def update(self, tilemap, movement=(0, 0)):
        if not self.game.player.isTimeStop():
            if self.walking:
                if tilemap.solid_check((self.rect().centerx + (-7 if self.flip else 7), self.pos[1] + 23)):
                    if (self.collisions['right'] or self.collisions['left']):
                        self.flip = not self.flip
                    else:
                        movement = (movement[0] - 0.5 if self.flip else 0.5, movement[1])
                else:
                    self.flip = not self.flip
                self.walking = max(0, self.walking - 1)
                if not self.walking:
                    dis = (self.game.player.pos[0] - self.pos[0], self.game.player.pos[1] - self.pos[1])
                    if (abs(dis[1]) < 16):
                        if (self.flip and dis[0] < 0):
                            self.game.sfx['shoot'].play()
                            self.game.enemyProjectiles.append([[self.rect().centerx - 7, self.rect().centery], -1.5, 0])
                            for i in range(4):
                                self.game.sparks.append(Spark(self.game, self.game.enemyProjectiles[-1][0], random.random() - 0.5 + math.pi, 2 + random.random()))
                        if (not self.flip and dis[0] > 0):
                            self.game.sfx['shoot'].play()
                            self.game.enemyProjectiles.append([[self.rect().centerx + 7, self.rect().centery], 1.5, 0])
                            for i in range(4):
                                self.game.sparks.append(Spark(self.game, self.game.enemyProjectiles[-1][0], random.random() - 0.5, 2 + random.random()))
            elif random.random() < 0.01:
                self.walking = random.randint(30, 120)

            super().update(tilemap, movement=movement)

            if movement[0] != 0:
                self.set_action('run')
            else:
                self.set_action('idle')

        self.isKilled()

    def isKilled(self):
        if abs(self.game.player.dashing) >= 50:
            if self.rect().colliderect(self.game.player.rect()):
                self.game.screenshake = max(16, self.game.screenshake)
                self.game.sfx['hit'].play()
                for i in range(30):
                    angle = random.random() * math.pi * 2
                    speed = random.random() * 5
                    if self.game.player.isTimeStop():
                        self.game.sparks.append(Spark(self.game, self.rect().center, angle, 0.1 + random.random()))
                    else:
                        self.game.sparks.append(Spark(self.game, self.rect().center, angle, 2 + random.random()))
                    self.game.particles.append(Particle(self.game, 'particle', self.rect().center, velocity=[math.cos(angle + math.pi) * speed * 0.5, math.sin(angle + math.pi) * speed * 0.5], frame=random.randint(0, 7)))
                self.game.sparks.append(Spark(self.game, self.rect().center, 0, 5 + random.random()))
                self.game.sparks.append(Spark(self.game, self.rect().center, math.pi, 5 + random.random()))
                self.isDead = True

        # [[x, y], direction, timer]
        for projectile in self.game.playerProjectiles.copy():
            if self.rect().collidepoint(projectile[0]):
                self.game.playerProjectiles.remove(projectile)
                self.game.sfx['hit'].play()
                for i in range(30):
                    angle = random.random() * math.pi * 2
                    speed = random.random() * 5
                    if self.game.player.isTimeStop():
                        self.game.sparks.append(Spark(self.game, self.rect().center, angle, 0.1 + random.random()))
                    else:
                        self.game.sparks.append(Spark(self.game, self.rect().center, angle, 2 + random.random()))
                    self.game.particles.append(Particle(self.game, 'particle', self.rect().center, velocity=[math.cos(angle + math.pi) * speed * 0.5, math.sin(angle + math.pi) * speed * 0.5], frame=random.randint(0, 7)))
                self.isDead = True

        for slash in self.game.slashes.copy():
            if self.rect().colliderect(slash.rect()):
                self.game.slashes.remove(slash)
                self.game.sfx['hit'].play()
                for i in range(30):
                    angle = random.random() * math.pi * 2
                    speed = random.random() * 5
                    if self.game.player.isTimeStop():
                        self.game.sparks.append(Spark(self.game, self.rect().center, angle, 0.1 + random.random()))
                    else:
                        self.game.sparks.append(Spark(self.game, self.rect().center, angle, 2 + random.random()))
                    self.game.particles.append(Particle(self.game, 'particle', self.rect().center, velocity=[math.cos(angle + math.pi) * speed * 0.5, math.sin(angle + math.pi) * speed * 0.5], frame=random.randint(0, 7)))
                self.isDead = True



    def render(self, surf, offset=(0, 0)):
        super().render(surf, offset=offset)

        if self.flip:
            surf.blit(pygame.transform.flip(self.game.assets['gun'], True, False), (self.rect().centerx - 4 - self.game.assets['gun'].get_width() - offset[0], self.rect().centery - offset[1]))
        else:
            surf.blit(self.game.assets['gun'], (self.rect().centerx + 4 - offset[0], self.rect().centery - offset[1]))

class Player(PhysicsEntity):
    def __init__(self, game, pos, size, weapon = 0):
        super().__init__(game, 'player', pos, size)
        self.air_time = 0
        self.jumps = 1
        self.wall_slide = False
        self.dashing = 0
        self.bullets = 3
        self.weapon = 0

        # teleport ability
        self.teleport = {
            "enable": True,
            "previousPosition": None,
            "telePhase": 0
        }

    def setWeapon(self, weapon):
        self.weapon = weapon

    def update(self, tilemap, movement=(0, 0)):
        super().update(tilemap, movement=movement)
        self.air_time += 1

        if self.air_time > 120:
            if not self.game.dead:
                self.game.screenshake = max(16, self.game.screenshake)

            if self.isTimeStop():
                self.air_time = 0
                self.tele()
            else:
                self.game.dead += 1

        if self.collisions['down']:
            self.air_time = 0
            self.jumps = 1

        self.wall_slide = False
        if (self.collisions['right'] or self.collisions['left']) and self.air_time > 4:
            self.wall_slide = True
            self.velocity[1] = min(self.velocity[1], 0.5)
            if self.collisions['right']:
                self.flip = False
            else:
                self.flip = True
            self.set_action('wall_slide')

        if not self.wall_slide:
            if self.air_time > 4:
                self.set_action('jump')
            elif movement[0] != 0:
                self.set_action('run')
            else:
                self.set_action('idle')

        if abs(self.dashing) in {60, 50}:
            for i in range(20):
                angle = random.random() * math.pi * 2
                speed = random.random() * 0.5 + 0.5
                pvelocity = [math.cos(angle) * speed, math.sin(angle) * speed]
                self.game.particles.append(Particle(self.game, 'particle', self.rect().center, velocity=pvelocity, frame=random.randint(0, 7)))
        if self.dashing > 0:
            self.dashing = max(0, self.dashing - 1)
        if self.dashing < 0:
            self.dashing = min(0, self.dashing + 1)
        if abs(self.dashing) > 50:
            self.velocity[0] = abs(self.dashing) / self.dashing * 8
            if abs(self.dashing) == 51:
                self.velocity[0] *= 0.1
            pvelocity = [abs(self.dashing) / self.dashing * random.random() * 3, 0]
            self.game.particles.append(Particle(self.game, 'particle', self.rect().center, velocity=pvelocity, frame=random.randint(0, 7)))

        if self.velocity[0] > 0:
            self.velocity[0] = max(self.velocity[0] - 0.1, 0)
        else:
            self.velocity[0] = min(self.velocity[0] + 0.1, 0)

    def render(self, surf, offset=(0, 0)):
        if abs(self.dashing) <= 50:
            super().render(surf, offset=offset)

        if self.isTimeStop():
            surf.blit(self.game.assets["star"], (self.teleport["previousPosition"][0] - offset[0], self.teleport["previousPosition"][1] - offset[1]))


    def shoot(self):
        if self.bullets > 0:
            self.bullets -= 1
            self.game.sfx['shoot'].play()
            if self.flip:
                self.game.playerProjectiles.append([[self.rect().centerx - 7, self.rect().centery], -1.5, 0])
            else:
                self.game.playerProjectiles.append([[self.rect().centerx + 7, self.rect().centery], 1.5, 0])

    def tele(self):

        if self.teleport["enable"]:
            if self.teleport["telePhase"] == 0:
                # TODO: SET TELE POINT
                self.game.sfx['timeResume'].play()
                self.teleport["previousPosition"] = self.pos.copy()
                self.teleport["telePhase"] += 1
                self.game.stopTimer.reset()
                self.game.alphaTimer.reset()
                self.game.alpha = 100
            else:
                # TODO: TELE TO TELE POINT
                self.game.sfx["timeStop"].play()
                self.pos = self.teleport["previousPosition"]
                self.resetTele()

    def resetTele(self):
        self.teleport["previousPosition"] = None
        self.teleport["telePhase"] = 0
        self.game.stopTimer.reset()
        self.game.alphaTimer.reset()
        self.game.alpha = 0

    def jump(self):
        if self.wall_slide:
            if self.flip and self.last_movement[0] < 0:
                self.velocity[0] = 3.5
                self.velocity[1] = -2.5
                self.air_time = 5
                self.jumps = max(0, self.jumps - 1)
                return True
            elif not self.flip and self.last_movement[0] > 0:
                self.velocity[0] = -3.5
                self.velocity[1] = -2.5
                self.air_time = 5
                self.jumps = max(0, self.jumps - 1)
                return True

        elif self.jumps:
            self.velocity[1] = -3
            self.jumps -= 1
            self.air_time = 5
            return True

    def dash(self):
        if not self.dashing:
            self.game.sfx['dash'].play()
            if self.flip:
                self.dashing = -60
            else:
                self.dashing = 60

    def defaultSkill(self):
        if self.weapon:
            self.shoot()
        else: self.cut()

    def cut(self):
        if len(self.game.slashes) <= 1:
            self.game.sfx['shoot'].play()
            if self.flip:
                self.game.slashes.append(Slash(self.game, pos=[
                    self.rect().centerx - 7,
                    self.rect().y
                ]))
            else:
                self.game.slashes.append(Slash(self.game, pos=[
                    self.rect().centerx + 7,
                    self.rect().y
                ]))

    def boom(self):
        # self.game.sfx['shoot'].play()
        self.game.booms.append(Boom(self.game, pos=[
            self.rect().centerx,
            self.rect().y
        ]))

    def isTimeStop(self):
        return self.teleport["enable"] and self.teleport["telePhase"] == 1

