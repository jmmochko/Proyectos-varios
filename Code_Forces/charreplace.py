originalstr = input('original string: ')
oldchar = input('char to replace: ')
newchar = input('char to replace it with: ')
res = ""
for i in range(len(originalstr)):
    if(originalstr[i] == oldchar):
        res += newchar
    else:
        res += originalstr[i]
print(res)