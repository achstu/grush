import sys

board_size, turns = map(int, input().split())

players = int(input())

for _ in range(players):
    row, col = map(int, input().split())

for _ in range(turns):
    agents = int(input())

    for _ in range(agents):
        row, col, object, dist, rot = input().split()

    for _ in range(agents):
        print("FIRE", flush=True)

