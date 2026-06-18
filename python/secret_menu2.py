#비밀 메뉴2
#dp?
#만약 두 배열을 돌면서 같은 문자가 나오면 우리는 각 두 문자열의 인덱스를 +1 해서
#최대 길이를 찾아야함 근데 각각 +1하는거를 좌표로 생각함
#같은 문자열을 만나면 현재 좌표에서 -1 -1 했을때는 같았었나?를 생각하는거임
#그래서 -1 -1 때의 연속 문자열을 계속 더해가다가 최대 길이를 찾는 방식
#dp를 이렇게 풀었던거 같은데 아님 말고

n,m,k = map(int, input().split())
first = input().split()
second = input().split()

result = [[0]*m for _ in range(n)]
max=0

for i in range(n):
    for j in range(m):
        if first[i] == second[j]:
            if i ==0 or j ==0:
                result[i][j] = 1
            else:
                result[i][j] = result[i-1][j-1] + 1
            if max < result[i][j]:
                max = result [i][j]

print(max)