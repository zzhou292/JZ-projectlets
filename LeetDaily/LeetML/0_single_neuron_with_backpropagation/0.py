import numpy as np


def train_neuron(features: np.ndarray, labels: np.ndarray, initial_weights: np.ndarray, initial_bias: float, learning_rate: float, epochs: int) -> (np.ndarray, float, list[float]):  	
    weights = np.array(initial_weights)
    bias = initial_bias
    mse_values = []


    for epoch in range(epochs):
        pred = np.dot(features,weights) + bias
        pred = sigmoid(pred)
        mse = np.mean((pred - labels) ** 2)
        mse_values.append(mse)

        errors = pred - labels
        weight_gradients = (2/len(labels)) * np.dot(features.T, errors * pred * (1 - pred))
        bias_gradient = (2/len(labels)) * np.sum(errors * pred * (1 - pred))
        weights = weights - learning_rate * weight_gradients
        bias = bias - learning_rate * bias_gradient
    return weights, bias, mse_values


features = np.array([[1.0, 2.0], [2.0, 1.0], [-1.0, -2.0]])
labels = np.array([1, 0, 0])
initial_weights = np.array([0.1, -0.2])
initial_bias = 0.0
learning_rate = 0.1
epochs = 2

train_neuron(features, labels, initial_weights, initial_bias, learning_rate, epochs)