import numpy as np

from sklearn.svm import SVC

def main():
  test_0()

def test_0():
  X = np.array([[-1, -1], [-2, -1], [1, 1], [2, 1]])
  y = np.array([1, 1, 2, 2])
  clf = SVC()
  clf.fit(X, y)
  SVC(C=1.0, cache_size=200, class_weight=None, coef0=0.0,
      decision_function_shape='ovr', degree=3, gamma='auto', kernel='rbf',
      max_iter=-1, probability=False, random_state=None, shrinking=True,
      tol=0.001, verbose=False)
  print(clf.predict([[-0.8, -1]]))

if __name__ == '__main__':
  main()