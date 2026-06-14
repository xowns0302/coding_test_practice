#로드밸런서 트래픽 예측
#로드밸런서가 많은 워커노드들한테 트래픽을 분산시키는 문제
#라운드 로빈 방식으로 스케줄링
#topological sort를 쓰라는데
"""
토폴로지컬 소트
먼저 모든 자식들이 기본적으로 받는 요청 수가 있음
그거 받고 남은것들 차례대로 더 넣어주면 됨
로드 밸런서에 들어온 요청 수 // 자식 수 == 자식들이 기본적으로 받는 요청 수
로드밸런서에 들어온 요청 수 mod 자식 수 == 추가적으로 뿌려줘야하는 요청 수
"""

n, k = map(int, input().split())
child = [[] for _ in range(n+1)]
r = [0]*(n+1)
result = [0]*(n+1)
result[1] = k

for i in range(1, n+1):
    data = list(map(int, input().split()))
    r[i] = data[0]
    if r[i]>0:
        child[i] = data[1:]

for i in range(1, n + 1):
    if r[i] > 0:
        base = result[i] // r[i]
        remain = result[i] % r[i]

        for j in range(r[i]):
            nxt = child[i][j]
            result[nxt] += base

            if j < remain:
                result[nxt] += 1
                  
print(*result[1:])