import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# Загрузка данных
data = np.loadtxt('output.txt')
x, y = data[:,0], data[:,1]

fig, ax = plt.subplots()
line, = ax.plot([], [], 'b-')

def init():
    ax.set_xlim(np.min(x)-0.1, np.max(x)+0.1)
    ax.set_ylim(np.min(y)-0.1, np.max(y)+0.1)
    line.set_data([], [])
    return line,

def update(frame):
    # Увеличиваем шаг анимации для ускорения (например, по 5000 точек за кадр)
    step = 5000
    idx = min(frame * step, len(x))
    line.set_data(x[:idx], y[:idx])
    return line,

frames = (len(x) + 4999) // 5000  # Количество кадров с учётом шага
ani = FuncAnimation(fig, update, frames=frames, init_func=init, blit=False, interval=1)
plt.show()