"""Small load-test driver for PulseGrid development benchmarks."""
import random

PLAYERS = 1000
TICKS = 100
players = [(random.random()*200, random.random()*200) for _ in range(PLAYERS)]
for _ in range(TICKS):
    players = [(x + random.uniform(-.5,.5), y + random.uniform(-.5,.5)) for x,y in players]
print(f"simulated {PLAYERS} players for {TICKS} ticks")
