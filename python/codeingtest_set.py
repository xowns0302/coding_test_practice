#코딩테스트 세트
"""
적정세트수 구하는문제
전체 가능 세트수는 0 ~ 2*10^12
이걸 이분탐색으로 찾기
절반나누고 절반 값으로 테스트 해보고 가능하면 절반부터 끝까지 다시 탐색
test는 절반값으로 s배열만들어서 si는 각 난이도별 문제수
si > testset이면 di를 다음 난이도로 넘겨주고
si + di >= testset이면 남는 문제수만큼 다음 난이도로 넘겨주고
si + di < testset이면 불가능한 세트수니까 절반 나눠서다시 탐색
근데 s[n-1]이 testset보다 크거나 같으면 가능한 세트수니까 절반부터 끝까지 다시 탐색
아니면 절반 나누어서 다시 탐색
"""

def test(testSets):
    s = [0]*n
    s[0] = c[0]
    for i in range(n-1):
        if s[i] > testSets:
            s[i+1] = c[i+1] +d[i]
        elif s[i] +d[i] >= testSets:
            s[i+1] = c[i+1] + (s[i] + d[i] - testSets)
        else:
            return False
    if s[n-1] >= testSets:
        return True
    else:
        return False

def bSearch(start, end):
    if start == end:
        return start
    mid = (start+end+1)//2 #여기 주의
    if test(mid):
        return bSearch(mid, end)
    else:
        return bSearch(start,mid-1)
    
n, t =map(int, input().split())
for i in range(t):
    c = [0]*n
    d = [0]*n
    temp = list(map(int, input().split()))
    for i in range(n-1):
        c[i] = temp[2*i]
        d[i] = temp[2*i+1]
    c[n-1]= temp[2*(n-1)]
    print(bSearch(0, 2*10**12))
#    print(c)
#    print(d)