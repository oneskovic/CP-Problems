import numpy as np
from collections import namedtuple
Point = namedtuple('Point', 'x y')

file = open('inputs/5.txt','r')
lines = file.readlines()
point_start = []
point_end = []

mat = np.zeros((1000,1000),dtype=int)
for l in lines:
    numbers = []
    for t in l.split('->'):
        numbers.append(int(t.split(',')[0]))
        numbers.append(int(t.split(',')[1]))
    point1 = Point(numbers[0],numbers[1])
    point2 = Point(numbers[2],numbers[3])

    point_start.append(point1)
    point_end.append(point2)

for i in range(len(point_start)):
    dx = 0
    dy = 0
    if point_start[i].x == point_end[i].x:
        dx = 0
        dy = np.sign(point_end[i].y - point_start[i].y)
    elif point_start[i].y == point_end[i].y:
        dy = 0
        dx = np.sign(point_end[i].x - point_start[i].x)
    else:
        dx = np.sign(point_end[i].x - point_start[i].x)
        dy = np.sign(point_end[i].y - point_start[i].y)
    current_point = point_start[i]
    while current_point != point_end[i]:
        mat[current_point.x][current_point.y] += 1
        current_point = Point(current_point.x + dx, current_point.y + dy)   
    mat[current_point.x][current_point.y] += 1

condition = (mat >= 2)
print(condition.sum())