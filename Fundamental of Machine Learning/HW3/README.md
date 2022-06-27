# Collaborative filtering

## 목표
- 주어진 dataset을 이용하여 Collaborative filtering을 통한 rating 예측하기
-----------
## Preprocessing
- user_id, businees_id 에 따른 rating 관리.
- 빈도가 많은 순으로 user 100개, business 50개 추출.
- rating matrix 구현(size : 100*50)
- 각 행, 열이 비어 있지 않도록 train, test split

## Matrix Factorization
```python
# matrix factorization 정의
import numpy as np

class MF():

    def __init__(self, R, K, alpha, beta, iterations):
        """
        Perform matrix factorization to predict empty
        entries in a matrix.

        Arguments
        - R (ndarray)   : user-item rating matrix
        - K (int)       : number of latent dimensions
        - alpha (float) : learning rate
        - beta (float)  : regularization parameter
        """

        self.R = R
        self.num_users, self.num_items = R.shape
        self.K = K
        self.alpha = alpha
        self.beta = beta
        self.iterations = iterations

    def train(self):
        # Initialize user and item latent feature matrice
        self.P = np.random.normal(scale=1./self.K, size=(self.num_users, self.K))
        self.Q = np.random.normal(scale=1./self.K, size=(self.num_items, self.K))

        # Initialize the biases
        self.b_u = np.zeros(self.num_users)
        self.b_i = np.zeros(self.num_items)
        self.b = np.mean(self.R[np.where(self.R != 0 )]) # R = [1 2 0] -> self.b = mean([1 2]) = 1.5   np.mean(R) = 3/3 = 1

        # Create a list of training samples
        self.samples = [
            (i, j, self.R[i, j])
            for i in range(self.num_users)
            for j in range(self.num_items)
            if self.R[i, j] > 0
        ] # R = [[1,0], [0,2]]  --> self.samples = [(0,0,1), (1,1,2)]

        # Perform stochastic gradient descent for number of iterations
        training_process = []
        for i in range(self.iterations):
            np.random.shuffle(self.samples)
            self.sgd()
            mse = self.mse() # R(i,j) -> P(i,:) * Q.T(j,:) + b + b_i(i) + b_u(j)
            training_process.append((i, mse))
            if (i+1) % 10 == 0:
                print("Iteration: %d ; error = %.4f" % (i+1, mse))

        return training_process

    def mse(self):
        """
        A function to compute the total mean square error
        """
        xs, ys = self.R.nonzero()
        predicted = self.full_matrix()
        error = 0
        for x, y in zip(xs, ys):
            error += pow(self.R[x, y] - predicted[x, y], 2)
        return np.sqrt(error)

    def sgd(self):
        """
        Perform stochastic graident descent
        """
        for i, j, r in self.samples:
            # Computer prediction and error
            prediction = self.get_rating(i, j)
            e = (r - prediction)

            # Update biases
            self.b_u[i] += self.alpha * (e - self.beta * self.b_u[i])
            self.b_i[j] += self.alpha * (e - self.beta * self.b_i[j])

            # Update user and item latent feature matrices
            self.P[i, :] += self.alpha * (e * self.Q[j, :] - self.beta * self.P[i,:])
            self.Q[j, :] += self.alpha * (e * self.P[i, :] - self.beta * self.Q[j,:])

    def get_rating(self, i, j):
        """
        Get the predicted rating of user i and item j
        """
        prediction = self.b + self.b_u[i] + self.b_i[j] + self.P[i, :].dot(self.Q[j, :].T)
        return prediction

    def full_matrix(self):
        """
        Computer the full matrix using the resultant biases, P and Q
        """
        return self.b + self.b_u[:,np.newaxis] + self.b_i[np.newaxis:,] + self.P.dot(self.Q.T)
```

## MSE
- test case와의 loss를 확인 (Mean Square Error 사용)
```python
def mse(matrix,predicted):
        """
        A function to compute the total mean square error
        """
        xs, ys = matrix.nonzero()
        
        error = 0
        for x, y in zip(xs, ys):
            error += pow(matrix[x, y] - predicted[x, y], 2)
        return np.sqrt(error)
```
## Train
- Rank의 변화에 따른 학습 변화를 알아보기 위함.
```python
def train_by_rank(rank):
  mf = MF(rating, K=rank, alpha=0.1, beta=0.05, iterations=50)
  train_loss = mf.train()
  test_loss = mse(test_matrix,mf.full_matrix())
  plot(train_loss,rank)
  test_loss = mse(test_matrix,mf.full_matrix())
  print("Test loss : ",test_loss)
```

## Result

| Rank       | 5    | 10   | 15   | 20  |
|------------|------|------|------|-----|
| Train loss | 12.7680 | 6.8082 |5.2934 |4.9590|
| Test loss       | 11.2683 | 9.4799 |8.9925 |8.9385 |
