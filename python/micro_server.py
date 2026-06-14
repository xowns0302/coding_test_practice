#이거 어렵다 ㅠ
#클러스터는 여러대의 마이크로 서버로 구성
#1000MiB의 메모리를 가짐
#100은 예비용 실제 사용가능 메모리는 900
#서비스들이 사용하는 메모리의 총합은 900이하
#n개의 서비스가 실행 대기중
#i번째 서비스는 정확히 mi 메모리를 요구
#각 서비스는 최소 300 최대 900
#모든 서비스를 실행하기 위해 몇개의 서버가 필요한지 찾는 문제
"""""
이 문제는 case를 잘 나누는것 이 중요함
1. 300만으로 조합
2. 601이상 혼자 서버 사용
3. 301~599는 되는 애들끼리 조합
4. 300, 600조합
이렇게 4가지 케이스가 있고 이걸 잘 분해해서 처리 해야함
300의 숫자 세서 시작 인덱스설정해주고 
601이상 숫자 세서 끝 인덱스설정해주고 
시작, 끝 인덱스 늘리고 줄여가면서 풀면 됨
"""

t = int(input())

for _ in range(t):
    n = int(input())
    services = list(map(int, input().split()))
    services.sort()
    num300 = 0
    for i in range(n):
        if services[i]<=300:
            num300 +=1
    servers = 0
    start = num300
    end = n-1
    while start <= end:
        servers += 1
        if services[end]>600:#601이상은 혼자 서버 하나 써야됨
            end -= 1
        elif start != end and services[start] + services[end] <= 900:
            #301~599는 지네들 끼리 조합해서 넣음
            #근데 여기서 이제 start== end 가 같은 조합 안된 한 개가 남을 수 있음
            start += 1
            end -= 1
        elif num300>0:
            #조합 안된 한 개를 300이랑 묶어서 같이 서버 쓰기
            num300 -= 1
            end -= 1
        else:
            end -= 1
    servers += (num300+2)//3 #그런데도 300이 남았으면 300끼리 조합
    print(servers)
