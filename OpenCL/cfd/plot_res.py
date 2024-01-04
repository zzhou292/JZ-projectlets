import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Load your CSV data
df = pd.read_csv('velocity_data_50.csv')  # Replace with your file name

# Assuming x and y are indices, create a 2D array for the velocity magnitude squared
velocity_matrix = np.zeros((100, 400))  # 100 for y, 400 for x

for _, row in df.iterrows():
    x, y = int(row['x']), int(row['y'])
    velocity_matrix[y, x] = row[' velocity_magnitude_squared']  # assuming this is the correct column name

# Create a heatmap
plt.figure(figsize=(12, 6))
plt.imshow(velocity_matrix, origin='lower', cmap='viridis')
plt.colorbar(label='Velocity Magnitude Squared')
plt.xlabel('X Axis')
plt.ylabel('Y Axis')
plt.title('Heatmap of Velocity Magnitude Squared')
plt.show()
