fp_in = open('data.txt', 'r')
fp_out = open('average.txt', 'w')
lines_count = 0
while True:
    lines_count += 1
    each_line = fp_in.readline()
    if not each_line:
        break
    ll = each_line.split(',')
    ave = 0
    for i in range(3, 7):
        ave += float(ll[i])
    ave /= 5
    fp_out.writelines('%f\n' % ave)
    print('Line %d have %d characters' % (lines_count, len(each_line)))

print('The file have %d lines' % lines_count)
fp_in.close()
fp_out.close()
