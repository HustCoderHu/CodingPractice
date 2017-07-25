import matplotlib
matplotlib.use('Agg')

import matplotlib.pyplot as plt
import numpy as np


x = np.linspace(0, 2 * np.pi, 50)
plt.plot(x, np.sin(x))
plt.savefig("first.png")
# plt.show()
