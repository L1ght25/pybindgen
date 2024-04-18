import sys
import os


if __name__ == "__main__":
    path = sys.argv[1]
    if not os.path.exists(path):
        os.makedirs(path)

    with open(os.path.join(path, "yamaker_mock.dep"), 'w') as fp:
        pass
