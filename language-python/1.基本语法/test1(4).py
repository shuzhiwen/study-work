def Isprime(x):
    for i in range(2, x):
        if x % i == 0:
            return 0
    return 1


def separate(x):
    List_low = []
    List_up = []
    for i in range(2, x + 1):
        count = 0
        if x == 0 or Isprime(i) == 0:
            continue
        else:
            while x % i == 0:
                count += 1
                x = x / i
        if count:
            List_low.append(i)
            List_up.append(count)
    return [List_low, List_up]


for i in range(1000, 2001):
    List = separate(i)
    print('%8d:' % i, end='')
    for j in range(len(List[0])):
        print('%d' % List[0][j], end='')
        if j != len(List[0]) - 1:
            print(',', end='')
        else:
            print(';', end='')
    for j in range(len(List[1])):
        print('%d' % List[1][j], end='')
        if j != len(List[1]) - 1:
            print(',', end='')
        else:
            print()
