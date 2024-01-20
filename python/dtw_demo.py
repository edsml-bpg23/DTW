
import numpy as np
import logging

from matplotlib import pyplot as plt

from utils.utils import init_logging

init_logging()

logger = logging.getLogger(__name__)


def build_distance_matrix(x: np.ndarray, y: np.ndarray) -> np.ndarray:
    m, n = x.shape[0], y.shape[0]
    distance_matrix = np.zeros((m, n))
    for i in range(m):
        for j in range(n):
            distance_matrix[i, j] = abs(x[i] - y[j])

    return distance_matrix


def dynamic_time_warping(signal_a: np.ndarray, signal_b: np.ndarray) -> tuple[list[tuple[int, int]], np.ndarray]:
    """
    Dynamic-programming function to calculate the alignment between two 1 dimensional signals.
    Based on this code: https://github.com/kamperh/lecture_dtw_notebook/blob/main/dtw.ipynb
    """

    distance_matrix = build_distance_matrix(signal_a, signal_b)

    # initialise cost matrix
    m, n = distance_matrix.shape
    cost_matrix = np.zeros((m + 1, n + 1))
    cost_matrix[1:, 0] = np.inf
    cost_matrix[0, 1:] = np.inf

    print(cost_matrix)

    # populate the cost matrix while tracking the traceback matrix
    traceback_matrix = np.zeros((m, n))
    for i in range(1, m+1):
        for j in range(1, n+1):
            penalty = [
                cost_matrix[i-1, j-1],  # match (0)
                cost_matrix[i-1, j],  # insert (1)
                cost_matrix[i, j-1],  # delete (2)
            ]
            p_idx = np.argmin(penalty)
            cost_matrix[i, j] = distance_matrix[i-1, j-1] + penalty[p_idx]
            traceback_matrix[i-1, j-1] = p_idx

    # traceback to find the minimum cost path through the distance matrix
    i, j = m - 1, n - 1
    path = [(i, j)]  # coordinates of the minimum cost path
    while i > 0 or j > 0:
        match traceback_matrix[i, j]:
            case 0:
                i -= 1
                j -= 1
            case 1:
                i -= 1
            case 2:
                j -= 1
        path.append((i, j))

    cost_matrix = cost_matrix[1:, 1:]  # strip the infinity buffer from the cost matrix

    # return the reverse path (as it's recorded backwards) and the cost matrix
    return path[::-1], cost_matrix



if __name__ == '__main__':
    x = np.array([0, 0, 1, 1, 0, 0, -1, 0, 0, 0, 0])
    y = np.array([0, 0, 0, 0, 1, 1, 0, 0, 0, -1, -0.5, 0, 0])

    path, cost_matrix = dynamic_time_warping(x, y)

    fig, axes = plt.subplots(1, 2, figsize=(20, 10))
    axes[0].set_title(f"Aligment cost = {cost_matrix[-1, -1]}")
    for x_i, y_j in path:
        axes[0].plot([x_i, y_j], [x[x_i] + 1.5, y[y_j] - 1.5], c="C7")
    axes[0].plot(np.arange(x.shape[0]), x + 1.5, "-o", c="C3")
    axes[0].plot(np.arange(y.shape[0]), y - 1.5, "-o", c="C0")
    axes[0].axis("off")

    axes[1].set_title("Cost matrix with path")
    axes[1].imshow(cost_matrix, cmap=plt.cm.binary, interpolation="nearest", origin="lower")
    x_path, y_path = zip(*path)
    axes[1].plot(y_path, x_path)
    # plt.xlabel("$j$")
    # plt.ylabel("$i$");

    plt.show()









