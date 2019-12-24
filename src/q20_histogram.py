import cv2
import numpy as np
import matplotlib.pyplot as plt

# Read image
img = cv2.imread("../pictures_results/q22.jpg").astype(np.float)

# Display histogram
plt.hist(img.ravel(), bins=255, rwidth=0.8, range=(0, 255))
plt.savefig("../pictures_results/q22_his.png")
plt.show()