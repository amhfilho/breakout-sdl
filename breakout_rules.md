# Atari Breakout (1976 Arcade) — Rules

Source: Atari arcade game manual TM-058 (4th printing), https://archive.org/stream/ArcadeGameManualBreakout/breakout_djvu.txt

## Objective

Score as many points as possible by hitting a ball with a paddle toward a wall of bricks. Each brick the ball hits disappears and the ball rebounds.

## Playfield

- Wall of **8 rows × 14 bricks** (112 bricks).
- The ball rebounds off the two side walls, the back wall (behind the bricks), the bricks and the paddle.
- The paddle moves left/right along the bottom, controlled by a rotary knob.
- One cabinet strip of color covers every two rows of bricks (the original screen was black and white).

## Serving

- Each ball is launched with the lit **serve** button.
- The ball appears about midway along the screen, at the slowest speed, in a **random direction** that always has a component toward the paddle (it may hit a side wall first).
- The operator sets **3 or 5 balls** per game.

## Volleys and ball rebound

- If the ball hits the paddle, it rebounds toward the bricks. If the paddle misses it, the ball leaves the screen and that ball is lost.
- The paddle has **four portions**. The portion hit determines which of **four rebound directions** the ball takes.
- The incoming angle does not matter, only where the ball hits the paddle. This is why the ball can return in the same left/right direction or the opposite one.
- Per Figure 3-4 of the manual, the four portions (left to right) send the ball:
  1. **Far left:** up and to the left, at a sharp (shallow) angle.
  2. **Inner left:** up and to the left, steeper.
  3. **Inner right:** up and to the right, steeper.
  4. **Far right:** up and to the right, at a sharp (shallow) angle.
- So the left half of the paddle always sends the ball left, the right half always sends it right, and the outer edges give the sharpest angles.
- The ball never travels exactly perpendicular to the paddle (or to the bricks or any boundary).
- Rebound angles become **more perpendicular as ball speed increases**.
- The four-portion rule still applies when the paddle is halved.

## Scoring

| Rows (counting from the paddle side) | Points per brick |
|---|---|
| First two rows (nearest the paddle) | 1 |
| Next two rows | 3 |
| Next two rows | 5 |
| Last two rows (farthest from the paddle) | 7 |

- One wall is worth **448 points** (28 bricks × (1 + 3 + 5 + 7)).
- Only one brick can disappear at a time: after a brick hit, the ball must touch the back wall or the paddle before another brick can be destroyed.
- Clearing the whole wall brings a **second full wall** the next time the ball hits the back wall or the paddle. No extra balls are given and no third wall appears, so the maximum score is **896 points**.
- Optional bonus: the operator can award a free credit at a preset score (100 to 800 points in 100-point steps).

## Speed changes

There are four ball speeds. Each serve starts at the slowest.

| Event | Speed result |
|---|---|
| Start of each serve | Slowest speed |
| 4th paddle hit | First speed-up |
| 12th paddle hit | Second, faster speed-up |
| Hitting a 5-point or 7-point brick | Immediately the **fastest** speed, whatever it was before |

Speed resets to the slowest at the start of every new serve.

## Breakout (tunneling through the wall)

- If the player opens a gap in the wall and sends the ball through, the ball bounces between the back wall and the high-value bricks, scoring many points without returning to the paddle.
- The ball does not return toward the paddle until it comes back out through an opening in the wall.
- While this happens, the **paddle shrinks to half its normal width** for that volley.

## Sounds

- **Bounce:** ball hits a side wall or the back wall.
- **Blip:** ball hits the paddle.
- **Tick:** one per point when a brick is hit.
- **Buzz:** a bonus credit is awarded (if enabled).

## End of game

The game ends when the player misses the last ball served and that ball leaves the screen.

## Two-player games

Players alternate serves with equal numbers of balls. Each player has their own independent brick wall, so player 2 does not benefit from a gap made by player 1.

---

*Note: Figure 3-4 of the manual shows the rebound directions but gives no numeric angle values, so none are listed here.*
