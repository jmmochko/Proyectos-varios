T = int(input())
for t in range(T):
    s = input().split(":")
    s[0] = int(s[0])
    if(s[0]==12):
        s[1] += " PM"
    elif s[0]==0:
        s[0] = 12
        s[1] += " AM"
    elif(s[0]>12):
        s[0]-=12
        s[1] += " PM"
    else:
        s[1] += " AM"
    s[0] = str(s[0])
    if(len(s[0])==1):
        s[0] = '0' + s[0]
    print(s[0] + ":" + s[1])