import matplotlib
import matplotlib.pyplot as plt
import random
import numpy as np


def do_sample_uniform(min_value, max_value, n_trials):
    """
    Sampling uniformly distributed n_trials numbers between min_value and max_value
    :param min_value: minimum value of the sampled numbers
    :param max_value: maximum value of the sampled numbers
    :param n_trials: the number of sampled numbers
    :return: a list of sampled numbers
    """
    # Sample -> Integer
    result = []
    for i in range(n_trials):
        result.append(random.randrange(min_value,max_value+1))
    return result


def do_sample_gaussian(mu, sigma, n_trials):
    """
    Sampling gaussian distributed n_trials numbers whose mean is mu and standard deviation is sigma
    :param mu: mean value of the sampled numbers
    :param sigma: standard deviation value of the sampled numbers
    :param n_trials: the number of sampled numbers
    :return: a list of sampled numbers
    """
    result = np.round(np.random.normal(mu, sigma, n_trials))

    return result


def do_sample_two_gaussians(mu1, sigma1, mu2, sigma2, n_trials):
    """
    Sampling two gaussian distributed n_trials numbers
    whose mean is mu1/mu2 and standard deviation is sigma1/sigma2 respectively
    :param mu1: mean value of the first sampled numbers
    :param sigma1: standard deviation value of the first sampled numbers
    :param mu2: mean value of the second sampled numbers
    :param sigma2: standard deviation value of the second sampled numbers
    :param n_trials: the number of sampled numbers
    :return: a list of sampled numbers
    """
    result1 = np.round(np.random.normal(mu1, sigma1, n_trials))
    result2 = np.round(np.random.normal(mu2, sigma2, n_trials))

    result = np.concatenate([result1,result2])

    return result


def get_statistics(data):
    """
    Compute mean and variance of data
    :param data: a list of numbers
    :return: mean and variance of data
    """
    mean = np.mean(data)
    variance = np.var(data)

    return mean, variance


def plot_result(data, filename):
    """
    ** Do not modify the code in this function **
    """
    min_data = int(min(data))
    max_data = int(max(data))
    frequency = dict()
    for idx in range(min_data, max_data + 1):
        frequency[idx] = 0

    for element in data:
        frequency[int(element)] += 1

    bar_x, bar_y = zip(*sorted(frequency.items(), key=lambda x: x[0]))
    plt.bar(bar_x, bar_y)

    plt.xlabel("Sample", fontsize=20)
    plt.ylabel("Frequency", fontsize=20)

    plt.savefig(filename)

    plt.close()


def run_uniform():
    """
    ** Do not modify the code in this function **
    """
    print("Sampling uniform distribution")

    min_value = int(input("Min value: "))
    max_value = int(input("Max value: "))
    n_trials = int(input("# trials: "))

    return do_sample_uniform(min_value, max_value, n_trials)


def run_gaussian():
    """
    ** Do not modify the code in this function **
    """
    print("Sampling Gaussian distribution")

    mu = float(input("Mu value: "))
    sigma = float(input("Sigma value: "))
    n_trials = int(input("# trials: "))

    return do_sample_gaussian(mu, sigma, n_trials)


def run_mixture_gaussians():
    """
    ** Do not modify the code in this function **
    """
    print("Sampling Gaussian distribution")

    mu1 = float(input("Mu1 value: "))
    sigma1 = float(input("Sigma1 value: "))
    mu2 = float(input("Mu2 value: "))
    sigma2 = float(input("Sigma2 value: "))
    n_trials = int(input("# trials: "))

    return do_sample_two_gaussians(mu1, sigma1, mu2, sigma2, n_trials)


def main():
    """
    ** Do not modify the code in this function **
    """
    function_list = [run_uniform, run_gaussian, run_mixture_gaussians]
    filename_list = ["uniform.png", "gaussian.png", "mixture_gaussian.png"]

    print("Input")
    while True:
        print("Which distribution?")
        print("1: Uniform, 2: Gaussian, 3: Mixture of Gaussian")

        try:
            user_input = int(input("> ")) - 1
        except ValueError:
            continue

        if 0 <= user_input <= 2:
            result = function_list[user_input]()
            filename = filename_list[user_input]

            plot_result(result, filename)

            mean, variance = get_statistics(result)
            print("\nOutput")
            print("Mean : %.2lf" % mean)
            print("Variance : %.2lf" % variance)
            print("Open {} file to see the histogram".format(filename))

            return
        else:
            pass


if __name__ == "__main__":
    matplotlib.use('Agg')
    random.seed(12345)
    np.random.seed(12345)
    main()
