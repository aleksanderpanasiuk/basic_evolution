import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


def show(number_of_generations):
    points = pd.read_csv("resources/points.csv", header=0)
    points.plot.scatter(x=0, y=1)

    parameters = pd.read_csv(
        f"resources/generations/parameters_{number_of_generations}.csv",
        header=0)

    x = np.linspace(0, 10, 100)
    legend = ["Points"]

    for i in range(3):
        par = list(parameters.loc[i])

        y = par[0] * np.sin((par[1]*x + par[2])*np.pi/180) + \
            par[3] * np.sin((par[4]*x + par[5])*np.pi/180) + \
            par[6] * np.sin((par[7]*x + par[8])*np.pi/180) + par[9]

        plt.title(f"{number_of_generations}")
        plt.plot(x, y)
        legend.append(f"Creature nr {str(i)}")

    plt.legend(legend)


if __name__ == "__main__":
    show(20)
    show(60)
    show(100)
    plt.show()
