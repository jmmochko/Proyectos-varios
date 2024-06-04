res = 0
for i in range(1,10000):
    for j in range(1,10000):
        if(3/i + 3/j == 1):
            res += 1
            print(i)
            print(j)
print(res)