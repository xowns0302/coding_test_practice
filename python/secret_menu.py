#파이썬에서는 문자열 통째로 비교하는 걸 허용함
m,n,k =map(int, input().split())
M = input().split()
N = input().split()

secret = False
for i in range(n-m+1):
    if(M == N[i: i+m]):
        secret = True
        break

if secret == True:
    print('secret')
else:
    print('normal')

