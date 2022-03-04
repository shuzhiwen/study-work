def Isprime(x):
    for i in range(2, x):
        if x % i == 0:
            return 0
    return 1


def separate(x):
    List_low = []
    List_up = []
    for i in range(2, x):
        count = 0
        if Isprime(i) == 0:
            continue
        else:
            while x % i == 0:
                count += 1
                x = x / i
        if count:
            List_low.append(i)
            List_up.append(count)
    return [List_low, List_up]


print(separate(int(input('Please input the number: '))))
