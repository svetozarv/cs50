def lines(a, b):
    """Return lines in both a and b"""

    lines_in_common = set()

    file1 = a.split("\n")
    file2 = b.split("\n")
    for line1 in file1:
        for line2 in file2:
            if line1 == line2:
                lines_in_common.add(line1)

    return list(lines_in_common)


def sentences(a, b):
    """Return sentences in both a and b"""

    from nltk.tokenize import sent_tokenize

    sentences = set()

    file1_sentences_list = sent_tokenize(a)
    file2_sentences_list = sent_tokenize(b)

    for sentence1 in file1_sentences_list:
        for sentence2 in file2_sentences_list:
            if sentence1 == sentence2:
                sentences.add(sentence1)

    return list(sentences)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    file1 = a
    file2 = b

    start_index = 0
    end_index = n

    file1_substr_set = set()
    file2_substr_set = set()

    while end_index <= len(file1):
        file1_substr_set.add(file1[start_index:end_index])
        start_index += 1
        end_index += 1

    start_index = 0
    end_index = n

    while end_index <= len(file2):
        file2_substr_set.add(file2[start_index:end_index])
        start_index += 1
        end_index += 1

    return list(file1_substr_set.intersection(file2_substr_set))


