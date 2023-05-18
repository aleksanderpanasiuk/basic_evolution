import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


def position(n):
    if n == 0:
        return 0, 0
    if n == 1:
        return 0, 1
    if n == 2:
        return 1, 0
    if n == 3:
        return 1, 1


def show(n, number_of_generations):
    pos_x, pos_y = position(n-2)

    points = pd.read_csv("resources/points.csv", header=0)
    points_x = list(points["x"])
    points_y = list(points["y"])
    axis[pos_x, pos_y].plot(points_x, points_y, 'o')
    legend = ["Points"]

    parameters = pd.read_csv(
        f"resources/generations/parameters_{number_of_generations}.csv",
        header=0)

    x = np.linspace(0, 10, 100)

    no_creatures = 3
    for i in range(no_creatures):
        par = list(parameters.loc[i])

        y = par[0] * np.sin((par[1]*x + par[2])*np.pi/180) + \
            par[3] * np.sin((par[4]*x + par[5])*np.pi/180) + \
            par[6] * np.sin((par[7]*x + par[8])*np.pi/180) + par[9]

        axis[pos_x, pos_y].plot(x, y, linewidth=no_creatures-i)
        legend.append(f"Creature nr {i+1}")

    axis[pos_x, pos_y].set_title(f"Generation {number_of_generations}")
    axis[pos_x, pos_y].legend(legend)


if __name__ == "__main__":
    figure, axis = plt.subplots(2, 2)
    figure.canvas.manager.set_window_title("Basic Evolution results")

    for i in range(2, 6):
        show(i, i*20)

    plt.show()
