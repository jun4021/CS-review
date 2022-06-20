import re
import math

def main():
    """
    Program entry point
    You can change inputs for checking the correctness of your implementation
    """
    training1_sentence = "John likes to watch movies. Mary likes movies too."
    training2_sentence = "In the machine learning, " \
                         "naive Bayes classifiers are a family of simple probabilistic classifiers."
    testing_sentence = "John also likes to watch football games."

    alpha = 0.1
    prob1 = 0.5
    prob2 = 0.5

    print(naive_bayes(training1_sentence, training2_sentence, testing_sentence, alpha, prob1, prob2))


def naive_bayes(training1_sentence, training2_sentence, testing_sentence, alpha, prob1, prob2):
    """
    Implement Naive Bayes Algorithm
    Descriptions are written in the pdf file.
    Return normalized log probability
    of p(the author of the training1_sentence|testing_sentence)
    and p(the author of the training2_sentence|testing_sentence)
    :param training1_sentence:
    :param training2_sentence:
    :param testing_sentence:
    :param alpha:
    :param prob1:
    :param prob2:
    :return:
    """
    bow_train1 = create_BOW(training1_sentence)
    bow_train2 = create_BOW(training2_sentence)
    bow_test = create_BOW(testing_sentence)

    
    classify1 = calculate_doc_prob(bow_train1,bow_test,alpha)
    classify2 = calculate_doc_prob(bow_train2,bow_test,alpha)

    return normalize_log_prob(classify1, classify2)


def calculate_doc_prob(bow_train, bow_test, alpha):
    """
    Implement log likelihood function
    Descriptions are written in the pdf file.
    :param bow_train:
    :param bow_test:
    :param alpha:
    :return:
    """
    total_dict = list(bow_train[0].keys())
    for token in bow_test[0].keys():
        if token not in total_dict:
            total_dict.append(token)

 
    # N is the number of all word tokens
    N = 0
    for i in bow_train[1]:
        N += i 
    d = len(total_dict)
    
    # log probability of the test sentence given the author
    logprob = 0
    test_index = 0
    for token in bow_test[0].keys():
        train_index = bow_train[0].get(token)
        if (train_index !=None):
            xi = bow_train[1][train_index]
        else:
            xi = 0
        logprob += bow_test[1][test_index] *math.log((xi+alpha)/(N + alpha * d))
        test_index += 1
    return logprob


def normalize_log_prob(prob1, prob2):
    """
    Normalize two probabilities
    ** Do not modify this function **
    :param prob1:
    :param prob2:
    :return: normalized two probabilities
    """
    maxprob = max(prob1, prob2)

    prob1 -= maxprob
    prob2 -= maxprob
    prob1 = math.exp(prob1)
    prob2 = math.exp(prob2)

    normalize_constant = 1.0 / float(prob1 + prob2)
    prob1 *= normalize_constant
    prob2 *= normalize_constant

    return prob1, prob2


def replace_non_alphabetic_chars_to_space(sentence):
    """
    Remove non-alphabetic characters
    ** Do not modify this function **
    :param sentence: input sentences
    :return: cleaned sentences
    """
    return re.sub(r'[^a-z]+', ' ', sentence)


def create_BOW(sentences):
    """
    Create Bag of Words from sentences
    ** Do not modify this function **
    :param sentences: input sentences
    :return: (bow dictionary, bow format of the sentences)
    """
    bow_dict = {}
    bow = []

    sentences = sentences.lower()
    sentences = replace_non_alphabetic_chars_to_space(sentences)
    words = sentences.split()
    for token in words:
        if len(token) < 1:
            continue
        if token not in bow_dict:
            new_idx = len(bow)
            bow.append(0)
            bow_dict[token] = new_idx
        bow[bow_dict[token]] += 1

    return bow_dict, bow


if __name__ == "__main__":
    main()
