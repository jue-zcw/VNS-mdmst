import math
import os
from os import path
import numpy as np
import matplotlib.pyplot as plt

if __name__=="__main__":
    prob_name = "crd103"
    file_name = path.dirname(__file__) + "\MDMST_" + prob_name + ".txt"
    points = np.loadtxt(file_name, delimiter="\t")
    print(points.shape)
    node_num = (int)(points[0][0])
    print(node_num)
    total_node_num = (int)(points[1][0])
    print(total_node_num)
    node_pos = points[2:total_node_num+2][:]
    x = []
    y = []
    for node in node_pos:
        x.append(node[1])
        y.append(node[2])
    plt.scatter(x[0:node_num], y[0:node_num], marker='o',edgecolors='g')
    plt.scatter(x[node_num:total_node_num], y[node_num:total_node_num], marker='o',edgecolors='r')
    for index in range(total_node_num+2, points.shape[0]-1):
        plt.plot([points[index][0],points[index][2]], [points[index][1],points[index][3]], color='b')
    plt.xlabel(prob_name + ", length=" + str(points[points.shape[0]-1][0]))
    os.remove(prob_name+".txt")
    os.remove(file_name)
    plt.show()
        
