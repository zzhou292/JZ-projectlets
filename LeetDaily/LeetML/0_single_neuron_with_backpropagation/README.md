Single Neuron with Backpropagation

Write a Python function that simulates a single neuron with sigmoid activation, and implements backpropagation to update the neuron's weights and bias. The function should take a list of feature vectors, associated true binary labels, initial weights, initial bias, a learning rate, and the number of epochs. The function should update the weights and bias using gradient descent based on the MSE loss, and return the updated weights, bias, and a list of MSE values for each epoch, each rounded to four decimal places.
Example:
Input:

features = [[1.0, 2.0], [2.0, 1.0], [-1.0, -2.0]], labels = [1, 0, 0], initial_weights = [0.1, -0.2], initial_bias = 0.0, learning_rate = 0.1, epochs = 2

Output:

updated_weights = [0.1036, -0.1425], updated_bias = -0.0167, mse_values = [0.3033, 0.2942]

Reasoning:

The neuron receives feature vectors and computes predictions using the sigmoid activation. Based on the predictions and true labels, the gradients of MSE loss with respect to weights and bias are computed and used to update the model parameters across epochs.