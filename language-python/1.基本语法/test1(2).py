def string():
    count_cap = 0
    count_small = 0
    count_num = 0
    count_other = 0
    s = input('Please input the string:')
    for i in range(len(s)):
        if s[i] >= 'a' and s[i] <= 'z':
            count_small += 1
        elif s[i] >= 'A' and s[i] <= 'Z':
            count_cap += 1
        elif s[i] >= '0' and s[i] <= '9':
            count_num += 1
        else:
            count_other += 1
    tup = (count_cap, count_small, count_num, count_other)
    return tup


print(string())
