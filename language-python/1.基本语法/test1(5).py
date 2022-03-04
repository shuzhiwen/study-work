count = 0
s = input('Please input the string: ')
ss = list(s)

for i in range(len(s) - 1):
    if s[i] == 'a' and s[i + 1] == 'b':
        count += 1
        ss[i] = 'A'
        ss[i + 1] = 'B'

print('There are %d "ab"' % count)
print(''.join(ss))
print(' '.join(s.split('ab')))
