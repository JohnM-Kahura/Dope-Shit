import pandas as pd
import matplotlib.pyplot as plt
data = pd.read_excel('./poverty_by_characteristics_original.xlsx')
data.plot()
plt.show()